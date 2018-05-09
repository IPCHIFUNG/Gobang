#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setHomePageBtnVisable(true);
	setGamePageBtnVisable(false);
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
	��ť�������Ӧ�¼�

	@author ������
*/
void MainWindow::buttonClicked()
{
	QString btnName = sender()->objectName();

	if (btnName == "Button_PVE") {

	}
	else if (btnName == "Button_PVP")
		;
	else if (btnName == "Button_Load")
		;
	else if (btnName == "Button_Ranking")
		;
	else if (btnName == "Button_Exit")
		;
}

/*
	���̱������Ӧ�¼�

	@author ������
*/
void MainWindow::boardClicked()
{
	QString str;
}