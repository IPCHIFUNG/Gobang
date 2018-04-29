#include "GameInterface.h"

GameInterface::GameInterface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void GameInterface::showStep(Gobang::Step step)		// 显示一步棋
{

}

void GameInterface::setBackgroundMusic(bool isOn)	// 播放和暂停背景音乐
{

}

void GameInterface::playSoundEffects()				// 播放落子音效
{

}

void GameInterface::boardClicked()					// 棋盘被点击响应事件
{
	QString str;
}