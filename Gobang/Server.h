#ifndef SERVER_H
#define SERVER_H

#include<stdio.h>
#include <stdlib.h>
#include<WinSock2.h>
#include<WinSock.h>

#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include<string>
#include<qMessageBox>
#include<Qthread>

using namespace std;

class Server : public QThread
{
	Q_OBJECT
public:
	explicit Server(char *IPAddr, int port);
	Server(int port);
	~Server();
public:
	void server_start();                  //开启服务端
	void client_start();                  //开启客户端
	void msg_send(int x, int y,int operation);          //网络发送信息

private:
	SOCKET server_s;
	SOCKET client_s;
	int x, y;
	int operation;
	int port;
	char * IPAddr;
	bool judge;
	
private:
	void sendMessage(SOCKET target, string msg);        //

protected:
	virtual void run();

signals:
	void msg_rec(int operation, int x, int y);
};


#endif // !SERVER_H
