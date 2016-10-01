#include "stdafx.h"
#include "sqlite3.h"
#include "SoketServer.h"


CSoketServer::CSoketServer()
{
}


CSoketServer::~CSoketServer()
{
}

bool CSoketServer::init()
{

	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		printf("error");
		return false;
	}


	hServSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	 
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);


	result = bind(hServSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));

	if (result != 0)
	{
		printf("error");
		return false;
	}


	listen(hServSock, 10);

	//clntAddr = { 0 };
	int size = sizeof(SOCKADDR_IN);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &size);
	
	if (hClntSock == SOCKET_ERROR)
	{
		printf("error");
		return false;
	}

	printf("IP : %s , Port : %d\n", inet_ntoa(clntAddr.sin_addr), clntAddr.sin_port);


	return true;
}

void CSoketServer::Loop()
{
	while (1)
	{
		char buf[255];
		memset(buf, 0, sizeof(buf));
		int recvsize = recv(hClntSock, buf, sizeof(buf), 0);
	
		if (recvsize > 0)
		{
			buf[recvsize = '\0'];
								
			InsertInBase(buf);		
		}
	}

	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
}
char maxid[10];
static int callback(void *data, int argc, char **argv, char **azColName){
	 
	if(argc>0 && argv[0]!=0)
		strcpy_s(maxid,argv[0]) ;
	return 0;
}
void CSoketServer::InsertInBase(char * buf)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	std::string sql;
	events ev(buf);
	char* data = "";

	rc = sqlite3_open("test.db", &db);

	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return;
	}else{
		fprintf(stderr, "Opened database successfully\n");
	}
	/* Create SQL statement */
	sql = "CREATE TABLE EVENTS("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"TIMEEV         TIME    NOT NULL," \
		"SOURCEEV       CHAR(50)," \
		"TYPEEV         CHAR(50));";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);

	sql = "SELECT MAX(ID) from EVENTS";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
	if (rc == SQLITE_OK) 
		ev.setid(atoi(maxid)+1);


	sql = "INSERT INTO EVENTS (ID, TIMEEV, SOURCEEV, TYPEEV) "  \
		"VALUES (" + ev.setsqlmsg() + " ); " ;
	
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}else{
		fprintf(stdout, "Records created successfully\n");
	}
	printf("client >> %s\n", ev.printvalues().c_str());
	sqlite3_close(db);
}

