#define _CRT_SECURE_NO_WARNINGS
#include"main.h"
void m()
{
	string file;
	printf("输入要打开的数据库:");
	getline(file);
	KVDBHandler handler(file);
	string op;
	printf("正在操作的数据库为:%s\n",file.c_str());
	printf("输入指令:");
	while (true)   //输入指令
	{
		getline(op);
		if (op == "select")  //重新选择操作的数据库
		{
			printf("输入要打开的数据库：");
			getline(file);
			handler.changefile(file);
		}
		else if (op == "set")  //写入数据
		{
			string key;
			string value;
			printf("输入key:");
			getline(key);
			printf("输入value:");
			getline(value);
			int result = handler.set(key, value);
			if (result == 0)
			{
				printf("错误：key值不能为空\n");
			}
			else if (result == -1)
			{
				printf("错误：value值不能为空\n");
			}
			else
			{
				printf("数据写入成功\n");
			}
		}
		else if (op == "get")  //读取数据
		{
			string key;
			printf("输入key:");
			getline(key);
			string value;
			int result = handler.get(key, value);
			if (result == 0)
			{
				printf("错误：key值不能为空\n");
			}
			else if (result == -1)
			{
				printf("错误：找不到key值为%s的value值\n", key.c_str());
			}
			else
			{
				printf("所找的value值为%s\n", value.c_str());
			}
		}
		else if (op == "remove")
		{
			string key;
			printf("输入key:");
			getline(key);
			int result = handler.del(key);
			if (result == 0)
			{
				printf("错误：key值不能为空\n");
			}
			else if (result == -1)
			{
				printf("错误：找不到key值为%s的value值\n", key.c_str());
			}
			else
			{
				printf("删除成功\n");
			}
		}
		else  //输入了错误的指令
		{
			printf("错误：输入指令有误\n");
		}
		system("pause");
		system("cls");
		printf("正在操作的数据库为:%s\n", file.c_str());
		printf("输入指令:");
	}
}