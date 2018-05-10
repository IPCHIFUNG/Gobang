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

}

/*
	����������Ч

	@author ������
*/
void MainWindow::playSoundEffects()
{

}

/*
	������ҳ��ť�Ŀɼ���

	@author ������
*/
void MainWindow::setHomePageBtnVisable(bool isOn)
{
	// TO_DO:������ҳ��ť�Ŀɼ���
}

/*
	������Ϸҳ��ť�Ŀɼ���

	@author ������
*/
void MainWindow::setGamePageBtnVisable(bool isOn)
{
	// TO_DO:������Ϸҳ��ť�Ŀɼ���
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