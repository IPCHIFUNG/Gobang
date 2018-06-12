#ifndef GOBANG_H
#define GOBANG_H

#define BOARDLENGTH 19	// ���̳���
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

	void initBoard();						// ��ʼ�����̻������������
	void newStep(Step step);				// ��һ����
	Step popLastStep();						// �������һ����
	void shiftTurn();						// ��������
	void setDifficulty(int dif);			// �����Ѷ�	
	Step AIWalk(int type);					// ��������

	int isOverWithRestricted();				// �ж���Ϸ�Ƿ�������񷵻�ChessType::NOCHESS, �Ƿ������Ӷ�Ӧö�٣��н���
	int isOverWithoutRestricted();			// �ж���Ϸ�Ƿ�������񷵻�ChessType::NOCHESS, �Ƿ������Ӷ�Ӧö�٣��޽���

	void saveBoard(char * path);			// �����̱��浽�ļ���
	void loadBoard(char * path);			// ���ļ����ȡ����
	void readRanking();						// ��ȡ���а�
	void writeRanking();					// �������а�
	void addRanking(std::string name, int n);	// ���������Ϣ

	int getTurn();							// ���ص�ǰ�ִ�
	int getAtPosition(int x, int y);		// ���أ�x, y��λ�õ�����
	std::deque<Step> & getSteps();			// ���ش�������˳���˫�˶���
	std::deque<Step> & getOverSteps();      // ���ش��浼����Ϸ����������λ�õ�˫�˶���
	std::deque<rank> & getRankings();		// �������а�
	std::deque<Step> & getWinModel();	// ���ص���ʤ��������

private:

	int board[BOARDLENGTH][BOARDLENGTH];								// ������Ϣ
	int turn;															// �ִ�
	int cModel[4];														// ����
	AIUtil *AIutil;														// AI
	std::deque<rank> * rankings;										// ���а�
	std::deque<Step> * steps;											// ��������˳���˫�˶���
	std::deque<Step> * overSteps;										// ���浼����Ϸ����������λ��
	std::deque<Step> * winnerSteps;										// ����ʤ������

	int isOver(bool isRestricted);										// �ж���Ϸ�Ƿ�������񷵻�ChessType::NOCHESS, �Ƿ������Ӷ�Ӧö��
	int searchNumOfChess(int m, int n, int temp, bool isRestricted);	// �ж�������
	bool judgeRestricted(int model1, int model2);						// �ж�����

	void setChessModel(int model, int temp);							// ��������
	int getChessModel(int temp);										// �������
	void setWinnerModel(int direction);									// ���û�ʤ����
	void setBanModel(int dir1, int dir2, int ban_model);				// ���ý�������

};

/*
	�����ϵ���������

	@author Ҷ־��
*/
const enum ChessType
{
	BLACKCHESS,	// ����
	WHITECHESS,	// ����
	NOCHESS		// ����
};

/*
	�����ϵ�����·��

	@author Ӧ��Ң
*/
const enum ChessModel
{
	LIVETHREE,	// ����
	LIVEFOUR,	// ����
	CHONGFOUR,	// ����
};

#endif // !GOBANG_H
