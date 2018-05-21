#include "Server.h"

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
	delete this;
}

void Server::server_begin(char *message)
{
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		printf("Failed to load Winsock");
		return;
	}

	//����socket
	SOCKET s, s2;
	s = socket(AF_INET, SOCK_STREAM, 0);

	//��ʼ����ַ
	sockaddr_in addr,addr2;
	int addrSize = sizeof(addr2);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	//��socket
	bind(s, (sockaddr*)&addr, addrSize);
	listen(s, 5);                         //set max connect number is 5

	cout << "Server is started!" << endl;

	//����
	while (true)
	{
		s2 = accept(s, (sockaddr*)&addr2, &addrSize);

		if (s2 != NULL)
		{
			cout << inet_ntoa(addr2.sin_addr) << "is connected!" << endl;
			send(s2, message, sizeof(message), 0);

			//recv(s, recvBuf, sizeof(recvBuf), 0);

			closesocket(s2);
			closesocket(s);
			WSACleanup();
			break;
		}
		else
		{
			Sleep(100);
		}
	}
}

void Server::client_begin(char *message)
{
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		printf("Failed to load Winsock");
		return;
	}

	//����socket
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == s) {
		QMessageBox::about(NULL, "Error1", QString::fromLocal8Bit("�׽��ִ�������"));
		return;
	}

	sockaddr_in addr;
	int addrSize = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(IPAddr);

	cout << "Client is started!" << endl;

	//���ӷ�����
	if (connect(s, (sockaddr*)&addr, addrSize) == INVALID_SOCKET) {
		QMessageBox::about(NULL, "Error2", QString::fromLocal8Bit("����ʧ��"));
		return;
	}
	else
	{
		//��������  
		recv(s, message, sizeof(message), 0);
	}

	closesocket(s);
	WSACleanup();


}