#include "GameInterface.h"

GameInterface::GameInterface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void GameInterface::showStep(Gobang::Step step)		// ��ʾһ����
{

}

void GameInterface::setBackgroundMusic(bool isOn)	// ���ź���ͣ��������
{

}

void GameInterface::playSoundEffects()				// ����������Ч
{

}

void GameInterface::boardClicked()					// ���̱������Ӧ�¼�
{
	QString str;
}