#pragma once
#include <winsock.h>
#include "..\events.h"

#define BUFSIZE 100		
#define PORT 3000		

class CSoketServer
{
private:
	WSADATA wsaData;
	SOCKET hServSock;
	SOCKADDR_IN servAddr;
	SOCKET hClntSock;
	SOCKADDR_IN clntAddr;

	int Rvalue;
	int Lvalue;
	
public:
	CSoketServer();
	~CSoketServer();

	bool init();

	void LastInput();

	void LValueInput();

	void Loop();

	void InsertInBase(char * buf);

};

