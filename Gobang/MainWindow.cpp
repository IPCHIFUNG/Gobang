#include "MainWindow.h"
#include "ServerDialog.h"
#include <qmessagebox.h>

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

	// 初始化棋盘
	blackChess = QPixmap("./image/BLACK.png");
	whiteChess = QPixmap("./image/WHITE.png");
	HLBlackChess = QPixmap("./image/BLACK(highlight).png");
	HLWhiteChess = QPixmap("./image/WHITE(highlight).png");
	for (int i = 0; i < BOARDLENGTH; i++)
		for (int j = 0; j < BOARDLENGTH; j++)
		{
			chess[i][j].setParent(ui.centralWidget);
			chess[i][j].setGeometry(357 + j * 47, 7 + i * 47, 42, 42);
		}
	ui.btn_chessboard->raise();

	// 读取音乐和音效
	music.setMedia(QUrl::fromLocalFile("./sound/FlowerDance.mp3"));
	soundEff.setMedia(QUrl::fromLocalFile("./sound/b.mp3"));
	isMusicOn = true;
	music.play();

	gobang = Gobang();
	gameType = GameType::NONE;
	winner = ChessType::NOCHESS;
}

/*
	清空棋盘

	@author 叶志枫
*/
void MainWindow::clearBoard()
{
	// 初始化高亮棋子保存信息
	Gobang::Step temp; temp.x = -1; temp.y = -1;
	highlightStep(temp, -2);
	// 清理棋盘
	std::deque<Gobang::Step> &steps = gobang.getSteps();
	while (!steps.empty())
	{
		chess[steps.front().x][steps.front().y].setPixmap(QPixmap(""));
		steps.pop_front();
	}
}

/*
	打包走棋操作

	@author 叶志枫
*/
void MainWindow::walkAStep(Gobang::Step new_step)
{
	gobang.newStep(new_step);
	showStep(new_step, gobang.getTurn());
	highlightStep(new_step, gobang.getTurn());
	gobang.shiftTurn();
	playSoundEffects();
	switch (isRestricted)
	{
	case QMessageBox::Yes:
		winner = gobang.isOverWithRestricted();
		break;
	case QMessageBox::No:
		winner = gobang.isOverWithoutRestricted();
		break;
	default:
		break;
	}
	showWinnerDialog();
	if (winner != ChessType::NOCHESS)
	{
		gameType = GameType::NONE;
		return;
	}
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
	if (type != ChessType::BLACKCHESS && type != ChessType::WHITECHESS)
		throw "Invalid type";
	switch (type)
	{
	case ChessType::BLACKCHESS:
		chess[step.x][step.y].setPixmap(blackChess);
		break;
	case ChessType::WHITECHESS:
		chess[step.x][step.y].setPixmap(whiteChess);
		break;
	default:
		chess[step.x][step.y].setPixmap(QPixmap(""));
		break;
	}
}

/*
	高亮棋子

	@author 叶志枫
	@para step - 需要高亮的棋子
	@para type - 需要高亮的棋子类型
*/
void MainWindow::highlightStep(Gobang::Step step, int type)
{
	static int x = -1;
	static int y = -1;
	static int last_type = -1;
	if (-2 == type)
	{
		x = -1; y = -1; last_type = -1;
		return;
	}
	if (-1 != x && -1 != y && -1 != last_type)
	{
		if (ChessType::BLACKCHESS == last_type)
			chess[x][y].setPixmap(blackChess);
		else if (ChessType::WHITECHESS == last_type)
			chess[x][y].setPixmap(whiteChess);
		else
			chess[x][y].setPixmap(QPixmap(""));
	}
	if (step.x < 0 || step.x > BOARDLENGTH)
		throw "step.x is out of range";
	if (step.y < 0 || step.y > BOARDLENGTH)
		throw "step.y is out of range";
	if (type != ChessType::BLACKCHESS && type != ChessType::WHITECHESS)
		throw "Invalid type";
	x = step.x;
	y = step.y;
	last_type = type;
	switch (type)
	{
	case ChessType::BLACKCHESS:
		chess[step.x][step.y].setPixmap(HLBlackChess);
		break;
	case ChessType::WHITECHESS:
		chess[step.x][step.y].setPixmap(HLWhiteChess);
		break;
	default:
		chess[step.x][step.y].setPixmap(QPixmap(""));
		break;
	}
}

/*
	播放和暂停背景音乐

	@author 王开阳
	@para 是否播放音乐
*/
void MainWindow::setBackgroundMusic()
{
	if (isMusicOn)
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
	soundEff.stop();
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
	从屏幕获取棋子坐标

	@author 叶志枫
	@return Gobang::Step - 棋子坐标
*/
Gobang::Step MainWindow::getStepFromScreen()
{
	QPoint point = QWidget::mapFromGlobal(cursor().pos());
	Gobang::Step * step = new Gobang::Step;
	if (step == NULL)
	{
		qDebug() << "内存溢出";
		exit(1);
	}
	step->y = (point.x() - 357) / 47;
	step->x = (point.y() - 7) / 47;
	return *step;
}

/*
	显示胜方信息

	@para ChessType - 胜方棋子种类
*/
void MainWindow::showWinnerDialog()
{
	switch (winner)
	{
	case ChessType::BLACKCHESS:
		QMessageBox::information(this, QString::fromLocal8Bit("游戏获胜"), QString::fromLocal8Bit("黑棋获胜！"), QMessageBox::NoButton);
		disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
		break;
	case ChessType::WHITECHESS:
		QMessageBox::information(this, QString::fromLocal8Bit("游戏获胜"), QString::fromLocal8Bit("白棋获胜！"), QMessageBox::NoButton);
		disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
		break;
	case ChessType::NOCHESS:
		if (gobang.getSteps().size() == BOARDLENGTH * BOARDLENGTH)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("游戏平局"), QString::fromLocal8Bit("双方平局！"), QMessageBox::NoButton);
			disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
		}
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
		ui.lbl_ranking->raise();
		ui.btn_close->raise();
	}
	else if (btnName == "btn_team")
	{
		ui.lbl_team->raise();
		ui.btn_close->raise();
	}
	else if (btnName == "btn_rules")
	{
		ui.lbl_rules->raise();
		ui.btn_close->raise();
	}
	else if (btnName == "btn_music")
	{
		if (isMusicOn)
		{
			ui.btn_music->setStyleSheet("QPushButton{border-image: url(:/MainWindow/image/music.png);}"
				"QPushButton:hover{border-image: url(:/MainWindow/image/music(close).png);}"
				"QPushButton:pressed{border-image: url(:/MainWindow/image/music.png);}");
			isMusicOn = false;
			music.play();
		}
		else
		{
			ui.btn_music->setStyleSheet("QPushButton{border-image: url(:/MainWindow/image/music(close).png);}"
				"QPushButton:hover{border-image: url(:/MainWindow/image/music.png);}"
				"QPushButton:pressed{border-image: url(:/MainWindow/image/music(close).png);}");
			isMusicOn = true;
			music.pause();
		}
	}
	else if (btnName == "btn_close")
	{
		ui.lbl_ranking->lower();
		ui.lbl_team->lower();
		ui.lbl_rules->lower();
		ui.btn_close->lower();
	}
	else if (btnName == "btn_exit")
		exit(0);
}

/*
	人机对战按钮被点击响应事件

	@author - 王开阳 叶志枫
*/
void MainWindow::pveBtnClicked()
{
	clearBoard();
	gobang.initBoard();
	isFirstHand = QMessageBox::question(this, QString::fromLocal8Bit("五子棋"), QString::fromLocal8Bit("是否要先手落子？"), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
	computerColor = ChessType::WHITECHESS;
	if (isFirstHand == QMessageBox::Cancel)
		return;
	if (isFirstHand == QMessageBox::No)
		computerColor = ChessType::BLACKCHESS;
	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
	gameType = GameType::PVE;
	computer.Start(this, computerColor);
}

/*
	人人对战响应事件

	@author - 王开阳 叶志枫
*/
void MainWindow::pvpBtnClicked()
{
	clearBoard();
	gobang.initBoard();
	isRestricted = QMessageBox::question(this, QString::fromLocal8Bit("五子棋"), QString::fromLocal8Bit("是否要带禁手开始游戏？"), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
	if (isRestricted == QMessageBox::Cancel)
		return;
	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
	gameType = GameType::PVP;
}

/*
	按钮被点击响应事件

	@author - 王开阳 叶志枫
*/
void MainWindow::onlineBtnClicked()
{
	// 创建并显示连接窗口
	ServerDialog serverDialog = new ServerDialog(this);
	serverDialog.setMainWindow(this);
	serverDialog.exec();

	// 用户点击取消或关闭按钮则返回
	if (!serverDialog.isOKClicked())
		return;

	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
	gameType = GameType::ONLINE;
}

/*
	按钮被点击响应事件

	@author - 王开阳 叶志枫
*/
void MainWindow::loadBtnClicked()
{
	std::string file = selectFile();
	try
	{
		if (file != "")
			gobang.loadBoard(const_cast<char*>(file.c_str()));
		else
			return;
	}
	catch (const char* msg)
	{
		qDebug() << msg;
	}

	int size = gobang.getSteps().size();
	auto iterator = gobang.getSteps().begin();
	for (int i = 0; i < size; i++)
		switch (i % 2)
		{
		case 0:
			chess[iterator->x][iterator->y].setPixmap(blackChess);
			iterator++;
			break;
		case 1:
			chess[iterator->x][iterator->y].setPixmap(whiteChess);
			iterator++;
			break;
		default:
			break;
		}
	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(false);
	setGamePageBtnVisable(true);
}

/*
	重新开始按钮被点击响应事件

	@author - 王开阳 叶志枫
*/
void MainWindow::restartBtnClicked()
{
	// 清理棋盘
	clearBoard();
	gobang.initBoard();
	connect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
}

/*
	提示按钮被点击响应事件

	@author - 叶志枫
*/
void MainWindow::promptBtnClicked()
{
	try
	{
		Gobang::Step new_step = gobang.AIWalk(gobang.getTurn());
		gobang.newStep(new_step);
		showStep(new_step, gobang.getTurn());
		highlightStep(new_step, gobang.getTurn());
		gobang.shiftTurn();
		playSoundEffects();
	}
	catch (const char* msg)
	{
		qDebug() << msg;
	}
}

/*
	按钮被点击响应事件

	@author - 王开阳 叶志枫
*/
void MainWindow::retractBtnClicked()
{
	Gobang::Step step = gobang.popLastStep();
	if (step.x != -1 && step.y != -1)
	{
		chess[step.x][step.y].setPixmap(QPixmap(""));
		gobang.shiftTurn();
	}
}

/*
	按钮被点击响应事件

	@author - 王开阳 叶志枫
*/
void MainWindow::giveUpBtnClicked()
{
	winner = (gobang.getTurn() + 1) % 2;
	showWinnerDialog();
	disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
}

/*
	按钮被点击响应事件

	@author - 王开阳 叶志枫
*/
void MainWindow::saveBtnClicked()
{
	std::string dir = selectDirectory();
	try
	{
		if (dir != "")
			gobang.saveBoard(const_cast<char*>(dir.c_str()));
	}
	catch (const char* msg)
	{
		qDebug() << msg;
	}
}

/*
	按钮被点击响应事件

	@author - 王开阳 叶志枫
*/
void MainWindow::returnBtnClicked()
{
	disconnect(ui.btn_chessboard, SIGNAL(pressed()), this, SLOT(boardClicked()));
	setHomePageBtnVisable(true);
	setGamePageBtnVisable(false);
}

/*
	棋盘被点击响应事件

	@author 王开阳
*/
void MainWindow::boardClicked()
{
	Gobang::Step new_step;
	try
	{
		switch (gameType)
		{
		case GameType::PVE:
			if (gobang.getTurn() == computerColor)
				return;
			new_step = getStepFromScreen();
			walkAStep(new_step);
			break;
		case GameType::PVP:
			new_step = getStepFromScreen();
			walkAStep(new_step);
			break;
		case GameType::ONLINE:
			break;
		default:
			break;
		}
	}
	catch (const char* msg)
	{
		qDebug() << msg;
	}
}

/*
	窗口关闭事件

	@author - 叶志枫
	@para QCloseEvent - 关闭事件
*/
void MainWindow::closeEvent(QCloseEvent * event)
{
	event->accept();
	//event->ignore();
}

/*
	读取存档文件界面

	@author 王开阳
*/
std::string MainWindow::selectFile()
{
	QFileDialog fd;
	fd.setAcceptMode(QFileDialog::AcceptOpen);	//文件对话框为读取类型
	fd.setViewMode(QFileDialog::Detail);		//详细
	fd.setFileMode(QFileDialog::ExistingFile);	//存在的单个文件名
	fd.setWindowTitle(QString::fromLocal8Bit("选择要读取的文件"));
	fd.setDefaultSuffix("txt");
	QStringList filters;
	filters << QString::fromLocal8Bit("文本文件 (*.txt)");
	fd.setNameFilters(filters);					//文件过滤
	if (!fd.exec())
		return "";
	return fd.selectedFiles()[0].toStdString();
}

/*
	保存存档文件界面

	@author 王开阳
*/
std::string MainWindow::selectDirectory()
{
	QFileDialog fd;
	fd.setAcceptMode(QFileDialog::AcceptSave);	//文件对话框为保存类型
	fd.setViewMode(QFileDialog::Detail);		//详细
	fd.setFileMode(QFileDialog::Directory);		//存在的文件夹
	fd.setWindowTitle(QString::fromLocal8Bit("选择要保存的目录"));
	fd.setDefaultSuffix("txt");
	QStringList filters;
	filters << QString::fromLocal8Bit("文本文件 (*.txt)");
	fd.setNameFilters(filters);					//文件过滤
	if (!fd.exec())
		return "";
	return fd.selectedFiles()[0].toStdString();
}

#include <thread>
#include <chrono>

AIThread::AIThread()
{
}

AIThread::~AIThread()
{
}

/*
	开启AI走棋线程

	@author 叶志枫
	@para color - 电脑执棋颜色
*/
bool AIThread::Start(MainWindow *mainapp, int color)
{
	this->mainapp = mainapp;
	this->color = color;
	thread th(&AIThread::Main, this);
	th.detach();
	return true;
}

/*
	AI走棋线程

	@author 叶志枫
*/
void AIThread::Main()
{
	while (GameType::PVE == mainapp->getGameType())
	{
		if (mainapp->getGobang().getTurn() != color)
		{
			this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}
		Gobang::Step new_step = mainapp->getGobang().AIWalk(color);
		mainapp->walkAStep(new_step);
	}
}