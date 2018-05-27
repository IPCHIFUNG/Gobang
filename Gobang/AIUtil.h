#ifndef AIUTIL_H
#define AIUTIL_H

#include <stdlib.h>
#define HASHSIZE (1<<21)

typedef long long LL;

typedef enum
{
	HASHALPHA,		//alpha
	HASHBETA,		//beta
	HASHEXACT
} HashType;

class AIUtil
{
public:
	AIUtil(int *board);
	~AIUtil();

	typedef struct AIStep
	{
		int x;
		int y;
		int player;
	} AIStep;

	typedef struct {
		int g5;											// 成五
		int l4, l3, rc4, rl3, l2, rl2, d4, d3, d2;		// l4--活四，l3--活三，rc4--跳四，rl3--跳活三，l2--活二，rl2--跳活二，d4--死四，d3--死三，d2--死二
		int c4, m3;										// c4--冲四，m3--眠三
	}Points;

	typedef struct {
		LL check;
		HashType type;
		int val;
		int depth;
	}HashElem;

	
	void init_zobrist();
	void init_hashtable();
	int alpha_beta(int type, int depth, int alpha, int beta, LL st);

private:
	int *board;
	LL zobrist[3][20][20];
	HashElem hashtable[HASHSIZE];

	/* cpoint[i][j][0] 表示电脑绝杀棋情况 */
	/* cpoint[i][j][1] 表示玩家绝杀棋情况 */
	/* cpoint[i][j][2] 表示电脑得分 */
	/* cpoint[i][j][3] 表示玩家得分 */

	int cpoint[19][19][4];
	const int CHENG5 = 20000;		// 成五
	const int LIVE4 = 2000;			// 活四
	const int CHONG4 = 300;			// 连冲四
	const int RCHONG4 = 250;		// 跳冲四
	const int LIVE3 = 450;			// 活三
	const int RLIVE3 = 300;			// 跳三
	const int LIVE2 = 100;			// 活二
	const int RLIVE2 = 70;			// 跳二
	const int MIAN3 = 50;			// 眠三
	const int DEAD4 = -10;			// 死四
	const int DEAD3 = -10;			// 死三
	const int DEAD2 = -10;			// 死二
	const int inf = 9000000;		// alpha_beta
	const int unknow = 9900000;		// 未知

	LL rand14();
	int getBoard(int x, int y);
	int cal_all_points(AIStep *step, int *kill);
	void cal_point(int x, int y);
	int get_points(AIStep *step, int *kill);
	void cal_chess(Points *po, AIStep *steps, int m, int n);
	int find_in_hash(int depth, int alpha, int beta, LL st);

};

const enum AIChessType
{
	AIBLACKCHESS,	// 黑棋
	AIWHITECHESS,	// 白棋
	AINOCHESS		// 无棋
};



#endif // !AIUTIL_H

