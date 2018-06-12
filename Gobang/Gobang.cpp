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

std::deque<Gobang::Step> & Gobang::getWinModel()
{
	return *winnerSteps;
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
	�����Ѷ�

	* dif = 1  ����  �����Ѷ�
	* dif = 2  ����  �м��Ѷ�
	* dif = 3  ����  �߼��Ѷ�

	@para dif---�Ѷȵȼ�
	@author Ӧ��Ң
*/
void Gobang::setDifficulty(int dif)
{
	AIutil->DEPTH = 2 + 2 * dif;
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
		int DEPTH = AIutil->DEPTH;								// �������
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

	winnerSteps = new std::deque<Step>();

	for (int i = 0; i < 4; i++)
		cModel[i] = -1;


	/* ------------------------------------------------------------- */

	if (!isRestricted || turn == ChessType::WHITECHESS) {
		result[0] = searchNumOfChess(1, 0, 0, isRestricted);		// ��ֱ���ң�0---��ֱ
		if (result[0] == 5) {
			setWinnerModel(0, turn);
			return turn;
		}

		result[1] = searchNumOfChess(0, 1, 1, isRestricted);		// ˮƽ���ң�1---ˮƽ
		if (result[1] == 5) {
			setWinnerModel(1, turn);
			return turn;
		}

		result[2] = searchNumOfChess(1, 1, 2, isRestricted);		// ���Խ��߲��ң�2---���Խ���
		if (result[2] == 5) {
			setWinnerModel(2, turn);
			return turn;
		}

		result[3] = searchNumOfChess(1, -1, 3, isRestricted);		// ���Խ��߲��ң�3---���Խ���
		if (result[3] == 5) {
			setWinnerModel(3, turn);
			return turn;
		}
	}
	else {
		result[0] = searchNumOfChess(1, 0, 0, isRestricted);		// ��ֱ���ң�0---��ֱ
		if (result[0] > 5) {										// ��������
			setBanModel(0, -1, 0);
			return sign;
		}
		else if (result[0] == 5) {									// �������
			setWinnerModel(0, turn);
			return turn;
		}

		model[0] = getChessModel(0);								// ��ֱ����

		result[1] = searchNumOfChess(0, 1, 1, isRestricted);		// ˮƽ���ң�1---ˮƽ
		if (result[1] > 5) {										// ��������
			setBanModel(1, -1, 0);
			return sign;
		}
		else if (result[1] == 5) {									// �������
			setWinnerModel(1, turn);
			return turn;
		}
		model[1] = getChessModel(1);								// ˮƽ����
		if (judgeRestricted(model[0], model[1])) {
			setBanModel(0, 1, 1);
			return sign;
		}


		result[2] = searchNumOfChess(1, 1, 2, isRestricted);		// ���Խ��߲��ң�2---���Խ���
		if (result[2] > 5) {										// ��������
			setBanModel(2, -1, 0);
			return sign;
		}
		else if (result[2] == 5) {									// �������
			setWinnerModel(2, turn);
			return turn;
		}
		model[2] = getChessModel(2);								// ���Խ�������
		if (judgeRestricted(model[0], model[2])) {
			setBanModel(0, 2, 1);
			return sign;
		}
		else if (judgeRestricted(model[1], model[2])) {
			setBanModel(1, 2, 1);
			return sign;
		}

		result[3] = searchNumOfChess(1, -1, 3, isRestricted);		// ���Խ��߲��ң�3---���Խ���
		if (result[3] > 5) {										// ��������
			setBanModel(3, -1, 0);
			return sign;
		}
		else if (result[3] == 5) {									// �������
			setWinnerModel(3, turn);
			return turn;
		}
		model[3] = getChessModel(3);								// ���Խ�������
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
	���û�ʤ����

	@para direction---���ҷ���type---��ɫ����
	@author Ӧ��Ң
*/
void Gobang::setWinnerModel(int direction, int type)
{
	Step last_step = steps->back();		// ���һ��
	int i, j;							// ��������
	int m, n;							// ɨ�跽��

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

	// ���ҷ����·�ɨ�� 
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

	// ���󷽼��Ϸ�ɨ��
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
	���ý�������

	@para dir1---���ҷ���1��dir2---���ҷ���2��ban_model---��������
	@author Ӧ��Ң
*/
void Gobang::setBanModel(int dir1, int dir2, int ban_model)
{
	if (ban_model == 0)
		setWinnerModel(dir1, (turn + 1) % 2);
	else {
		int dir = dir1;
		int judge = 0;
		while (judge < 2) {
			Step last_step = steps->back();		// ���һ��
			int m, n;							// ɨ�跽��

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
			lchess[0] ��ʾ(y, x) ��ߵ�����(y, x) ����������ͬ������Ŀ��
			lempty[0] ��ʾ(y, x) ��ߵ�һ���յ�����������յ���Ŀ
			lchess[1] ��ʾ(y, x) ��ߵ�����(y, x) ���ٸ�һ���յ������ͬ������Ŀ
			lempty[1] ��ʾ�� lchess[1] ��ͬ������ߵ������յ���Ŀ

			rchess��remptyͬ��
			ͬ������Ϊ����Ϊ��
			*/
			int lchess[2], rchess[2];
			int lempty[2], rempty[2];
			int i, j;											// i---x���꣬j---y����
			int chessNum = 0;									// ͬɫ������Ŀ

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
				int ok = 0;        // ͬһ��������������γɻ����ͳ��ģ���������  
				if ((lempty[0] == 1 && lchess[1] >= 1) || (rempty[0] == 1 && rchess[1] >= 1)) {
					Gobang::Step temp1, temp2;												// ����
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
					Gobang::Step temp1, temp2;												// ����
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
					Gobang::Step temp1, temp2;												// ����
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
					Gobang::Step temp1, temp2;												// ����
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
					Gobang::Step temp1, temp2;												// ����
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
					Gobang::Step temp1, temp2;												// ����
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
	else if (model1 == ChessModel::CHONGFOUR && model2 == ChessModel::LIVEFOUR)
		return true;						// ���Ľ��� ���ĳ���
	else if (model1 == ChessModel::CHONGFOUR && model2 == ChessModel::CHONGFOUR)
		return true;						// ���Ľ��� ˫����

	return false;
}