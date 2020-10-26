#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using std::endl;
using std::cout;
using std::string;

class String {
public:
	String()
		: _pstr(new char[5]() + 4) //留出4字节存放引用计数, 1字节存放'\0'，+4即偏移到数据的位置
	{
		cout << "String()" << endl;
		initRefcount();
	}

	String(const char *pstr)
		: _pstr(new char[strlen(pstr) + 5]() + 4) //申请数据+5(引用计数)的空间，指针偏移到数据的位置
	{
		cout << "String(const char *pstr)" << endl;
		strcpy(_pstr, pstr);
		initRefcount();
	}

	String(const String &rhs)
		: _pstr(rhs._pstr) {
		cout << "String(const String  &rhs)" << endl;
		increRefcount();
	}

	String &operator=(const String &rhs) {
		cout << "String & operator=(const String &rhs)" << endl;
		if (this != &rhs)//防止自复制
		{
			releaseFunc(); // 释放左操作数
			_pstr = rhs._pstr; //浅拷贝
			increRefcount();
		}
		return *this; // 返回*this
	}

	char &operator[](size_t idx) {
		if (idx < size()) {
			if (getRefcount() > 1) //引用计数不是最后一个
			{
				char *ptmp = new char[size() + 5]() + 4;
				strcpy(ptmp, _pstr);
				decreRefcount();
				_pstr = ptmp;
				initRefcount();
			}
			return _pstr[idx];
		} else {
			static char nullchar = '\0';
			return nullchar;
		}
	}

	~String() {
		cout << "~String()" << endl;
		releaseFunc();
	}

public:
	//获取引用计数
	int getRefcount() const {
		return *(int *) (_pstr - 4);
	}

	//转C风格字符串
	const char *c_str() const {
		return _pstr;
	}

	//字符串大小
	size_t size() const {
		return strlen(_pstr);
	}

private:

	//初始化引用计数
	void initRefcount() {
		// 引用计数初始化为1
		// (pstr - 4) 指针回到堆起始位置（引用计数起始位置）
		// (int *) 强转为 int*指针类型
		// *(int *)(pstr - 4) 解引用
		// *(int *)(pstr - 4) = 1 初始化为1

		*(int *) (_pstr - 4) = 1;
	}

	//引用计数自增
	void increRefcount() {
		++*(int *) (_pstr - 4);
	}

	//引用计数自减
	void decreRefcount() {
		--*(int *) (_pstr - 4);
	}

	//堆空间释放
	void releaseFunc() {
		decreRefcount();
		if (getRefcount() == 0) {
			delete[] (_pstr - 4);
		}
	}

	friend std::ostream &operator<<(std::ostream &os, const String &rhs);

private:
	char *_pstr;
};

std::ostream &operator<<(std::ostream &os, const String &rhs) {
	os << rhs._pstr;
	return os;
}

void test() {
	String s1 = "Hello";
	String s2 = s1;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s1 count is " << s1.getRefcount() << endl;
	cout << "s2 count is " << s2.getRefcount() << endl;
	printf("s1 address is %p\n", s1.c_str());
	printf("s2 address is %p\n", s2.c_str());

	//调用拷贝构造函数
	cout << endl;
	String s3("world");
	s3 = s1;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1 count is " << s1.getRefcount() << endl;
	cout << "s2 count is " << s2.getRefcount() << endl;
	cout << "s3 count is " << s3.getRefcount() << endl;
	printf("s1 address is %p\n", s1.c_str());
	printf("s2 address is %p\n", s2.c_str());
	printf("s3 address is %p\n", s3.c_str());

	//写时复制
	cout << endl;
	cout << "s3[0]写操作: s3[0] = 'h'" << endl;
	s3[0] = 'h';
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1 count is " << s1.getRefcount() << endl;
	cout << "s2 count is " << s2.getRefcount() << endl;
	cout << "s3 count is " << s3.getRefcount() << endl;
	printf("s1 address is %p\n", s1.c_str());
	printf("s2 address is %p\n", s2.c_str());
	printf("s3 address is %p\n", s3.c_str());

	//读操作（出错）
	cout << endl;
	cout << "s1[0]读操作" << endl;
	cout << "s1[0] = " << s1[0] << endl;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1 count is " << s1.getRefcount() << endl;
	cout << "s2 count is " << s2.getRefcount() << endl;
	cout << "s3 count is " << s3.getRefcount() << endl;
	printf("s1 address is %p\n", s1.c_str());
	printf("s2 address is %p\n", s2.c_str());
	printf("s3 address is %p\n", s3.c_str());
}

int main() {
	test();
	string hello;

	return 0;
}