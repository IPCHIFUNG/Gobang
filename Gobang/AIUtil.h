#ifndef AIUTIL_H
#define AIUTIL_H


class AIUtil
{
public:
	AIUtil(int *board);
	~AIUtil();

	typedef struct AIStep
	{
		int x;
		int y;
	} AIStep;

	void cal_chess(AIStep steps, int m, int n, int type, bool isRestricted);

private:
	int *board;


	/* cpoint[i][j][0] ��ʾ���Ծ�ɱ����� */
	/* cpoint[i][j][1] ��ʾ��Ҿ�ɱ����� */
	/* cpoint[i][j][2] ��ʾ���Ե÷� */
	/* cpoint[i][j][3] ��ʾ��ҵ÷� */

	int cpoint[19][19][4];
	const int CHENG5 = 20000;		// ����
	const int LIVE4 = 2000;			// ����
	const int CHONG4 = 300;			// ������
	const int RCHONG4 = 250;		// ������
	const int LIVE3 = 450;			// ����
	const int RLIVE3 = 300;			// ����
	const int LIVE2 = 100;			// ���
	const int RLIVE2 = 70;			// ����
	const int MIAN3 = 50;			// ����
	const int DEAD4 = -10;			// ����
	const int DEAD3 = -10;			// ����
	const int DEAD2 = -10;			// ����
	const int inf = 9000000;		// 
	const int unknow = 9900000;		// 

	int getBoard(int x, int y);


};

const enum AIChessType
{
	AIBLACKCHESS,	// ����
	AIWHITECHESS,	// ����
	AINOCHESS		// ����
};

#endif // !AIUTIL_H

