#include <iostream>
#include <vector>
#include <string>
#include <ext/pool_allocator.h>

using namespace std;

class AA {
public :
	AA() {
		cout << "I am construct !" << endl;
	}

	~AA() {
		cout << "I am destruct !" << endl;
	}

	string aa;
    string bb;
};

int main() {
	cout << "----- [ 测试析构函数是否会被调用 ] -----" << endl;
	{
		AA * ptr = new AA; //临时指针变量，在离开作用空间的时候，是不会调用该指针指向的类型的析构函数的，必须显示调用delete。
		//delete ptr;
	}
	std::cout << "----- [ 测试 __pool_alloc ] -----" << std::endl;
	vector<string, __gnu_cxx::__pool_alloc<string>> testStr;


	return 0;
}

