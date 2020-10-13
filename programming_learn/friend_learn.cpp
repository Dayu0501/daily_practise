#include <iostream>
#include <string>

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

	solution() {}

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
	int aa = 0;
	int bb = 0;
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

class subSolution : public friend_solution {
public:
	//下面函数展示，友元关系是不能够被继承的
//    void processTest(solution obj) {
//        cout << "aa - bb = " << obj.aa - obj.bb << endl;
//    }

private:
	string _val;
	string _param;
};

/**************************************************************/

class testSolution {
public :
	struct VALUE {
		string hello;
		string world;
	} data;


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

	return 0;
}

//#include <iostream>
//
//using namespace std;
//
//class CObj {
//public:
//    CObj() : mX(0), mY(0) {}
//
//    friend class CFriend;
//
//private:
//    void PrintData() const {
//        cout << "mX = " << mX << endl
//             << "mY = " << mY << endl;
//    }
//
//    int mX;
//    int mY;
//};
//
//class CFriend {
//public:
//    CFriend(int x, int y) {
//        mObj.mX = x;    //直接调用类CObj的私有数据成员
//        mObj.mY = y;
//    }
//
//    void ShowData() const {
//        mObj.PrintData();   //直接调用类CObj的私有成员函数
//    }
//
//private:
//    CObj mObj;
//};
//
//int main() {
//    CFriend one(3, 4);
//    one.ShowData();
//
//    return 0;
//}