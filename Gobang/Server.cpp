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
    开启服务器

	@author 王锴贞
*/
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
	judge = false;
}

/*
    开启客户端

    @author 王锴贞
*/
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
	QMessageBox::about(NULL, "Tip", QString::fromLocal8Bit("客户端连接成功"));
	judge = true;
}

/*
    向ui发送信息

	@author 王锴贞
	@para x,y 下一步棋子位置
	@para operation 棋子操作
    
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
    发送信息函数

	@author 王锴贞
    @para target 目标套接字
    @para msg 目标信息
    
*/
void Server::sendMessage(SOCKET target, string msg)
{
	if (send(target, msg.data(), msg.length(), 0) == SOCKET_ERROR)
		throw "Send error";
}

/*
    接收消息线程 

    @author 王锴贞
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
			QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("客户端接收失败"));
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
				QMessageBox::about(NULL, "Error", QString::fromLocal8Bit("数据转化失败（run）"));
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














