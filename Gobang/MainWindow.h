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
	void setBackgroundMusic(bool isOn);	// ���ź���ͣ��������

private slots:
	void buttonClicked();				// ��ť�������Ӧ�¼�
};