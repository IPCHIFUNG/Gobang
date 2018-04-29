#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void MainWindow::setBackgroundMusic(bool isOn)	// 播放和暂停背景音乐
{

}

void MainWindow::buttonClicked()				// 按钮被点击响应事件
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