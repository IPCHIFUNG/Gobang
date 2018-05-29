#include "ChessThread.h"

ChessThread::ChessThread(MainWindow & mwin, Gobang & gb, int t) :MWin(mwin), gobang(gb)
{
	type = t;
}

void ChessThread::run()
{
	switch (type)
	{
	case PlayerType::HUMAN:
		step = MWin.getStepFromScreen();
		break;
	case PlayerType::AI:
		step = gobang.AIWalk(gobang.getTurn());
		break;
	default:
		break;
	}
		gobang.newStep(step);
		MWin.showStep(step, gobang.getTurn());
		gobang.shiftTurn();
		MWin.playSoundEffects();
		MWin.highlightStep(step);
}