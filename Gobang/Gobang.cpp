#include "Gobang.h"

#include <stdio.h>

Gobang::Gobang()
{
	// ��ʼ������
	initBoard();
	// ��ʼ��˫�˶���
	steps = new std::deque<Step>();
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
	�ж���Ϸ�Ƿ����

	@author Ӧ��Ң
	@return ChessType   NOCHESS---��ʤ��������BLACKCHESS---�����ʤ��WHITECHESS---�����ʤ
*/
int Gobang::isOver()
{
	Step s;
	int i, j;                            //i----�����꣬j----������

	int s1, s2, h1, h2, z1, z2, f1, f2;  //s1,s2������ֱͳ�ƣ�h1,h2����ˮƽͳ�ƣ�z1,z2�������Խ���ͳ�ƣ�f1,f2���ڸ��Խ���ͳ��
	int sign = (turn + 1) % 2;           //sign----�������

	s = steps->back();
	s1 = s2 = h1 = h2 = z1 = z2 = f1 = f2 = 0;

	/* ------------------------------------------------------------- */

	//��ֱ����ͳ��
	for (i = s.x, j = s.y; j >= 0; j--){
		if (board[i][j] == sign)
			s1++;
		else
			break;
	}
	//��ֱ����ͳ��
	for (i = s.x, j = s.y; j < BOARDLENGTH; j++) {
		if (board[i][j] == sign)
			s2++;
		else
			break;
	}
	
	//ˮƽ����ͳ��
	for (i = s.x, j = s.y; i >= 0; i--) {
		if (board[i][j] == sign)
			h1++;
		else
			break;
	}
	//ˮƽ����ͳ��
	for (i = s.x, j = s.y; i < BOARDLENGTH; i++) {
		if (board[i][j] == sign)
			h2++;
		else
			break;
	}

	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == sign)
			z1++;
		else
			break;
	}
	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i < BOARDLENGTH && j < BOARDLENGTH; i++, j++) {
		if (board[i][j] == sign)
			z2++;
		else
			break;
	}

	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i < BOARDLENGTH && j >= 0; i++, j--) {
		if (board[i][j] == sign)
			f1++;
		else
			break;
	}
	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i >= 0 && j < BOARDLENGTH; i--, j++) {
		if (board[i][j] == sign)
			f2++;
		else
			break;
	}

	/* ------------------------------------------------------------- */

	if (s1 + s2 > 5)
		return sign;
	if (h1 + h2 > 5)
		return sign;
	if (z1 + z2 > 5)
		return sign;
	if (f1 + f2 > 5)
		return sign;
	if (sign == ChessType::BLACKCHESS) {
		//��������

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

	return ChessType::NOCHESS;
}

/*
	�ж��Ƿ���ڽ���

	@author Ӧ��Ң
	@return bool   true---���ڽ��֣�false---�����ڽ���
	*/
bool Gobang::isBanned()
{
	Step s;

	s = steps->back();


	return false;
}