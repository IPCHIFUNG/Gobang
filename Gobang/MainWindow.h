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
<<<<<<< HEAD

	//void showStep(Gobang::Step step);			// ��ʾһ����

	//void setBackgroundMusic(bool isOn);		// ���ź���ͣ��������
	//void playSoundEffects();				// ����������Ч
=======
	void setBackgroundMusic(bool isOn);	// ���ź���ͣ��������
>>>>>>> cd7ad7cc68b37563368e5cda2e946e5ed961d45f

private slots:
	void buttonClicked();				// ��ť�������Ӧ�¼�
};