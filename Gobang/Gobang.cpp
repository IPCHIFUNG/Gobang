#include "Gobang.h"

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
	@return ChessType
*/
int Gobang::isOver()
{
	Step s;
	int i, j;                            //i----�����꣬j----������
	int s1, s2, h1, h2, z1, z2, f1, f2;  //s1,s2��ֱ�жϣ�h1,h2ˮƽ�жϣ�z1,z2���Խ����жϣ�f1,f2���Խ����ж�
	int sign = (turn + 1) % 2;

	s = steps->back();
	s1 = s2 = h1 = h2 = z1 = z2 = f1 = f2 = 0;
	
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

	if (s1 + s2 > 4)
		return sign;
	if(h1 + h2 > 4)
		return sign;
	if (z1 + z2 > 4)
		return sign;
	if (f1 + f2 > 4)
		return sign;

	return ChessType::NOCHESS;
}