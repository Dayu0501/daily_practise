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


int main() {
	/*
	 * 所以验证了侯捷的一个例子是错误的，维持原判*/
	myClass kaka {1, 2, 3};
	myClass haha = {1, 2, 3};
	myClass bubu({1, 2, 3});

	myClass ins = kaka;

	return 0;
}

