#pragma once
#include<io.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
#include"Data.h"
#include"map.h"
#include<time.h>
class KVDBHandler
{
private:
	FILE *fp;
	FILE *fl;
	string path;
	string cntpath;
	string logpath;
	int cnt;
	map m;
	void check();
public:
	KVDBHandler(const string &db_file); //若文件db_file存在，则打开数据库；否则，创建新的数据库
	void changefile(const string& db_file); //改变打开的文件
	int set(const string& key, const string& value); //写入数据
	int get(const string& key, string &value)const;//读取数据
	int del(const string &key);
	void purge();
	~KVDBHandler();
};
void read(FILE *fp, Data &data);
size_t write(FILE *fp, Data &data);