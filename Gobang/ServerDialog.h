/* ----------------------------------------------------------------- */
/*
	服务器连接弹窗，用于联机对战
	可作为主机创建服务器，也可连接至服务器

	@author - 叶志枫
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
	bool okClicked;							// 保存确定按钮是否被点击状态
	

private slots:
	void changeButton(int index);			// tab页切换时改变按钮
	void loginBtnClicked();					// 登录按钮响应
	void hostBtnClicked();					// 开启主机按钮响应
	void connectBtnClicked();				// 连接按钮响应
	void cancelBtnClicked();				// 取消按钮响应
};

#endif // !DIALOG_H
