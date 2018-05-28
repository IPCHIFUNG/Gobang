#include "MainWindow.h"
#include "ServerDialog.h"
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
	for (int i = 0; i < BOARDLENGTH; i++)
		for (int j = 0; j < BOARDLENGTH; j++)
		{
			chess[i][j].setParent(ui.centralWidget);
			chess[i][j].setGeometry(357 + j * 47, 7 + i * 47, 42, 42);
		}
	ui.btn_chessboard->raise();

	// ��ȡ���ֺ���Ч
	music.setMedia(QUrl::fromLocalFile("./sound/FlowerDance.mp3"));
	soundEff.setMedia(QUrl::fromLocalFile("./sound/b.mp3"));
	setBackgroundMusic(true);

	gobang = Gobang();
	gameType = GameType::NONE;
}

/*
	�������
*/
void MainWindow::clearBoard()
{
	std::deque<Gobang::Step> &steps = gobang.getSteps();
	while (!steps.empty())
	{
		chess[steps.front().x][steps.front().y].setPixmap(QPixmap(""));
		steps.pop_front();
	}
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
		break;
	}
}

/*
	��������
*/
void MainWindow::highlightStep(Gobang::Step step)
{

}

/*
	���ź���ͣ��������

	@author ������
	@para �Ƿ񲥷�����
*/
void MainWindow::setBackgroundMusic(bool isOn)
{
	if (isOn)
		music.play();
	else
		music.pause();
}

/*
	����������Ч

	@author ������
*/
void MainWindow::playSoundEffects()
{
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
void MainWindow::showWinnerDialog(int type)
{
	switch (type)
	{
	case ChessType::BLACKCHESS:		// �����ʤ
		QMessageBox::information(this, QString::fromLocal8Bit("��Ϸ��ʤ"), QString::fromLocal8Bit("�����ʤ��"), QMessageBox::NoButton);
		break;
	case ChessType::WHITECHESS:		// �����ʤ
		QMessageBox::information(this, QString::fromLocal8Bit("��Ϸ��ʤ"), QString::fromLocal8Bit("�����ʤ��"), QMessageBox::NoButton);
		break;
	case ChessType::NOCHESS:		// ƽ��
		break;
	default:
		break;
	}
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
		ui.btn_close->raise();
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
	else if (btnName == "btn_close")
	{
		ui.lbl_ranking->lower();
		ui.lbl_team->lower();
		ui.lbl_rules->lower();
		ui.btn_close->lower();
	}
	else if (btnName == "btn_exit")
		exit(0);
}

/*
	�˻���ս��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::pveBtnClicked()
{
	clearBoard();
	gobang.initBoard();
	isFirstHand = QMessageBox::question(this, QString::fromLocal8Bit("������"), QString::fromLocal8Bit("�Ƿ�Ҫ�������ӣ�"), QMessageBox::Yes, QMessageBox::No);
	try {
		switch (isFirstHand)
		{
		case QMessageBox::Yes:		// ����
			gobang.AIWalk(ChessType::WHITECHESS);
			break;
		case QMessageBox::No:		// ����
			gobang.AIWalk(ChessType::BLACKCHESS);
			break;
		default:
			break;
		}
	}
	catch (const char *msg) {
		QMessageBox::information(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(msg), QMessageBox::NoButton);
	}

	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
	gameType = GameType::PVE;
}

/*
	���˶�ս��Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::pvpBtnClicked()
{
	clearBoard();
	gobang.initBoard();
	isRestricted = QMessageBox::question(this, QString::fromLocal8Bit("������"), QString::fromLocal8Bit("�Ƿ�Ҫ�����ֿ�ʼ��Ϸ��"), QMessageBox::Yes, QMessageBox::No);
	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
	gameType = GameType::PVP;
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::onlineBtnClicked()
{
	// ��������ʾ���Ӵ���
	ServerDialog serverDialog = new ServerDialog(this);
	//serverDialog.setMainWindow(this);
	serverDialog.exec();

	// �û����ȡ����رհ�ť�򷵻�
	if (!serverDialog.isOKClicked())
		return;

	//��������λ��
	Gobang::Step step = getStepFromScreen();
	if (!serverDialog.isOKClicked())
	{
		Server *s = serverDialog.getServer();
		s->setMessage(step.x, step.y);
	}


	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
	gameType = GameType::ONLINE;
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::loadBtnClicked()
{
	std::string file = selectFile();
	if (file != "")
		gobang.loadBoard(const_cast<char*>(file.c_str()));
	else
		return;

	int size = gobang.getSteps().size();
	auto iterator = gobang.getSteps().begin();
	for (int i = 0; i < size; i++)
		switch (i % 2)
		{
		case 0:
			chess[iterator->x][iterator->y].setPixmap(blackChess);
			iterator++;
			break;
		case 1:
			chess[iterator->x][iterator->y].setPixmap(whiteChess);
			iterator++;
			break;
		default:
			break;
		}
	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::restartBtnClicked()
{
	clearBoard();
	gobang.initBoard();
	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
}

/*
	��ʾ��ť�������Ӧ�¼�

	@author - Ҷ־��
*/
void MainWindow::promptBtnClicked()
{
	try
	{
		Gobang::Step new_step = gobang.AIWalk(gobang.getTurn());
		gobang.newStep(new_step);
		showStep(new_step, gobang.getTurn());
		gobang.shiftTurn();
		playSoundEffects();
		highlightStep(new_step);
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
	Gobang::Step step = gobang.popLastStep();
	if (step.x != -1 && step.y != -1)
	{
		chess[step.x][step.y].setPixmap(QPixmap(""));
		gobang.shiftTurn();
	}
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::giveUpBtnClicked()
{
	int winner = (gobang.getTurn() + 1) % 2;
	showWinnerDialog(winner);
	disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::saveBtnClicked()
{
	std::string dir = selectDirectory();
	if (dir != "")
		gobang.saveBoard(const_cast<char*>(dir.c_str()));
}

/*
	��ť�������Ӧ�¼�

	@author - ������ Ҷ־��
*/
void MainWindow::returnBtnClicked()
{
	disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(true);
	setGamePageBtnVisable(false);
}

/*
	���̱������Ӧ�¼�

	@author ������
*/
void MainWindow::boardClicked()
{
	Gobang::Step step = getStepFromScreen();
	try
	{
		gobang.newStep(step);
		showStep(step, gobang.getTurn());	// ��ʾ����
		gobang.shiftTurn();
		playSoundEffects();
		highlightStep(step);				// ��������

		int result;
		switch (isRestricted)
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
		showWinnerDialog(result);
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