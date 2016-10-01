#include "stdafx.h"
#include "SoketClient.h"
#include <stdio.h>
#include "..\events.h"
#include <ctime>


SoketClient::SoketClient()
{
}


SoketClient::~SoketClient()
{
}

bool SoketClient::init()
{
	//버전 생성
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		printf("error");
		return false;
	}

	//소켓 설정(TCP 할지 UDP할지)
	hServSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//아이피 설정
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	result = connect(hServSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));
	if (result == SOCKET_ERROR)
	{
		printf("connect() Error\n");
		return false;
	}


	return true;

}

void SoketClient::Loop()
{
	int count = 0; 
	while (count < 10)
	{
		time_t tm;
		time(&tm);
		events ev(0, tm, "client" ,"process_load");
		std::string str = ev.setmessage();
		int sendsize = send(hServSock, str.c_str(), str.size(), 0);
		if (sendsize)
			printf(">> sended");
		/*while (true)
		{
			char buf[255];
			memset(buf, 0, sizeof(buf));
			recv(hServSock, buf, sizeof(buf), 0);
			printf("%s", buf);

			if (strlen(buf) > 0)
			{
				break;
			}
		}*/
		Sleep(10000);
		count ++;
	}

	
	closesocket(hServSock);
	WSACleanup();
}
