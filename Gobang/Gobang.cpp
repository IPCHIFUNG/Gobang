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
	�ж���Ϸ�Ƿ����

	@author Ӧ��Ң
	@return ChessType   NOCHESS---��ʤ��������
*/
int Gobang::isOver()
{
	Step s;
	int i, j;                            //i----�����꣬j----������
	int left, right;                     //left��С�㣬right������
	int sign = (turn + 1) % 2;           //sign----�������

	s = steps->back();

	left = right = 0;
	//��ֱ����ͳ��
	for (i = s.x, j = s.y; j >= 0; j--){
		if (board[i][j] == sign)
			left++;
		else
			break;
	}
	//��ֱ����ͳ��
	for (i = s.x, j = s.y; j < BOARDLENGTH; j++) {
		if (board[i][j] == sign)
			right++;
		else
			break;
	}
	if (left + right > 4)
		return sign;

	left = right = 0;
	//ˮƽ����ͳ��
	for (i = s.x, j = s.y; i >= 0; i--) {
		if (board[i][j] == sign)
			left++;
		else
			break;
	}
	//ˮƽ����ͳ��
	for (i = s.x, j = s.y; i < BOARDLENGTH; i++) {
		if (board[i][j] == sign)
			right++;
		else
			break;
	}
	if (left + right > 4)
		return sign;

	left = right = 0;
	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == sign)
			left++;
		else
			break;
	}
	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i < BOARDLENGTH && j < BOARDLENGTH; i++, j++) {
		if (board[i][j] == sign)
			right++;
		else
			break;
	}
	if (left + right > 4)
		return sign;

	left = right = 0;
	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i < BOARDLENGTH && j >= 0; i++, j--) {
		if (board[i][j] == sign)
			left++;
		else
			break;
	}
	//���Խ�������ͳ��
	for (i = s.x, j = s.y; i >= 0 && j < BOARDLENGTH; i--, j++) {
		if (board[i][j] == sign)
			right++;
		else
			break;
	}
	if (left + right > 4)
		return sign;

	return ChessType::NOCHESS;
}

