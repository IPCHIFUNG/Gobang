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
	void server_start();
	void client_start();
	void setMessage(int, int);
	void setMessage(int);

private:
	SOCKET server_s;
	SOCKET client_s;

	int port;
	char * IPAddr;
	int x, y, operation;
	
	void server_send();
	void client_send();

protected:
	virtual void run();

signals:
	void resultReady(int value);
};


#endif // !SERVER_H
