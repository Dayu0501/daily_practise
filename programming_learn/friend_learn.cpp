#include <iostream>
#include <heapapi.h>

using namespace std;

class solution;
class friend_func_solution {
public:
	void calculator(solution obj);
};

//被别人友元的，相当于给别人开放一些属于自己的权限
class friend_solution;
class solution {
public:
	solution(int a1, int b1) : aa(a1), bb(b1) {}

	friend void print(solution obj) {
		cout << "aa = " << obj.aa << endl;
		cout << "bb = " << obj.bb << endl;
	}

	friend void friend_func_solution::calculator(solution obj);

	friend class friend_solution;

	friend void operator+(solution val1, solution val2) {
		cout << "operator + result : " << (val1.aa + val2.aa) * (val1.bb + val2.bb) << endl;
	}

private:
	int aa;
	int bb{};
};

void friend_func_solution::calculator(solution obj) {
	cout << "aa + bb = " << obj.aa + obj.bb << endl;
}

class friend_solution {
public:
	void process(solution obj) {
		cout << "aa * bb = " << obj.aa * obj.bb << endl;
	}
};

class subSolution : public solution {
public:


};

int main() {

	cout << "----- [ 全局友元函数测试 ] ------" << endl;
	solution ins(100, 200);
	print(ins);

	cout << "----- [ 类成员函数作为别的类的友元函数 ] ------" << endl;
	friend_func_solution insFriend;
	insFriend.calculator(ins);

	cout << "----- [ 友元操作符重载 ] -----" << endl;

	ins + ins;
	cout << "5 + 5 = " << 5 + 5 << endl;

	cout << "----- [ 友元类 ] ------" << endl;
	friend_solution insFriendSolution;
	insFriendSolution.process(ins);

	cout << "----- [ 友元是否可继承测试 ] -----" << endl;



	return 0;
}