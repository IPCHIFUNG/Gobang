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

/*
	返回确定按钮是否被点击

	@author - 叶志枫
	@return bool - 确定按钮是否被点击
*/
bool ServerDialog::isOKClicked()
{
	return okClicked;
}



void ServerDialog::setMainWindow(MainWindow * mainWindow)
{
	this->mainWindow = mainWindow;
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

	@author - 王锴贞
*/
void ServerDialog::loginBtnClicked()
{

}

/*
	开启主机按钮响应

	@author - 王锴贞
*/
void ServerDialog::hostBtnClicked()
{

	QString text = ui->le_server_port->text();
	bool ok = false;

	if (text == "")
	{
		QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("端口号不能为空"));
		return;
	}

	int addr = text.toInt(&ok, 10);
	if (false == ok) {
		QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("端口号必须为纯数字"));
		return;
	}

	mainWindow->s = new Server(addr);
	mainWindow->s->server_start();

	connect(mainWindow->s, SIGNAL(msg_rec(int, int, int)), mainWindow, SLOT(mainWindow->handleRecv_mes(int x, int y, int operation)));

	mainWindow->s->start();
	okClicked = true;
	this->close();
}

/*
	连接按钮响应

	@author - 王锴贞
*/
void ServerDialog::connectBtnClicked()
{
	QString text1 = ui->le_ip->text();
	QString text2 = ui->le_client_port->text();
	bool ok = false;

	if (text1 == "" || text2 == "")
	{
		QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("IP地址或端口输入为空"));
		return;
	}

	char*  ip = "";
	QByteArray ba = text1.toLatin1();
	ip = ba.data();
	int port = text2.toInt(&ok, 10);

	if (false == ok) {
		QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("端口号必须为纯数字"));
		return;
	}

	mainWindow->s = new Server(ip, port);
	mainWindow->s->client_start();
	connect(mainWindow->s, SIGNAL(msg_rec(int, int, int)), mainWindow, SLOT(mainWindow->handleRecv_mes(int x, int y, int operation)));

	mainWindow->s->start();
	okClicked = true;
	this->close();
}

/*
	取消按钮响应

	@author - 叶志枫
*/
void ServerDialog::cancelBtnClicked()
{
	this->close();
}