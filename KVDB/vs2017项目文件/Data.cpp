#include"Data.h"
Data::Data()
{

}
void Data::clear()
{
	key.clear();
	value.clear();
	keylen = 0;
	valuelen = 0;
	isdel = 0;
}

Data::Data(const string &k, const string &v)
{
	key = k;
	value = v;
	keylen = k.size();
	valuelen = v.size();
	isdel = false;
}
Data::~Data()
{

}