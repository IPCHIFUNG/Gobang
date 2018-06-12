#pragma once

#include "ui_MainWindow.h"
#include "Gobang.h"
#include "Server.h"

#include <QtWidgets/QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QCloseEvent>
#include <qinputdialog.h>
#include <string>

class MainWindow;

/* ---------------------------------------------- */
/*
		AI�����̣߳�����Start�Կ����̣߳�
									 -By Ҷ־��   */
/* ---------------------------------------------- */
class AIThread : public QObject
{
	Q_OBJECT

public:
	AIThread();
	~AIThread();
	bool Start(MainWindow *mainapp, int color);
	void Main();
	bool isThinking() { return isCalculating; };

	MainWindow *mainapp;

signals:
	void showWinnerDialog();
signals:
	void showInf(int color, int x, int y);

private:
	int color;
	bool isCalculating = false;
};


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	Gobang::Step getStepFromScreen();								// ����Ļ��ȡ��������
	void walkAStep(Gobang::Step new_step);
	void showStep(Gobang::Step step, int type);						// ��ʾһ����
	void delInf();													// ɾ��������Ϣ
	void playSoundEffects();										// ����������Ч
	void highlightStep(Gobang::Step step, int type);				// ��������
	void highlightSteps(std::deque<Gobang::Step> steps);			// ��������Ⱥ
	void showRankings();											// ��ʾ���а�

	Gobang & getGobang() { return gobang; };
	int getIsRestricted() { return isRestricted; };
	int gameType;													// ��Ϸ����
	int winner;														// ��ʤ���������ɫ
	Server *s;

private:
	Ui::MainWindowClass ui;
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
	void closeEvent(QCloseEvent *event);		// ���ڹر��¼�
	std::string getName();						// ����ʤ���������
	void setHomePageBtnVisable(bool isOn);		// ������ҳ��ť�Ŀɼ���
	void setGamePageBtnVisable(bool isOn);		// ������Ϸҳ��ť�Ŀɼ���
	std::string selectFile();					// ѡ���ȡ�ļ�
	std::string selectDirectory();				// ѡ�񱣴�Ŀ¼
	bool isMusicOn;								// ���ź���ͣ��������
	int isRestricted;							// �Ƿ�����ֿ�ʼ��Ϸ
	int isFirstHand;							// �Ƿ����ֿ�ʼ��Ϸ

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

public slots:
	void showWinnerDialog();								// ��ʾʤ����Ϣ
	void showInf(int color, int x, int y);					// ��ʾ������Ϣ
	void handleRecv_mes(int operation, int x, int y);       //����������һ�˲�����Ϣ
	void Do_msg(char *msg);                                 //����������һ��������Ϣ
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