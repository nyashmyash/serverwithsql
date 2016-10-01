// FirstSoket-Client.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "SoketClient.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SoketClient Client;

	if (Client.init())
	{
		Client.Loop();
	}

	return 0;
}

