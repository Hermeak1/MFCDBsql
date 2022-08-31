#include "pch.h"
#include "CMyBook.h"

CMyBook::CMyBook(int _id, CString name, CString _author, int _price, CString _other)
	: id(_id), bookname(name), author(_author), price(_price), other(_other)
{
	
}