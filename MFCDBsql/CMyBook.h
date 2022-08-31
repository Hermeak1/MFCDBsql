#pragma once
class CMyBook
{
public:
	int id;
	CString bookname;
	CString author;
	int price;
	CString other;

	CMyBook(int _id, CString name, CString _author, int _price, CString _other);
};

