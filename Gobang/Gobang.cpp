#include <stdio.h>
#include "Gobang.h"

Gobang::Gobang()
{
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
	turn = ChessType::BLACKCHESS;
	// ��ʼ��˫�˶���
	steps = new std::deque<Step>();
	overSteps = new std::deque<Step>();
}

/*
	�����̱��浽�ļ���

	@author Ҷ־��
	@para ����·��
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
	���ļ����ȡ����

	@author Ҷ־��
	@para ����·��
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
std::deque<Gobang::Step> Gobang::getSteps()
{
	return *steps;
}

/*
	���ص�����Ϸ����������λ�õ�˫�˶���

	@author Ӧ��Ң
	@return ˫�˶���
*/
std::deque<Gobang::Step> Gobang::getOverSteps()
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

	steps->push_back(step);

	turn = (turn + 1) % 2;
}

/*
	�˻���ս

	@author Ӧ��Ң
	@return ����Step���͵�����
*/
Gobang::Step Gobang::AIWalk(int type)
{
	if (type != ChessType::BLACKCHESS || type != ChessType::WHITECHESS)
		throw "The chess type does not existing";





	return Step();
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
	int sign = (turn + 1) % 2;						// sign----�������
	int result[4] = { -1,-1,-1,-1 }, model[4] = { -1,-1,-1,-1 };	// result---������Ŀ��model---����


/* ------------------------------------------------------------- */

	if (!isRestricted) {
		result[0] = searchNumOfChess(1, 0, 0);		// ��ֱ���ң�0---��ֱ
		if (result[0] == 5)
			return sign;

		result[1] = searchNumOfChess(0, 1, 1);		// ˮƽ���ң�1---ˮƽ
		if (result[1] == 5)
			return sign;

		result[2] = searchNumOfChess(1, 1, 2);		// ���Խ��߲��ң�2---���Խ���
		if (result[2] == 5)
			return sign;

		result[3] = searchNumOfChess(1, -1, 3);		// ���Խ��߲��ң�3---���Խ���
		if (result[3] == 5)
			return sign;
	}
	else {
		result[0] = searchNumOfChess(1, 0, 0);		// ��ֱ����,0---��ֱ
		if (result[0] == 5)
			return sign;
		else if (result[0] > 5)						// ��������
			return turn;
		model[0] = getChessModel(0);				// ��ֱ����

		result[1] = searchNumOfChess(0, 1,1);		// ˮƽ���ң�1---ˮƽ
		if (result[1] == 5)
			return sign;
		else if (result[0] > 5)						// ��������
			return turn;
		model[1] = getChessModel(1);				// ˮƽ����
		if (judgeRestricted(model[0], model[1]))
			return turn;

		result[2] = searchNumOfChess(1, 1,2);		// ���Խ��߲��ң�2---���Խ���
		if (result[2] == 5)
			return sign;
		else if (result[0] > 5)						// ��������
			return turn;
		model[2] = getChessModel(2);				// ���Խ�������
		if (judgeRestricted(model[0], model[2]))
			return turn;
		else if (judgeRestricted(model[1], model[2]))
			return turn;

		result[3] = searchNumOfChess(1, -1,3);		// ���Խ��߲��ң�3---���Խ���
		if (result[3] == 5)
			return sign;
		else if (result[0] > 5)						// ��������
			return turn;
		model[3] = getChessModel(3);				// ���Խ�������
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
	�ж���������

	@para m---ˮƽ���ң�n---��ֱ���ң�temp---���ҷ���
	@author Ӧ��Ң
	@return
*/
int Gobang::searchNumOfChess(int m, int n, int temp)
{
	Step s = steps->back();
	int i, j;												// i---x���꣬j---y����
	int chessNum = -1, blankNum = 0, otherNum = 0;			// chessNum---��ͬ������Ŀ��blankNum---��λ��Ŀ��otherNum---��ͬɫ������
	int blankOtherChessNum = 0;								// blankOtherChessNum---��λ��һ��λ�ò�ͬɫ������
	int blankChessNum1 = 0, blankChessNum2 = 0;				// blankChessNum---��λ��ͬɫ������
	int chessTypeNow = (turn + 1) % 2;						// chessTypeNow----��ǰ�������



	// ���ҷ����·�ɨ�� 
	i = s.x;
	j = s.y;
	while (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH && board[i][j] == chessTypeNow) {
		i += m;
		j += n;
		chessNum++;
	}
	if (board[i][j] == ChessType::NOCHESS) {         // �ж��ҷ����·��Ƿ��п�λ��
		blankNum++;
		i += m;
		j += n;
		if (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH && board[i][j] == turn)
			blankOtherChessNum++;
		else if (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH && board[i][j] == chessTypeNow) {
			blankChessNum1++;
			i += m;
			j += n;
			if (i < BOARDLENGTH && j >= 0 && j < BOARDLENGTH && board[i][j] == turn)
				blankOtherChessNum++;
		}
	}
	else
		otherNum++;

	// ���󷽼��Ϸ�ɨ��
	i = s.x;
	j = s.y;
	while (i >= 0 && j >= 0 && j < BOARDLENGTH && board[i][j] == chessTypeNow) {
		i -= m;
		j -= n;
		chessNum++;
	}
	if (board[i][j] == ChessType::NOCHESS) {        // �ж��󷽻��Ϸ��Ƿ��п�λ��
		blankNum++;
		i -= m;
		j -= n;
		if (i >= 0 && j >= 0 && j < BOARDLENGTH && board[i][j] == turn)
			blankOtherChessNum++;
		else if (i >= 0 && j >= 0 && j < BOARDLENGTH && board[i][j] == chessTypeNow) {
			blankChessNum2++;
			i -= m;
			j -= n;
			if (i >= 0 && j >= 0 && j < BOARDLENGTH && board[i][j] == turn)
				blankOtherChessNum++;
		}
	}
	else
		otherNum++;

	if (chessNum == 5)
		return chessNum;

	if ((chessNum + blankChessNum1 == 3 || chessNum + blankChessNum2 == 3) && otherNum + blankOtherChessNum < 2)
		setChessModel(ChessModel::LIVETHREE, temp);		// ����
	else if (4 == chessNum && otherNum == 0)
		setChessModel(ChessModel::LIVEFOUR, temp);		// ����
	else if ((chessNum == 4 && otherNum == 1) || chessNum + blankChessNum1 == 4 || chessNum + blankChessNum1 == 4)
		setChessModel(ChessModel::CHONGFOUR, temp);		// ����


	return chessNum;
}

/*
	��������

	@para model---����
	@author Ӧ��Ң
	@return
*/
void Gobang::setChessModel(int model,int temp)
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