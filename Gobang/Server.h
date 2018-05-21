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
	Server(char *IPAddr, int port);
	Server(int port);
	~Server();
	void server_begin(char*);
	void client_begin(char*);
	
private:
	int port;
	char * IPAddr;
	WSADATA data;
};


#endif // !SERVER_H
