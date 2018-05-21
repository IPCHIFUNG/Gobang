#include "ServerDialog.h"
#include "ui_ServerDialog.h"

ServerDialog::ServerDialog(QWidget *parent)
	: QDialog(parent), ui(new Ui::ServerDialog)
{
	ui->setupUi(this);
	okClicked = false;

	// 设置窗口标题
	this->setWindowTitle(QString::fromLocal8Bit("联机对战"));
	// 设置窗口居中
	this->move(parent->geometry().center() - this->rect().center());

	// 初始化信号与槽
	connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changeButton(int)));
	connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(loginBtnClicked()));
	connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(cancelBtnClicked()));
}

ServerDialog::~ServerDialog()
{
	delete ui;
}

void ServerDialog::setMainWindow(MainWindow * mainWindow)
{
	this->mainWindow = mainWindow;
}

/*
	返回确定按钮是否被点击

	@author - 叶志枫
	@return bool - 确定按钮是否被点击
*/
bool ServerDialog::isOKClicked()
{
	return okClicked;
}

/*
	tab页切换时改变按钮

	@author - 叶志枫
	@para int - 切换到的tab页页数
*/
void ServerDialog::changeButton(int index)
{
	switch (index)
	{
	case 0:
		ui->btn_ok->setText(QString::fromLocal8Bit("登录"));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(connectBtnClicked()));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(hostBtnClicked()));
		connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(loginBtnClicked()));
		break;
	case 1:
		ui->btn_ok->setText(QString::fromLocal8Bit("开启主机"));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(loginBtnClicked()));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(connectBtnClicked()));
		connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(hostBtnClicked()));
		break;
	case 2:
		ui->btn_ok->setText(QString::fromLocal8Bit("连接"));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(loginBtnClicked()));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(hostBtnClicked()));
		connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(connectBtnClicked()));
		break;
	default:
		break;
	}
}

/*
	登录按钮响应

	@author - 叶志枫
*/
void ServerDialog::loginBtnClicked()
{

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