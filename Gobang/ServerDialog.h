/* ----------------------------------------------------------------- */
/*
	���������ӵ���������������ս
	����Ϊ����������������Ҳ��������������

	@author - Ҷ־��
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
	void changeButton(int index);			// tabҳ�л�ʱ�ı䰴ť
	void cancelBtnClicked();				// ȡ����ť��Ӧ
};

#endif // !DIALOG_H