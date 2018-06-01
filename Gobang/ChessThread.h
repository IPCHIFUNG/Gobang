#pragma once

#include "MainWindow.h"
#include <Qthread>

class MainWindow;
class Gobang;

class ChessThread :public QThread
{
public:
	ChessThread(MainWindow & mwin, Gobang & gb, int t);
	void run();
private:
	MainWindow & MWin;
	Gobang & gobang;
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