#include "Gobang.h"

#include <stdio.h>

Gobang::Gobang()
{
	// 初始化棋盘
	initBoard();
	// 初始化双端队列
	steps = new std::deque<Step>();
	overSteps = new std::deque<Step>();
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
	返回导致游戏结束的落子位置的双端队列

	@author 应禹尧
	@return 双端队列
*/
std::deque<Gobang::Step> Gobang::getOverSteps()
{

	return *overSteps;
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
	人机对战

	@author 应禹尧
	@return 返回Step类型的坐标
*/
Gobang::Step Gobang::AIWalk(int type)
{
	if (type != ChessType::BLACKCHESS || type != ChessType::WHITECHESS)
		throw "The chess type does not existing";





	return Step();
}

/*
	判断游戏是否结束，有禁手

	@author 应禹尧
	@return ChessType   NOCHESS---无胜负产生，BLACKCHESS---黑棋获胜，WHITECHESS---白棋获胜
*/
int Gobang::isOverWithRestricted()
{
	// true表示有禁手
	return isOver(true);
}

/*
	判断游戏是否结束，无禁手

	@author 应禹尧
	@return ChessType   NOCHESS---无胜负产生，BLACKCHESS---黑棋获胜，WHITECHESS---白棋获胜
*/
int Gobang::isOverWithoutRestricted()
{
	// false表示无禁手
	return isOver(false);
}

/*
	判断游戏是否结束

	@author 应禹尧
	@return ChessType   NOCHESS---无胜负产生，BLACKCHESS---黑棋获胜，WHITECHESS---白棋获胜
*/
int Gobang::isOver(bool isRestricted)
{
	Step s;
	int i, j;										//i----横坐标，j----纵坐标

	int s1, s2, h1, h2, z1, z2, f1, f2;				//s1,s2用于竖直统计，h1,h2用于水平统计，z1,z2用于主对角线统计，f1,f2用于副对角线统计
	int sk1, sk2, hk1, hk2, zk1, zk2, fk1, fk2;		//sk1,sk2用于竖直空位统计，hk1,hk2用于水平空位统计，zk1,zk2用于主对角线空位统计，fk1,fk2用于副对角线空位统计
	int sign = (turn + 1) % 2;						//sign----棋子类别

	int result[4];

	s = steps->back();
	s1 = s2 = h1 = h2 = z1 = z2 = f1 = f2 = 0;
	sk1 = sk2 = hk1 = hk2 = zk1 = zk2 = fk1 = fk2 = 0;

	/* ------------------------------------------------------------- */

	result[0] = searchNumOfChess(0, 1);		//竖直查找
	result[1] = searchNumOfChess(1, 0);		//水平查找
	result[2] = searchNumOfChess(1, 1);		//主对角线查找
	result[3] = searchNumOfChess(1, -1);	//副对角线查找


	//竖直向上统计
	for (i = s.x, j = s.y; j >= 0; j--) {
		if (board[i][j] == sign)
			s1++;
		else {
			while (board[i][j] == ChessType::NOCHESS && j >= 0) {
				sk1++;
				j--; 
			}
			break;
		}
	}
	//竖直向下统计
	for (i = s.x, j = s.y; j < BOARDLENGTH; j++) {
		if (board[i][j] == sign)
			s2++;
		else {
			while (board[i][j] == ChessType::NOCHESS && j < BOARDLENGTH) {
				sk2++;
				j++;
			}
			break;
		}
	}

	//水平向左统计
	for (i = s.x, j = s.y; i >= 0; i--) {
		if (board[i][j] == sign)
			h1++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i >= 0) {
				hk1++;
				i--;
			}
			break;
		}
	}
	//水平向右统计
	for (i = s.x, j = s.y; i < BOARDLENGTH; i++) {
		if (board[i][j] == sign)
			h2++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i < BOARDLENGTH) {
				hk2++;
				i++;
			}
			break;
		}
	}

	//主对角线向上统计
	for (i = s.x, j = s.y; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == sign)
			z1++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i >= 0 && j >= 0) {
				zk1++;
				i--;
				j--;
			}
			break;
		}
	}
	//主对角线向下统计
	for (i = s.x, j = s.y; i < BOARDLENGTH && j < BOARDLENGTH; i++, j++) {
		if (board[i][j] == sign)
			z2++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i < BOARDLENGTH && j < BOARDLENGTH) {
				zk2++;
				i++;
				j++;
			}
			break;
		}
	}

	//副对角线向上统计
	for (i = s.x, j = s.y; i < BOARDLENGTH && j >= 0; i++, j--) {
		if (board[i][j] == sign)
			f1++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i < BOARDLENGTH && j >= 0) {
				fk1++;
				i++;
				j--;
			}
			break;
		}
	}
	//副对角线向下统计
	for (i = s.x, j = s.y; i >= 0 && j < BOARDLENGTH; i--, j++) {
		if (board[i][j] == sign)
			f2++;
		else {
			while (board[i][j] == ChessType::NOCHESS && i >= 0 && j < BOARDLENGTH) {
				fk2++;
				i--;
				j++;
			}
			break;
		}
	}

	/* ------------------------------------------------------------- */

	if (!isRestricted) {
		if (s1 + s2 > 5)
			return sign;
		if (h1 + h2 > 5)
			return sign;
		if (z1 + z2 > 5)
			return sign;
		if (f1 + f2 > 5)
			return sign;
	}
	else {
		if (sign == ChessType::BLACKCHESS) {
			//三三禁手
			if (s1 + s2 - 1 + h1 + h2 - 2 == 5 && sk1 + sk2 == 3 && hk1 + hk2 == 3) {
				return turn;
			}
			if (s1 + s2 - 1 + z1 + z2 - 2 == 5 && sk1 + sk2 == 3 && zk1 + zk2 == 3) {
				return turn;
			}
			if (s1 + s2 - 1 + f1 + f2 - 2 == 5 && sk1 + sk2 == 3 && fk1 + fk2 == 3) {
				return turn;
			}
			if (h1 + h2 - 1 + z1 + z2 - 2 == 5 && hk1 + hk2 == 3 && zk1 + zk2 == 3) {
				return turn;
			}
			if (h1 + h2 - 1 + f1 + f2 - 2 == 5 && hk1 + hk2 == 3 && fk1 + fk2 == 3) {
				return turn;
			}
			if (z1 + z2 - 1 + f1 + f2 - 2 == 5 && zk1 + zk2 == 3 && fk1 + fk2 == 3) {
				return turn;
			}

			//四四禁手


			//长连禁手
			if (s1 + s2 > 6)
				return turn;
			if (h1 + h2 > 6)
				return turn;
			if (z1 + z2 > 6)
				return turn;
			if (f1 + f2 > 6)
				return turn;
		}
		if (s1 + s2 > 5)
			return sign;
		if (h1 + h2 > 5)
			return sign;
		if (z1 + z2 > 5)
			return sign;
		if (f1 + f2 > 5)
			return sign;
	}


	return ChessType::NOCHESS;
}

/*
	判断棋子数量

	@para m---水平查找，n---竖直查找
	@author 应禹尧
	@return 
*/
int Gobang::searchNumOfChess(int m, int n)
{
	int temp_x, temp_y;




	return 0;
}

/*
	判断棋型是否为活三

	@para x---横坐标，y---纵坐标
	@author 应禹尧
	@return bool    true---棋型为活三，false---棋型不为活三
*/
bool Gobang::isLiveThree(int x, int y)
{
	return false;
}

/*
	判断棋型是否为活四

	@para x---横坐标，y---纵坐标
	@author 应禹尧
	@return bool    true---棋型为活四，false---棋型不为活四
*/
bool Gobang::isLiveFour(int x, int y)
{
	return false;
}

/*
	判断棋型是否为冲四

	@para x---横坐标，y---纵坐标
	@author 应禹尧
	@return bool    true---棋型为冲四，false---棋型不为冲四
*/
bool Gobang::isPunchingFour(int x, int y)
{
	return false;
}