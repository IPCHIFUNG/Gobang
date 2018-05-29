#include <stdio.h>
#include "Gobang.h"
#include "AIUtil.h"

Gobang::Gobang()
{
	AIutil = new AIUtil();
	// 初始化棋盘
	initBoard();

	for (int i = 0; i < 10; i++)
		ranking[i] = "";
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
	// 初始化棋盘
	for (int i = 0; i < BOARDLENGTH; i++)
		for (int j = 0; j < BOARDLENGTH; j++)
			board[i][j] = ChessType::NOCHESS;

	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			AIutil->state[i][j] = 2;

	turn = ChessType::BLACKCHESS;
	// 初始化双端队列
	/*if (steps != NULL)
		steps->clear();
	if (overSteps != NULL)
		overSteps->clear();*/
	steps = new std::deque<Step>();
	overSteps = new std::deque<Step>();
}

/*
	从文件里读取棋盘

	@author 叶志枫
	@para 读取路径
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
	fclose(inFile);
}

/*
	把棋盘保存到文件里

	@author 叶志枫
	@para 保存路径
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
	读取排行榜

	@author 王开阳
	@para 读取路径
*/
void Gobang::readRanking()
{
	FILE * inFile;

	inFile = fopen("Ranking.txt", "r");
	if (inFile == nullptr)
		throw "Unable to open file.";

	int n;
	char tmp[50];
	for (int i = 0; i < 10 && !feof(inFile); i++)
	{
		fscanf(inFile, "%s\t%d\n", tmp, &n);
		ranking[i] = tmp;
		ranking[i] = ranking[i] + "\t" + std::to_string(n) + "\n";
	}
	fclose(inFile);
}

/*
保存排行榜

@author 王开阳
@para 保存路径
*/
void Gobang::writeRanking()
{
	FILE * outFile;

	outFile = fopen("Ranking.txt", "w");
	if (outFile == nullptr)
		throw "Unable to open file.";

	for (int i = 0; i < 10 && ranking[i] != ""; i++)
	{
		fprintf(outFile, "%s", ranking[i].c_str());
	}
	fclose(outFile);
}

/*
	返回排行榜

	@author 王开阳
*/
std::string Gobang::getRanking(int n)
{
	return ranking[n];
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
	返回（x, y）位置的棋子

	@author 叶志枫
	@para int x - x 坐标
	@para int y - y 坐标
	@return ChessType - 返回棋子类型，越界返回-1
*/
int Gobang::getAtPosition(int x, int y)
{
	if (x < 0 || x >= BOARDLENGTH)
		return -1;
	if (y < 0 || y >= BOARDLENGTH)
		return -1;
	return board[x][y];
}

/*
	返回储存落子顺序的双端队列

	@author 叶志枫
	@return 双端队列
*/
std::deque<Gobang::Step> & Gobang::getSteps()
{
	return *steps;
}

/*
	返回导致游戏结束的落子位置的双端队列

	@author 应禹尧
	@return 双端队列
*/
std::deque<Gobang::Step> & Gobang::getOverSteps()
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
		throw "Error:This loc has a chess !";

	board[step.x][step.y] = turn;
	AIutil->state[step.x][step.y] = turn;

	steps->push_back(step);
}

/*
	弹出最后一步棋

	@author 叶志枫
	@return step - 最后一步棋
*/
Gobang::Step Gobang::popLastStep()
{
	if (!steps->empty())
	{
		Gobang::Step lastStep = steps->back();
		steps->pop_back();
		board[lastStep.x][lastStep.y] = ChessType::NOCHESS;
		AIutil->state[lastStep.x][lastStep.y] = ChessType::NOCHESS;
		return lastStep;
	}
	Gobang::Step lastStep;
	lastStep.x = -1;
	lastStep.y = -1;
	return lastStep;
}

/*
	换人走棋

	@author 叶志枫
*/
void Gobang::shiftTurn()
{
	turn = (turn + 1) % 2;
}

/*
	人机对战

	@author 应禹尧
	@return 返回Step类型的坐标
*/
Gobang::Step Gobang::AIWalk(int type)
{
	if (type != ChessType::BLACKCHESS && type != ChessType::WHITECHESS)
		throw "The chess type does not exist";

	const int inf = 9000000;					// alpha_beta
	Step s = steps->back();
	Step walk;
	AIUtil::AIStep AIs;
	int sign = (turn + 1) % 2;
	int DEPTH = 6;								// 搜索深度
	int alpha = -inf;
	int beta = inf;
	LL st;

	AIs.x = s.x;
	AIs.y = s.y;

	AIutil->copy_and_cal_points();

	AIutil->init_zobrist();
	AIutil->init_hashtable();

	st = AIutil->cal_zobrist();
	AIutil->alpha_beta(turn, DEPTH, alpha, beta, st);		// 搜索 

	walk.y = AIutil->getX();
	walk.x = AIutil->getY();

	return walk;
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
	Step s = steps->back();
	int sign = (turn + 1) % 2;										// sign----棋子类别
	int result[4] = { -1,-1,-1,-1 }, model[4] = { -1,-1,-1,-1 };	// result---棋子数目，model---棋型

	for (int i = 0; i < 4; i++)
		cModel[i] = -1;


	/* ------------------------------------------------------------- */

	if (!isRestricted) {
		result[0] = searchNumOfChess(1, 0, 0, isRestricted);		// 竖直查找，0---竖直
		if (result[0] == 5)
			return sign;

		result[1] = searchNumOfChess(0, 1, 1, isRestricted);		// 水平查找，1---水平
		if (result[1] == 5)
			return sign;

		result[2] = searchNumOfChess(1, 1, 2, isRestricted);		// 主对角线查找，2---主对角线
		if (result[2] == 5)
			return sign;

		result[3] = searchNumOfChess(1, -1, 3, isRestricted);		// 副对角线查找，3---副对角线
		if (result[3] == 5)
			return sign;
	}
	else {
		result[0] = searchNumOfChess(1, 0, 0, isRestricted);		// 竖直查找，0---竖直
		if (result[0] > 5) {										// 长连禁手
			if (sign == ChessType::BLACKCHESS)
				return turn;
			else
				return sign;
		}
		else if (result[0] == 5)
			return sign;
		model[0] = getChessModel(0);								// 竖直类型

		result[1] = searchNumOfChess(0, 1, 1, isRestricted);		// 水平查找，1---水平
		if (result[1] > 5) {										// 长连禁手
			if (sign == ChessType::BLACKCHESS)
				return turn;
			else
				return sign;
		}
		else if (result[1] == 5)
			return sign;
		model[1] = getChessModel(1);								// 水平类型
		if (judgeRestricted(model[0], model[1]))
			return turn;

		result[2] = searchNumOfChess(1, 1, 2, isRestricted);		// 主对角线查找，2---主对角线
		if (result[2] > 5) {										// 长连禁手
			if (sign == ChessType::BLACKCHESS)
				return turn;
			else
				return sign;
		}
		else if (result[2] == 5)
			return sign;
		model[2] = getChessModel(2);								// 主对角线类型
		if (judgeRestricted(model[0], model[2]))
			return turn;
		else if (judgeRestricted(model[1], model[2]))
			return turn;

		result[3] = searchNumOfChess(1, -1, 3, isRestricted);		// 副对角线查找，3---副对角线
		if (result[3] > 5) {										// 长连禁手
			if (sign == ChessType::BLACKCHESS)
				return turn;
			else
				return sign;
		}
		else if (result[3] == 5)
			return sign;
		model[3] = getChessModel(3);								// 副对角线类型
		if (judgeRestricted(model[0], model[3]))
			return turn;
		else if (judgeRestricted(model[1], model[3]))
			return turn;
		else if (judgeRestricted(model[2], model[3]))
			return turn;
	}

	return ChessType::NOCHESS;
}

/*
	判断棋子数量

	@para m---水平查找，n---竖直查找，temp---查找方向
	@author 应禹尧
	@return
*/
int Gobang::searchNumOfChess(int m, int n, int temp, bool isRestricted)
{
	Step s = steps->back();
	int i, j;												// i---x坐标，j---y坐标
	int chessNum = -1;										// chessNum---相同棋子数目
	int chessTypeNow = (turn + 1) % 2;						// chessTypeNow----当前棋子类别


	if (!isRestricted || chessTypeNow == ChessType::WHITECHESS) {
		// 往右方及下方扫描 
		i = s.x;
		j = s.y;
		while (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH && board[i][j] == chessTypeNow) {
			i += m;
			j += n;
			chessNum++;
		}

		// 往左方及上方扫描
		i = s.x;
		j = s.y;
		while (i >= 0 && j >= 0 && j < BOARDLENGTH && board[i][j] == chessTypeNow) {
			i -= m;
			j -= n;
			chessNum++;
		}
	}
	else {
		int blankNum = 0, otherNum = 0;						// blankNum---空位数目，otherNum---不同色棋子数
		int blankOtherChessNum = 0;							// blankOtherChessNum---空位后一个位置不同色棋子数
		int blankChessNum1 = 0, blankChessNum2 = 0;			// blankChessNum---空位后同色棋子数
		int boardNum = 0;									// 墙

		// 往右方及下方扫描 
		i = s.x;
		j = s.y;
		while (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH && board[i][j] == chessTypeNow) {
			i += m;
			j += n;
			chessNum++;
		}
		if (board[i][j] == ChessType::NOCHESS) {         // 判断右方或下方是否有空位置
			blankNum++;
			i += m;
			j += n;
			if (board[i][j] == turn) {
				if (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH)
					blankOtherChessNum++;
			}
			else if (board[i][j] == chessTypeNow) {
				if (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH) {
					blankChessNum1++;
					i += m;
					j += n;
					if (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH)
						if (board[i][j] == turn)
							blankOtherChessNum++;
				}
			}
			else if (i >= BOARDLENGTH || j < 0 || j >= BOARDLENGTH)
				boardNum++;
		}
		else
			otherNum++;

		// 往左方及上方扫描
		i = s.x;
		j = s.y;
		while (i >= 0 && j >= 0 && j < BOARDLENGTH && board[i][j] == chessTypeNow) {
			i -= m;
			j -= n;
			chessNum++;
		}
		if (board[i][j] == ChessType::NOCHESS) {        // 判断左方或上方是否有空位置
			blankNum++;
			i -= m;
			j -= n;
			if (board[i][j] == turn) {
				if (i >= 0 && j >= 0 && j < BOARDLENGTH)
					blankOtherChessNum++;
			}
			else if (board[i][j] == chessTypeNow) {
				if (i >= 0 && j >= 0 && j < BOARDLENGTH) {
					blankChessNum2++;
					i -= m;
					j -= n;
					if (i >= 0 && j >= 0 && j < BOARDLENGTH)
						if (board[i][j] == turn)
							blankOtherChessNum++;
				}

			}
			else if (i < 0 || j < 0 || j >= BOARDLENGTH)
				boardNum++;
		}
		else
			otherNum++;

		if (chessNum > 4)
			return chessNum;

		if (chessNum + blankChessNum1 == 3 && blankOtherChessNum + boardNum < 2 && otherNum == 0)
			setChessModel(ChessModel::LIVETHREE, temp);		// 活三
		else if (chessNum + blankChessNum2 == 3 && blankOtherChessNum + boardNum < 2 && otherNum == 0)
			setChessModel(ChessModel::LIVETHREE, temp);		// 活三
		else if (chessNum == 4 && otherNum == 0)
			setChessModel(ChessModel::LIVEFOUR, temp);		// 活四
		else if (chessNum == 4 && otherNum == 1)
			setChessModel(ChessModel::CHONGFOUR, temp);		// 冲四
		else if (chessNum + blankChessNum1 == 4)
			setChessModel(ChessModel::CHONGFOUR, temp);		// 冲四
		else if (chessNum + blankChessNum1 == 4)
			setChessModel(ChessModel::CHONGFOUR, temp);		// 冲四
	}

	return chessNum;
}

/*
	设置棋型

	@para model---棋型
	@author 应禹尧
	@return
*/
void Gobang::setChessModel(int model, int temp)
{
	cModel[temp] = model;
}

/*
	获得棋型

	@para m---水平查找，n---竖直查找
	@author 应禹尧
	@return
*/
int Gobang::getChessModel(int temp)
{
	return cModel[temp];
}

/*
	返回是否禁手

	@para model1---类型1，model2---类型2
	@author 应禹尧
	@return bool  true---禁手，false---非禁手
*/
bool Gobang::judgeRestricted(int model1, int model2)
{
	if (model1 == ChessModel::LIVETHREE && model2 == ChessModel::LIVETHREE)
		return true;						// 三三禁手 双活三
	else if (model1 == ChessModel::LIVEFOUR && model2 == ChessModel::LIVEFOUR)
		return true;						// 四四禁手 双活四
	else if (model1 == ChessModel::LIVEFOUR && model2 == ChessModel::CHONGFOUR)
		return true;						// 四四禁手 活四冲四
	else if (model1 == ChessModel::CHONGFOUR && model2 == ChessModel::CHONGFOUR)
		return true;						// 四四禁手 双冲四

	return false;
}