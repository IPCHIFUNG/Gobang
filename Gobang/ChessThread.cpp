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

		int result;
		switch (MWin.isRestricted)
		{
		case QMessageBox::Yes:
			result = gobang.isOverWithRestricted();
			break;
		case QMessageBox::No:
			result = gobang.isOverWithoutRestricted();
			break;
		default:
			break;
		}

		switch (result)
		{
		case ChessType::BLACKCHESS:
			MWin.showWinnerDialog(ChessType::BLACKCHESS);
			disconnect(MWin.ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
			break;
		case ChessType::WHITECHESS:
			MWin.showWinnerDialog(ChessType::WHITECHESS);
			disconnect(MWin.ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
			break;
		case ChessType::NOCHESS:
			if (gobang.getSteps().size() == BOARDLENGTH * BOARDLENGTH)
			{
				MWin.showWinnerDialog(ChessType::NOCHESS);
				disconnect(MWin.ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
			}
			break;
		default:
			break;
		}
}