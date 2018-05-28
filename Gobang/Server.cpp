#include "Server.h"
#include "ServerMsgItem.h"

Server::Server(char *IPAddr, int port)
{
	this->IPAddr = IPAddr;
	this->port = port;
}

Server::Server(int port)
{
	this->port = port;
	x = -1;
	y = -1;
	operation = -1;
}

Server::~Server()
{
	closesocket(server_s);
	closesocket(client_s);
	WSACleanup();
}
//����������
void Server::server_start()
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("�����������ʧ��"));
		return;
	}

	//��ʼ��socket
	server_s = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == server_s) {
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("������׽��ִ�������"));
		return;
	}

	//��ʼ����ַ
	sockaddr_in addrSrv, addrCli;
	int addrSize = sizeof(addrCli);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	addrSrv.sin_addr.S_un.S_addr = INADDR_ANY;

	//��socket
	::bind(server_s, (sockaddr*)&addrSrv, addrSize);
	QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("����������"));

	//����
	if (listen(server_s, 2) == SOCKET_ERROR) {
		QMessageBox::about(NULL, "Error", "Listen failed");
		return;
	}
	client_s = accept(server_s, (sockaddr*)&addrCli, &addrSize);
	if (client_s == SOCKET_ERROR)
	{
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("�������Ӵ���"));
		return;
	}
	QMessageBox::about(NULL, "Tip", (inet_ntoa(addrCli.sin_addr)) + QString::fromLocal8Bit("�������ӳɹ�"));

}

//�����ͻ���
void Server::client_start()
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("�ͻ���������ʧ��"));
		return;
	}

	//��ʼ��socket
	server_s = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == server_s) {
		QMessageBox::about(NULL, "Error1", QString::fromLocal8Bit("�׽��ִ�������"));
		return;
	}

	sockaddr_in addrSrv;
	int addrSize = sizeof(addrSrv);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	addrSrv.sin_addr.S_un.S_addr = inet_addr(IPAddr);

	QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("�ͻ��˿���"));

	//���ӷ�����
	if (::connect(server_s, (sockaddr*)&addrSrv, addrSize) == INVALID_SOCKET) {
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("����ʧ��"));
		return;
	}
}

//���ò�������
void Server::setMessage(int x,int y)
{
	this->x = x;
	this->y = y;
}
void Server::setMessage(int operation)
{
	this->operation = operation;
}

//�����˷�����Ϣ
void Server::client_send()
{
	x = 4;
	y = 3;
	if (x != -1 && y != -1)
	{
		string str = ServerMsgItem(x, y).convertToString();

		if (send(server_s, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("�ͻ��˷���ʧ��"));
			return;
		}
		x = -1;
		y = -1;
	}
	if (operation != -1) {
		string str = ServerMsgItem(operation).convertToString();
		if (send(server_s, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("����˷���ʧ��"));
			return;
		}
	}
}

//��ͻ��˷�����Ϣ
void Server::server_send() {
	x = 4;
	y = 3;
	if (x != -1 && y != -1)
	{
		string str = ServerMsgItem(x, y).convertToString();

		if (send(client_s, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("�ͻ��˷���ʧ��"));
			return;
		}
		x = -1;
		y = -1;
	}
	if (operation != -1) {
		string str = ServerMsgItem(operation).convertToString();
		if (send(client_s, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("����˷���ʧ��"));
			return;
		}
	}
}

void Server::run()
{
	char recvBuf[200] = { "" };
	int nLen = recv(server_s, recvBuf, sizeof(recvBuf), 0);
	if (nLen <= 0)
	{
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("�ͻ��˽���ʧ��"));
		return;
	}
	QMessageBox::about(NULL, "kefuduan out", recvBuf);


	int op;
	if (recvBuf[16] == '0')
	{
		emit resultReady(0);
	}
	else
	{
		switch (recvBuf[16]) {
		case  '1':
			op = 1;
			break;
		case  '2':
			op = 2;
			break;
		case  '3':
			op = 3;
			break;
		case  '4':
			op = 4;
			break;
		case  '5':
			op = 5;
			break;
		case  '6':
			op = 6;
			break;
		case  '7':
			op = 7;
			break;

		default:
			break;
		}
		emit resultReady(op);
	}
	exec();
	
}












