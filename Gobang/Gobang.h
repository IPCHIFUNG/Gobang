#ifndef GOBANG_H
#define GOBANG_H

#define BOARDLENGTH 19	// ���̳���

class Gobang
{
public:
	Gobang();
	~Gobang();

	void initBoard();	// ��ʼ�����̻������������

private:

	// ������Ϣ
	ChessType board[BOARDLENGTH][BOARDLENGTH];

};

/*
	�����ϵ���������

	@author Ҷ־��
*/
const enum ChessType
{
	NOCHESS,	// ����
	BLACKCHESS,	// ����
	WHITECHESS	// ����
};





#endif // !GOBANG_H
