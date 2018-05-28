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
//开启服务器
void Server::server_start()
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("服务端类库加载失败"));
		return;
	}

	//初始化socket
	server_s = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == server_s) {
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("服务端套接字创建错误"));
		return;
	}

	//初始化地址
	sockaddr_in addrSrv, addrCli;
	int addrSize = sizeof(addrCli);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	addrSrv.sin_addr.S_un.S_addr = INADDR_ANY;

	//绑定socket
	::bind(server_s, (sockaddr*)&addrSrv, addrSize);
	QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("服务器开启"));

	//监听
	if (listen(server_s, 2) == SOCKET_ERROR) {
		QMessageBox::about(NULL, "Error", "Listen failed");
		return;
	}
	client_s = accept(server_s, (sockaddr*)&addrCli, &addrSize);
	if (client_s == SOCKET_ERROR)
	{
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("接收连接错误"));
		return;
	}
	QMessageBox::about(NULL, "Tip", (inet_ntoa(addrCli.sin_addr)) + QString::fromLocal8Bit("接收连接成功"));

}

//开启客户端
void Server::client_start()
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("客户端类库加载失败"));
		return;
	}

	//初始化socket
	server_s = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == server_s) {
		QMessageBox::about(NULL, "Error1", QString::fromLocal8Bit("套接字创建错误"));
		return;
	}

	sockaddr_in addrSrv;
	int addrSize = sizeof(addrSrv);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	addrSrv.sin_addr.S_un.S_addr = inet_addr(IPAddr);

	QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("客户端开启"));

	//连接服务器
	if (::connect(server_s, (sockaddr*)&addrSrv, addrSize) == INVALID_SOCKET) {
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("连接失败"));
		return;
	}
}

//设置操作类型
void Server::setMessage(int x,int y)
{
	this->x = x;
	this->y = y;
}
void Server::setMessage(int operation)
{
	this->operation = operation;
}

//向服务端发送消息
void Server::client_send()
{
	x = 4;
	y = 3;
	if (x != -1 && y != -1)
	{
		string str = ServerMsgItem(x, y).convertToString();

		if (send(server_s, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("客户端发送失败"));
			return;
		}
		x = -1;
		y = -1;
	}
	if (operation != -1) {
		string str = ServerMsgItem(operation).convertToString();
		if (send(server_s, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("服务端发送失败"));
			return;
		}
	}
}

//向客户端发送消息
void Server::server_send() {
	x = 4;
	y = 3;
	if (x != -1 && y != -1)
	{
		string str = ServerMsgItem(x, y).convertToString();

		if (send(client_s, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("客户端发送失败"));
			return;
		}
		x = -1;
		y = -1;
	}
	if (operation != -1) {
		string str = ServerMsgItem(operation).convertToString();
		if (send(client_s, str.data(), sizeof(str), 0) == SOCKET_ERROR) {
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("服务端发送失败"));
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
		QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("客户端接收失败"));
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












