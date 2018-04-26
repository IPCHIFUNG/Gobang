#ifndef GOBANG_H
#define GOBANG_H

#define BOARDLENGTH 19	// 棋盘长度

class Gobang
{
public:
	Gobang();
	~Gobang();

	void initBoard();	// 初始化棋盘或用于清空棋盘

private:

	// 棋盘信息
	ChessType board[BOARDLENGTH][BOARDLENGTH];

};

/*
	棋盘上的棋子类型

	@author 叶志枫
*/
const enum ChessType
{
	NOCHESS,	// 无棋
	BLACKCHESS,	// 黑棋
	WHITECHESS	// 白棋
};





#endif // !GOBANG_H
