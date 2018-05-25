#ifndef AIUTIL_H
#define AIUTIL_H


class AIUtil
{
public:
	AIUtil(int *board);
	~AIUtil();

	typedef struct AIStep
	{
		int x;
		int y;
	} AIStep;

	void cal_chess(AIStep steps, int m, int n, int type, bool isRestricted);

private:
	int *board;


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
	const int inf = 9000000;		// 
	const int unknow = 9900000;		// 

	int getBoard(int x, int y);


};

const enum AIChessType
{
	AIBLACKCHESS,	// 黑棋
	AIWHITECHESS,	// 白棋
	AINOCHESS		// 无棋
};

#endif // !AIUTIL_H

