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
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 0), &data) != 0)
	{
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("服务端类库加载失败"));
		return;
	}

	//创建socket
	SOCKET s, s2;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == s) {
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("服务端套接字创建错误"));
		return;
	}

	//初始化地址
	sockaddr_in addr, addr2;
	int addrSize = sizeof(addr2);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	//绑定socket
	::bind(s, (sockaddr*)&addr, addrSize);
	/*if (retVal == SOCKET_ERROR) {
		printf("Failed bind:%d\n", WSAGetLastError());
		return;
	}
	*/

	QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("服务器开启"));

	//监听

	if (listen(s, 2) == SOCKET_ERROR) {
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("Listen failed"));
		return;
	}
	s2 = accept(s, (sockaddr*)&addr2, &addrSize);
	if (s2 != SOCKET_ERROR)
	{
		QMessageBox::about(NULL, "Tip", (inet_ntoa(addr2.sin_addr)));
		//cout << inet_ntoa(addr2.sin_addr) << "is connected!" << endl;
		send(s2, message, sizeof(message), 0);

		//recv(s, recvBuf, sizeof(recvBuf), 0);


	}
	//else
	//{
	//	Sleep(100);}

	closesocket(s2);
	closesocket(s);
	WSACleanup();
}

void Server::client_begin()
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 0), &data) != 0)
	{
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("客户端类库加载失败"));
		return;
	}

	//创建socket
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == s) {
		QMessageBox::about(NULL, "Error1", QString::fromLocal8Bit("套接字创建错误"));
		return;
	}

	sockaddr_in addr;
	int addrSize = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(IPAddr);

	QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("客户端开启"));

	//连接服务器
	if (connect(s, (sockaddr*)&addr, addrSize) == INVALID_SOCKET) {
		QMessageBox::about(NULL, "Error2", QString::fromLocal8Bit("连接失败"));
		return;
	}
	else
	{
		//接收数据 
		char *message1;
		recv(s, message1, sizeof(message1), 0);
		QMessageBox::about(NULL, "Sussess", message1);
	}

	closesocket(s);
	WSACleanup();

}