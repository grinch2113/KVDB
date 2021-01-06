#pragma once
class string
{
private:
	char *str;
	size_t _size;
	size_t length = 0;
public:
	string();
	string(const char* s);
	string(const string &r);
	bool empty()const;
	int size()const;
	void reSize();
	const char* c_str()const;
	void push_back(const char ch);
	void pop_back();
	void clear();
	char operator[](int index)const;
	void operator=(const string &s);
	void operator=(const char* s);
	friend bool operator==(const string &a, const string &b);
	friend string operator+(const string &a, const string &b);
	friend string operator+(const string &a, const char* b);
	~string();
};
extern void getline(string &s);
