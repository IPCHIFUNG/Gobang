#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include<stdio.h>
#include <stdlib.h>
#include<WinSock2.h>
#include<WinSock.h>

#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include<string>
#include<qMessageBox>
#include<thread>
#include "MainWindow.h"

using namespace std;

class Server
{

public:
	Server(char *IPAddr, int port);
	Server(int port);
	~Server();
	void server_begin();
	void client_begin();
	void setMessage(int, int);
	void setMessage(int);
	void setMainWindow(MainWindow * mainWindow);

private:
	SOCKET s;
	int port;
	char * IPAddr;
	int x, y, operation;
	MainWindow * mainWindow;
	
	static void receive(MainWindow*,SOCKET s);
	
	
};


#endif // !SERVER_H
