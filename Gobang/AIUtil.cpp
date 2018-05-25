#include "AIUtil.h"
#define JUDGE_EDGE(y, x) \
	((y < 0 || y > 18 || x < 0 || x > 18) ? 0 : 1)

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

/*
	@author 应禹尧
*/
int AIUtil::getBoard(int x, int y)
{
	return board[x * 19 + y];
}

/*
	判断某一方向棋型

	@para m---水平查找，n---竖直查找，isRestricted---是否禁手
	@author 应禹尧
*/
void AIUtil::cal_chess(Points *po, AIStep *steps, int m, int n)
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
	int player = steps->player;
	int chessNum = 0;

	lchess[0] = lchess[1] = lempty[0] = lempty[1] = 0;
	rchess[0] = rchess[1] = rempty[0] = rempty[1] = 0;

	i = steps->x - m;
	j = steps->y - n;
	while (JUDGE_EDGE(i, j) && getBoard(i, j) == player) {
		lchess[0]++;
		i -= m;
		j -= n;
	}
	while (JUDGE_EDGE(i, j) && getBoard(i, j) == AIChessType::AINOCHESS) {
		lempty[0]++;
		i -= m;
		j -= n;
	}
	while (JUDGE_EDGE(i, j) && getBoard(i, j) == player) {
		lchess[1]++;
		i -= m;
		j -= n;
	}
	while (JUDGE_EDGE(i, j) && getBoard(i, j) == AIChessType::AINOCHESS) {
		lempty[1]++;
		i -= m;
		j -= n;
	}

	i = steps->x + m;
	j = steps->y + n;
	while (JUDGE_EDGE(i, j) && getBoard(i, j) == player) {
		rchess[0]++;
		i += m;
		j += n;
	}
	while (JUDGE_EDGE(i, j) && getBoard(i, j) == AIChessType::AINOCHESS) {
		rempty[0]++;
		i += m;
		j += n;
	}
	while (JUDGE_EDGE(i, j) && getBoard(i, j) == player) {
		rchess[1]++;
		i += m;
		j += n;
	}
	while (JUDGE_EDGE(i, j) && getBoard(i, j) == AIChessType::AINOCHESS) {
		rempty[1]++;
		i += m;
		j += n;
	}

	chessNum = lchess[0] + rchess[0] + 1;

	if (chessNum >= 5) 
		po->g5++; /* ooooo */
	else if (chessNum == 4) {
		if (lempty[0] >= 1 && rempty[0] >= 1) 
			po->l4++; /* xoooox */
		else if (lempty[0] + rempty[0]) 
			po->c4++;
		else 
			po->d4++;
	}
	else if (chessNum == 3) {
		int ok = 0; /* 同一个方向上如果可形成活三和冲四，舍弃活三  */
		if ((lempty[0] == 1 && lchess[1] >= 1) || (rempty[0] == 1 && rchess[1] >= 1)) {
			po->rc4++;
			ok = 1;
		}
		if (!ok && lempty[0] + rempty[0] >= 3 && lempty[0] >= 1 && rempty[0] >= 1) {
			po->l3++;
			ok = 1;
		}
		else if (lempty[0] + rempty[0])
			po->m3++;
		else
			po->d3++;
	}
	else if (chessNum == 2) {
		int ok = 0;
		if ((lempty[0] == 1 && lchess[1] >= 2) || (rempty[0] == 1 && rchess[1] >= 2)) {
			po->rc4++;
			ok = 1;
		}
		if (!ok && ((lempty[0] == 1 && lchess[1] == 1 && rempty[0] >= 1 && lempty[1] >= 1)
			|| (rempty[0] == 1 && rchess[1] == 1 && lempty[0] >= 1 && rempty[1] >= 1))) {
			po->rl3++;
		}
		else if ((lempty[0] == 1 && lchess[1] == 1 && rempty[0] + lempty[1] >= 1)
			|| (rempty[0] == 1 && rchess[1] == 1 && lempty[0] + rempty[1] >= 1))
			po->m3++;
		if (lempty[0] + rempty[0] >= 4 && lempty[0] >= 1 && rempty[0] >= 1)
			po->l2++;
		else if (lempty[0] + rempty[0] == 0)
			po->d2++;
	}
	else if (chessNum == 1) {
		int ok = 0;
		if ((lempty[0] == 1 && lchess[1] >= 3) || (rempty[0] == 1 && rchess[1] >= 3)) {
			po->rc4++;
			ok = 1;
		}
		if (!ok && ((lempty[0] == 1 && lchess[1] == 2 && rempty[0] >= 1 && lempty[1] >= 1)
			|| (rempty[0] == 1 && rchess[1] == 2 && lempty[0] >= 1 && rempty[1] >= 1))) {
			po->rl3++;
		}
		else if ((lempty[0] == 1 && lchess[1] == 2 && rempty[0] + lempty[1] >= 1)
			|| (rempty[0] == 1 && rchess[1] == 2 && lempty[0] + rempty[1] >= 1))
			po->m3++;
		if ((lempty[0] == 1 && lchess[1] == 1 && rempty[0] + lempty[1] >= 3 && rempty[0] >= 1 && lempty[1] >= 1)
			|| (rempty[0] == 1 && rchess[1] == 1 && rempty[1] + lempty[0] >= 3 && lempty[0] >= 1 && rempty[1] >= 1)) {
			po->rl2++;
		}
		if ((lempty[0] == 2 && lchess[1] == 1 && rempty[0] >= 1 && lempty[1] >= 1)
			|| (rempty[0] == 2 && rchess[1] == 1 && lempty[0] >= 1 && rempty[1] >= 1)) {
			po->rl2++;
		}
	}
}

/*
	alpha_beta剪枝

	@para type---棋子类型，depth---搜索深度，alpha，beta---极大极小值，st---
	@author 应禹尧
*/
int AIUtil::alpha_beta(int type, int depth, int alpha, int beta, LL st) 
{
	AIStep step[2];
	int kill[2];
	int i;

	step[0].player = 0;
	step[1].player = 1;
	int s1 = cal_all_points(&step[0], &kill[0]);
	int s2 = cal_all_points(&step[1], &kill[1]);

	return 0;
}

/*
	计算所有点价值

	@para step---落子信息，kill---
	@author 应禹尧
*/
int AIUtil::cal_all_points(AIStep *step, int *kill) 
{
	int i, j, flag;
	int ans = 0;

	*kill = 0;
	if (step->player)
		flag = 3;
	else
		flag = 2;

	for (i = 0; i < 19; i++) {
		for (j = 0; j < 19; j++) {
			if (getBoard(i, j) == AIChessType::AINOCHESS) {
				ans += cpoint[i][j][flag];
				if (cpoint[i][j][flag - 2] >(*kill)) {
					*kill = cpoint[i][j][flag - 2];
					step->y = i;
					step->x = j;
				}
			}
		}
	}

	return ans;
}

/* 
	统计某个点的分数 

	@para x---横坐标，y---纵坐标
	@author 应禹尧
*/
void AIUtil::cal_point(int x, int y)
{
	AIStep tco;
	tco.x = x;
	tco.y = y;
	
	if (getBoard(y, x) == AIChessType::AINOCHESS) {
		tco.player = 0;
		cpoint[y][x][2] = get_points(&tco, &cpoint[y][x][0]); // 攻击力 
		tco.player = 1;
		cpoint[y][x][3] = get_points(&tco, &cpoint[y][x][1]); // 防御力 
	}
}

/*
	计算某个点的分数

	@para step---落子信息，kill---
	@author 应禹尧
*/
int AIUtil::get_points(AIStep *step, int *kill) {
	Points po;
	AIStep tco;
	int player = step->player;
	int y = step->y;
	int x = step->x;
	int ans = 0;
	int nc4, nl3;					// nc4---总冲四，nl3---总活三

	*kill = 0;
	po.g5 = po.rc4 = po.l4 = po.l3 = po.rl3 = po.l2 = po.rl2 = po.c4 = po.m3 = po.d4 = po.d3 = po.d2 = 0;
	tco.player = player;
	tco.y = y;
	tco.x = x;

	cal_chess(&po, &tco, 1, 0);
	cal_chess(&po, &tco, 0, 1);
	cal_chess(&po, &tco, 1, 1);
	cal_chess(&po, &tco, -1, 1);

	nc4 = po.c4 + po.rc4;
	nl3 = po.l3 + po.rl3;
	if (po.g5 >= 1) { /* 成五 */
		*kill = 3;
		ans = CHENG5;
	}
	else if (po.l4 >= 1 || nc4 >= 2 || (nc4 && nl3)) { /* 绝杀 */
		*kill = 2;
		ans = LIVE4;
	}
	else {
		if (nl3 >= 2) { /* 双活三 */
			*kill = 1;
		}
		ans = po.l3*LIVE3 + po.rl3*RLIVE3 + po.l2*LIVE2 + po.rl2*RLIVE2 + po.c4*CHONG4 + po.rc4*RCHONG4 + po.m3*MIAN3 + po.d4*DEAD4 + po.d3*DEAD3 + po.d2*DEAD2;
	}
	return ans;
}