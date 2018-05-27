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
	x = 2;
	y = 3;
	operation = -1;
}

Server::~Server()
{
	closesocket(s);
	WSACleanup();
}

void Server::server_begin()
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 0), &data) != 0)
	{
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("服务端类库加载失败"));
		return;
	}

	//创建socket
	SOCKET s2;
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
		QMessageBox::about(NULL, "Error", "Listen failed");
		return;
	}
	s2 = accept(s, (sockaddr*)&addr2, &addrSize);
	if (s2 == SOCKET_ERROR)
	{
		
	}
	
	while (true) {
		
		QMessageBox::about(NULL, "Tip", (inet_ntoa(addr2.sin_addr)) + QString::fromLocal8Bit("接收连接成功"));

		if (x != -1 && y != -1)
		{
			string str = ServerMsgItem(x, y).convertToString();
			if (send(s2, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
				QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("服务端发送失败"));
				return;
			}
			x = -1;
			y = -1;
		}
		if (operation != -1) {
			string str = ServerMsgItem(operation).convertToString();
			if (send(s2, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
				QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("服务端发送失败"));
				return;
			}
		}

		char recvBuf[] = {""};
		int nLen=recv(s, recvBuf, sizeof(recvBuf), 0);
		if (nLen <= 0)
		{
			QMessageBox::about(NULL, "Error", "Recv failed");
			break;
		}
		//getOperation(recvBuf);
		QMessageBox::about(NULL, "fuwuduan Out", recvBuf);
		
	
	}
	closesocket(s2);
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
	
	//接收数据 
	//char *message1 = "";
	//recv(s, message1, sizeof(message1), 0);
	//QString str = QString(QLatin1String(message1));
	//QMessageBox::about(NULL, "Sussess", message1);
	char recvBuf[] = { "" };
	int nLen = recv(s, recvBuf, sizeof(recvBuf), 0);
	if (nLen <= 0)
	{
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("客户端接收失败"));
		return;
	}
	QMessageBox::about(NULL, "kefuduan out",recvBuf);
	//getOperation(recvBuf);

	//发送数据
	if (x != -1 && y != -1)
	{
		string str = ServerMsgItem(x, y).convertToString();

		if (send(s, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("客户端发送失败"));
			return;
		}
		x = -1;
		y = -1;
	}
	if (operation != -1) {
		string str = ServerMsgItem(operation).convertToString();
		if (send(s, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("服务端发送失败"));
			return;
		}
	}
	
	

}

void Server::setMessage(int x,int y)
{
	this->x = x;
	this->y = y;
}

void Server::setMessage(int operation)
{
	this->operation = operation;
}

int Server::getOperation(char buffer[])
{
	int op;
	if (buffer[16] == '0')
	{

	}
	else
	{
		switch (buffer[16]) {
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
	}
	
	return 0;
}


