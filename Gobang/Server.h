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
	void openListeningThread();
	void openConnectingThread();

	static void listeningThread();
	static void connectingThread();

private:
	int port;
	char * IPAddr;

	
};


#endif // !SERVER_H
