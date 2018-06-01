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
	玩家或电脑落子类型

	@author 王开阳
*/
const enum PlayerType
{
	HUMAN,	// 玩家
	AI		// 电脑
};