#include "AIUtil.h"


/*
@author Ӧ��Ң
*/
AIUtil::AIUtil(int *board)
{
	this->board = board;
}

/*
@author Ӧ��Ң
*/
AIUtil::~AIUtil()
{


}

int AIUtil::getBoard(int x, int y)
{
	return board[x * 19 + y];
}

/*
�ж�ĳһ��������

@para m---ˮƽ���ң�n---��ֱ���ң�isRestricted---�Ƿ����
@author Ӧ��Ң
*/
void AIUtil::cal_chess(AIStep steps, int m, int n, int type, bool isRestricted)
{
	/*  lchess[0] ��ʾ(y, x) ��ߵ�����(y, x) ����������ͬ������Ŀ��
	lempty[0] ��ʾ(y, x) ��ߵ�һ���յ�����������յ���Ŀ
	lchess[1] ��ʾ(y, x) ��ߵ�����(y, x) ���ٸ�һ���յ������ͬ������Ŀ
	lempty[1] ��ʾ�� lchess[1] ��ͬ������ߵ������յ���Ŀ

	rchess��remptyͬ��
	ͬ������Ϊ����Ϊ��
	*/
	int lchess[2], rchess[2];
	int lempty[2], rempty[2];
	int i, j;											// i---x���꣬j---y����

	lchess[0] = lchess[1] = lempty[0] = lempty[1] = 0;
	rchess[0] = rchess[1] = rempty[0] = rempty[1] = 0;

	i = steps.x;
	j = steps.y;
	while (getBoard(i, j) == type) {
		lchess[0]++;
		i -= m;
		j -= n;
	}
	while (getBoard(i, j) == AIChessType::AINOCHESS) {
		lempty[0]++;
		i -= m;
		j -= n;
	}
	while (getBoard(i, j) == type) {
		lchess[1]++;
		i -= m;
		j -= n;
	}
	while (getBoard(i, j) == AIChessType::AINOCHESS) {
		lempty[1]++;
		i -= m;
		j -= n;
	}
}


