#pragma once
#include <mysql.h>
#include <vector>
#include "CMyBook.h"
#define DB_HOST "127.0.0.1"
#define DB_USER  "root"//DB ���� ����
#define DB_PASS  "1234"//DB ���� ��ȣ
#define DB_NAME "bookdb"//DB �̸� 

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

