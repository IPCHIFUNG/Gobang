#include "ServerDialog.h"
#include "ui_ServerDialog.h"

ServerDialog::ServerDialog(QWidget *parent)
	: QDialog(parent), ui(new Ui::ServerDialog)
{
	ui->setupUi(this);

	this->move(parent->geometry().center() - this->rect().center());

	connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changeButton(int)));
	connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(hostBtnClicked()));
	connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(cancelBtnClicked()));
}

ServerDialog::~ServerDialog()
{
	delete ui;
}

/*
	tab页切换时改变按钮

	@author - 叶志枫
	@para int - 切换到的tab页页数
*/
void ServerDialog::changeButton(int index)
{
	if (index == 0)
	{
		ui->btn_ok->setText(QString::fromLocal8Bit("开启主机"));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(connectBtnClicked()));
		connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(hostBtnClicked()));
	}
	else
	{
		ui->btn_ok->setText(QString::fromLocal8Bit("连接"));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(hostBtnClicked()));
		connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(connectBtnClicked()));
	}
}

/*
	开启主机按钮响应

	@author - 叶志枫
*/
void ServerDialog::hostBtnClicked()
{
}

/*
	连接按钮响应

	@author - 叶志枫
*/
void ServerDialog::connectBtnClicked()
{
}

/*
	取消按钮响应

	@author - 叶志枫
*/
void ServerDialog::cancelBtnClicked()
{
	this->close();
}