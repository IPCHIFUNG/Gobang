#include "GameInterface.h"

GameInterface::GameInterface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

/*
显示一步棋

@author 王开阳
@para 下一步落子
*/
void GameInterface::showStep(Gobang::Step step)
{

}

/*
播放和暂停背景音乐

@author 王开阳
@para 是否播放音乐
*/
void GameInterface::setBackgroundMusic(bool isOn)
{

}

/*
播放落子音效

@author 王开阳
*/
void GameInterface::playSoundEffects()
{

}

/*
棋盘被点击响应事件

@author 王开阳
*/
void GameInterface::boardClicked()
{
	QString str;
}