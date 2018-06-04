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
#include"Gobang.h"

using namespace std;

class Server : public QThread
{
	Q_OBJECT
public:
	explicit Server(char *IPAddr, int port);
	explicit Server(int port);
	~Server();
public: 
	void server_start();                                        //开启服务端
	void client_start();                                        //开启客户端
	void msg_send(int x, int y,int operation);                  //网络发送信息
	void setRecv_mes(int x, int y, int operation);              //设置线程接受的消息
	int getRecv_mes_op();                                       //获得operation
	Gobang::Step getRecv_mes_step();                            //获得下一步位置
private:
	SOCKET server_s;
	SOCKET client_s;
	
	int port;
	char * IPAddr;
	int x, y, operation;
	bool judge;
	
private:
	void sendMessage(SOCKET target, string msg);        //send函数

protected:
	virtual void run();                                //接收消息线程           

signals:
	void msg_rec(int operation, int x, int y);         //接收信息后向ui发送信号
};


#endif // !SERVER_H
