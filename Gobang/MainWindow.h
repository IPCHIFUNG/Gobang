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

	//void showStep(Gobang::Step step);			// ��ʾһ����

	//void setBackgroundMusic(bool isOn);		// ���ź���ͣ��������
	//void playSoundEffects();				// ����������Ч

	void setBackgroundMusic(bool isOn);	// ���ź���ͣ��������

private slots:
	void buttonClicked();				// ��ť�������Ӧ�¼�
};