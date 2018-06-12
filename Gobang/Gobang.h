#ifndef GOBANG_H
#define GOBANG_H

#define BOARDLENGTH 19	// ���̳���
#define INF 9000000

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

private:

	int board[BOARDLENGTH][BOARDLENGTH];	// ������Ϣ
	int turn;								// �ִ�
	int cModel[4];							// ����
	AIUtil *AIutil;							// AI
	std::deque<rank> * rankings;			// ���а�
	std::deque<Step> * steps;				// ��������˳���˫�˶���
	std::deque<Step> * overSteps;			// ���浼����Ϸ����������λ��

	int isOver(bool isRestricted);			// �ж���Ϸ�Ƿ�������񷵻�ChessType::NOCHESS, �Ƿ������Ӷ�Ӧö��
	int searchNumOfChess(int m, int n, int temp, bool isRestricted);     // �ж�������
	void setChessModel(int model, int temp);	// ��������
	int getChessModel(int temp);			// �������

	bool judgeRestricted(int model1, int model2);	// �ж�����

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
