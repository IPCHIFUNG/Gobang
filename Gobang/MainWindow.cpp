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

	// ��ȡ���ֺ���Ч
	music.setMedia(QUrl::fromLocalFile("./sound/FlowerDance.mp3"));
	soundEff.setMedia(QUrl::fromLocalFile("./sound/������Чa.mp3"));

	// ��ʼ���ź����
	connect(ui.btn_pve, SIGNAL(clicked()), this, SLOT(gameBtnsClicked()));
	connect(ui.btn_pvp, SIGNAL(clicked()), this, SLOT(gameBtnsClicked()));
	connect(ui.btn_online, SIGNAL(clicked()), this, SLOT(gameBtnsClicked()));
	connect(ui.btn_load, SIGNAL(clicked()), this, SLOT(gameBtnsClicked()));

	connect(ui.btn_exit, SIGNAL(clicked()), this, SLOT(btnsClicked()));

	gobang = Gobang();
}

/*
	�������
*/
void MainWindow::clearBoard()
{
	std::deque<Gobang::Step>::iterator ite;
	for (ite = gobang.getSteps().begin(); ite != gobang.getSteps().end(); ite++)
		chess[ite->x][ite->y].setPixmap(QPixmap(""));
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
	if (type != ChessType::BLACKCHESS || type != ChessType::WHITECHESS)
		throw "Invalid type";
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

	}
	else if (btnName == "btn_team")
	{

	}
	else if (btnName == "btn_rules")
	{

	}
	else if (btnName == "btn_exit")
		exit(0);
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
		
	}
	else if (btnName == "btn_pvp")
	{
		clearBoard();
		gobang.initBoard();
		connect(ui.lbl_chessboard, SIGNAL(clicked()), this, SLOT(boardClicked()));
	}
	else if (btnName == "btn_online")
	{
		ServerDialog serverDialog = new ServerDialog(this);
		serverDialog.exec();
	}
	else if (btnName == "btn_load")
	{

	}
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

	}
	else if (btnName == "btn_return")
	{

	}
}

/*
	���̱������Ӧ�¼�

	@author ������
*/
void MainWindow::boardClicked(QMouseEvent *event)
{
	QPoint point = event->pos();
	Gobang::Step step;

	step.x = (point.x() - 377) / 47 + 0.5;
	step.y = (point.y() - 424) / 47 + 0.5;
	gobang.newStep(step);

	showStep(step, gobang.getTurn());	// ��ʾ����
	highlightStep(step);				// ��������
}