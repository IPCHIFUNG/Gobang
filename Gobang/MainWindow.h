#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Gobang.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainWindowClass ui;

private:
	void clearBoard();									// 清空棋盘
	void showStep(Gobang::Step step, int type);			// 显示一步棋
	void highlightStep(Gobang::Step step);				// 高亮棋子
	void setBackgroundMusic(bool isOn);					// 播放和暂停背景音乐
	void playSoundEffects();							// 播放落子音效

	void setHomePageBtnVisable(bool isOn);				// 设置主页按钮的可见性
	void setGamePageBtnVisable(bool isOn);				// 设置游戏页按钮的可见性

	void showWinnerDialog(int type);					// 显示胜方信息

private slots:
	void buttonClicked();								// 按钮被点击响应事件
	void boardClicked();								// 棋盘被点击响应事件
};