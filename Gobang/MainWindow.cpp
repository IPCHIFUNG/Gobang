#include "MainWindow.h"
#include "ServerDialog.h"
#include "ServerMsgItem.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// ��ʼ��������
	this->setWindowTitle(QString::fromLocal8Bit("������"));
	this->setWindowIcon(QIcon(":/MainWindow/image/WHITE_64.ico"));
	this->setFixedSize(this->width(), this->height());

	// ��ʼ����ť
	setHomePageBtnVisable(true);
	setGamePageBtnVisable(false);

	// ��ʼ������
	blackChess = QPixmap("./image/BLACK.png");
	whiteChess = QPixmap("./image/WHITE.png");
	HLBlackChess = QPixmap("./image/BLACK(highlight).png");
	HLWhiteChess = QPixmap("./image/WHITE(highlight).png");
	for (int i = 0; i < BOARDLENGTH; i++)
		for (int j = 0; j < BOARDLENGTH; j++)
		{
			chess[i][j].setParent(ui.centralWidget);
			chess[i][j].setGeometry(357 + j * 47, 7 + i * 47, 42, 42);
		}
	ui.btn_chessboard->raise();

	connect(&computer, SIGNAL(showInf(int, int, int)), this, SLOT(showInf(int, int, int)));
	connect(&computer, SIGNAL(showWinnerDialog()), this, SLOT(showWinnerDialog()));

	// ��ȡ���ֺ���Ч
	music.setMedia(QUrl::fromLocalFile("./sound/FlowerDance.mp3"));
	soundEff.setMedia(QUrl::fromLocalFile("./sound/b.mp3"));
	music.play();
	isMusicOn = true;

	gobang = Gobang();
	gobang.readRanking();
	gameType = GameType::NONE;
	winner = ChessType::NOCHESS;
}

/*
	�������

	@author Ҷ־��
*/
void MainWindow::clearBoard()
{
	// ��ʼ���������ӱ�����Ϣ
	Gobang::Step temp; temp.x = -1; temp.y = -1;
	highlightStep(temp, -2);
	// ��������
	std::deque<Gobang::Step> &steps = gobang.getSteps();
	while (!steps.empty())
	{
		chess[steps.front().x][steps.front().y].setPixmap(QPixmap(""));
		steps.pop_front();
	}
}

/*
	����������

	@author Ҷ־��
*/
void MainWindow::walkAStep(Gobang::Step new_step)
{
	gobang.newStep(new_step);
	showStep(new_step, gobang.getTurn());
	highlightStep(new_step, gobang.getTurn());
	playSoundEffects();
	showInf(gobang.getTurn(), new_step.x, new_step.y);
	switch (isRestricted)
	{
	case QMessageBox::Yes:
		winner = gobang.isOverWithRestricted();
		break;
	case QMessageBox::No:
		winner = gobang.isOverWithoutRestricted();
		break;
	default:
		break;
	}
	showWinnerDialog();
	if (winner != ChessType::NOCHESS)
	{
		gameType = GameType::NONE;
		return;
	}
	gobang.shiftTurn();
}

/*
	��ʾ������Ϣ

	@author ������
*/
void MainWindow::showInf(int color, int x, int y)
{
	QString s = ui.text_chessinf->toPlainText();
	switch (color)
	{
	case ChessType::BLACKCHESS:
		s += QString::fromLocal8Bit("����------------( ") + QString::number(x) + " , " + QString::number(y) + " )\n";
		break;
	case ChessType::WHITECHESS:
		s += QString::fromLocal8Bit("����------------( ") + QString::number(x) + " , " + QString::number(y) + " )\n";
		break;
	default:
		break;
	}
	ui.text_chessinf->setText(s);
	QTextCursor cursor = ui.text_chessinf->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui.text_chessinf->setTextCursor(cursor);
}

/*
	ɾ��������Ϣ

	@author ������
*/
void MainWindow::delInf()
{
	QString s = ui.text_chessinf->toPlainText();
	for (int i = s.length() - 2; i > 0; i--)
		if (s[i] == '\n')
		{
			s = s.left(i + 1);
			break;
		}
	ui.text_chessinf->setText(s);
	QTextCursor cursor = ui.text_chessinf->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui.text_chessinf->setTextCursor(cursor);
}

/*
	��ʾһ����

	@author ������
	@para step - ��һ������
	@para type - ��һ����������
*/
void MainWindow::showStep(Gobang::Step step, int type)
{
	if (step.x < 0 || step.x > BOARDLENGTH)
		throw "step.x is out of range";
	if (step.y < 0 || step.y > BOARDLENGTH)
		throw "step.y is out of range";
	if (type != ChessType::BLACKCHESS && type != ChessType::WHITECHESS)
		throw "Invalid type";
	switch (type)
	{
	case ChessType::BLACKCHESS:
		chess[step.x][step.y].setPixmap(blackChess);
		break;
	case ChessType::WHITECHESS:
		chess[step.x][step.y].setPixmap(whiteChess);
		break;
	default:
		chess[step.x][step.y].setPixmap(QPixmap(""));
		break;
	}
}

/*
	��������

	@author Ҷ־��
	@para step - ��Ҫ����������
	@para type - ��Ҫ��������������
*/
void MainWindow::highlightStep(Gobang::Step step, int type)
{
	static int x = -1;
	static int y = -1;
	static int last_type = -1;
	if (-2 == type)
	{
		x = -1; y = -1; last_type = -1;
		return;
	}
	if (-1 != x && -1 != y && -1 != last_type)
	{
		if (ChessType::BLACKCHESS == last_type)
			chess[x][y].setPixmap(blackChess);
		else if (ChessType::WHITECHESS == last_type)
			chess[x][y].setPixmap(whiteChess);
		else
			chess[x][y].setPixmap(QPixmap(""));
	}
	if (step.x < 0 || step.x > BOARDLENGTH)
		throw "step.x is out of range";
	if (step.y < 0 || step.y > BOARDLENGTH)
		throw "step.y is out of range";
	if (type != ChessType::BLACKCHESS && type != ChessType::WHITECHESS)
		throw "Invalid type";
	x = step.x;
	y = step.y;
	last_type = type;
	switch (type)
	{
	case ChessType::BLACKCHESS:
		chess[step.x][step.y].setPixmap(HLBlackChess);
		break;
	case ChessType::WHITECHESS:
		chess[step.x][step.y].setPixmap(HLWhiteChess);
		break;
	default:
		chess[step.x][step.y].setPixmap(QPixmap(""));
		break;
	}
}

/*
	��������Ⱥ

	@author Ҷ־��
	@para step - ��Ҫ����������Ⱥ
*/
void MainWindow::highlightSteps(std::deque<Gobang::Step> steps, int color)
{
	QPixmap *pixmap = color == ChessType::BLACKCHESS ? &HLBlackChess : &HLWhiteChess;
	while (steps.size() > 0)
	{
		Gobang::Step temp = steps.back();
		steps.pop_back();
		chess[temp.x][temp.y].setPixmap(*pixmap);
	}
	pixmap = NULL;
}

/*
	��ʾ���а�

	@author ������
*/
void MainWindow::showRankings()
{
	std::string names = "", steps = "";
	for (auto it = gobang.getRankings().begin(); it != gobang.getRankings().end(); it++)
	{
		names += it->name + " ---" + "\n";
		steps += "--- " + to_string(it->n) + "\n";
	}
	ui.lbl_names->setText(QString::fromStdString(names));
	ui.lbl_steps->setText(QString::fromStdString(steps));
}

/*
	����������Ч

	@author ������
*/
void MainWindow::playSoundEffects()
{
	soundEff.stop();
	soundEff.play();
}

/*
	������ҳ��ť�Ŀɼ���

	@author ������
*/
void MainWindow::setHomePageBtnVisable(bool isOn)
{
	ui.btn_pve->setVisible(isOn);
	ui.btn_pvp->setVisible(isOn);
	ui.btn_online->setVisible(isOn);
	ui.btn_load->setVisible(isOn);
}

/*
	������Ϸҳ��ť�Ŀɼ���

	@author ������
*/
void MainWindow::setGamePageBtnVisable(bool isOn)
{
	ui.btn_restart->setVisible(isOn);
	ui.btn_prompt->setVisible(isOn);
	ui.btn_retract->setVisible(isOn);
	ui.btn_giveUp->setVisible(isOn);
	ui.btn_save->setVisible(isOn);
	ui.btn_return->setVisible(isOn);
}

/*
	����Ļ��ȡ��������

	@author Ҷ־��
	@return Gobang::Step - ��������
*/
Gobang::Step MainWindow::getStepFromScreen()
{
	QPoint point = QWidget::mapFromGlobal(cursor().pos());
	Gobang::Step * step = new Gobang::Step;
	if (step == NULL)
	{
		qDebug() << "�ڴ����";
		exit(1);
	}
	step->y = (point.x() - 357) / 47;
	step->x = (point.y() - 7) / 47;
	return *step;
}

/*
	��ʾʤ����Ϣ

	@para ChessType - ʤ����������
*/
void MainWindow::showWinnerDialog()
{
	int isSave;
	switch (winner)
	{
	case ChessType::BLACKCHESS:
		highlightSteps(*gobang.getWinnerModel(), BLACKCHESS);
		isSave = QMessageBox::information(this, QString::fromLocal8Bit("��Ϸ��ʤ"), QString::fromLocal8Bit("�����ʤ��\n�Ƿ�Ҫ������Ϸ��¼��"), QMessageBox::Yes, QMessageBox::No);
		if (isSave == QMessageBox::Yes)
			gobang.addRanking(getName(), gobang.getSteps().size() / 2 + 1);
		disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
		setHomePageBtnVisable(true);
		setGamePageBtnVisable(false);
		break;
	case ChessType::WHITECHESS:
		highlightSteps(*gobang.getWinnerModel(), WHITECHESS);
		isSave = QMessageBox::information(this, QString::fromLocal8Bit("��Ϸ��ʤ"), QString::fromLocal8Bit("�����ʤ��\n�Ƿ�Ҫ������Ϸ��¼��"), QMessageBox::Yes, QMessageBox::No);
		if (isSave == QMessageBox::Yes)
			gobang.addRanking(getName(), gobang.getSteps().size() / 2);
		disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
		setHomePageBtnVisable(true);
		setGamePageBtnVisable(false);
		break;
	case ChessType::NOCHESS:
		if (gobang.getSteps().size() == BOARDLENGTH * BOARDLENGTH)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("��Ϸƽ��"), QString::fromLocal8Bit("˫��ƽ�֣�"), QMessageBox::NoButton);
			disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
			setHomePageBtnVisable(true);
			setGamePageBtnVisable(false);
		}
		break;
	default:
		break;
	}
}

/*
	�����������

	@author ������
*/
std::string MainWindow::getName()
{
	bool ok = FALSE;
	QString name = QInputDialog::getText(this, QString::fromLocal8Bit("������"), QString::fromLocal8Bit("�����������ǳƣ�"), QLineEdit::Normal, QString::null, &ok);
	if (ok && !name.isEmpty())
		return name.toStdString();
	return "";
}

/*
	��ť�������Ӧ�¼�

	@author ������
*/
void MainWindow::btnsClicked()
{
	QString btnName = sender()->objectName();

	if (btnName == "btn_ranking")
	{
		ui.lbl_ranking->raise();
		ui.lbl_names->raise();
		ui.lbl_steps->raise();
		ui.btn_close->raise();
		showRankings();
	}
	else if (btnName == "btn_team")
	{
		ui.lbl_team->raise();
		ui.btn_close->raise();
	}
	else if (btnName == "btn_rules")
	{
		ui.lbl_rules->raise();
		ui.btn_close->raise();
	}
	else if (btnName == "btn_music")
		if (isMusicOn)
		{
			ui.btn_music->setStyleSheet("QPushButton{border-image: url(:/MainWindow/image/music(close).png);}"
				"QPushButton:hover{border-image: url(:/MainWindow/image/music.png);}");
			music.pause();
			isMusicOn = false;
		}
		else
		{
			ui.btn_music->setStyleSheet("QPushButton{border-image: url(:/MainWindow/image/music.png);}"
				"QPushButton:hover{border-image: url(:/MainWindow/image/music(close).png);}");
			music.play();
			isMusicOn = true;
		}
	else if (btnName == "btn_close")
	{
		ui.lbl_ranking->lower();
		ui.lbl_team->lower();
		ui.lbl_rules->lower();
		ui.lbl_names->lower();
		ui.lbl_steps->lower();
		ui.btn_close->lower();
	}
	else if (btnName == "btn_exit")
	{
		gobang.writeRanking();
		exit(0);
	}
}

/*
	�˻���ս��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::pveBtnClicked()
{
	clearBoard();
	gobang.initBoard();
	isFirstHand = QMessageBox::question(this, QString::fromLocal8Bit("������"), QString::fromLocal8Bit("�Ƿ�Ҫ�������ӣ�"), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
	computerColor = ChessType::WHITECHESS;
	if (isFirstHand == QMessageBox::Cancel)
		return;
	if (isFirstHand == QMessageBox::No)
		computerColor = ChessType::BLACKCHESS;
	isRestricted = QMessageBox::question(this, QString::fromLocal8Bit("������"), QString::fromLocal8Bit("�Ƿ�Ҫ�����ֿ�ʼ��Ϸ��"), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
	if (isRestricted == QMessageBox::Cancel)
		return;
	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
	gameType = GameType::PVE;
	ui.text_chessinf->setText("");
	computer.Start(this, computerColor);
}

/*
	���˶�ս��Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::pvpBtnClicked()
{
	clearBoard();
	gobang.initBoard();
	isRestricted = QMessageBox::question(this, QString::fromLocal8Bit("������"), QString::fromLocal8Bit("�Ƿ�Ҫ�����ֿ�ʼ��Ϸ��"), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
	if (isRestricted == QMessageBox::Cancel)
		return;
	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
	gameType = GameType::PVP;
	ui.text_chessinf->setText("");
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::onlineBtnClicked()
{
	// ��������ʾ���Ӵ���
	ServerDialog serverDialog = new ServerDialog(this);
	serverDialog.setMainWindow(this);
	serverDialog.exec();

	// �û����ȡ����رհ�ť�򷵻�
	if (!serverDialog.isOKClicked())
		return;

	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
	gameType = GameType::ONLINE;
	ui.text_chessinf->setText("");
	isRestricted = QMessageBox::Yes;
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::loadBtnClicked()
{
	std::string file = selectFile();
	try
	{
		if (file != "")
		{
			clearBoard();
			gobang.initBoard();
			gobang.loadBoard(const_cast<char*>(file.c_str()));
		}
		else
			return;
	}
	catch (const char* msg)
	{
		qDebug() << msg;
	}

	QString s = "";
	int size = gobang.getSteps().size();
	auto iterator = gobang.getSteps().begin();
	for (int i = 0; i < size; i++)
		switch (i % 2)
		{
		case 0:
			chess[iterator->x][iterator->y].setPixmap(blackChess);
			s += QString::fromLocal8Bit("����------------( ") + QString::number(iterator->x) + " , " + QString::number(iterator->y) + " )\n";
			iterator++;
			break;
		case 1:
			chess[iterator->x][iterator->y].setPixmap(whiteChess);
			s += QString::fromLocal8Bit("����------------( ") + QString::number(iterator->x) + " , " + QString::number(iterator->y) + " )\n";
			iterator++;
			break;
		default:
			break;
		}
	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
	isRestricted = QMessageBox::Yes;
	gameType = GameType::PVP;

	ui.text_chessinf->setText(s);
	QTextCursor cursor = ui.text_chessinf->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui.text_chessinf->setTextCursor(cursor);
}

/*
	���¿�ʼ��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::restartBtnClicked()
{
	// ��������
	clearBoard();
	gobang.initBoard();
	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	ui.text_chessinf->setText("");
}

/*
	��ʾ��ť�������Ӧ�¼�

	@author - Ҷ־��
*/
void MainWindow::promptBtnClicked()
{
	try
	{
		Gobang::Step new_step;
		switch (gameType)
		{
		case GameType::PVE:
			if (gobang.getTurn() == computerColor)
				return;
			new_step = gobang.AIWalk(gobang.getTurn());
			walkAStep(new_step);
			break;
		default:
			new_step = gobang.AIWalk(gobang.getTurn());
			walkAStep(new_step);
			break;
		}

	}
	catch (const char* msg)
	{
		qDebug() << msg;
	}
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::retractBtnClicked()
{
	Gobang::Step step;
	switch (gameType)
	{
	case GameType::PVE:
		if (gobang.getTurn() == computerColor)
			return;
		step = gobang.popLastStep();
		if (step.x != -1 && step.y != -1)
		{
			chess[step.x][step.y].setPixmap(QPixmap(""));
			delInf();
		}
		step = gobang.popLastStep();
		if (step.x != -1 && step.y != -1)
		{
			chess[step.x][step.y].setPixmap(QPixmap(""));
			delInf();
		}
		highlightStep(step, -2);
		break;
	default:
		step = gobang.popLastStep();
		if (step.x != -1 && step.y != -1)
		{
			chess[step.x][step.y].setPixmap(QPixmap(""));
			delInf();
			gobang.shiftTurn();
		}
		highlightStep(step, -2);
		break;
	}
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::giveUpBtnClicked()
{
	winner = (gobang.getTurn() + 1) % 2;
	showWinnerDialog();
	disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::saveBtnClicked()
{
	std::string dir = selectDirectory();
	try
	{
		if (dir != "")
			gobang.saveBoard(const_cast<char*>(dir.c_str()));
	}
	catch (const char* msg)
	{
		qDebug() << msg;
	}
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::returnBtnClicked()
{
	disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	gameType = GameType::NONE;
	setHomePageBtnVisable(true);
	setGamePageBtnVisable(false);
}

/*
	���̱������Ӧ�¼�

	@author ������
*/
void MainWindow::boardClicked()
{
	Gobang::Step new_step;
	try
	{
		switch (gameType)
		{
		case GameType::PVE:
			if (gobang.getTurn() == computerColor)
				return;
			new_step = getStepFromScreen();
			walkAStep(new_step);
			break;
		case GameType::PVP:
			new_step = getStepFromScreen();
			walkAStep(new_step);
			break;
		case GameType::ONLINE:
			if (!s->judge && gobang.getTurn() == ChessType::WHITECHESS)
				return;
			if (s->judge && gobang.getTurn() == ChessType::BLACKCHESS)
				return;
			new_step = getStepFromScreen();
			s->msg_send(new_step.x, new_step.y, OperationType::WALK);
			walkAStep(new_step);
			break;
		default:
			break;
		}
	}
	catch (const char* msg)
	{
		qDebug() << msg;
	}
}

/*
	���ڹر��¼�

	@author - Ҷ־��
	@para QCloseEvent - �ر��¼�
*/
void MainWindow::closeEvent(QCloseEvent * event)
{
	gobang.writeRanking();
	event->accept();
	//event->ignore();
}

/*
	��ȡ�浵�ļ�����

	@author ������
*/
std::string MainWindow::selectFile()
{
	QFileDialog fd;
	fd.setAcceptMode(QFileDialog::AcceptOpen);	//�ļ��Ի���Ϊ��ȡ����
	fd.setViewMode(QFileDialog::Detail);		//��ϸ
	fd.setFileMode(QFileDialog::ExistingFile);	//���ڵĵ����ļ���
	fd.setWindowTitle(QString::fromLocal8Bit("ѡ��Ҫ��ȡ���ļ�"));
	fd.setDefaultSuffix("txt");
	QStringList filters;
	filters << QString::fromLocal8Bit("�ı��ļ� (*.txt)");
	fd.setNameFilters(filters);					//�ļ�����
	if (!fd.exec())
		return "";
	return fd.selectedFiles()[0].toStdString();
}

/*
	����浵�ļ�����

	@author ������
*/
std::string MainWindow::selectDirectory()
{
	QFileDialog fd;
	fd.setAcceptMode(QFileDialog::AcceptSave);	//�ļ��Ի���Ϊ��������
	fd.setViewMode(QFileDialog::Detail);		//��ϸ
	fd.setFileMode(QFileDialog::Directory);		//���ڵ��ļ���
	fd.setWindowTitle(QString::fromLocal8Bit("ѡ��Ҫ�����Ŀ¼"));
	fd.setDefaultSuffix("txt");
	QStringList filters;
	filters << QString::fromLocal8Bit("�ı��ļ� (*.txt)");
	fd.setNameFilters(filters);					//�ļ�����
	if (!fd.exec())
		return "";
	return fd.selectedFiles()[0].toStdString();
}

/*
	����������һ�˲�����Ϣ

	@author ������
	@para operation ��������
	@para x��y λ������
*/
void MainWindow::handleRecv_mes(int operation, int x, int y)
{
	int isOKClicked = -1;

	switch (operation)
	{
	case OperationType::WALK:
		try
		{
			if (!s->judge)
			{
				if (gobang.getTurn() == ChessType::BLACKCHESS)
				{
					s->msg_send(-1, -1, OperationType::ERR);
					return;
				}
			}
			else
			{
				if (gobang.getTurn() == ChessType::WHITECHESS)
				{
					s->msg_send(-1, -1, OperationType::ERR);
					return;
				}
			}
			Gobang::Step new_step;
			new_step.x = x;
			new_step.y = y;
			walkAStep(new_step);
		}
		catch (char *msg)
		{
			QMessageBox::warning(NULL, "ERROR", msg);
		}
		break;
	case OperationType::TIPS:
		if (!s->judge)
		{
			if (gobang.getTurn() == ChessType::BLACKCHESS)
			{
				s->msg_send(-1, -1, OperationType::ERR);
				return;
			}
		}
		else
		{
			if (gobang.getTurn() == ChessType::WHITECHESS)
			{
				s->msg_send(-1, -1, OperationType::ERR);
				return;
			}
		}
		isOKClicked = QMessageBox::question(this, QString::fromLocal8Bit("��ʾ����"), QString::fromLocal8Bit("�Ƿ�ͬ��Է���ʾ"), QMessageBox::Yes, QMessageBox::No);
		switch (isOKClicked)
		{
		case QMessageBox::Yes:
			s->msg_send(-1, -1, OperationType::AGREE);
			break;
		case QMessageBox::No:
			s->msg_send(-1, -1, OperationType::DISAGREE);
			break;
		default:
			s->msg_send(-1, -1, OperationType::ERR);
			break;
		}
		break;
	case OperationType::RESTART:
		isOKClicked = QMessageBox::question(this, QString::fromLocal8Bit("���¿�ʼ����"), QString::fromLocal8Bit("�Ƿ�ͬ�����¿�ʼ��Ϸ"), QMessageBox::Yes, QMessageBox::No);
		switch (isOKClicked)
		{
		case QMessageBox::Yes:
			s->msg_send(-1, -1, OperationType::AGREE);
			break;
		case QMessageBox::No:
			s->msg_send(-1, -1, OperationType::DISAGREE);
			break;
		default:
			s->msg_send(-1, -1, OperationType::ERR);
			break;
		}
		break;
	case OperationType::CHEAT:
		isOKClicked = QMessageBox::question(this, QString::fromLocal8Bit("��������"), QString::fromLocal8Bit("�Ƿ�ͬ�����"), QMessageBox::Yes, QMessageBox::No);
		switch (isOKClicked)
		{
		case QMessageBox::Yes:
			s->msg_send(-1, -1, OperationType::AGREE);
			break;
		case QMessageBox::No:
			s->msg_send(-1, -1, OperationType::DISAGREE);
			break;
		default:
			s->msg_send(-1, -1, OperationType::ERR);
			break;
		}
		break;
	case OperationType::GIVEUP:

		break;
	case OperationType::ERR:
		break;
	case OperationType::AGREE:
		break;
	case OperationType::DISAGREE:
		break;

	default:
		break;
	}
}

/*
	����������һ��������Ϣ

	@author ������
	@para msg ������Ϣ
*/
void MainWindow::Do_msg(char *msg) {
	QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit(msg));

}

#include <thread>
#include <chrono>

AIThread::AIThread()
{
}

AIThread::~AIThread()
{
}

/*
	����AI�����߳�

	@author Ҷ־��
	@para color - ����ִ����ɫ
*/
bool AIThread::Start(MainWindow *mainapp, int color)
{
	this->mainapp = mainapp;
	this->color = color;
	std::thread th(&AIThread::Main, this);
	th.detach();
	return true;
}

/*
	AI�����߳�

	@author Ҷ־��
*/
void AIThread::Main()
{
	while (GameType::PVE == mainapp->gameType)
	{
		if (mainapp->getGobang().getTurn() != color)
		{
			this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}
		Gobang::Step new_step = mainapp->getGobang().AIWalk(color);
		mainapp->getGobang().newStep(new_step);
		mainapp->showStep(new_step, mainapp->getGobang().getTurn());
		mainapp->highlightStep(new_step, mainapp->getGobang().getTurn());
		mainapp->playSoundEffects();
		emit showInf(mainapp->getGobang().getTurn(), new_step.x, new_step.y);
		switch (mainapp->getIsRestricted())
		{
		case QMessageBox::Yes:
			mainapp->winner = mainapp->getGobang().isOverWithRestricted();
			break;
		case QMessageBox::No:
			mainapp->winner = mainapp->getGobang().isOverWithoutRestricted();
			break;
		default:
			break;
		}
		emit showWinnerDialog();
		if (mainapp->winner != ChessType::NOCHESS)
		{
			mainapp->gameType = GameType::NONE;
			return;
		}
		mainapp->getGobang().shiftTurn();
	}
}