#ifndef SERVER_H
#define SERVER_H

#include <thread>

class Server
{
public:
	Server(char * IPAddr, int port);
	Server(int port);
	~Server();

private:

private:
	int port;
	char * IPAddr;

};


#endif // !SERVER_H
