#pragma once

#include <QtWidgets/QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QCloseEvent>
#include <string>
#include "ui_MainWindow.h"
#include "Gobang.h"
#include "Server.h"
#include "ChessThread.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	Gobang::Step getStepFromScreen();			// ����Ļ��ȡ��������
	void showStep(Gobang::Step step, int type);	// ��ʾһ����
	void playSoundEffects();					// ����������Ч
	void highlightStep(Gobang::Step step, int type);		// ��������
	void showWinnerDialog();			// ��ʾʤ����Ϣ
	Gobang & getGobang();
	int getIsRestricted();
	int getGameType();
	void setWinner(int w);
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
	void setBackgroundMusic(bool isOn);			// ���ź���ͣ��������
	void closeEvent(QCloseEvent *event);		// ���ڹر��¼�

	void setHomePageBtnVisable(bool isOn);		// ������ҳ��ť�Ŀɼ���
	void setGamePageBtnVisable(bool isOn);		// ������Ϸҳ��ť�Ŀɼ���
	std::string selectFile();					// ѡ���ȡ�ļ�
	std::string selectDirectory();				// ѡ�񱣴�Ŀ¼
	int isRestricted;							// �Ƿ�����ֿ�ʼ��Ϸ
	int isFirstHand;							// �Ƿ����ֿ�ʼ��Ϸ
	int winner;

private slots:
	void btnsClicked();							// ��ť�������Ӧ�¼�
	void pveBtnClicked();
	void pvpBtnClicked();
	void onlineBtnClicked();
	void loadBtnClicked();
	void restartBtnClicked();
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