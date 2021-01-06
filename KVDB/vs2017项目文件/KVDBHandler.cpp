#define _CRT_SECURE_NO_WARNINGS
#include"KVDBHandler.h"
#include<locale>
void sort(int *&a, int low, int high)
{
	if (high <= low)
	{
		return;
	}
	int i = low;
	int j = high + 1;
	int pivotkey = a[low];
	while (1)
	{
		while (a[++i] < pivotkey)
		{
			if (i == high)
				break;
		}
		while (a[--j] > pivotkey)
		{
			if (j == low)
				break;
		}
		if (i >= j)
		{
			break;
		}
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
	int temp = a[low];
	a[low] = a[j];
	a[j] = temp;
	sort(a, low, j - 1);
	sort(a, j + 1, high);
}
const char* getTime(char ti[])
{
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	strftime(ti, 100, "%Y/%m/%d %H:%M:%S", tm);
	return ti;
}

size_t write(FILE *fp, Data &data)
{
	int offset = ftell(fp);
	fwrite(&data.keylen, sizeof(int), 1, fp);
	fwrite(data.key.c_str(), sizeof(char), data.keylen, fp);
	fwrite(&data.isdel, sizeof(int), 1, fp);
	
	fwrite(&data.valuelen, sizeof(int), 1, fp);
	fwrite(data.value.c_str(), sizeof(char), data.valuelen, fp);
	return offset;
}

void read(FILE *f, string &value)
{
	int keylen;
	fread(&keylen, sizeof(int), 1, f);
	fseek(f, keylen + sizeof(int), SEEK_CUR);
	
	int vallen;
	fread(&vallen, sizeof(int), 1, f);
	char *value_ = (char*)malloc(vallen + 1);
	fread(value_, sizeof(char), vallen, f);
	value_[vallen] = 0;
	value = value_;
	free(value_);
	value_ = NULL;


}


void read(FILE *f, Data &data)
{
	
	
	fread(&data.keylen, sizeof(int), 1, f);
	char *key_ = (char*)malloc(data.keylen + 1);
	fread(key_, sizeof(char), data.keylen, f);
	key_[data.keylen] = 0;
	data.key = key_;
	free(key_);
	key_ = NULL;
	
	fread(&data.isdel, sizeof(int), 1, f);
	if (data.isdel == 1)
	{
		fread(&data.valuelen, sizeof(int), 1, f);
		fseek(f, data.valuelen, SEEK_CUR);
		return;
	}
	
	fread(&data.valuelen, sizeof(int), 1, f);
	char *value_ = (char*)malloc(data.valuelen + 1);
	fread(value_, sizeof(char), data.valuelen, f);
	value_[data.valuelen] = 0;
	data.value = value_;
	free(value_);
	value_ = NULL;

}
void KVDBHandler::check()
{
	cnt++;
	if (cnt == 1000)
	{
		purge();
		cnt = 0;
	}
	fp = fopen(cntpath.c_str(), "rb+");
	fwrite(&cnt, sizeof(int), 1, fp);
	fclose(fp);
}

KVDBHandler::KVDBHandler(const string & db_file)
{
	changefile(db_file);
}

KVDBHandler::~KVDBHandler()
{

}

void KVDBHandler::changefile(const string & db_file)
{
	path = "D:\\KVDB\\";
	cnt = 1;
	if (_access(path.c_str(), 0) != 0)
	{
		_mkdir(path.c_str());
	}
	path = path + db_file + "\\";
	if (_access(path.c_str(), 0) != 0)
	{
		printf("数据库不存在，已创建数据库%s\n", db_file.c_str());
		_mkdir(path.c_str());
		cnt = 0;
	}
	else
	{
		printf("数据库%s打开成功\n", db_file.c_str());
	}
	logpath = path + "log.txt";
	path = path + db_file;
	cntpath = path + ".cnt";
	path = path + ".bin";
	m.createmap(path);
	fp = fopen(path.c_str(), "ab");
	fclose(fp);
	fp = fopen(cntpath.c_str(), "ab");
	if (cnt != 0)
	{
		fread(&cnt, sizeof(int), 1, fp);
	}
	fclose(fp);
	fl = fopen(logpath.c_str(),"a");
}

int KVDBHandler::set(const string & key, const string & value)
{
	char t[100] = { 0 };
	if (key.size() != 0 && value.size() != 0)
	{
		int result = del(key);
		fp = fopen(path.c_str(), "ab");
		fseek(fp, 0L, SEEK_END);
		Data data(key, value);
		size_t offset = write(fp, data);
		fclose(fp);
		fprintf(fl, "[Info][%s]:写入了<%s,%s>\n", getTime(t), key.c_str(), value.c_str());
		m.set(key, offset);
		check();
		return 1;
	}
	if (key.size() == 0)
	{
		fprintf(fl, "[Info][%s]:拒绝了用户写入长度为0的key值\n", getTime(t));
		return 0;
	}
	if (value.size() == 0)
	{
		fprintf(fl, "[Info][%s]:拒绝了用户写入长度为0的value值\n", getTime(t));
		return -1;
	}
}

int KVDBHandler::get(const string & key, string & value) const
{
	char t[100] = { 0 };
	if (key.size() == 0)
	{
		fprintf(fl, "[Info][%s]:拒绝了用户读取长度为0的key值\n", getTime(t));
		return 0;
	}
	FILE *f = fopen(path.c_str(), "rb");
	int offset = m.get(key);
	if (offset == -1)
	{
		fprintf(fl, "[Info][%s]:试图寻找%s对应的value值，但找不到\n", getTime(t),key.c_str());
		fclose(f);
		return -1;
	}
	fseek(f, offset, SEEK_SET);
	read(f, value);
	fclose(f);
	fprintf(fl, "[Info][%s]:找到目标对象<%s,%s>\n", getTime(t), key.c_str(),value.c_str());
	return 1;
}

int KVDBHandler::del(const string & key)
{
	string value;
	char t[100] = { 0 };
	int result = get(key, value);
	if (result == 0)
	{
		fprintf(fl, "[Info][%s]:拒绝了用户删除长度为0的key值\n", getTime(t));
		return result;
	}
	else if (result == -1)
	{
		fprintf(fl, "[Info][%s]:拒绝了用户删除找不到的目标对象<%s,%s>\n", getTime(t),key.c_str(),value.c_str());
		return result;
	}
	FILE *f = fopen(path.c_str(), "rb+");
	int offset = m.get(key);
	fseek(f, offset, SEEK_SET);
	int keylen;
	fread(&keylen, sizeof(int), 1, f);
	fseek(f, keylen, SEEK_CUR);
	int isdel = 1;
	fwrite(&isdel, sizeof(int), 1, f);
	fclose(f);
	m.del(key);
	check();
	fprintf(fl, "[Info][%s]:删除了目标对象<%s,%s>\n", getTime(t), key.c_str(), value.c_str());
	return 1;

}

void KVDBHandler::purge()
{
	char t[100] = { 0 };
	printf("执行purge...\n");
	string newpath = path + "temp";
	FILE *cntfp = fopen(newpath.c_str(), "ab");
	FILE *f = fopen(path.c_str(), "rb");
	Data data;
	int offset = 0;
	int datasize = m.getsize();
	int *value = (int*)malloc(sizeof(int)*datasize);
	m.purge(value);
	sort(value, 0, datasize - 1);
	int size = 0;

	for (int i = 0; i < datasize; i++)
	{
		int offset = value[i];
		if (i > 0)
		{
			offset = value[i] - value[i - 1] - size;
		}
		fseek(f, offset, SEEK_CUR);
		read(f, data);
		size = 3 * sizeof(int) + data.keylen + data.valuelen;
		m.set(data.key, ftell(cntfp));
		write(cntfp, data);
	}
	fclose(f);
	fclose(cntfp);
	int result = remove(path.c_str());
	rename(newpath.c_str(), path.c_str());
	fprintf(fl, "[Info][%s]:purge执行成功\n", getTime(t));
	free(value);
	value = NULL;
}
