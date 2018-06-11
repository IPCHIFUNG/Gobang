#include "Gobang.h"
#include "AIUtil.h"
#define JUDGE_EDGE(y, x) \
	((y < 0 || y > 18 || x < 0 || x > 18) ? 0 : 1)

/*
	@author Ӧ��Ң
*/
AIUtil::AIUtil()
{
}

/*
	@author Ӧ��Ң
*/
AIUtil::~AIUtil()
{
}

/*
	��ʼ����ֵ

	@author Ӧ��Ң
*/
void AIUtil::init_zobrist() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 19; j++) {
			for (int k = 0; k < 19; k++) {
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
	for (int i = 0; i < HASHSIZE; i++)
		hashtable[i].val = unknow;
}

/*
	�����ֵ

	@author Ӧ��Ң
*/
LL AIUtil::cal_zobrist()
{
	LL z = 0;
	int i, j;
	for (i = 0; i < 19; i++) {
		for (j = 0; j < 19; j++) {
			if (state[i][j] == AIChessType::AINOCHESS)
				z ^= zobrist[2][i][j];
			else if (state[i][j] == AIChessType::AIBLACKCHESS)
				z ^= zobrist[0][i][j];
			else if (state[i][j] == AIChessType::AIWHITECHESS)
				z ^= zobrist[1][i][j];
		}
	}
	return z;
}

int AIUtil::copy_and_cal_points()
{
	int i, j;
	int yes = 0;
	memset(cpoint, 0, sizeof(cpoint));

	for (i = 0; i < 19; i++) {
		for (j = 0; j < 19; j++) {
			if (state[i][j] == AIChessType::AINOCHESS) {
				cal_point(i, j);								// ����ÿ�������ӵ�ķ���
			}
		}
	}
	return yes;
}

int AIUtil::getX()
{
	return comx;
}

int AIUtil::getY()
{
	return comy;
}

/*
	alpha_beta��֦

	@para AIType---�������ͣ�depth---������ȣ�alpha��beta---����Сֵ
	@author Ӧ��Ң
*/
int AIUtil::alpha_beta(int AIType, int depth, int alpha, int beta, LL st) 
{
	AIStep step[2];									// ������Ϣ
	int kill[2];									// ��ɱ
	int value;										// ��ֵ
	HashType hashf = HASHALPHA;

	int s1 = cal_all_points(&step[0], &kill[0]);
	int s2 = cal_all_points(&step[1], &kill[1]);

	step[0].player = AIChessType::AIBLACKCHESS;		// ����
	step[1].player = AIChessType::AIWHITECHESS;		// ����

	if ((value = find_in_hash(depth, alpha, beta, st)) != unknow)
		return value;

	if (depth == 0) {										// �ﵽ������ȣ����ؼ�ֵ 
		int s = s1 - s2;
		record_hash(depth, s, st, HASHEXACT);
		if (((!AIType) && s >= 0) || (AIType && s < 0))		// ������ռ���򷵻���ֵ�����򷵻ظ�ֵ
			return abs(s);
		if (((!AIType) && s < 0) || (AIType && s >= 0))
			return -abs(s);
	}

	Subpoints sp[19 * 19];
	LL tst;
	int n = set_order(sp);									// �Ժ�ѡ�㰴�߷ֵ��ͷ����� 
	int y, x;


	// ������һ������ || (�Է�����һ������ && ������һ���ɾ�ɱ��) ||  ������һ����˫�������Է�����һ���ɾ�ɱ��
	int self = AIType;
	int opp = (AIType + 1) % 2;
	if (kill[self] == 3 || (kill[opp] < 3 && kill[self] == 2) || (kill[self] == 1 && kill[opp] < 2)) {
		if (depth == DEPTH) {
			comy = step[self].y;
			comx = step[self].x;
		}
		alpha = CHENG5;

		return alpha;
	}

	// ���ѡ10 ����ѡ�� 
	for (int i = 0; i < 10 && i < n; i++) {									
		tst = st;
		x = sp[i].x;
		y = sp[i].y;
		state[y][x] = AIType;												// �� (y, x) ����
		st ^= zobrist[AIType][y][x];
		change_cpoint(y, x);												// (y, x) �ĸ������ϵĵ÷��ܵ�Ӱ�죬��Ҫ�ı�  
		value = -alpha_beta(AIType ^ 1, depth - 1, -beta, -alpha, st);
		state[y][x] = AIChessType::AINOCHESS;
		st ^= zobrist[AIType][y][x];
		change_cpoint(y, x);

		if (value > alpha) {
			if (depth == DEPTH) {
				comy = y;
				comx = x;
			}
			tst = st;
			hashf = HASHEXACT;
			alpha = value;
		}

		if (alpha >= beta) { // ǧ���ܰѵȺ�ȥ�������� 
			record_hash(depth, beta, tst, HASHBETA);
			return beta;
		}
	}
	record_hash(depth, alpha, tst, hashf);

	return alpha;
}

/*
	�������е��ֵ

	@para step---������Ϣ��kill---��ɱ��Ϣ
	@author Ӧ��Ң
*/
int AIUtil::cal_all_points(AIStep *step, int *kill) 
{
	int flag;
	int value = 0;

	*kill = 0;
	if (step->player)
		flag = 3;
	else
		flag = 2;

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (state[i][j] == AIChessType::AINOCHESS) {
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
	
	if (state[x][y] == AIChessType::AINOCHESS) {
		tco.player = 0;
		cpoint[x][y][2] = get_points(&tco, &cpoint[x][y][0]); // ������ 
		tco.player = 1;
		cpoint[x][y][3] = get_points(&tco, &cpoint[x][y][1]); // ������ 
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
	po.bb5 = po.g5 = po.rc4 = po.l4 = po.l3 = po.rl3 = po.l2 = po.rl2 = po.c4 = po.m3 = po.d4 = po.d3 = po.d2 = 0;
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
		return value;
	}
	else if (po.bb5 >= 1) {
		if (player == AIChessType::AIBLACKCHESS) {			// ���峤������
			value = BAN;
			return value;
		}
		else {												// �������
			*kill = 3;
			value = CHENG5;
			return value;
		}
	}
	if (player == AIChessType::AIBLACKCHESS) {			// �������֡����Ľ���
		if (zl3 >= 2 || (po.l4 + zc4 >= 2)) {
			value = BAN;
			return value;
		}
	}
	if (po.l4 >= 1 || zc4 >= 2 || (zc4 && zl3)) {		// ��ɱ 
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
	while (JUDGE_EDGE(i, j) && state[i][j] == player) {
		lchess[0]++;
		i -= m;
		j -= n;
	}
	while (JUDGE_EDGE(i, j) && state[i][j] == AIChessType::AINOCHESS) {
		lempty[0]++;
		i -= m;
		j -= n;
	}
	while (JUDGE_EDGE(i, j) && state[i][j] == player) {
		lchess[1]++;
		i -= m;
		j -= n;
	}
	while (JUDGE_EDGE(i, j) && state[i][j] == AIChessType::AINOCHESS) {
		lempty[1]++;
		i -= m;
		j -= n;
	}

	i = steps->x + m;
	j = steps->y + n;
	while (JUDGE_EDGE(i, j) && state[i][j] == player) {
		rchess[0]++;
		i += m;
		j += n;
	}
	while (JUDGE_EDGE(i, j) && state[i][j] == AIChessType::AINOCHESS) {
		rempty[0]++;
		i += m;
		j += n;
	}
	while (JUDGE_EDGE(i, j) && state[i][j] == player) {
		rchess[1]++;
		i += m;
		j += n;
	}
	while (JUDGE_EDGE(i, j) && state[i][j] == AIChessType::AINOCHESS) {
		rempty[1]++;
		i += m;
		j += n;
	}

	chessNum = lchess[0] + rchess[0] + 1;

	if (chessNum > 5)
		po->bb5++;
	else if (chessNum == 5)
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
int AIUtil::find_in_hash(int depth, int alpha, int beta, LL st)
{
	int p = (st&(HASHSIZE - 1));
	int val = hashtable[p].val;

	if (val == unknow)
		return val;
	if (hashtable[p].check == st) {
		if (hashtable[p].depth >= depth) {
			if (hashtable[p].HashType == HASHEXACT) {
				return val;
			}
			if (hashtable[p].HashType == HASHALPHA && val <= alpha) {
				return alpha;
			}
			if (hashtable[p].HashType == HASHBETA && val >= beta) {
				return beta;
			}
		}
	}
	
	return unknow;
}

/*
	��¼��ϣֵ

	@para depth---��ȣ�
	@author Ӧ��Ң
*/
void AIUtil::record_hash(int depth, int val, LL st, HashType AIType)
{
	int p = (st&(HASHSIZE - 1));

	hashtable[p].check = st;
	hashtable[p].val = val;
	hashtable[p].depth = depth;
	hashtable[p].HashType = AIType;
}

/*
	�Ƚ�

	@para
	@author Ӧ��Ң
*/
int compare(const void* _a, const void* _b)
{
	Subpoints *a = (Subpoints *)_a;
	Subpoints *b = (Subpoints *)_b;

	return ((b->point[0] + b->point[1]) - (a->point[0] + a->point[1]));
}

/*
	����˳��

	@para 
	@author Ӧ��Ң
*/
int AIUtil::set_order(Subpoints *od)
{
	int n = 0;

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (state[i][j] == AIChessType::AINOCHESS) {
				od[n].y = i;
				od[n].x = j;
				od[n].point[0] = cpoint[i][j][2];
				od[n].point[1] = cpoint[i][j][3];
				od[n].kill[0] = cpoint[i][j][0];
				od[n].kill[1] = cpoint[i][j][1];
				n++;
			}
		}
	}

	qsort(od, n, sizeof(Subpoints), compare);

	return n;
}



/*
	�ı�� (y, x) 4 �������¿����ӵ�ķ���

	@para
	@author Ӧ��Ң
*/
void AIUtil::change_cpoint(int y, int x)
{
	int i, j;

	for (i = 0; i < 19; i++) {
		if (state[y][i] == AIChessType::AINOCHESS) {
			cal_point(y, i);
		}
		if (state[i][x] == AIChessType::AINOCHESS) {
			cal_point(i, x);
		}
	}
	for (i = 0; i < 19; i++) {
		j = i - (y - x);
		if (0 < j && j < 19 && state[i][j] == AIChessType::AINOCHESS) {
			cal_point(i, j);
		}
		j = (y + x) - i;
		if (0 < j && j < 19 && state[i][j] == AIChessType::AINOCHESS) {
			cal_point(i, j);
		}
	}
}

