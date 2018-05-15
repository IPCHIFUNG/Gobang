#include "MainWindow.h"
#include "ServerDialog.h"

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
}

/*
	�������
*/
void MainWindow::clearBoard()
{
	int size = gobang.getSteps().size();
	auto iterator = gobang.getSteps().begin();
	for (int i = 0; i < size; i++)
	{
		chess[iterator->x][iterator->y].setPixmap(QPixmap(""));
		iterator++;
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
		break;
	case ChessType::WHITECHESS:		// �����ʤ
		break;
	case ChessType::NOCHESS:		// ƽ��
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
	}
	else if (btnName == "btn_team")
	{
		ui.lbl_team->raise();
	}
	else if (btnName == "btn_rules")
	{
		ui.lbl_rules->raise();
	}
	else if (btnName == "btn_exit")
		exit(0);
	ui.btn_return->setVisible(true);
}

/*
	��ť�������Ӧ�¼�

	@author ������
*/
void MainWindow::gameBtnsClicked()
{
	QString btnName = sender()->objectName();

	if (btnName == "btn_pve")
	{
		clearBoard();
		gobang.initBoard();

		int choice;
		switch (choice)
		{
		case ChessType::BLACKCHESS:		// ����
			gobang.AIWalk(BLACKCHESS);
			break;
		case ChessType::WHITECHESS:		// ����
			gobang.AIWalk(WHITECHESS);
			break;
		}
	}
	else if (btnName == "btn_pvp")
	{
		clearBoard();
		gobang.initBoard();
	}
	else if (btnName == "btn_online")
	{
		ServerDialog serverDialog = new ServerDialog(this);
		serverDialog.exec();
	}
	else if (btnName == "btn_load")
	{
		std::string file = selectFile();
		if (file != "")
			gobang.loadBoard(const_cast<char*>(file.c_str()));
		else
			return;
	}
	connect(ui.btn_chessboard, SIGNAL(clicked()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
}

/*
	��ť�������Ӧ�¼�

	@author ������
*/
void MainWindow::gamePropertiesBtnsClicked()
{
	QString btnName = sender()->objectName();

	if (btnName == "btn_restart")
	{

	}
	else if (btnName == "btn_prompt")
	{

	}
	else if (btnName == "btn_retract")
	{

	}
	else if (btnName == "btn_giveUp")
	{

	}
	else if (btnName == "btn_save")
	{
		std::string dir = selectDirectory();
		if (dir != "")
			gobang.saveBoard(const_cast<char*>(dir.c_str()));
	}
	else if (btnName == "btn_return")
	{
		disconnect(ui.btn_chessboard, SIGNAL(clicked()), this, SLOT(boardClicked()));
		ui.lbl_ranking->lower();
		ui.lbl_team->lower();
		ui.lbl_rules->lower();
		setHomePageBtnVisable(true);
		setGamePageBtnVisable(false);
	}
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

		int result = gobang.isOverWithRestricted();
		showWinnerDialog(result);
	}
	catch (const char* msg)
	{
		qDebug() << msg;
	}
}

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