#pragma once
#include <mysql.h>
#include <vector>
#include "CMyBook.h"
#define DB_HOST "***.***.**"
#define DB_USER  "****"//DB Á¢¼Ó °èÁ¤
#define DB_PASS  "****"//DB °èÁ¤ ¾ÏÈ£
#define DB_NAME "****"//DB ÀÌ¸§ 

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

