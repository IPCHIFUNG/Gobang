#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

/*
��ʾһ����

@author ������
@para ��һ������
*/
void MainWindow::showStep(Gobang::Step step)
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
��ť�������Ӧ�¼�

@author ������
*/
void MainWindow::buttonClicked()
{
	QString butName = sender()->objectName();

	if (butName == "Button_PVE") {

	}
	else if (butName == "Button_PVP")
		;
	else if (butName == "Button_Load")
		;
	else if (butName == "Button_Ranking")
		;
	else if (butName == "Button_Exit")
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