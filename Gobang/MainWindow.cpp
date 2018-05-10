#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// 初始化标题栏
	this->setWindowTitle(QString::fromLocal8Bit("五子棋"));
	this->setWindowIcon(QIcon(":/MainWindow/image/WHITE_64.ico"));

	// 初始化按钮
	setHomePageBtnVisable(true);
	setGamePageBtnVisable(false);

	connect(ui.btn_exit, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

/*
	清空棋盘
*/
void MainWindow::clearBoard()
{
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
	高亮棋子
*/
void MainWindow::highlightStep(Gobang::Step step)
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
	显示胜方信息

	@para ChessType - 胜方棋子种类
*/
void MainWindow::showWinnerDialog(int type)
{
	switch (type)
	{
	case ChessType::BLACKCHESS:		// 黑棋获胜
		break;
	case ChessType::WHITECHESS:		// 白起获胜
		break;
	case ChessType::NOCHESS:		// 平局
		break;
	default:
		break;
	}
}

/*
	按钮被点击响应事件

	@author 王开阳
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
	棋盘被点击响应事件

	@author 王开阳
*/
void MainWindow::boardClicked()
{
	QString str;
}