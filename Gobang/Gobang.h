#ifndef GOBANG_H
#define GOBANG_H

#define BOARDLENGTH 19	// 棋盘长度
#define INF 9000000
#define JUDGE_EDGE(y, x) \
	((y < 0 || y > 18 || x < 0 || x > 18) ? 0 : 1)

#include <string>
#include <queue>
#include "AIUtil.h"

class Gobang
{
public:
	Gobang();
	~Gobang();

	typedef struct Step
	{
		int x;
		int y;
	}Step;

	typedef struct rank
	{
		std::string name;
		int n;
	}rank;

	void initBoard();						// 初始化棋盘或用于清空棋盘
	void newStep(Step step);				// 走一步棋
	Step popLastStep();						// 弹出最后一步棋
	void shiftTurn();						// 换人走棋
	void setDifficulty(int dif);			// 设置难度	
	Step AIWalk(int type);					// 机器走棋

	int isOverWithRestricted();				// 判断游戏是否结束，否返回ChessType::NOCHESS, 是返回棋子对应枚举，有禁手
	int isOverWithoutRestricted();			// 判断游戏是否结束，否返回ChessType::NOCHESS, 是返回棋子对应枚举，无禁手

	void saveBoard(char * path);			// 把棋盘保存到文件里
	void loadBoard(char * path);			// 从文件里读取棋盘
	void readRanking();						// 读取排行榜
	void writeRanking();					// 保存排行榜
	void addRanking(std::string name, int n);	// 添加排行信息

	int getTurn();							// 返回当前轮次
	int getAtPosition(int x, int y);		// 返回（x, y）位置的棋子
	std::deque<Step> & getSteps();			// 返回储存落子顺序的双端队列
	std::deque<Step> & getOverSteps();      // 返回储存导致游戏结束的落子位置的双端队列
	std::deque<rank> & getRankings();		// 返回排行榜
	std::deque<Step> & getWinModel();	// 返回导致胜负的棋子

private:

	int board[BOARDLENGTH][BOARDLENGTH];								// 棋盘信息
	int turn;															// 轮次
	int cModel[4];														// 棋型
	AIUtil *AIutil;														// AI
	std::deque<rank> * rankings;										// 排行榜
	std::deque<Step> * steps;											// 储存落子顺序的双端队列
	std::deque<Step> * overSteps;										// 储存导致游戏结束的落子位置
	std::deque<Step> * winnerSteps;										// 储存胜负落子

	int isOver(bool isRestricted);										// 判断游戏是否结束，否返回ChessType::NOCHESS, 是返回棋子对应枚举
	int searchNumOfChess(int m, int n, int temp, bool isRestricted);	// 判断棋子数
	bool judgeRestricted(int model1, int model2);						// 判断棋型

	void setChessModel(int model, int temp);							// 设置棋型
	int getChessModel(int temp);										// 获得棋型
	void setWinnerModel(int direction);									// 设置获胜棋型
	void setBanModel(int dir1, int dir2, int ban_model);				// 设置禁手棋型

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

/*
	棋盘上的棋子路数

	@author 应禹尧
*/
const enum ChessModel
{
	LIVETHREE,	// 活三
	LIVEFOUR,	// 活四
	CHONGFOUR,	// 冲四
};

#endif // !GOBANG_H
