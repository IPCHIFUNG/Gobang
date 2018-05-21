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

void ServerDialog::setMainWindow(MainWindow * mainWindow)
{
	this->mainWindow = mainWindow;
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

	@author - Ҷ־��
*/
void ServerDialog::loginBtnClicked()
{

}

/*
	����������ť��Ӧ

	@author - Ҷ־��
*/
void ServerDialog::hostBtnClicked()
{
}

/*
	���Ӱ�ť��Ӧ

	@author - Ҷ־��
*/
void ServerDialog::connectBtnClicked()
{
}

/*
	ȡ����ť��Ӧ

	@author - Ҷ־��
*/
void ServerDialog::cancelBtnClicked()
{
	this->close();
}