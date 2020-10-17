#include <iostream>


using namespace std;

class memAA {
public:
	memAA() {
		cout << "I am memAA constructor !" << endl;
	}

	~memAA() {
		cout << "I am memAA destructor !" << endl;
	}

	/*
	 (1)重载时，返回类型必须声明为void*
	 (2)重载时，第一个参数类型必须为表达要求分配空间的大小（字节），类型为size_t
	 (3)重载时，可以带其它参数
	 (4)分配函数为类成员函数或全局函数;如果分配函数在全局范围之外的名称空间范围中声明，或者在全局范围中声明为静态，则程序是病态的
	 (5)operator new调用时的参数和new的参数是有所区别的。new在调用的时候会忽略第一个size_t的参数，
	    但是如果直接调用operator new来进行内存分配的时候是需要这个参数的，也就是调用new的时候相当于调用的是new(size_t),如果调用的是new(typename),
	    就一定会存在一个这样的重载 operator new (size_t, class)，也即是说new调用的时候，会省去第一参数，这个参数是编译器自己加上去的。
	 */
	static void * operator new(size_t size) {
		cout << "I am memAA operator new !" << endl;
	}

	//下面是placement new的声明定义
	static void * operator new(size_t size, void *p) {

	}

	void operator delete(void * p) {
		cout << "I am memAA operator delete !" << endl;
	}


	int aa;
	int bb;
};

int main() {
	std::cout << "----- [ new 一个指针 ] -----" << std::endl;
	{
		auto pIns = new memAA(); //匹配到的是一个参数的new
		delete pIns; //会调用该类的operator delete
	}

	std::cout << "----- [ new 一个存在3个元素的指针数组 ] -----" << std::endl;
	{
		auto arrayIns = new memAA[3];
		memAA * tmp = arrayIns;

		std::cout << "----- [ 调用new传指针为参数 ] -----" << std::endl;
		for (int i = 0; i < 3; ++i) {
			new(tmp++)memAA; //此处匹配到的是两个参数的new
		}

		std::cout << "----- [ 显示调用析构函数 ] -----" << std::endl;

		memAA * p = new(tmp--)memAA; //此处调用的是上面两个参数的operator new(placement new)
		p->~memAA(); //placement new返回的指针是可以显示调用析构函数的。

	}

	std::cout << "----- [ 创建一个临时对象 ] -----" << std::endl;
	memAA ins;

	return 0;
}