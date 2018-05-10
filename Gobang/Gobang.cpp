#include "Gobang.h"

#include <stdio.h>

Gobang::Gobang()
{
	// ��ʼ������
	initBoard();
	// ��ʼ��˫�˶���
	steps = new std::deque<Step>();
	overSteps = new std::deque<Step>();
}

Gobang::~Gobang()
{
}

/*
	��ʼ�����̻������������

	@author Ҷ־��
*/
void Gobang::initBoard()
{
	for (int i = 0; i < BOARDLENGTH; i++)
		for (int j = 0; j < BOARDLENGTH; j++)
			board[i][j] = ChessType::NOCHESS;
	turn = ChessType::BLACKCHESS;
}

/*
	�����̱��浽�ļ���

	@author Ҷ־��
	@para ����·��
	@throw char *
*/
void Gobang::saveBoard(char * path)
{
	FILE * outFile;

	outFile = fopen(path, "w");
	if (outFile == nullptr)
		throw "Unable to open file.";

	int size = steps->size();
	fprintf(outFile, "%d\n", size);
	auto iterator = steps->begin();
	for (int i = 0; i < size; i++)
	{
		Step tmp = *iterator;
		fprintf(outFile, "%d\t%d\n", tmp.x, tmp.y);
		iterator++;
	}
	fclose(outFile);
}

/*
	���ļ����ȡ����

	@author Ҷ־��
	@para ����·��
*/
void Gobang::loadBoard(char * path)
{
	FILE * inFile;

	inFile = fopen(path, "r");
	if (inFile == nullptr)
		throw "Unable to open file.";
	int size = 0;
	fscanf(inFile, "%d\n", &size);
	Step tmp;
	for (int i = 0; i < size; i++)
	{
		fscanf(inFile, "%d\t%d\n", &tmp.x, &tmp.y);
		steps->push_back(tmp);
	}
	turn = size % 2;
}

/*
	���ص�ǰ�ִ�

	@author Ҷ־��
	@return ChessType
*/
int Gobang::getTurn()
{
	return turn;
}

/*
	���ش�������˳���˫�˶���

	@author Ҷ־��
	@return ˫�˶���
*/
std::deque<Gobang::Step> Gobang::getSteps()
{
	return *steps;
}

/*
	���ص�����Ϸ����������λ�õ�˫�˶���

	@author Ӧ��Ң
	@return ˫�˶���
*/
std::deque<Gobang::Step> Gobang::getOverSteps()
{

	return *overSteps;
}

/*
	��һ����

	@author Ӧ��Ң
	@para step������λ��
*/
void Gobang::newStep(Step step)
{
	//�����λ���Ѿ���������
	if (board[step.x][step.y] != ChessType::NOCHESS)
		throw"Error:This loc has a chess !";

	board[step.x][step.y] = turn;

	steps->push_back(step);

	turn = (turn + 1) % 2;
}

/*
	�˻���ս

	@author Ӧ��Ң
	@return ����Step���͵�����
*/
Gobang::Step Gobang::AIWalk(int type)
{
	if (type != ChessType::BLACKCHESS || type != ChessType::WHITECHESS)
		throw "The chess type does not existing";





	return Step();
}

/*
	�ж���Ϸ�Ƿ�������н���

	@author Ӧ��Ң
	@return ChessType   NOCHESS---��ʤ��������BLACKCHESS---�����ʤ��WHITECHESS---�����ʤ
*/
int Gobang::isOverWithRestricted()
{
	// true��ʾ�н���
	return isOver(true);
}

/*
	�ж���Ϸ�Ƿ�������޽���

	@author Ӧ��Ң
	@return ChessType   NOCHESS---��ʤ��������BLACKCHESS---�����ʤ��WHITECHESS---�����ʤ
*/
int Gobang::isOverWithoutRestricted()
{
	// false��ʾ�޽���
	return isOver(false);
}

/*
	�ж���Ϸ�Ƿ����

	@author Ӧ��Ң
	@return ChessType   NOCHESS---��ʤ��������BLACKCHESS---�����ʤ��WHITECHESS---�����ʤ
*/
int Gobang::isOver(bool isRestricted)
{
	Step s;
	int i, j;										//i----�����꣬j----������

	int s1, s2, h1, h2, z1, z2, f1, f2;				//s1,s2������ֱͳ�ƣ�h1,h2����ˮƽͳ�ƣ�z1,z2�������Խ���ͳ�ƣ�f1,f2���ڸ��Խ���ͳ��
	int sk1, sk2, hk1, hk2, zk1, zk2, fk1, fk2;		//sk1,sk2������ֱ��λͳ�ƣ�hk1,hk2����ˮƽ��λͳ�ƣ�zk1,zk2�������Խ��߿�λͳ�ƣ�fk1,fk2���ڸ��Խ��߿�λͳ��
	int sign = (turn + 1) % 2;						//sign----�������

	int result[4];

	s = steps->back();
	s1 = s2 = h1 = h2 = z1 = z2 = f1 = f2 = 0;
	sk1 = sk2 = hk1 = hk2 = zk1 = zk2 = fk1 = fk2 = 0;

	/* ------------------------------------------------------------- */

	result[0] = searchNumOfChess(0, 1);		//��ֱ����
	result[1] = searchNumOfChess(1, 0);		//ˮƽ����
	result[2] = searchNumOfChess(1, 1);		//���Խ��߲���
	result[3] = searchNumOfChess(1, -1);	//���Խ��߲���


	//��ֱ����ͳ��
	for (i = s.x, j = s.y; j >= 0; j--) {
		if (board[i][j] == sign)
			s1++;
		else {
			while (board[i][j] == ChessType::NOCHESS && j >= 0) {
				sk1++;
				j--; 
			}
			break;
		}
	}
	//��ֱ����ͳ��
	for (i = s.x, j = s.y; j < BOARDLENGTH; j++) {
		if (board[i][j] == sign)
			s2++;
		else {
			while (board[i][j] == ChessType::NOCHESS && j < BOARDLENGTH) {
				sk2++;
				j++;
			}
			break;
		}
	}

	//ˮƽ����ͳ��
	for (i = s.x, j = s.y; i >= 0; i--) {
		if (board[i][j] == sign)
			h1++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i >= 0) {
				hk1++;
				i--;
			}
			break;
		}
	}
	//ˮƽ����ͳ��
	for (i = s.x, j = s.y; i < BOARDLENGTH; i++) {
		if (board[i][j] == sign)
			h2++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i < BOARDLENGTH) {
				hk2++;
				i++;
			}
			break;
		}
	}

	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == sign)
			z1++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i >= 0 && j >= 0) {
				zk1++;
				i--;
				j--;
			}
			break;
		}
	}
	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i < BOARDLENGTH && j < BOARDLENGTH; i++, j++) {
		if (board[i][j] == sign)
			z2++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i < BOARDLENGTH && j < BOARDLENGTH) {
				zk2++;
				i++;
				j++;
			}
			break;
		}
	}

	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i < BOARDLENGTH && j >= 0; i++, j--) {
		if (board[i][j] == sign)
			f1++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i < BOARDLENGTH && j >= 0) {
				fk1++;
				i++;
				j--;
			}
			break;
		}
	}
	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i >= 0 && j < BOARDLENGTH; i--, j++) {
		if (board[i][j] == sign)
			f2++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i >= 0 && j < BOARDLENGTH) {
				fk2++;
				i--;
				j++;
			}
			break;
		}
	}

	/* ------------------------------------------------------------- */

	if (!isRestricted) {
		if (s1 + s2 > 5)
			return sign;
		if (h1 + h2 > 5)
			return sign;
		if (z1 + z2 > 5)
			return sign;
		if (f1 + f2 > 5)
			return sign;
	}
	else {
		if (sign == ChessType::BLACKCHESS) {
			//��������
			if (s1 + s2 - 1 + h1 + h2 - 2 == 5 && sk1 + sk2 == 3 && hk1 + hk2 == 3) {
				return turn;
			}
			if (s1 + s2 - 1 + z1 + z2 - 2 == 5 && sk1 + sk2 == 3 && zk1 + zk2 == 3) {
				return turn;
			}
			if (s1 + s2 - 1 + f1 + f2 - 2 == 5 && sk1 + sk2 == 3 && fk1 + fk2 == 3) {
				return turn;
			}
			if (h1 + h2 - 1 + z1 + z2 - 2 == 5 && hk1 + hk2 == 3 && zk1 + zk2 == 3) {
				return turn;
			}
			if (h1 + h2 - 1 + f1 + f2 - 2 == 5 && hk1 + hk2 == 3 && fk1 + fk2 == 3) {
				return turn;
			}
			if (z1 + z2 - 1 + f1 + f2 - 2 == 5 && zk1 + zk2 == 3 && fk1 + fk2 == 3) {
				return turn;
			}

			//���Ľ���


			//��������
			if (s1 + s2 > 6)
				return turn;
			if (h1 + h2 > 6)
				return turn;
			if (z1 + z2 > 6)
				return turn;
			if (f1 + f2 > 6)
				return turn;
		}
		if (s1 + s2 > 5)
			return sign;
		if (h1 + h2 > 5)
			return sign;
		if (z1 + z2 > 5)
			return sign;
		if (f1 + f2 > 5)
			return sign;
	}


	return ChessType::NOCHESS;
}

/*
	�ж���������

	@para m---ˮƽ���ң�n---��ֱ����
	@author Ӧ��Ң
	@return 
*/
int Gobang::searchNumOfChess(int m, int n)
{
	int temp_x, temp_y;




	return 0;
}

/*
	�ж������Ƿ�Ϊ����

	@para x---�����꣬y---������
	@author Ӧ��Ң
	@return bool    true---����Ϊ������false---���Ͳ�Ϊ����
*/
bool Gobang::isLiveThree(int x, int y)
{
	return false;
}

/*
	�ж������Ƿ�Ϊ����

	@para x---�����꣬y---������
	@author Ӧ��Ң
	@return bool    true---����Ϊ���ģ�false---���Ͳ�Ϊ����
*/
bool Gobang::isLiveFour(int x, int y)
{
	return false;
}

/*
	�ж������Ƿ�Ϊ����

	@para x---�����꣬y---������
	@author Ӧ��Ң
	@return bool    true---����Ϊ���ģ�false---���Ͳ�Ϊ����
*/
bool Gobang::isPunchingFour(int x, int y)
{
	return false;
}