#pragma once

#include <QtWidgets/QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QCloseEvent>
#include <string>
#include "ui_MainWindow.h"
#include "Gobang.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainWindowClass ui;
	int gameType;
	Gobang gobang;
	QMediaPlayer music;
	QMediaPlayer soundEff;
	QLabel chess[BOARDLENGTH][BOARDLENGTH];

private:
	QPixmap blackChess;
	QPixmap whiteChess;

private:
	void clearBoard();									// 清空棋盘
	void showStep(Gobang::Step step, int type);			// 显示一步棋
	void highlightStep(Gobang::Step step);				// 高亮棋子
	void showWinnerDialog(int type);					// 显示胜方信息

	void setBackgroundMusic(bool isOn);					// 播放和暂停背景音乐
	void playSoundEffects();							// 播放落子音效
	void closeEvent(QCloseEvent *event);				// 窗口关闭事件

	void setHomePageBtnVisable(bool isOn);				// 设置主页按钮的可见性
	void setGamePageBtnVisable(bool isOn);				// 设置游戏页按钮的可见性
	std::string selectFile();							// 选择读取文件
	std::string selectDirectory();						// 选择保存目录
	Gobang::Step getStepFromScreen();					// 从屏幕获取棋子坐标

private slots:
	void btnsClicked();									// 按钮被点击响应事件
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
	void boardClicked();								// 棋盘被点击响应事件
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