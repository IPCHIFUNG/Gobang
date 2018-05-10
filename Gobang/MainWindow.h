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
	void clearBoard();									// �������
	void showStep(Gobang::Step step, int type);			// ��ʾһ����
	void highlightStep(Gobang::Step step);				// ��������
	void setBackgroundMusic(bool isOn);					// ���ź���ͣ��������
	void playSoundEffects();							// ����������Ч

	void setHomePageBtnVisable(bool isOn);				// ������ҳ��ť�Ŀɼ���
	void setGamePageBtnVisable(bool isOn);				// ������Ϸҳ��ť�Ŀɼ���

	void showWinnerDialog(int type);					// ��ʾʤ����Ϣ

private slots:
	void buttonClicked();								// ��ť�������Ӧ�¼�
	void boardClicked();								// ���̱������Ӧ�¼�
};