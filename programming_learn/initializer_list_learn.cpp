#include <iostream>
#include <initializer_list>

using namespace std;

class myClass {
public:
	myClass(initializer_list<int> obj) {
		cout << "I am initializer_list !" << endl;
	}

	myClass(int a, int b, int c) {
		cout << "param list con !" << endl;
	}

	int aa;
	int bb;
	int cc;
};


template <typename T>
class smart_ptr {
public:
	explicit smart_ptr(T* ptr = nullptr)
		: ptr_(ptr) {}
	~smart_ptr()
	{
		delete ptr_;
	}
	T* get() const { return ptr_; }
private:
	T* ptr_;
};

int main() {
	/*
	 * 所以验证了侯捷的一个例子是错误的，维持原判*/
	myClass kaka{1, 2, 3};
	myClass haha = {1, 2, 3};
	myClass bubu({1, 2, 3});

	myClass ins = kaka;

	string hello = "hello";
	int dd = 1;
	switch (dd) {
		case 2:
			cout << "haha" << endl;
			break;
		case 3:
			cout << "bubu" << endl;
			break;
	}

	return 0;
}

