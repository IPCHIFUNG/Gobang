#include <stdio.h>
#include "Gobang.h"
#include "AIUtil.h"

Gobang::Gobang()
{
	AIutil = new AIUtil();
	rankings = new std::deque<rank>();
	// 初始化棋盘
	initBoard();
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
	while (!feof(inFile))
	{
		fscanf(inFile, "%s\t%d\n", tmp, &n);
		rank r = { tmp,n };
		rankings->push_back(r);
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

	for (auto it = rankings->begin(); it != rankings->end(); it++)
		fprintf(outFile, "%s\t%d\n", it->name.c_str(), it->n);

	fclose(outFile);
}

/*
	返回排行榜

	@author 王开阳
*/
std::deque<Gobang::rank> & Gobang::getRankings()
{
	return *rankings;
}

std::deque<Gobang::Step> & Gobang::getWinModel()
{
	return *winnerSteps;
}

/*
	添加排行榜

	@author 王开阳
*/
void Gobang::addRanking(std::string name, int n)
{
	if (name == "")
		return;
	rank r = { name,n };
	for (auto it = rankings->begin();; it++)
		if (it == rankings->end())
		{
			rankings->push_back(r);
			break;
		}
		else if (it->n > r.n)
		{
			rankings->insert(it, r);
			break;
		}
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
	设置难度

	* dif = 1  ——  初级难度
	* dif = 2  ——  中级难度
	* dif = 3  ——  高级难度

	@para dif---难度等级
	@author 应禹尧
*/
void Gobang::setDifficulty(int dif)
{
	AIutil->DEPTH = 2 + 2 * dif;
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

	Step walk;

	if (steps->size() <= 1) {

		if (board[9][9] == ChessType::NOCHESS) {	// AI第一次落子
			walk.x = 9;
			walk.y = 9;
		}
		else {
			walk.x = 10;
			walk.y = 9;
		}
	}
	else {
		AIUtil::AIStep AIs;
		int DEPTH = AIutil->DEPTH;								// 搜索深度
		int alpha = -INF;
		int beta = INF;
		LL st;

		AIutil->copy_and_cal_points();

		AIutil->init_zobrist();
		AIutil->init_hashtable();

		st = AIutil->cal_zobrist();
		AIutil->alpha_beta(turn, DEPTH, alpha, beta, st);		// 搜索 

		walk.y = AIutil->getX();
		walk.x = AIutil->getY();
	}

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

	winnerSteps = new std::deque<Step>();

	for (int i = 0; i < 4; i++)
		cModel[i] = -1;


	/* ------------------------------------------------------------- */

	if (!isRestricted || turn == ChessType::WHITECHESS) {
		result[0] = searchNumOfChess(1, 0, 0, isRestricted);		// 竖直查找，0---竖直
		if (result[0] == 5) {
			setWinnerModel(0, turn);
			return turn;
		}

		result[1] = searchNumOfChess(0, 1, 1, isRestricted);		// 水平查找，1---水平
		if (result[1] == 5) {
			setWinnerModel(1, turn);
			return turn;
		}

		result[2] = searchNumOfChess(1, 1, 2, isRestricted);		// 主对角线查找，2---主对角线
		if (result[2] == 5) {
			setWinnerModel(2, turn);
			return turn;
		}

		result[3] = searchNumOfChess(1, -1, 3, isRestricted);		// 副对角线查找，3---副对角线
		if (result[3] == 5) {
			setWinnerModel(3, turn);
			return turn;
		}
	}
	else {
		result[0] = searchNumOfChess(1, 0, 0, isRestricted);		// 竖直查找，0---竖直
		if (result[0] > 5) {										// 长连禁手
			setBanModel(0, -1, 0);
			return sign;
		}
		else if (result[0] == 5) {									// 黑棋成五
			setWinnerModel(0, turn);
			return turn;
		}

		model[0] = getChessModel(0);								// 竖直类型

		result[1] = searchNumOfChess(0, 1, 1, isRestricted);		// 水平查找，1---水平
		if (result[1] > 5) {										// 长连禁手
			setBanModel(1, -1, 0);
			return sign;
		}
		else if (result[1] == 5) {									// 黑棋成五
			setWinnerModel(1, turn);
			return turn;
		}
		model[1] = getChessModel(1);								// 水平类型
		if (judgeRestricted(model[0], model[1])) {
			setBanModel(0, 1, 1);
			return sign;
		}


		result[2] = searchNumOfChess(1, 1, 2, isRestricted);		// 主对角线查找，2---主对角线
		if (result[2] > 5) {										// 长连禁手
			setBanModel(2, -1, 0);
			return sign;
		}
		else if (result[2] == 5) {									// 黑棋成五
			setWinnerModel(2, turn);
			return turn;
		}
		model[2] = getChessModel(2);								// 主对角线类型
		if (judgeRestricted(model[0], model[2])) {
			setBanModel(0, 2, 1);
			return sign;
		}
		else if (judgeRestricted(model[1], model[2])) {
			setBanModel(1, 2, 1);
			return sign;
		}

		result[3] = searchNumOfChess(1, -1, 3, isRestricted);		// 副对角线查找，3---副对角线
		if (result[3] > 5) {										// 长连禁手
			setBanModel(3, -1, 0);
			return sign;
		}
		else if (result[3] == 5) {									// 黑棋成五
			setWinnerModel(3, turn);
			return turn;
		}
		model[3] = getChessModel(3);								// 副对角线类型
		if (judgeRestricted(model[0], model[3])) {
			setBanModel(0, 3, 1);
			return sign;
		}
		else if (judgeRestricted(model[1], model[3])) {
			setBanModel(1, 3, 1);
			return sign;
		}
		else if (judgeRestricted(model[2], model[3])) {
			setBanModel(2, 3, 1);
			return sign;
		}
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
	int chessTypeNow = (turn + 1) % 2;						// chessTypeNow----当前棋子类别
	int chessNum = -1;										// chessNum---相同棋子数目

	if (!isRestricted || turn == ChessType::WHITECHESS) {
		// 往右方及下方扫描 
		i = s.x;
		j = s.y;
		while (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH && board[i][j] == turn) {
			i += m;
			j += n;
			chessNum++;
		}

		// 往左方及上方扫描
		i = s.x;
		j = s.y;
		while (i >= 0 && j >= 0 && j < BOARDLENGTH && board[i][j] == turn) {
			i -= m;
			j -= n;
			chessNum++;
		}
	}
	else {
		/*  lchess[0] 表示(y, x) 左边的且与(y, x) 相连的连续同类棋数目；
		lempty[0] 表示(y, x) 左边第一个空点数起的连续空点数目
		lchess[1] 表示(y, x) 左边的且与(y, x) 至少隔一个空点的连续同类棋数目
		lempty[1] 表示在 lchess[1] 个同类棋左边的连续空点数目

		rchess，rempty同理
		同理设下为左，上为右
		*/
		int lchess[2], rchess[2];
		int lempty[2], rempty[2];
		int i, j;											// i---x坐标，j---y坐标

		lchess[0] = lchess[1] = lempty[0] = lempty[1] = 0;
		rchess[0] = rchess[1] = rempty[0] = rempty[1] = 0;

		i = s.x - m;
		j = s.y - n;
		while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
			lchess[0]++;
			i -= m;
			j -= n;
		}
		while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
			lempty[0]++;
			i -= m;
			j -= n;
		}
		while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
			lchess[1]++;
			i -= m;
			j -= n;
		}
		while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
			lempty[1]++;
			i -= m;
			j -= n;
		}

		i = s.x + m;
		j = s.y + n;
		while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
			rchess[0]++;
			i += m;
			j += n;
		}
		while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
			rempty[0]++;
			i += m;
			j += n;
		}
		while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
			rchess[1]++;
			i += m;
			j += n;
		}
		while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
			rempty[1]++;
			i += m;
			j += n;
		}

		chessNum = lchess[0] + rchess[0] + 1;

		if (chessNum > 4)
			return chessNum;
		else if (chessNum == 4) {
			if (lempty[0] >= 1 && rempty[0] >= 1)
				setChessModel(ChessModel::LIVEFOUR, temp);		// 活四
			else if (lempty[0] + rempty[0])
				setChessModel(ChessModel::CHONGFOUR, temp);		// 冲四
		}
		else if (chessNum == 3) {
			int ok = 0;        // 同一个方向上如果可形成活三和冲四，舍弃活三  
			if ((lempty[0] == 1 && lchess[1] >= 1) || (rempty[0] == 1 && rchess[1] >= 1)) {
				setChessModel(ChessModel::CHONGFOUR, temp);		// 冲四
				ok = 1;
			}
			if (!ok && lempty[0] + rempty[0] >= 3 && lempty[0] >= 1 && rempty[0] >= 1)
				setChessModel(ChessModel::LIVETHREE, temp);		// 活三
		}
		else if (chessNum == 2) {
			int ok = 0;
			if ((lempty[0] == 1 && lchess[1] >= 2) || (rempty[0] == 1 && rchess[1] >= 2)) {
				setChessModel(ChessModel::CHONGFOUR, temp);		// 冲四
				ok = 1;
			}
			if (!ok && ((lempty[0] == 1 && lchess[1] == 1 && rempty[0] >= 1 && lempty[1] >= 1) || (rempty[0] == 1 && rchess[1] == 1 && lempty[0] >= 1 && rempty[1] >= 1)))
				setChessModel(ChessModel::LIVETHREE, temp);		// 活三
		}
		else if (chessNum == 1) {
			int ok = 0;
			if ((lempty[0] == 1 && lchess[1] >= 3) || (rempty[0] == 1 && rchess[1] >= 3)) {
				setChessModel(ChessModel::CHONGFOUR, temp);		// 冲四
				ok = 1;
			}
			if (!ok && ((lempty[0] == 1 && lchess[1] == 2 && rempty[0] >= 1 && lempty[1] >= 1) || (rempty[0] == 1 && rchess[1] == 2 && lempty[0] >= 1 && rempty[1] >= 1)))
				setChessModel(ChessModel::LIVETHREE, temp);		// 活三
		}
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
	设置获胜棋型

	@para direction---查找方向，type---颜色类型
	@author 应禹尧
*/
void Gobang::setWinnerModel(int direction, int type)
{
	Step last_step = steps->back();		// 最后一步
	int i, j;							// 横纵坐标
	int m, n;							// 扫描方向

	if (direction == 0) {
		m = 1;
		n = 0;
	}
	else if (direction == 1) {
		m = 0;
		n = 1;
	}
	else if (direction == 2) {
		m = 1;
		n = 1;
	}
	else if (direction == 3) {
		m = 1;
		n = -1;
	}

	Gobang::Step temp;
	temp.x = type;
	temp.y = -1;
	winnerSteps->push_back(temp);

	// 往右方及下方扫描 
	i = last_step.x;
	j = last_step.y;
	while (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH && board[i][j] == turn) {
		Gobang::Step temp;
		temp.x = i;
		temp.y = j;
		winnerSteps->push_back(temp);
		i += m;
		j += n;
	}

	// 往左方及上方扫描
	i = last_step.x;
	j = last_step.y;
	while (i >= 0 && j >= 0 && j < BOARDLENGTH && board[i][j] == turn) {
		Gobang::Step temp;
		temp.x = i;
		temp.y = j;
		winnerSteps->push_back(temp);
		i -= m;
		j -= n;
	}
}

/*
	设置禁手棋型

	@para dir1---查找方向1，dir2---查找方向2，ban_model---禁手类型
	@author 应禹尧
*/
void Gobang::setBanModel(int dir1, int dir2, int ban_model)
{
	if (ban_model == 0)
		setWinnerModel(dir1, (turn + 1) % 2);
	else {
		int dir = dir1;
		int judge = 0;
		while (judge < 2) {
			Step last_step = steps->back();		// 最后一步
			int m, n;							// 扫描方向

			if (dir == 0) {
				m = 1;
				n = 0;
			}
			else if (dir == 1) {
				m = 0;
				n = 1;
			}
			else if (dir == 2) {
				m = 1;
				n = 1;
			}
			else if (dir == 3) {
				m = 1;
				n = -1;
			}

			/*
			lchess[0] 表示(y, x) 左边的且与(y, x) 相连的连续同类棋数目；
			lempty[0] 表示(y, x) 左边第一个空点数起的连续空点数目
			lchess[1] 表示(y, x) 左边的且与(y, x) 至少隔一个空点的连续同类棋数目
			lempty[1] 表示在 lchess[1] 个同类棋左边的连续空点数目

			rchess，rempty同理
			同理设下为左，上为右
			*/
			int lchess[2], rchess[2];
			int lempty[2], rempty[2];
			int i, j;											// i---x坐标，j---y坐标
			int chessNum = 0;									// 同色棋子数目

			lchess[0] = lchess[1] = lempty[0] = lempty[1] = 0;
			rchess[0] = rchess[1] = rempty[0] = rempty[1] = 0;

			i = last_step.x - m;
			j = last_step.y - n;
			while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
				lchess[0]++;
				i -= m;
				j -= n;
			}
			while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
				lempty[0]++;
				i -= m;
				j -= n;
			}
			while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
				lchess[1]++;
				i -= m;
				j -= n;
			}
			while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
				lempty[1]++;
				i -= m;
				j -= n;
			}

			i = last_step.x + m;
			j = last_step.y + n;
			while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
				rchess[0]++;
				i += m;
				j += n;
			}
			while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
				rempty[0]++;
				i += m;
				j += n;
			}
			while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
				rchess[1]++;
				i += m;
				j += n;
			}
			while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
				rempty[1]++;
				i += m;
				j += n;
			}

			chessNum = lchess[0] + rchess[0] + 1;

			if (chessNum == 4) {
				Gobang::Step temp1, temp2;
				temp1.x = (turn + 1) % 2;
				temp1.y = -1;
				winnerSteps->push_back(temp1);
				temp2.x = last_step.x;
				temp2.y = last_step.y;
				winnerSteps->push_back(temp2);

				i = last_step.x - m;
				j = last_step.y - n;
				while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
					Gobang::Step temp;
					temp.x = i;
					temp.y = j;
					winnerSteps->push_back(temp);
					i -= m;
					j -= n;
				}
				i = last_step.x + m;
				j = last_step.y + n;
				while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
					Gobang::Step temp;
					temp.x = i;
					temp.y = j;
					winnerSteps->push_back(temp);
					i += m;
					j += n;
				}
			}
			else if (chessNum == 3) {
				int ok = 0;        // 同一个方向上如果可形成活三和冲四，舍弃活三  
				if ((lempty[0] == 1 && lchess[1] >= 1) || (rempty[0] == 1 && rchess[1] >= 1)) {
					Gobang::Step temp1, temp2;												// 冲四
					temp1.x = (turn + 1) % 2;
					temp1.y = -1;
					winnerSteps->push_back(temp1);
					temp2.x = last_step.x;
					temp2.y = last_step.y;
					winnerSteps->push_back(temp2);

					i = last_step.x - m;
					j = last_step.y - n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i -= m;
						j -= n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
						i -= m;
						j -= n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i -= m;
						j -= n;
					}
					i = last_step.x + m;
					j = last_step.y + n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i += m;
						j += n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
						i += m;
						j += n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i += m;
						j += n;
					}

					ok = 1;
				}
				if (!ok && lempty[0] + rempty[0] >= 3 && lempty[0] >= 1 && rempty[0] >= 1) {
					Gobang::Step temp1, temp2;												// 活三
					temp1.x = (turn + 1) % 2;
					temp1.y = -1;
					winnerSteps->push_back(temp1);
					temp2.x = last_step.x;
					temp2.y = last_step.y;
					winnerSteps->push_back(temp2);

					i = last_step.x - m;
					j = last_step.y - n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i -= m;
						j -= n;
					}
					i = last_step.x + m;
					j = last_step.y + n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i += m;
						j += n;
					}
				}
			}
			else if (chessNum == 2) {
				int ok = 0;
				if ((lempty[0] == 1 && lchess[1] >= 2) || (rempty[0] == 1 && rchess[1] >= 2)) {
					Gobang::Step temp1, temp2;												// 冲四
					temp1.x = (turn + 1) % 2;
					temp1.y = -1;
					winnerSteps->push_back(temp1);
					temp2.x = last_step.x;
					temp2.y = last_step.y;
					winnerSteps->push_back(temp2);

					i = last_step.x - m;
					j = last_step.y - n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i -= m;
						j -= n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
						i -= m;
						j -= n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i -= m;
						j -= n;
					}
					i = last_step.x + m;
					j = last_step.y + n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i += m;
						j += n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
						i += m;
						j += n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i += m;
						j += n;
					}

					ok = 1;
				}
				if (!ok && ((lempty[0] == 1 && lchess[1] == 1 && rempty[0] >= 1 && lempty[1] >= 1) || (rempty[0] == 1 && rchess[1] == 1 && lempty[0] >= 1 && rempty[1] >= 1))) {
					Gobang::Step temp1, temp2;												// 活三
					temp1.x = (turn + 1) % 2;
					temp1.y = -1;
					winnerSteps->push_back(temp1);
					temp2.x = last_step.x;
					temp2.y = last_step.y;
					winnerSteps->push_back(temp2);

					i = last_step.x - m;
					j = last_step.y - n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i -= m;
						j -= n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
						i -= m;
						j -= n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i -= m;
						j -= n;
					}
					i = last_step.x + m;
					j = last_step.y + n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i += m;
						j += n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
						i += m;
						j += n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i += m;
						j += n;
					}
				}
			}
			else if (chessNum == 1) {
				int ok = 0;
				if ((lempty[0] == 1 && lchess[1] >= 3) || (rempty[0] == 1 && rchess[1] >= 3)) {
					Gobang::Step temp1, temp2;												// 冲四
					temp1.x = (turn + 1) % 2;
					temp1.y = -1;
					winnerSteps->push_back(temp1);
					temp2.x = last_step.x;
					temp2.y = last_step.y;
					winnerSteps->push_back(temp2);

					i = last_step.x - m;
					j = last_step.y - n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i -= m;
						j -= n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
						i -= m;
						j -= n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i -= m;
						j -= n;
					}
					i = last_step.x + m;
					j = last_step.y + n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i += m;
						j += n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
						i += m;
						j += n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i += m;
						j += n;
					}

					ok = 1;
				}
				if (!ok && ((lempty[0] == 1 && lchess[1] == 2 && rempty[0] >= 1 && lempty[1] >= 1) || (rempty[0] == 1 && rchess[1] == 2 && lempty[0] >= 1 && rempty[1] >= 1))) {
					Gobang::Step temp1, temp2;												// 活三
					temp1.x = (turn + 1) % 2;
					temp1.y = -1;
					winnerSteps->push_back(temp1);
					temp2.x = last_step.x;
					temp2.y = last_step.y;
					winnerSteps->push_back(temp2);

					i = last_step.x - m;
					j = last_step.y - n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i -= m;
						j -= n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
						i -= m;
						j -= n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i -= m;
						j -= n;
					}
					i = last_step.x + m;
					j = last_step.y + n;
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i += m;
						j += n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == AIChessType::AINOCHESS) {
						i += m;
						j += n;
					}
					while (JUDGE_EDGE(i, j) && board[i][j] == turn) {
						Gobang::Step temp;
						temp.x = i;
						temp.y = j;
						winnerSteps->push_back(temp);
						i += m;
						j += n;
					}
				}
			}

			dir = dir2;
			judge++;
		}
	}
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
	else if (model1 == ChessModel::CHONGFOUR && model2 == ChessModel::LIVEFOUR)
		return true;						// 四四禁手 活四冲四
	else if (model1 == ChessModel::CHONGFOUR && model2 == ChessModel::CHONGFOUR)
		return true;						// 四四禁手 双冲四

	return false;
}