#include "MainWindow.h"
#include "GameInterface.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
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
���̱������Ӧ�¼�

@author ������
*/
void MainWindow::buttonClicked()
{
	QString butName = sender()->objectName();

	if (butName == "Button_PVE") {
		GameInterface g;
		g.show();
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