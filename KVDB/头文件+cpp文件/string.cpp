#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"string.h"
string::string()
{
	_size = 10;
	str = (char*)malloc(_size + 1);
	if (str == NULL)
	{
		printf("string:∑÷≈‰ƒ⁄¥Ê ß∞‹\n");
		return;
	}
	memset(str, 0, _size + 1);
	length = 0;
}
string::string(const char* s)
{
	_size = (strlen(s) / 10 + 1) * 10;
	str = (char*)malloc(_size + 1);
	if (str == NULL)
	{
		printf("string:∑÷≈‰ƒ⁄¥Ê ß∞‹\n");
		return;
	}
	memset(str, 0, _size + 1);
	memcpy(str, s, strlen(s));
	length = strlen(s);
}

string::string(const string & r)
{
	_size = r._size;
	str = (char*)malloc(_size + 1);
	memset(str, 0, _size + 1);
	memcpy(str, r.str, r.length);
	length = r.length;
}

string::~string()
{
	free(str);
	str = NULL;
}
bool string::empty()const
{
	if (length == 0)
	{
		return true;
	}
	return false;
}
int string::size()const
{
	return (int)length;
}
void string::reSize()
{
	if (_size - length < 10)
	{
		_size += 10;
		char *temp = (char*)realloc(str , _size + 1);
		if (temp == NULL)
		{
			printf("string:÷ÿ–¬∑÷≈‰ƒ⁄¥Ê ß∞‹\n");
			return;
		}
		str = temp;
		memset(str + length, 0, 11);
	}
	else
	{
		_size -= 10;
		str = (char*)realloc(str, _size + 1);
		str[_size] = 0;
	}
}
const char* string::c_str()const
{
	return str;
}
void string::push_back(const char ch)
{
	if (length == _size)
	{
		reSize();
	}
	str[length++] = ch;
}
void string::pop_back()
{
	if (empty())
	{
		printf("string.pop_back:◊÷∑˚¥ÆŒ™ø’\n");
		return;
	}
	length--;
	str[length] = 0;
}
void string::clear()
{
	free(str);
	_size = 10;
	str = (char*)malloc(_size + 1);
	if (str == NULL)
	{
		printf("string:∑÷≈‰ƒ⁄¥Ê ß∞‹\n");
		return;
	}
	memset(str, 0, _size + 1);
	length = 0;
}
string operator+(const string &a, const string &b)
{
	string result(a);
	for (int i = 0; i < b.length; i++)
	{
		result.push_back(b[i]);
	}
	return result;
}
string operator+(const string &a, const char* b)
{
	return a + string(b);
}
void string::operator=(const string &r)
{
	_size = r._size;
	free(str);
	str = (char*)malloc(_size + 1);
	if (str == NULL)
	{
		printf("string:∑÷≈‰ƒ⁄¥Ê ß∞‹\n");
		return;
	}
	memset(str, 0, _size + 1);
	memcpy(str, r.str, r.length);
	length = r.length;
}
void string::operator=(const char* s)
{
	_size = (strlen(s) / 10 + 1) * 10;
	free(str);
	str = (char*)malloc(_size + 1);
	if (str == NULL)
	{
		printf("string:∑÷≈‰ƒ⁄¥Ê ß∞‹\n");
		return;
	}
	memset(str, 0, _size + 1);
	memcpy(str, s, strlen(s));
	length = strlen(s);
}
bool operator==(const string &a, const string &b)
{
	if (strcmp(a.c_str(), b.c_str()) == 0)
	{
		return true;
	}
	return false;
}
char string::operator[](int index)const
{
	return *(str + index);
}
void getline(string &s)
{
	char ch = 0;
	s.clear();
	while (scanf("%c", &ch) && ch != '\n')
	{
		s.push_back(ch);
	}
}
