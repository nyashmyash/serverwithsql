#pragma once
#include <string>
class events
{
	int id;
	int timeev;
	std::string sourceev;
	std::string typeev;
public:
	events(std::string mess);
	events(int _id, int _timeev, std::string _sourceev, std::string _typeev);
	void setid(int id);
	int getid();
	int gettimeev();
	std::string getsourceev(); 
	std::string gettypeev();
	void getfrommessage(std::string mess);
	std::string setmessage();
	std::string printvalues();
	std::string setsqlmsg();

	~events(void);
};

