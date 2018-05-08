#ifndef GOBANG_H
#define GOBANG_H

#define BOARDLENGTH 19	// ���̳���

#include <queue>

class Gobang
{
public:
	Gobang();
	~Gobang();

	typedef struct Step
	{
		int x;
		int y;
	} Step;

	void initBoard();				// ��ʼ�����̻������������
	void newStep(Step step);		// ��һ����
	Step AIWalk(int type);					// ��������

	int isOver();					// �ж���Ϸ�Ƿ�������񷵻�ChessType::NOCHESS, �Ƿ������Ӷ�Ӧö��
	bool isBanned();                // �ж��Ƿ���ڽ��֣��񷵻�false���Ƿ���true

	void saveBoard(char * path);	// �����̱��浽�ļ���
	void loadBoard(char * path);	// ���ļ����ȡ����

	int getTurn();					// ���ص�ǰ�ִ�
	std::deque<Step> getSteps();	// ���ش�������˳���˫�˶���


private:

	int board[BOARDLENGTH][BOARDLENGTH];	// ������Ϣ
	int turn;								// �ִ�

	std::deque<Step> * steps;				// ��������˳���˫�˶���

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

#endif // !GOBANG_H
