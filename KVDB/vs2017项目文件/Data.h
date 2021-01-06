#pragma once
#include"string.h"
class Data
{
public:
	int keylen;
	int valuelen;
	int isdel;
	void clear();
	string key;
	string value;
	Data();
	Data(const string &k, const string &v);
	~Data();
};