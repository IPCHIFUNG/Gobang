#include "MainWindow.h"
#include "ServerDialog.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// 初始化标题栏
	this->setWindowTitle(QString::fromLocal8Bit("五子棋"));
	this->setWindowIcon(QIcon(":/MainWindow/image/WHITE_64.ico"));
	this->setFixedSize(this->width(), this->height());

	// 初始化按钮
	setHomePageBtnVisable(true);
	setGamePageBtnVisable(false);

	// 读取音乐和音效
	music.setMedia(QUrl::fromLocalFile("./sound/FlowerDance.mp3"));
	soundEff.setMedia(QUrl::fromLocalFile("./sound/棋子音效a.mp3"));

	// 初始化信号与槽
	connect(ui.btn_pve, SIGNAL(clicked()), this, SLOT(gameBtnsClicked()));
	connect(ui.btn_pvp, SIGNAL(clicked()), this, SLOT(gameBtnsClicked()));
	connect(ui.btn_online, SIGNAL(clicked()), this, SLOT(gameBtnsClicked()));
	connect(ui.btn_load, SIGNAL(clicked()), this, SLOT(gameBtnsClicked()));

	connect(ui.btn_exit, SIGNAL(clicked()), this, SLOT(btnsClicked()));

	gobang = Gobang();
}

/*
	清空棋盘
*/
void MainWindow::clearBoard()
{
	std::deque<Gobang::Step>::iterator ite;
	for (ite = gobang.getSteps().begin(); ite != gobang.getSteps().end(); ite++)
		chess[ite->x][ite->y].setPixmap(QPixmap(""));
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
	if (isOn)
		music.play();
	else
		music.pause();
}

/*
	播放落子音效

	@author 王开阳
*/
void MainWindow::playSoundEffects()
{
	soundEff.play();
}

/*
	设置主页按钮的可见性

	@author 王开阳
*/
void MainWindow::setHomePageBtnVisable(bool isOn)
{
	ui.btn_pve->setVisible(isOn);
	ui.btn_pvp->setVisible(isOn);
	ui.btn_online->setVisible(isOn);
	ui.btn_load->setVisible(isOn);
}

/*
	设置游戏页按钮的可见性

	@author 王开阳
*/
void MainWindow::setGamePageBtnVisable(bool isOn)
{
	ui.btn_restart->setVisible(isOn);
	ui.btn_prompt->setVisible(isOn);
	ui.btn_retract->setVisible(isOn);
	ui.btn_giveUp->setVisible(isOn);
	ui.btn_save->setVisible(isOn);
	ui.btn_return->setVisible(isOn);
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
void MainWindow::btnsClicked()
{
	QString btnName = sender()->objectName();

	if (btnName == "btn_ranking")
	{

	}
	else if (btnName == "btn_team")
	{

	}
	else if (btnName == "btn_rules")
	{

	}
	else if (btnName == "btn_exit")
		exit(0);
}

/*
	按钮被点击响应事件

	@author 王开阳
*/
void MainWindow::gameBtnsClicked()
{
	QString btnName = sender()->objectName();

	if (btnName == "btn_pve")
	{
		
	}
	else if (btnName == "btn_pvp")
	{
		clearBoard();
		gobang.initBoard();
		connect(ui.lbl_chessboard, SIGNAL(clicked()), this, SLOT(boardClicked()));
	}
	else if (btnName == "btn_online")
	{
		ServerDialog serverDialog = new ServerDialog(this);
		serverDialog.exec();
	}
	else if (btnName == "btn_load")
	{

	}
}

/*
	按钮被点击响应事件

	@author 王开阳
*/
void MainWindow::gamePropertiesBtnsClicked()
{
	QString btnName = sender()->objectName();

	if (btnName == "btn_restart")
	{

	}
	else if (btnName == "btn_prompt")
	{

	}
	else if (btnName == "btn_retract")
	{

	}
	else if (btnName == "btn_giveUp")
	{

	}
	else if (btnName == "btn_save")
	{

	}
	else if (btnName == "btn_return")
	{

	}
}

/*
	棋盘被点击响应事件

	@author 王开阳
*/
void MainWindow::boardClicked(QMouseEvent *event)
{
	QPoint point = event->pos();
	Gobang::Step step;

	step.x = (point.x() - 377) / 47 + 0.5;
	step.y = (point.y() - 424) / 47 + 0.5;
	gobang.newStep(step);

	showStep(step, gobang.getTurn());	// 显示棋子
	highlightStep(step);				// 高亮棋子
}