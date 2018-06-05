#pragma once

#include <QtWidgets/QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QCloseEvent>
#include <string>
#include "ui_MainWindow.h"
#include "Gobang.h"
#include "Server.h"
#include "ChessThread.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	Gobang::Step getStepFromScreen();			// 从屏幕获取棋子坐标
	void showStep(Gobang::Step step, int type);	// 显示一步棋
	void playSoundEffects();					// 播放落子音效
	void highlightStep(Gobang::Step step, int type);		// 高亮棋子
	void showWinnerDialog();			// 显示胜方信息
	Gobang & getGobang();
	int getIsRestricted();
	int getGameType();
	void setWinner(int w);
	Server *s;

private:
	Ui::MainWindowClass ui;
	int gameType;
	std::string ranking;
	Gobang gobang;
	QMediaPlayer music;
	QMediaPlayer soundEff;
	QLabel chess[BOARDLENGTH][BOARDLENGTH];

	QPixmap blackChess;
	QPixmap whiteChess;
	QPixmap HLBlackChess;
	QPixmap HLWhiteChess;

private:
	void clearBoard();							// 清空棋盘
	void setBackgroundMusic(bool isOn);			// 播放和暂停背景音乐
	void closeEvent(QCloseEvent *event);		// 窗口关闭事件

	void setHomePageBtnVisable(bool isOn);		// 设置主页按钮的可见性
	void setGamePageBtnVisable(bool isOn);		// 设置游戏页按钮的可见性
	std::string selectFile();					// 选择读取文件
	std::string selectDirectory();				// 选择保存目录
	int isRestricted;							// 是否带禁手开始游戏
	int isFirstHand;							// 是否先手开始游戏
	int winner;

private slots:
	void btnsClicked();							// 按钮被点击响应事件
	void pveBtnClicked();
	void pvpBtnClicked();
	void onlineBtnClicked();
	void loadBtnClicked();
	void restartBtnClicked();
	void promptBtnClicked();
	void retractBtnClicked();
	void giveUpBtnClicked();
	void saveBtnClicked();
	void returnBtnClicked();
	void boardClicked();						// 棋盘被点击响应事件
};

/*
	游戏类型

	@author 叶志枫
*/
const enum GameType
{
	NONE,		// 未开始游戏
	PVE,		// 人机对战
	PVP,		// 人人对战
	ONLINE		// 联机对战
};