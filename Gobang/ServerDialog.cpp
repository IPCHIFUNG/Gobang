#include "ServerDialog.h"
#include "ui_ServerDialog.h"


ServerDialog::ServerDialog(QWidget *parent)
	: QDialog(parent), ui(new Ui::ServerDialog)
{
	ui->setupUi(this);
	okClicked = false;

	// ���ô��ڱ���
	this->setWindowTitle(QString::fromLocal8Bit("������ս"));
	// ���ô��ھ���
	this->move(parent->geometry().center() - this->rect().center());

	// ��ʼ���ź����
	connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changeButton(int)));
	connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(loginBtnClicked()));
	connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(cancelBtnClicked()));
}

ServerDialog::~ServerDialog()
{
	delete ui;
}

/*
	����ȷ����ť�Ƿ񱻵��

	@author - Ҷ־��
	@return bool - ȷ����ť�Ƿ񱻵��
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
	tabҳ�л�ʱ�ı䰴ť

	@author - Ҷ־��
	@para int - �л�����tabҳҳ��
*/
void ServerDialog::changeButton(int index)
{
	switch (index)
	{
	case 0:
		ui->btn_ok->setText(QString::fromLocal8Bit("��¼"));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(connectBtnClicked()));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(hostBtnClicked()));
		connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(loginBtnClicked()));
		break;
	case 1:
		ui->btn_ok->setText(QString::fromLocal8Bit("��������"));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(loginBtnClicked()));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(connectBtnClicked()));
		connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(hostBtnClicked()));
		break;
	case 2:
		ui->btn_ok->setText(QString::fromLocal8Bit("����"));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(loginBtnClicked()));
		disconnect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(hostBtnClicked()));
		connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(connectBtnClicked()));
		break;
	default:
		break;
	}
}

/*
	��¼��ť��Ӧ

	@author - ������
*/
void ServerDialog::loginBtnClicked()
{

}

/*
	����������ť��Ӧ

	@author - ������
*/
void ServerDialog::hostBtnClicked()
{

	QString text = ui->le_server_port->text();
	bool ok = false;

	if (text == "")
	{
		QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("�˿ںŲ���Ϊ��"));
		return;
	}

	int addr = text.toInt(&ok, 10);
	if (false == ok) {
		QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("�˿ںű���Ϊ������"));
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
	���Ӱ�ť��Ӧ

	@author - ������
*/
void ServerDialog::connectBtnClicked()
{
	QString text1 = ui->le_ip->text();
	QString text2 = ui->le_client_port->text();
	bool ok = false;

	if (text1 == "" || text2 == "")
	{
		QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("IP��ַ��˿�����Ϊ��"));
		return;
	}

	char*  ip = "";
	QByteArray ba = text1.toLatin1();
	ip = ba.data();
	int port = text2.toInt(&ok, 10);

	if (false == ok) {
		QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("�˿ںű���Ϊ������"));
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
	ȡ����ť��Ӧ

	@author - Ҷ־��
*/
void ServerDialog::cancelBtnClicked()
{
	this->close();
}