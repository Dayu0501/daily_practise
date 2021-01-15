//
// Created by yulichao on 2021/1/14.
//

#include <iostream>

using namespace std;

class Parent {
public:
	virtual void print() {
		cout << "I am Parent !" << endl;
	}
};

class Child : public Parent {

	/* 下面的print是可以被下面访问到的 */
	void print() override {
		cout << "I am Child !" << endl;
	}

	/* 下面的test是不可以被访问到的 */
	void test() {
		cout << "I am Test !" << endl;
	}
};

int main() {

	Parent * ins = new Child;
	ins->print();

	std::cout << std::endl << "----- [ test ] -----" << std::endl;

	return 0;
}
