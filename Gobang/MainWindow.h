#pragma once

#include "ui_MainWindow.h"
#include "Gobang.h"
#include "Server.h"

#include <QtWidgets/QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QCloseEvent>
#include <string>

class MainWindow;

/* ---------------------------------------------- */
/*
		AI�����̣߳�����Start�Կ����̣߳�
									 -By Ҷ־��   */
/* ---------------------------------------------- */
class AIThread
{
public:
	AIThread();
	~AIThread();
	bool Start(MainWindow *mainapp, int color);
	void Main();

	MainWindow *mainapp;

private:
	int color;
};


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	Gobang::Step getStepFromScreen();						// ����Ļ��ȡ��������
	void walkAStep(Gobang::Step new_step);
	void showStep(Gobang::Step step, int type);				// ��ʾһ����
	void playSoundEffects();								// ����������Ч
	void highlightStep(Gobang::Step step, int type);		// ��������
	void showWinnerDialog();								// ��ʾʤ����Ϣ

	Gobang & getGobang() { return gobang; };
	int getGameType() { return gameType; };
	Server *s;

private:
	Ui::MainWindowClass ui;
	int gameType;
	std::string ranking;
	Gobang gobang;
	QMediaPlayer music;
	QMediaPlayer soundEff;
	QLabel chess[BOARDLENGTH][BOARDLENGTH];

	QPixmap blackChess;
	QPixmap whiteChess;
	QPixmap HLBlackChess;
	QPixmap HLWhiteChess;

private:
	void clearBoard();							// �������
	void setBackgroundMusic();					// ���ź���ͣ��������
	void closeEvent(QCloseEvent *event);		// ���ڹر��¼�

	void setHomePageBtnVisable(bool isOn);		// ������ҳ��ť�Ŀɼ���
	void setGamePageBtnVisable(bool isOn);		// ������Ϸҳ��ť�Ŀɼ���
	std::string selectFile();					// ѡ���ȡ�ļ�
	std::string selectDirectory();				// ѡ�񱣴�Ŀ¼
	bool isMusicOn;								// �������ֿ���
	int isRestricted;							// �Ƿ�����ֿ�ʼ��Ϸ
	int isFirstHand;							// �Ƿ����ֿ�ʼ��Ϸ
	int winner;									// ��ʤ���������ɫ

	AIThread computer;
	int computerColor;

private slots:
	void btnsClicked();							// ��ť�������Ӧ�¼�
	void pveBtnClicked();
	void pvpBtnClicked();
	void onlineBtnClicked();
	void loadBtnClicked();
	void restartBtnClicked();					// ���¿�ʼ��ť�������Ӧ�¼�
	void promptBtnClicked();
	void retractBtnClicked();
	void giveUpBtnClicked();
	void saveBtnClicked();
	void returnBtnClicked();
	void boardClicked();						// ���̱������Ӧ�¼�
};

/*
	��Ϸ����

	@author Ҷ־��
*/
const enum GameType
{
	NONE,		// δ��ʼ��Ϸ
	PVE,		// �˻���ս
	PVP,		// ���˶�ս
	ONLINE		// ������ս
};