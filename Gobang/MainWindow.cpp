#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// ��ʼ��������
	this->setWindowTitle(QString::fromLocal8Bit("������"));
	this->setWindowIcon(QIcon(":/MainWindow/image/WHITE_64.ico"));

	// ��ʼ����ť
	setHomePageBtnVisable(true);
	setGamePageBtnVisable(false);

	music.setMedia(QUrl::fromLocalFile("./sound/FlowerDance.mp3"));
	soundEff.setMedia(QUrl::fromLocalFile("./sound/������Чa.mp3"));

	connect(ui.btn_exit, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

/*
	�������
*/
void MainWindow::clearBoard()
{
}

/*
	��ʾһ����

	@author ������
	@para step - ��һ������
	@para type - ��һ����������
*/
void MainWindow::showStep(Gobang::Step step, int type)
{
	if (step.x < 350 || step.x > 1250)
		throw "step.x is out of range";
	if (step.y < 0 || step.y > 900)
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
void MainWindow::buttonClicked()
{
	QString btnName = sender()->objectName();

	if (btnName == "btn_pve")
	{

	}
	else if (btnName == "btn_pvp")
	{

	}
	else if (btnName == "btn_load")
	{

	}
	else if (btnName == "btn_ranking")
	{

	}
	else if (btnName == "btn_exit")
	{
		exit(0);
	}
}

/*
	���̱������Ӧ�¼�

	@author ������
*/
void MainWindow::boardClicked()
{
	QString str;
}