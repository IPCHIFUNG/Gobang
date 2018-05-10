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
	Step AIWalk(int type);			// ��������

	int isOverWithRestricted();     // �ж���Ϸ�Ƿ�������񷵻�ChessType::NOCHESS, �Ƿ������Ӷ�Ӧö�٣��н���
	int isOverWithoutRestricted();  // �ж���Ϸ�Ƿ�������񷵻�ChessType::NOCHESS, �Ƿ������Ӷ�Ӧö�٣��޽���

	void saveBoard(char * path);	// �����̱��浽�ļ���
	void loadBoard(char * path);	// ���ļ����ȡ����

	int getTurn();					// ���ص�ǰ�ִ�
	std::deque<Step> getSteps();	// ���ش�������˳���˫�˶���
	std::deque<Step> getOverSteps();// ���ش��浼����Ϸ����������λ�õ�˫�˶���


private:

	int board[BOARDLENGTH][BOARDLENGTH];	// ������Ϣ
	int turn;								// �ִ�

	std::deque<Step> * steps;				// ��������˳���˫�˶���
	std::deque<Step> * overSteps;			// ���浼����Ϸ����������λ��

	int isOver(bool isRestricted);			// �ж���Ϸ�Ƿ�������񷵻�ChessType::NOCHESS, �Ƿ������Ӷ�Ӧö��

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
