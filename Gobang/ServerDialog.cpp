#include "ServerDialog.h"
#include "ui_ServerDialog.h"

ServerDialog::ServerDialog(QWidget *parent)
	: QDialog(parent), ui(new Ui::ServerDialog)
{
	ui->setupUi(this);

	this->move(parent->geometry().center() - this->rect().center());

	connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changeButton(int)));
	connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(cancelBtnClicked()));
}

ServerDialog::~ServerDialog()
{
	delete ui;
}

/*
	tabҳ�л�ʱ�ı䰴ť

	@author - Ҷ־��
	@para int - �л�����tabҳҳ��
*/
void ServerDialog::changeButton(int index)
{
	if (index == 0)
	{
		ui->btn_ok->setText(QString::fromLocal8Bit("��������"));
	}
	else
	{
		ui->btn_ok->setText(QString::fromLocal8Bit("����"));
	}
}

/*
	ȡ����ť��Ӧ

	@author - Ҷ־��
*/
void ServerDialog::cancelBtnClicked()
{
	this->close();
}