#include "AIUtil.h"
#define JUDGE_EDGE(y, x) \
	((y < 0 || y > 18 || x < 0 || x > 18) ? 0 : 1)

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

/*
	@author Ӧ��Ң
*/
int AIUtil::getBoard(int x, int y)
{
	return board[x * 19 + y];
}

/*
	��ʼ����ֵ

	@author Ӧ��Ң
*/
void AIUtil::init_zobrist() {
	int i, j, k;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 19; j++) {
			for (k = 0; k < 19; k++) {
				zobrist[i][j][k] = rand14();
			}
		}
	}
}

LL AIUtil::rand14()
{
	double val = rand() / (RAND_MAX + 1.0);
	return (LL)(val * 10e18);
}

/*
	��ʼ����ϣֵ

	@author Ӧ��Ң
*/
void AIUtil::init_hashtable()
{
	int i;
	//find = 0;
	for (i = 0; i < HASHSIZE; i++)
		hashtable[i].val = unknow;
}

/*
	alpha_beta��֦

	@para type---�������ͣ�depth---������ȣ�alpha��beta---����Сֵ��st---
	@author Ӧ��Ң
*/
int AIUtil::alpha_beta(int type, int depth, int alpha, int beta, LL st) 
{
	AIStep step[2];
	int kill[2];
	int i;

	step[0].player = 0;
	step[1].player = 1;
	int value;
	HashType hashf = HASHALPHA;
	int s1 = cal_all_points(&step[0], &kill[0]);
	int s2 = cal_all_points(&step[1], &kill[1]);
/*
#if 1
	if ((value = find_in_hash(depth, alpha, beta, st)) != unknow)
		return value;
#endif
	if (depth == 0) { // �ﵽ����������ƣ����ع��� 
		int s = s1 - s2;
		record_hash(depth, s, st, HASHEXACT);
		if (((!player) && s >= 0) || (player && s < 0)) // ��� player ռ���򷵻���ֵ�����򷵻ظ�ֵ
			return ABS(s);
		if (((!player) && s < 0) || (player && s >= 0))
			return -ABS(s);
	}

	Subpoints sp[250];
	LL tst;
	int n = set_order(sp, player); // �Ժ�ѡ�㰴�߷ֵ��ͷ����� 
	int y, x;

#if 1
	// ������һ������ || (�Է�����һ������ && ������һ���ɾ�ɱ��) ||  ������һ����˫�������Է�����һ���ɾ�ɱ��
	int self = player;
	int opp = player ^ 1;
	if (kill[self] == 3 || (kill[opp] < 3 && kill[self] == 2) || (kill[self] == 1 && kill[opp] < 2)) {
		if (depth == DEPTH) {
			comy = co[self].y;
			comx = co[self].x;
		}
		alpha = G5;
		return alpha;
	}
#endif

	for (i = 0; i < 10 && i < n; i++) { // ���ѡ�� 20 ����ѡ�� 
		tst = st;
		y = sp[i].y;
		x = sp[i].x;
		state[y][x] = player; // �� (y, x) ����
		st ^= zobrist[player][y][x];
		change_cpoint(y, x); // (y, x) �ĸ������ϵĵ÷��ܵ�Ӱ�죬��Ҫ�ı�  
		val = -alpha_beta(player ^ 1, depth - 1, -beta, -alpha, st);
		state[y][x] = -1;
		st ^= zobrist[player][y][x];
		change_cpoint(y, x);

		if (val > alpha) {
			if (depth == DEPTH) {
				comy = y;
				comx = x;
			}
			tst = st;
			hashf = HASHEXACT;
			alpha = val;
		}

		if (alpha >= beta) { // ǧ���ܰѵȺ�ȥ�������� 
			record_hash(depth, beta, tst, HASHBETA);
			return beta;
		}
	}
	record_hash(depth, alpha, tst, hashf);
	return alpha;*/
	return 0;
}

/*
	�������е��ֵ

	@para step---������Ϣ��kill---
	@author Ӧ��Ң
*/
int AIUtil::cal_all_points(AIStep *step, int *kill) 
{
	int i, j, flag;
	int value = 0;

	*kill = 0;
	if (step->player)
		flag = 3;
	else
		flag = 2;

	for (i = 0; i < 19; i++) {
		for (j = 0; j < 19; j++) {
			if (getBoard(i, j) == AIChessType::AINOCHESS) {
				value += cpoint[i][j][flag];
				if (cpoint[i][j][flag - 2] >(*kill)) {
					*kill = cpoint[i][j][flag - 2];
					step->y = i;
					step->x = j;
				}
			}
		}
	}

	return value;
}

/* 
	ͳ��ĳ����ķ��� 

	@para x---�����꣬y---������
	@author Ӧ��Ң
*/
void AIUtil::cal_point(int x, int y)
{
	AIStep tco;
	tco.x = x;
	tco.y = y;
	
	if (getBoard(y, x) == AIChessType::AINOCHESS) {
		tco.player = 0;
		cpoint[y][x][2] = get_points(&tco, &cpoint[y][x][0]); // ������ 
		tco.player = 1;
		cpoint[y][x][3] = get_points(&tco, &cpoint[y][x][1]); // ������ 
	}
}

/*
	����ĳ����ķ���

	@para step---������Ϣ��kill---
	@author Ӧ��Ң
*/
int AIUtil::get_points(AIStep *step, int *kill) {
	Points po;
	AIStep tco;
	int player = step->player;
	int y = step->y;
	int x = step->x;
	int value = 0;
	int zc4, zl3;					// nc4---�ܳ��ģ�nl3---�ܻ���

	*kill = 0;
	po.g5 = po.rc4 = po.l4 = po.l3 = po.rl3 = po.l2 = po.rl2 = po.c4 = po.m3 = po.d4 = po.d3 = po.d2 = 0;
	tco.player = player;
	tco.y = y;
	tco.x = x;

	cal_chess(&po, &tco, 1, 0);
	cal_chess(&po, &tco, 0, 1);
	cal_chess(&po, &tco, 1, 1);
	cal_chess(&po, &tco, -1, 1);

	zc4 = po.c4 + po.rc4;
	zl3 = po.l3 + po.rl3;
	if (po.g5 >= 1) {										// ���� 
		*kill = 3;
		value = CHENG5;
	}
	else if (po.l4 >= 1 || zc4 >= 2 || (zc4 && zl3)) {		// ��ɱ 
		*kill = 2;
		value = LIVE4;
	}
	else {
		if (zl3 >= 2) {										// ˫����
			*kill = 1;
		}
		value = po.l3*LIVE3 + po.rl3*RLIVE3 + po.l2*LIVE2 + po.rl2*RLIVE2 + po.c4*CHONG4 + po.rc4*RCHONG4 + po.m3*MIAN3 + po.d4*DEAD4 + po.d3*DEAD3 + po.d2*DEAD2;
	}

	return value;
}


/*
	�ж�ĳһ��������

	@para m---ˮƽ���ң�n---��ֱ���ң�isRestricted---�Ƿ����
	@author Ӧ��Ң
*/
void AIUtil::cal_chess(Points *po, AIStep *steps, int m, int n)
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
		po->g5++;
	else if (chessNum == 4) {
		if (lempty[0] >= 1 && rempty[0] >= 1)
			po->l4++; 
		else if (lempty[0] + rempty[0])
			po->c4++;
		else
			po->d4++;
	}
	else if (chessNum == 3) {
		int ok = 0;        // ͬһ��������������γɻ����ͳ��ģ���������  
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
		if (!ok && ((lempty[0] == 1 && lchess[1] == 1 && rempty[0] >= 1 && lempty[1] >= 1) || (rempty[0] == 1 && rchess[1] == 1 && lempty[0] >= 1 && rempty[1] >= 1))) {
			po->rl3++;
		}
		else if ((lempty[0] == 1 && lchess[1] == 1 && rempty[0] + lempty[1] >= 1) || (rempty[0] == 1 && rchess[1] == 1 && lempty[0] + rempty[1] >= 1))
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
		if (!ok && ((lempty[0] == 1 && lchess[1] == 2 && rempty[0] >= 1 && lempty[1] >= 1) || (rempty[0] == 1 && rchess[1] == 2 && lempty[0] >= 1 && rempty[1] >= 1))) {
			po->rl3++;
		}
		else if ((lempty[0] == 1 && lchess[1] == 2 && rempty[0] + lempty[1] >= 1) || (rempty[0] == 1 && rchess[1] == 2 && lempty[0] + rempty[1] >= 1))
			po->m3++;
		if ((lempty[0] == 1 && lchess[1] == 1 && rempty[0] + lempty[1] >= 3 && rempty[0] >= 1 && lempty[1] >= 1)
			|| (rempty[0] == 1 && rchess[1] == 1 && rempty[1] + lempty[0] >= 3 && lempty[0] >= 1 && rempty[1] >= 1)) {
			po->rl2++;
		}
		if ((lempty[0] == 2 && lchess[1] == 1 && rempty[0] >= 1 && lempty[1] >= 1) || (rempty[0] == 2 && rchess[1] == 1 && lempty[0] >= 1 && rempty[1] >= 1)) {
			po->rl2++;
		}
	}
}

/*
	�����ϣֵ

	@para depth---��ȣ�
	@author Ӧ��Ң
*/
int find_in_hash(int depth, int alpha, int beta, LL st)
{
	/*int p = (st&(HASHSIZE - 1));
	int val = hashtable[p].val;
	if (val == unknow)
		return val;
	if (hashtable[p].check == st) {
		find++;
		if (hashtable[p].depth >= depth) {
			if (hashtable[p].type == HASHEXACT) {
				return val;
			}
			if (hashtable[p].type == HASHALPHA && val <= alpha) {
				return alpha;
			}
			if (hashtable[p].type == HASHBETA && val >= beta) {
				return beta;
			}
		}
	}*/
	return 0;
}