#pragma once

#include "MainWindow.h"
#include <Qthread>

class MainWindow;

class ChessThread :public QThread
{
public:
	ChessThread(MainWindow & mwin, int t);
	void run();
private:
	MainWindow & MWin;
	int type;
	Gobang::Step step;
};

/*
	��һ������������

	@author ������
*/
const enum PlayerType
{
	HUMAN,	// ���
	AI		// ����
};