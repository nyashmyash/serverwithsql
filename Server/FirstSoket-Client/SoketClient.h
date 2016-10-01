#pragma once
#include <winsock.h>
#define BUFSIZE 100		
#define PORT 3000	

class SoketClient
{
private:

	WSADATA wsaData;
	SOCKET hServSock;
	SOCKADDR_IN servAddr;



public:
	SoketClient();
	~SoketClient();

	bool init();
	void Loop();

};

