#include "GameInterface.h"

GameInterface::GameInterface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

/*
��ʾһ����

@author ������
@para ��һ������
*/
void GameInterface::showStep(Gobang::Step step)
{

}

/*
���ź���ͣ��������

@author ������
@para �Ƿ񲥷�����
*/
void GameInterface::setBackgroundMusic(bool isOn)
{

}

/*
����������Ч

@author ������
*/
void GameInterface::playSoundEffects()
{

}

/*
���̱������Ӧ�¼�

@author ������
*/
void GameInterface::boardClicked()
{
	QString str;
}