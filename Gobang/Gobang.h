#ifndef GOBANG_H
#define GOBANG_H

#define BOARDLENGTH 19	// 棋盘长度

#include <queue>

class Gobang
{
public:
	Gobang();
	~Gobang();

	typedef struct Step
	{
		int x;
		int y;
	} Step;

	void initBoard();				// 初始化棋盘或用于清空棋盘
	void newStep(Step step);		// 走一步棋
	Step AIWalk(int type);					// 机器走棋

	int isOver();					// 判断游戏是否结束，否返回ChessType::NOCHESS, 是返回棋子对应枚举
	bool isBanned();                // 判断是否存在禁手，否返回false，是返回true

	void saveBoard(char * path);	// 把棋盘保存到文件里
	void loadBoard(char * path);	// 从文件里读取棋盘

	int getTurn();					// 返回当前轮次
	std::deque<Step> getSteps();	// 返回储存落子顺序的双端队列


private:

	int board[BOARDLENGTH][BOARDLENGTH];	// 棋盘信息
	int turn;								// 轮次

	std::deque<Step> * steps;				// 储存落子顺序的双端队列

};

/*
	棋盘上的棋子类型

	@author 叶志枫
*/
const enum ChessType
{
	BLACKCHESS,	// 黑棋
	WHITECHESS,	// 白棋
	NOCHESS		// 无棋
};

#endif // !GOBANG_H
