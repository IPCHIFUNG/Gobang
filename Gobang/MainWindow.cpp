#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void MainWindow::setBackgroundMusic(bool isOn)	// ���ź���ͣ��������
{

}

void MainWindow::buttonClicked()				// ���̱������Ӧ�¼�
{
	QString butName = sender()->objectName();

	if (butName == "Button_PVE")
		;
	else if (butName == "Button_PVE")
		;
	else if (butName == "Button_PVP")
		;
	else if (butName == "Button_Load")
		;
	else if (butName == "Button_Ranking")
		;
	else if (butName == "Button_Exit")
		;
}