#include "Server.h"

Server::Server(sockaddr_in IPAddr, int port)
{
	this->addr = IPAddr;
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

	//创建socket
	SOCKET s, s2;
	s = socket(AF_INET, SOCK_STREAM, 0);

	//初始化地址
	sockaddr_in addr2;
	int addrSize = sizeof(addr2);
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	//绑定socket
	bind(s, (sockaddr*)&addr, addrSize);
	listen(s, 5);                         //set max connect number is 5

	cout << "Server is started!" << endl;

	//监听
	while (true)
	{
		s2 = accept(s, (sockaddr*)&addr2, &addrSize);
		if (s2 != NULL)
		{
			cout << inet_ntoa(addr2.sin_addr) << "is connected!" << endl;
			send(s2, message, sizeof(message), 0);

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

	//创建socket
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);


	sockaddr_in addr;
	int addrSize = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	cout << "Client is started!" << endl;

	//连接服务器
	connect(s, (sockaddr*)&addr, addrSize);

	//接收消息
	recv(s, message, sizeof(message), 0);

	closesocket(s);
	WSACleanup();


}