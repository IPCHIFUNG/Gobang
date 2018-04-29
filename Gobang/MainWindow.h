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

	//void showStep(Gobang::Step step);			// 显示一步棋

	//void setBackgroundMusic(bool isOn);		// 播放和暂停背景音乐
	//void playSoundEffects();				// 播放落子音效

	void setBackgroundMusic(bool isOn);	// 播放和暂停背景音乐

private slots:
	void buttonClicked();				// 按钮被点击响应事件
};