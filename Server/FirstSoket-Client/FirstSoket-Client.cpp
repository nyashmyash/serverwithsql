// FirstSoket-Client.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

