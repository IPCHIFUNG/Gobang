/* ----------------------------------------------------------------- */
/*
	���������ӵ���������������ս
	����Ϊ����������������Ҳ��������������

	@author - Ҷ־��
                                                                     */
/* ----------------------------------------------------------------- */

#ifndef DIALOG_H
#define DIALOG_H

#include "MainWindow.h"
#include"Server.h"
#include <QDialog>

#include<qMessageBox>



namespace Ui {
	class ServerDialog;
}

class ServerDialog : public QDialog
{
	Q_OBJECT

public:
	ServerDialog(QWidget *parent = 0);
	~ServerDialog();

	bool isOKClicked();
	void setMainWindow(MainWindow *mainWindow);
private:
	Ui::ServerDialog * ui;
	MainWindow *mainWindow;
	bool okClicked;							// ����ȷ����ť�Ƿ񱻵��״̬
	

private slots:
	void changeButton(int index);			// tabҳ�л�ʱ�ı䰴ť
	void loginBtnClicked();					// ��¼��ť��Ӧ
	void hostBtnClicked();					// ����������ť��Ӧ
	void connectBtnClicked();				// ���Ӱ�ť��Ӧ
	void cancelBtnClicked();				// ȡ����ť��Ӧ
};

#endif // !DIALOG_H
