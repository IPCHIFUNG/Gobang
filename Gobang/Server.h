#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include<stdio.h>
#include <stdlib.h>
#include<WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include<string>
#include<qMessageBox>
#include<thread>

using namespace std;

class Server
{
public:
	Server(char *IPAddr, int port);
	Server(int port);
	~Server();
	void server_begin();
	void client_begin();

private:
	SOCKET s;
	int port;
	char * IPAddr;
	int x, y, operation;
	void setMessage(int, int);
	void setMessage(int);
	int getOperation(char []);
};


#endif // !SERVER_H
