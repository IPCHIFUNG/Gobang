#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include<stdio.h>
#include <stdlib.h>
#include<WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include<string>

using namespace std;

class Server
{
public:
	Server(sockaddr_in addr, int port);
	Server(int port);
	~Server();

private:
	void server_begin(char*);
	void client_begin(char*);
private:
	int port;
	sockaddr_in addr;
	//char * IPAddr;
	WSADATA data;
};


#endif // !SERVER_H
