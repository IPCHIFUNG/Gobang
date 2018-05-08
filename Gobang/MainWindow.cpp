#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

/*
显示一步棋

@author 王开阳
@para 下一步落子
*/
void MainWindow::showStep(Gobang::Step step)
{

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
播放落子音效

@author 王开阳
*/
void MainWindow::playSoundEffects()
{

}

/*
按钮被点击响应事件

@author 王开阳
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
棋盘被点击响应事件

@author 王开阳
*/
void MainWindow::boardClicked()
{
	QString str;
}