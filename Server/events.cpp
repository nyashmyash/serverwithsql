#include "stdafx.h"
#include "events.h"
#include <Strsafe.h>
#include <list>
#include <iostream>
#include <sstream>
#include <ctime>


events::events(int _id, int _timeev, std::string _sourceev, std::string _typeev)
{
	id = _id;
	timeev = _timeev;
	typeev = _typeev;
	sourceev = _sourceev;
}


events::events(std::string mess)
{
	getfrommessage(mess);
}

void events::setid(int _id)
{
	id = _id;
}

int events::getid()
{
	return id;
}

int events::gettimeev()
{
	return timeev;
}

std::string events::getsourceev()
{
	return sourceev;
}

std::string events::gettypeev()
{
	return typeev;
}

void events::getfrommessage(std::string mess)
{
	int i = 0;
	std::istringstream ist(mess);
	std::string tmp;
	while ( ist >> tmp )
	{
		if (i == 0)
			id = atoi(tmp.c_str());
		if (i == 1)
			timeev = atoi(tmp.c_str());
		if (i == 2)
			sourceev = tmp.c_str();
		if (i == 3)
			typeev = tmp.c_str();
		i++;
	}
}

std::string events::setmessage()
{
	char str[1000];
	sprintf_s(str, "%d %d %s %s", id, timeev, sourceev.c_str(), typeev.c_str());
	return str;
}
std::string events::printvalues()
{
	char str[1000];
	time_t time = timeev;
	tm ts;
	localtime_s(&ts,&time);
	char szBuffer[80] = "DD-MM-YY HH:MM:SS"; 
	strftime(szBuffer, sizeof(szBuffer), "%d-%b-%Y %X%p", &ts);

	sprintf_s(str, "%d %s %s %s", id, szBuffer, sourceev.c_str(), typeev.c_str());
	return str;
}
std::string events::setsqlmsg()
{
	char str[1000];
	sprintf_s(str, "%d, %d, '%s', '%s'", id, timeev, sourceev.c_str(), typeev.c_str());
	return str;
}

events::~events(void)
{
}
