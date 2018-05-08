#include "Gobang.h"

#include <stdio.h>

Gobang::Gobang()
{
	// 初始化棋盘
	initBoard();
	// 初始化双端队列
	steps = new std::deque<Step>();
}

Gobang::~Gobang()
{
}

/*
	初始化棋盘或用于清空棋盘

	@author 叶志枫
*/
void Gobang::initBoard()
{
	for (int i = 0; i < BOARDLENGTH; i++)
		for (int j = 0; j < BOARDLENGTH; j++)
			board[i][j] = ChessType::NOCHESS;
	turn = ChessType::BLACKCHESS;
}

/*
	把棋盘保存到文件里

	@author 叶志枫
	@para 保存路径
	@throw char *
*/
void Gobang::saveBoard(char * path)
{
	FILE * outFile;

	outFile = fopen(path, "w");
	if (outFile == nullptr)
		throw "Unable to open file.";

	int size = steps->size();
	fprintf(outFile, "%d\n", size);
	auto iterator = steps->begin();
	for (int i = 0; i < size; i++)
	{
		Step tmp = *iterator;
		fprintf(outFile, "%d\t%d\n", tmp.x, tmp.y);
		iterator++;
	}
	fclose(outFile);
}

/*
	从文件里读取棋盘

	@author 叶志枫
	@para 保存路径
*/
void Gobang::loadBoard(char * path)
{
	FILE * inFile;

	inFile = fopen(path, "r");
	if (inFile == nullptr)
		throw "Unable to open file.";
	int size = 0;
	fscanf(inFile, "%d\n", &size);
	Step tmp;
	for (int i = 0; i < size; i++)
	{
		fscanf(inFile, "%d\t%d\n", &tmp.x, &tmp.y);
		steps->push_back(tmp);
	}
	turn = size % 2;
}

/*
	返回当前轮次

	@author 叶志枫
	@return ChessType
*/
int Gobang::getTurn()
{
	return turn;
}

/*
	返回储存落子顺序的双端队列

	@author 叶志枫
	@return 双端队列
*/
std::deque<Gobang::Step> Gobang::getSteps()
{
	return *steps;
}

/*
	走一步棋

	@author 应禹尧
	@para step：棋子位置
*/
void Gobang::newStep(Step step)
{
	//如果该位置已经存在棋子
	if (board[step.x][step.y] != ChessType::NOCHESS)
		throw"Error:This loc has a chess !";

	board[step.x][step.y] = turn;

	steps->push_back(step);

	turn = (turn + 1) % 2;
}

/*
	判断游戏是否结束

	@author 应禹尧
	@return ChessType   NOCHESS---无胜负产生，
*/
int Gobang::isOver()
{
	Step s;
	int i, j;                            //i----横坐标，j----纵坐标
	int left, right;                     //left往小算，right往大算
	int sign = (turn + 1) % 2;           //sign----棋子类别

	s = steps->back();

	left = right = 0;
	//竖直向上统计
	for (i = s.x, j = s.y; j >= 0; j--){
		if (board[i][j] == sign)
			left++;
		else
			break;
	}
	//竖直向下统计
	for (i = s.x, j = s.y; j < BOARDLENGTH; j++) {
		if (board[i][j] == sign)
			right++;
		else
			break;
	}
	if (left + right > 4)
		return sign;

	left = right = 0;
	//水平向左统计
	for (i = s.x, j = s.y; i >= 0; i--) {
		if (board[i][j] == sign)
			left++;
		else
			break;
	}
	//水平向右统计
	for (i = s.x, j = s.y; i < BOARDLENGTH; i++) {
		if (board[i][j] == sign)
			right++;
		else
			break;
	}
	if (left + right > 4)
		return sign;

	left = right = 0;
	//主对角线向上统计
	for (i = s.x, j = s.y; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == sign)
			left++;
		else
			break;
	}
	//主对角线向下统计
	for (i = s.x, j = s.y; i < BOARDLENGTH && j < BOARDLENGTH; i++, j++) {
		if (board[i][j] == sign)
			right++;
		else
			break;
	}
	if (left + right > 4)
		return sign;

	left = right = 0;
	//副对角线向上统计
	for (i = s.x, j = s.y; i < BOARDLENGTH && j >= 0; i++, j--) {
		if (board[i][j] == sign)
			left++;
		else
			break;
	}
	//副对角线向下统计
	for (i = s.x, j = s.y; i >= 0 && j < BOARDLENGTH; i--, j++) {
		if (board[i][j] == sign)
			right++;
		else
			break;
	}
	if (left + right > 4)
		return sign;

	return ChessType::NOCHESS;
}

