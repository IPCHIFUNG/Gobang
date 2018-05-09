#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setHomePageBtnVisable(true);
	setGamePageBtnVisable(false);
}

/*
	显示一步棋

	@author 王开阳
	@para step - 下一步落子
	@para type - 下一步落子类型
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
	设置主页按钮的可见性

	@author 王开阳
*/
void MainWindow::setHomePageBtnVisable(bool isOn)
{
	// TO_DO:设置主页按钮的可见性
}

/*
	设置游戏页按钮的可见性

	@author 王开阳
*/
void MainWindow::setGamePageBtnVisable(bool isOn)
{
	// TO_DO:设置游戏页按钮的可见性
}

/*
	按钮被点击响应事件

	@author 王开阳
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
	棋盘被点击响应事件

	@author 王开阳
*/
void MainWindow::boardClicked()
{
	QString str;
}