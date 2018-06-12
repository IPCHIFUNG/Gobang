#include <stdio.h>
#include "Gobang.h"
#include "AIUtil.h"

Gobang::Gobang()
{
	AIutil = new AIUtil();
	rankings = new std::deque<rank>();
	// ��ʼ������
	initBoard();
}

Gobang::~Gobang()
{
}

/*
	��ʼ�����̻������������

	@author Ҷ־��
*/
void Gobang::initBoard()
{
	// ��ʼ������
	for (int i = 0; i < BOARDLENGTH; i++)
		for (int j = 0; j < BOARDLENGTH; j++)
			board[i][j] = ChessType::NOCHESS;

	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			AIutil->state[i][j] = 2;

	turn = ChessType::BLACKCHESS;
	// ��ʼ��˫�˶���
	/*if (steps != NULL)
		steps->clear();
	if (overSteps != NULL)
		overSteps->clear();*/
	steps = new std::deque<Step>();
	overSteps = new std::deque<Step>();
}

/*
	���ļ����ȡ����

	@author Ҷ־��
	@para ��ȡ·��
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
	�����̱��浽�ļ���

	@author Ҷ־��
	@para ����·��
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
	��ȡ���а�

	@author ������
	@para ��ȡ·��
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
�������а�

@author ������
@para ����·��
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
	�������а�

	@author ������
*/
std::deque<Gobang::rank> & Gobang::getRankings()
{
	return *rankings;
}

/*
	������а�

	@author ������
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
	���ص�ǰ�ִ�

	@author Ҷ־��
	@return ChessType
*/
int Gobang::getTurn()
{
	return turn;
}

/*
	���أ�x, y��λ�õ�����

	@author Ҷ־��
	@para int x - x ����
	@para int y - y ����
	@return ChessType - �����������ͣ�Խ�緵��-1
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
	���ش�������˳���˫�˶���

	@author Ҷ־��
	@return ˫�˶���
*/
std::deque<Gobang::Step> & Gobang::getSteps()
{
	return *steps;
}

/*
	���ص�����Ϸ����������λ�õ�˫�˶���

	@author Ӧ��Ң
	@return ˫�˶���
*/
std::deque<Gobang::Step> & Gobang::getOverSteps()
{

	return *overSteps;
}

/*
	��һ����

	@author Ӧ��Ң
	@para step������λ��
*/
void Gobang::newStep(Step step)
{
	//�����λ���Ѿ���������
	if (board[step.x][step.y] != ChessType::NOCHESS)
		throw "Error:This loc has a chess !";

	board[step.x][step.y] = turn;
	AIutil->state[step.x][step.y] = turn;

	steps->push_back(step);
}

/*
	�������һ����

	@author Ҷ־��
	@return step - ���һ����
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
	��������

	@author Ҷ־��
*/
void Gobang::shiftTurn()
{
	turn = (turn + 1) % 2;
}

/*
	�˻���ս

	@author Ӧ��Ң
	@return ����Step���͵�����
*/
Gobang::Step Gobang::AIWalk(int type)
{
	if (type != ChessType::BLACKCHESS && type != ChessType::WHITECHESS)
		throw "The chess type does not exist";

	Step walk;

	if (steps->size() <= 1) {

		if (board[9][9] == ChessType::NOCHESS) {	// AI��һ������
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
		int DEPTH = 4;								// �������
		int alpha = -INF;
		int beta = INF;
		LL st;

		AIutil->copy_and_cal_points();

		AIutil->init_zobrist();
		AIutil->init_hashtable();

		st = AIutil->cal_zobrist();
		AIutil->alpha_beta(turn, DEPTH, alpha, beta, st);		// ���� 

		walk.y = AIutil->getX();
		walk.x = AIutil->getY();
	}

	return walk;
}

/*
	�ж���Ϸ�Ƿ�������н���

	@author Ӧ��Ң
	@return ChessType   NOCHESS---��ʤ��������BLACKCHESS---�����ʤ��WHITECHESS---�����ʤ
*/
int Gobang::isOverWithRestricted()
{
	// true��ʾ�н���
	return isOver(true);
}

/*
	�ж���Ϸ�Ƿ�������޽���

	@author Ӧ��Ң
	@return ChessType   NOCHESS---��ʤ��������BLACKCHESS---�����ʤ��WHITECHESS---�����ʤ
*/
int Gobang::isOverWithoutRestricted()
{
	// false��ʾ�޽���
	return isOver(false);
}

/*
	�ж���Ϸ�Ƿ����

	@author Ӧ��Ң
	@return ChessType   NOCHESS---��ʤ��������BLACKCHESS---�����ʤ��WHITECHESS---�����ʤ
*/
int Gobang::isOver(bool isRestricted)
{
	Step s = steps->back();
	int sign = (turn + 1) % 2;										// sign----�������
	int result[4] = { -1,-1,-1,-1 }, model[4] = { -1,-1,-1,-1 };	// result---������Ŀ��model---����

	for (int i = 0; i < 4; i++)
		cModel[i] = -1;


	/* ------------------------------------------------------------- */

	if (!isRestricted) {
		result[0] = searchNumOfChess(1, 0, 0, isRestricted);		// ��ֱ���ң�0---��ֱ
		if (result[0] == 5)
			return turn;

		result[1] = searchNumOfChess(0, 1, 1, isRestricted);		// ˮƽ���ң�1---ˮƽ
		if (result[1] == 5)
			return turn;

		result[2] = searchNumOfChess(1, 1, 2, isRestricted);		// ���Խ��߲��ң�2---���Խ���
		if (result[2] == 5)
			return turn;

		result[3] = searchNumOfChess(1, -1, 3, isRestricted);		// ���Խ��߲��ң�3---���Խ���
		if (result[3] == 5)
			return turn;
	}
	else {
		result[0] = searchNumOfChess(1, 0, 0, isRestricted);		// ��ֱ���ң�0---��ֱ
		if (result[0] > 5) {										// ��������
			if (turn == ChessType::BLACKCHESS)
				return sign;
			else
				return turn;
		}
		else if (result[0] == 5)
			return turn;
		model[0] = getChessModel(0);								// ��ֱ����

		result[1] = searchNumOfChess(0, 1, 1, isRestricted);		// ˮƽ���ң�1---ˮƽ
		if (result[1] > 5) {										// ��������
			if (turn == ChessType::BLACKCHESS)
				return sign;
			else
				return turn;
		}
		else if (result[1] == 5)
			return turn;
		model[1] = getChessModel(1);								// ˮƽ����
		if (judgeRestricted(model[0], model[1]))
			return sign;

		result[2] = searchNumOfChess(1, 1, 2, isRestricted);		// ���Խ��߲��ң�2---���Խ���
		if (result[2] > 5) {										// ��������
			if (turn == ChessType::BLACKCHESS)
				return sign;
			else
				return turn;
		}
		else if (result[2] == 5)
			return turn;
		model[2] = getChessModel(2);								// ���Խ�������
		if (judgeRestricted(model[0], model[2]))
			return sign;
		else if (judgeRestricted(model[1], model[2]))
			return sign;

		result[3] = searchNumOfChess(1, -1, 3, isRestricted);		// ���Խ��߲��ң�3---���Խ���
		if (result[3] > 5) {										// ��������
			if (turn == ChessType::BLACKCHESS)
				return sign;
			else
				return turn;
		}
		else if (result[3] == 5)
			return turn;
		model[3] = getChessModel(3);								// ���Խ�������
		if (judgeRestricted(model[0], model[3]))
			return sign;
		else if (judgeRestricted(model[1], model[3]))
			return sign;
		else if (judgeRestricted(model[2], model[3]))
			return sign;
	}

	return ChessType::NOCHESS;
}

/*
	�ж���������

	@para m---ˮƽ���ң�n---��ֱ���ң�temp---���ҷ���
	@author Ӧ��Ң
	@return
*/
int Gobang::searchNumOfChess(int m, int n, int temp, bool isRestricted)
{
	Step s = steps->back();
	int i, j;												// i---x���꣬j---y����
	int chessTypeNow = (turn + 1) % 2;						// chessTypeNow----��ǰ�������
	int chessNum = -1;										// chessNum---��ͬ������Ŀ

	if (!isRestricted || turn == ChessType::WHITECHESS) {
		// ���ҷ����·�ɨ�� 
		i = s.x;
		j = s.y;
		while (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH && board[i][j] == turn) {
			i += m;
			j += n;
			chessNum++;
		}

		// ���󷽼��Ϸ�ɨ��
		i = s.x;
		j = s.y;
		while (i >= 0 && j >= 0 && j < BOARDLENGTH && board[i][j] == turn) {
			i -= m;
			j -= n;
			chessNum++;
		}
	}
	else {
		/*int blankNum = 0, otherNum = 0;						// blankNum---��λ��Ŀ��otherNum---��ͬɫ������
		int blankOtherChessNum = 0;							// blankOtherChessNum---��λ��һ��λ�ò�ͬɫ������
		int blankChessNum1 = 0, blankChessNum2 = 0;			// blankChessNum---��λ��ͬɫ������
		int boardNum = 0;									// ǽ

		// ���ҷ����·�ɨ��
		i = s.x;
		j = s.y;
		while (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH && board[i][j] == turn) {
			i += m;
			j += n;
			chessNum++;
		}
		if (board[i][j] == ChessType::NOCHESS) {         // �ж��ҷ����·��Ƿ��п�λ��
			blankNum++;
			i += m;
			j += n;
			if (board[i][j] == chessTypeNow) {
				if (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH)
					blankOtherChessNum++;
			}
			else if (board[i][j] == turn) {
				if (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH) {
					blankChessNum1++;
					i += m;
					j += n;
					if (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH)
						if (board[i][j] == chessTypeNow)
							blankOtherChessNum++;
				}
			}
			else if (i >= BOARDLENGTH || j < 0 || j >= BOARDLENGTH)
				boardNum++;
		}
		else
			otherNum++;

		// ���󷽼��Ϸ�ɨ��
		i = s.x;
		j = s.y;
		while (i >= 0 && j >= 0 && j < BOARDLENGTH && board[i][j] == turn) {
			i -= m;
			j -= n;
			chessNum++;
		}
		if (board[i][j] == ChessType::NOCHESS) {        // �ж��󷽻��Ϸ��Ƿ��п�λ��
			blankNum++;
			i -= m;
			j -= n;
			if (board[i][j] == chessTypeNow) {
				if (i >= 0 && j >= 0 && j < BOARDLENGTH)
					blankOtherChessNum++;
			}
			else if (board[i][j] == turn) {
				if (i >= 0 && j >= 0 && j < BOARDLENGTH) {
					blankChessNum2++;
					i -= m;
					j -= n;
					if (i >= 0 && j >= 0 && j < BOARDLENGTH)
						if (board[i][j] == chessTypeNow)
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
			setChessModel(ChessModel::LIVETHREE, temp);		// ����
		else if (chessNum + blankChessNum2 == 3 && blankOtherChessNum + boardNum < 2 && otherNum == 0)
			setChessModel(ChessModel::LIVETHREE, temp);		// ����
		else if (chessNum == 4 && otherNum == 0)
			setChessModel(ChessModel::LIVEFOUR, temp);		// ����
		else if (chessNum == 4 && otherNum == 1)
			setChessModel(ChessModel::CHONGFOUR, temp);		// ����
		else if (chessNum + blankChessNum1 == 4)
			setChessModel(ChessModel::CHONGFOUR, temp);		// ����
		else if (chessNum + blankChessNum1 == 4)
			setChessModel(ChessModel::CHONGFOUR, temp);		// ����
		*/

		/*  lchess[0] ��ʾ(y, x) ��ߵ�����(y, x) ����������ͬ������Ŀ��
		lempty[0] ��ʾ(y, x) ��ߵ�һ���յ�����������յ���Ŀ
		lchess[1] ��ʾ(y, x) ��ߵ�����(y, x) ���ٸ�һ���յ������ͬ������Ŀ
		lempty[1] ��ʾ�� lchess[1] ��ͬ������ߵ������յ���Ŀ

		rchess��remptyͬ��
		ͬ������Ϊ����Ϊ��
		*/
		int lchess[2], rchess[2];
		int lempty[2], rempty[2];
		int i, j;											// i---x���꣬j---y����

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
				setChessModel(ChessModel::LIVEFOUR, temp);		// ����
			else if (lempty[0] + rempty[0])
				setChessModel(ChessModel::CHONGFOUR, temp);		// ����
		}
		else if (chessNum == 3) {
			int ok = 0;        // ͬһ��������������γɻ����ͳ��ģ���������  
			if ((lempty[0] == 1 && lchess[1] >= 1) || (rempty[0] == 1 && rchess[1] >= 1)) {
				setChessModel(ChessModel::CHONGFOUR, temp);		// ����
				ok = 1;
			}
			if (!ok && lempty[0] + rempty[0] >= 3 && lempty[0] >= 1 && rempty[0] >= 1)
				setChessModel(ChessModel::LIVETHREE, temp);		// ����
		}
		else if (chessNum == 2) {
			int ok = 0;
			if ((lempty[0] == 1 && lchess[1] >= 2) || (rempty[0] == 1 && rchess[1] >= 2)) {
				setChessModel(ChessModel::CHONGFOUR, temp);		// ����
				ok = 1;
			}
			if (!ok && ((lempty[0] == 1 && lchess[1] == 1 && rempty[0] >= 1 && lempty[1] >= 1) || (rempty[0] == 1 && rchess[1] == 1 && lempty[0] >= 1 && rempty[1] >= 1)))
				setChessModel(ChessModel::LIVETHREE, temp);		// ����
		}
		else if (chessNum == 1) {
			int ok = 0;
			if ((lempty[0] == 1 && lchess[1] >= 3) || (rempty[0] == 1 && rchess[1] >= 3)) {
				setChessModel(ChessModel::CHONGFOUR, temp);		// ����
				ok = 1;
			}
			if (!ok && ((lempty[0] == 1 && lchess[1] == 2 && rempty[0] >= 1 && lempty[1] >= 1) || (rempty[0] == 1 && rchess[1] == 2 && lempty[0] >= 1 && rempty[1] >= 1)))
				setChessModel(ChessModel::LIVETHREE, temp);		// ����
		}
	}

	return chessNum;
}

/*
	��������

	@para model---����
	@author Ӧ��Ң
	@return
*/
void Gobang::setChessModel(int model, int temp)
{
	cModel[temp] = model;
}

/*
	�������

	@para m---ˮƽ���ң�n---��ֱ����
	@author Ӧ��Ң
	@return
*/
int Gobang::getChessModel(int temp)
{
	return cModel[temp];
}

/*
	�����Ƿ����

	@para model1---����1��model2---����2
	@author Ӧ��Ң
	@return bool  true---���֣�false---�ǽ���
*/
bool Gobang::judgeRestricted(int model1, int model2)
{
	if (model1 == ChessModel::LIVETHREE && model2 == ChessModel::LIVETHREE)
		return true;						// �������� ˫����
	else if (model1 == ChessModel::LIVEFOUR && model2 == ChessModel::LIVEFOUR)
		return true;						// ���Ľ��� ˫����
	else if (model1 == ChessModel::LIVEFOUR && model2 == ChessModel::CHONGFOUR)
		return true;						// ���Ľ��� ���ĳ���
	else if (model1 == ChessModel::CHONGFOUR && model2 == ChessModel::CHONGFOUR)
		return true;						// ���Ľ��� ˫����

	return false;
}