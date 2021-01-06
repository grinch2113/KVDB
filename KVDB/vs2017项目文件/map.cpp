#define _CRT_SECURE_NO_WARNINGS
#include"map.h"
#include"Data.h"
map::map()
{
	maxsize = 1000003;
	size = 0;
}
void map::createmap(const string & path)
{
	this->path = path;
	if (head == NULL)
	{
		head = new HNode*[maxsize];
		for (int i = 0; i < maxsize; i++)
		{
			head[i] = new HNode();
			head[i]->num = -1;
		}
	}
		
	FILE *f = fopen(path.c_str(), "rb");
	if (f == NULL)
	{
		return;
	}
	fseek(f, 0L, SEEK_END);
	int size = ftell(f);
	fseek(f, 0L, SEEK_SET);
	while (ftell(f) != size)
	{
		size_t h;
		string key;
		size_t offset = read(h, key, f);
		if (offset == -1)
		{
			continue;
		}
		HNode *obj = new HNode();
		obj->num = offset;
		obj->key = key;
		HNode *temp = head[h];
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = obj;
		this->size++;
	}
	fclose(f);
}

bool map::empty()const
{
	for (int i = 0; i < maxsize; i++)
	{
		if (head[i]->next != NULL)
			return false;
	}
	return true;
}
void map::purge(int *&value)
{
	int count = size;
	for (int i = 0; i < maxsize; i++)
	{
		if (!head[i]->next)
			continue;
		HNode *temp = head[i];
		while (temp->next)
		{
			temp = temp->next;
			value[--count] = temp->num;
		}
	}
	clearmap();
}



int map::getsize() const
{
	return size;
}

void map::display()
{
	printf("----------------------\n");
	for (int i = 0; i < maxsize; i++)
	{ 
		if (head[i]->next)
		{
			printf("%d %d\n", i, head[i]->next->num);
		}
	}
	printf("----------------------\n");
}

void map::set(const string &key, const size_t &offset)
{
	size_t h = hash(key.c_str());
	HNode *obj = new HNode();
	obj->num = offset;
	obj->key = key;
	HNode *temp = head[h];
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = obj;
	size++;
}

void map::del(const string &key)
{
	size_t h = hash(key.c_str());
	HNode *temp = head[h];
	while (temp->next)
	{
		HNode *temp0 = temp->next;
		if (temp0->key == key)
		{
			temp->next = temp0->next;
			free(temp0);
			temp0 = NULL;
			break;
		}
		temp = temp->next;
	}
	size--;
}





void map::clearmap()
{
	for (int i = 0; i < maxsize; i++)
	{
		HNode *temp = head[i]->next;
		while (head[i]->next)
		{
			head[i]->next = temp->next;
			delete temp;
			temp = head[i]->next;
		}
		head[i]->num = -1;
		head[i]->next = NULL;
	}
	size = 0;
}

size_t map::get(const string & key)const
{
	size_t h = hash(key.c_str());
	HNode *temp = head[h];
	while (temp->next)
	{
		temp = temp->next;
		if (temp->key == key)
			return temp->num;
	}
	return -1;
}

map::~map()
{
	clearmap();
	for (int i = 0; i < maxsize; i++)
	{
		free(head[i]);
	}
	free(head);
	head = NULL;
}

size_t read(size_t & h, string &key, FILE * f)
{
	size_t offset = ftell(f);
	int keylen;
	fread(&keylen, sizeof(int), 1, f);
	char *key_ = (char*)malloc(sizeof(char)*(keylen + 1));
	memset(key_, 0, sizeof(char)*(keylen + 1));
	fread(key_, sizeof(char), keylen, f);
	h = hash(key_);
	key = key_;
	free(key_);
	key_ = NULL;
	int isdel;
	fread(&isdel, sizeof(int), 1, f);
	if (isdel == 1)
	{
		offset = -1;
	}
	int vallen;
	fread(&vallen, sizeof(int), 1, f);
	fseek(f, vallen, SEEK_CUR);
	return offset;
}

unsigned int hash(const char *str)
{
	unsigned int seed = 131; 
	unsigned int hash = 0;

	while (*str)
	{
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF) % 1000003;
}
