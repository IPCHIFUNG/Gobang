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
	void showStep(Gobang::Step step);	// ��ʾһ����
	void setBackgroundMusic(bool isOn);	// ���ź���ͣ��������
	void playSoundEffects();			// ����������Ч

private slots:
	void boardClicked();				// ���̱������Ӧ�¼�
};