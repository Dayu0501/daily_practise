//
// Created by yulichao on 2020/9/27.
//

#ifndef STL_ALG_TEST_H
#define STL_ALG_TEST_H

#include <iostream>
#include <utility>
using namespace std;
static int head = 10000;

//test operator question
class stone {
public:
	stone(int paramSize, string paramColor) : size(paramSize), color(std::move(paramColor)) {
		cout << "I am stone !" << endl;
	}

//	bool operator<(const stone paramObj) {
//		return (to_string(size) + color) < (to_string(paramObj.size) + paramObj.color);
//	} 如果该类加到set中，该云算符重载就不能被set所使用

//	bool operator<(const stone& myType) const {
//		return (to_string(size) + color) < (to_string(myType.size) + myType.color);
//	}

//	friend bool operator<(const stone & param1, const stone & param2) {
//		return (to_string(param1.size) + param1.color) < (to_string(param2.size) + param2.color);
//	}

//	bool operator==(const stone & paramObj) const {
//		return (to_string(size) + color) == (to_string(paramObj.size) + paramObj.color);
//	}

	int size;
	string color;
};

class compareObj {
public:
	bool operator()(const stone & param1, const stone& param2) {
		return (to_string(param1.size) + param1.color) < (to_string(param2.size) + param2.color);
	}
};

bool compareStone(const stone & param1, const stone & param2) {
	return (to_string(param1.size) + param1.color) < (to_string(param2.size) + param2.color);
}

class testObj {
public:
	int operator<(const testObj & param) {
		cout << "I am testObj operator < !" << endl;
//		return aa < param.aa;
		if (aa < param.aa) return 10;
		else return 0;
	}

//	void print() {
//		cout << "i am no const print" << endl;
//	}

	void print() const {
		cout << "I am const print " << endl;
		cout << "aa = " << aa << endl;
	}


	int aa;
	const int cc = aa;
};
#endif //STL_ALG_TEST_H
