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
	KVDBHandler(const string &db_file); //���ļ�db_file���ڣ�������ݿ⣻���򣬴����µ����ݿ�
	void changefile(const string& db_file); //�ı�򿪵��ļ�
	int set(const string& key, const string& value); //д������
	int get(const string& key, string &value)const;//��ȡ����
	int del(const string &key);
	void purge();
	~KVDBHandler();
};
void read(FILE *fp, Data &data);
size_t write(FILE *fp, Data &data);