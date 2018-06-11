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
}

Server::~Server()
{
	closesocket(server_s);
	closesocket(client_s);
	WSACleanup();
}

/*
    ����������

	@author ������
*/
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
	judge = false;
}

/*
    �����ͻ���

    @author ������
*/
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
	QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("�ͻ������ӳɹ�"));
	judge = true;
}

/*
    ��ui������Ϣ

	@author ������
	@para x,y ��һ������λ��
	@para operation ���Ӳ���
    
*/
void Server::msg_send(int x, int y,int operation)
{
	string msg;
	if (operation == 0)
		msg = ServerMsgItem(x, y).convertToString();
	else
		msg = ServerMsgItem(operation).convertToString();
	if(judge)
		sendMessage(server_s, msg);
	else
		sendMessage(client_s, msg);
}

/*
    ������Ϣ����

	@author ������
    @para target Ŀ���׽���
    @para msg Ŀ����Ϣ
    
*/
void Server::sendMessage(SOCKET target, string msg)
{
	if (send(target, msg.data(), msg.length(), 0) == SOCKET_ERROR)
		throw "Send error";
}

/*
    ������Ϣ�߳� 

    @author ������
*/
void Server::run()
{
	while (true)
	{
		char recvBuf[1024] ;
		memset(recvBuf, 0, sizeof(recvBuf));
		int nLen;
		if(judge)
			nLen = recv(server_s, recvBuf, sizeof(recvBuf), 0);
		else
			nLen = recv(client_s, recvBuf, sizeof(recvBuf), 0);
		if (nLen <= 0)
		{
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("�ͻ��˽���ʧ��"));
			return;
		}
		QMessageBox::about(NULL, "yunxing success", recvBuf);

		int op = ServerMsgItem::getOperationFromString(recvBuf);
		switch (op)
		{
		case OperationType::WALK:
			try
			{
				int x = ServerMsgItem::getXFromString(recvBuf);
				int y = ServerMsgItem::getYFromString(recvBuf);
				emit msg_rec(WALK, x, y);
			}
			catch (const std::exception&)
			{
				QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("����ת��ʧ�ܣ�run��"));
			}
			
			break;
		default:
			if (op < 0 || op > 7)
				throw"invalue operation";
			emit msg_rec(op, -1, -1);
			break;
		}
	}
	
	exec();
	
}














