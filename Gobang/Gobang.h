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
	Step AIWalk(int type);			// 机器走棋

	int isOverWithRestricted();     // 判断游戏是否结束，否返回ChessType::NOCHESS, 是返回棋子对应枚举，有禁手
	int isOverWithoutRestricted();  // 判断游戏是否结束，否返回ChessType::NOCHESS, 是返回棋子对应枚举，无禁手

	void saveBoard(char * path);	// 把棋盘保存到文件里
	void loadBoard(char * path);	// 从文件里读取棋盘

	int getTurn();					// 返回当前轮次
	std::deque<Step> getSteps();	// 返回储存落子顺序的双端队列
	std::deque<Step> getOverSteps();// 返回储存导致游戏结束的落子位置的双端队列


private:

	int board[BOARDLENGTH][BOARDLENGTH];	// 棋盘信息
	int turn;								// 轮次

	std::deque<Step> * steps;				// 储存落子顺序的双端队列
	std::deque<Step> * overSteps;			// 储存导致游戏结束的落子位置

	int isOver(bool isRestricted);			// 判断游戏是否结束，否返回ChessType::NOCHESS, 是返回棋子对应枚举

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
