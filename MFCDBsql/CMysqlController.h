#pragma once
#include <mysql.h>
#include <vector>
#include "CMyBook.h"
#define DB_HOST "127.0.0.1"
#define DB_USER  "root"//DB 접속 계정
#define DB_PASS  "1234"//DB 계정 암호
#define DB_NAME "bookdb"//DB 이름 

using std::vector;

class	CMysqlController
{
public :
	CMysqlController();
	~CMysqlController();
	bool 	SelectQuery(char* sql, vector<CMyBook*>& result);
	bool	InsertQuery(char* sql);
	bool DeleteQuery(char* sql);
};

