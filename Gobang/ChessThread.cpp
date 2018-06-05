#include "ChessThread.h"

ChessThread::ChessThread(MainWindow & mwin, int t) :MWin(mwin)
{
	type = t;
}

void ChessThread::run()
{
	switch (MWin.getGameType())
	{
	case GameType::PVE:
		switch (type)
		{
		case PlayerType::HUMAN:
			step = MWin.getStepFromScreen();
			break;
		case PlayerType::AI:
			step = MWin.getGobang().AIWalk(MWin.getGobang().getTurn());
			break;
		default:
			break;
		}
		break;
	case GameType::PVP:
		step = MWin.getStepFromScreen();
		break;
	case GameType::ONLINE:
		step = MWin.getStepFromScreen();
		MWin.s->msg_send(step.x, step.y, 1);
		step = MWin.s->getRecv_mes_step();
		break;
	default:
		break;
	}
	MWin.getGobang().newStep(step);
	MWin.showStep(step, MWin.getGobang().getTurn());
	MWin.highlightStep(step, MWin.getGobang().getTurn());
	MWin.getGobang().shiftTurn();
	MWin.playSoundEffects();

	switch (MWin.getIsRestricted())
	{
	case QMessageBox::Yes:
		MWin.setWinner(MWin.getGobang().isOverWithRestricted());
		break;
	case QMessageBox::No:
		MWin.setWinner(MWin.getGobang().isOverWithoutRestricted());
		break;
	default:
		break;
	}
}