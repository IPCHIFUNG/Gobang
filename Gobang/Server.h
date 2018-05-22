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

using namespace std;

class Server
{
public:
	Server(char *IPAddr, int port);
	Server(int port);
	~Server();
	void server_begin(char*);
	void client_begin();
	
private:
	int port;
	char * IPAddr;
	
};


#endif // !SERVER_H
