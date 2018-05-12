/* ----------------------------------------------------------------- */
/*
	服务器连接弹窗，用于联机对战
	可作为主机创建服务器，也可连接至服务器

	@author - 叶志枫
                                                                     */
/* ----------------------------------------------------------------- */

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
	class ServerDialog;
}

class ServerDialog : public QDialog
{
	Q_OBJECT


public:
	ServerDialog(QWidget *parent = 0);
	~ServerDialog();

private:
	Ui::ServerDialog *ui;

private slots:
	void changeButton(int index);			// tab页切换时改变按钮
	void cancelBtnClicked();				// 取消按钮响应
};

#endif // !DIALOG_H