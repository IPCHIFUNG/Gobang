#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GameInterface.h"
#include "Gobang.h"

class GameInterface : public QMainWindow
{
	Q_OBJECT

public:
	GameInterface(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainWindow ui;

private:
	void showStep(Gobang::Step step);	// 显示一步棋
	void setBackgroundMusic(bool isOn);	// 播放和暂停背景音乐
	void playSoundEffects();			// 播放落子音效

private slots:
	void boardClicked();				// 棋盘被点击响应事件
};