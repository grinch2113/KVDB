
#pragma once
#include<stdio.h>
#include<list>
#include<stdlib.h>
#include"string.h"
size_t read(size_t &h, string &key, FILE *f);
unsigned int hash(const char*);

struct minH
{
	int num;
	int index;
	minH()
	{
		num = -1;
		index = -1;
	}
};



struct HNode
{
	int num;
	string key;
	HNode *next;
	HNode()
	{
		next = NULL;
		num = -1;
	}
};
class map
{
private:
	HNode** head;
	int size;
	string path;
	int maxsize;
public:
	map();
	void createmap(const string &path);
	void set(const string &key, const size_t &offset);
	void del(const string &key);
	void display();
	void clearmap();
	bool empty() const;
	void purge(int *&value);
	int getsize()const;
	size_t get(const string &key)const;
	~map();
};
