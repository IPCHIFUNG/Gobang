#ifndef AIUTIL_H
#define AIUTIL_H

#include <stdlib.h>
#include <cstring>
#define HASHSIZE (1<<21)
#define ABS(x) \
	((x)<(0)?(-x):(x))

typedef long long LL;

typedef enum
{
	HASHALPHA,		//alpha
	HASHBETA,		//beta
	HASHEXACT
} HashType;

typedef struct {
	int y, x;
	int chose;
	int point[2]; /* �õ�������÷� */
	int kill[2]; /* �õ����Σ�3 Ϊ���壬2 Ϊ��ɱ��1 Ϊ˫���� */
}Subpoints;

class AIUtil
{
public:
	AIUtil();
	~AIUtil();

	int state[19][19];

	typedef struct AIStep
	{
		int x;
		int y;
		int player;
	} AIStep;

	typedef struct {
		int g5;											// ����
		int l4, l3, rc4, rl3, l2, rl2, d4, d3, d2;		// l4--���ģ�l3--������rc4--���ģ�rl3--��������l2--�����rl2--�������d4--���ģ�d3--������d2--����
		int c4, m3;										// c4--���ģ�m3--����
	}Points;

	typedef struct {
		LL check;
		HashType HashType;
		int val;
		int depth;
	}HashElem;

	void init_zobrist();
	void init_hashtable();
	int copy_and_cal_points();
	int getX();
	int getY();
	LL cal_zobrist();
	int alpha_beta(int type, int depth, int alpha, int beta, LL st);

private:
	LL zobrist[3][20][20];
	HashElem hashtable[HASHSIZE];

	int DEPTH = 8;
	int counter;
	int find;
	int comy, comx;

	/* cpoint[i][j][0] ��ʾ���Ծ�ɱ����� */
	/* cpoint[i][j][1] ��ʾ��Ҿ�ɱ����� */
	/* cpoint[i][j][2] ��ʾ���Ե÷� */
	/* cpoint[i][j][3] ��ʾ��ҵ÷� */

	int cpoint[19][19][4];
	const int CHENG5 = 20000;		// ����
	const int LIVE4 = 2000;			// ����
	const int CHONG4 = 300;			// ������
	const int RCHONG4 = 250;		// ������
	const int LIVE3 = 450;			// ����
	const int RLIVE3 = 300;			// ����
	const int LIVE2 = 100;			// ���
	const int RLIVE2 = 70;			// ����
	const int MIAN3 = 50;			// ����
	const int DEAD4 = -10;			// ����
	const int DEAD3 = -10;			// ����
	const int DEAD2 = -10;			// ����
	const int inf = 9000000;		// alpha_beta
	const int unknow = 9900000;		// δ֪

	LL rand14();
	int cal_all_points(AIStep *step, int *kill);
	void cal_point(int x, int y);
	int get_points(AIStep *step, int *kill);
	void cal_chess(Points *po, AIStep *steps, int m, int n);
	int find_in_hash(int depth, int alpha, int beta, LL st);
	void record_hash(int depth, int val, LL st, HashType type);
	int set_order(Subpoints *od);
	void change_cpoint(int y, int x);

};

const enum AIChessType
{
	AIBLACKCHESS,	// ����
	AIWHITECHESS,	// ����
	AINOCHESS		// ����
};



#endif // !AIUTIL_H

