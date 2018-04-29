#include "MainWindow.h"
#include "GameInterface.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

/*
播放和暂停背景音乐

@author 王开阳
@para 是否播放音乐
*/
void MainWindow::setBackgroundMusic(bool isOn)
{

}

/*
棋盘被点击响应事件

@author 王开阳
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