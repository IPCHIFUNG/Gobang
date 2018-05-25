#include "AIUtil.h"


/*
@author 应禹尧
*/
AIUtil::AIUtil(int *board)
{
	this->board = board;
}

/*
@author 应禹尧
*/
AIUtil::~AIUtil()
{


}

int AIUtil::getBoard(int x, int y)
{
	return board[x * 19 + y];
}

/*
判断某一方向棋型

@para m---水平查找，n---竖直查找，isRestricted---是否禁手
@author 应禹尧
*/
void AIUtil::cal_chess(AIStep steps, int m, int n, int type, bool isRestricted)
{
	/*  lchess[0] 表示(y, x) 左边的且与(y, x) 相连的连续同类棋数目；
	lempty[0] 表示(y, x) 左边第一个空点数起的连续空点数目
	lchess[1] 表示(y, x) 左边的且与(y, x) 至少隔一个空点的连续同类棋数目
	lempty[1] 表示在 lchess[1] 个同类棋左边的连续空点数目

	rchess，rempty同理
	同理设下为左，上为右
	*/
	int lchess[2], rchess[2];
	int lempty[2], rempty[2];
	int i, j;											// i---x坐标，j---y坐标

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


