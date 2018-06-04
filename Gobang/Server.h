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
	void server_start();                                        //���������
	void client_start();                                        //�����ͻ���
	void msg_send(int x, int y,int operation);                  //���緢����Ϣ
	void setRecv_mes(int x, int y, int operation);              //�����߳̽��ܵ���Ϣ
	int getRecv_mes_op();                                       //���operation
	Gobang::Step getRecv_mes_step();                            //�����һ��λ��
private:
	SOCKET server_s;
	SOCKET client_s;
	
	int port;
	char * IPAddr;
	int x, y, operation;
	bool judge;
	
private:
	void sendMessage(SOCKET target, string msg);        //send����

protected:
	virtual void run();                                //������Ϣ�߳�           

signals:
	void msg_rec(int operation, int x, int y);         //������Ϣ����ui�����ź�
};


#endif // !SERVER_H
