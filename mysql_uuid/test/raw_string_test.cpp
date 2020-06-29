//
// Created by yulichao on 2020/6/29.
//

#define NDEBUG   //用来控制assert是否有效 打开assert则无效，注释掉则assert有效,并且该宏的定义需要在include前

#include <string>
#include <iostream>
#include <cassert>
#include <array>
#include <numeric>


using namespace std;

//constexpr修饰的函数，是在编译期就能够确定的表达式 c++11中该函数能有含有一行语句, return语句。
constexpr int square(int a, int b) {

    return a * b;
}

//下面两个函数时一对，下面函数的递归调用，有这个无参的函数，能使下面递归函数停止
void print() {
    cout << "end !" << endl;
}
//下面函数成为variadic template（可变模板函数），该函数必须有一个无参的同名函数重载
template <typename T, typename... Types>
void print(const T& firstArg, const Types&... args) {
    cout << sizeof...(args) << endl; //生成实参个数
    cout << firstArg << endl;
    print(args...);
}


int main() {
    string hel = R"nc(hello world \n)nc";

    cout << "hel = " << hel << endl;
    int testInt = -1;
    assert(testInt > 0);

    bool testBool = false;
    assert(testBool);

    for (int i = 0; i < 10; ++i) {
        cout << "i = " << i << endl;
    }

    cout << "-----------------------------" << endl;

    array<float, 20> testArray{0, 1, 2, 3,4};
    for (auto item : testArray) {
        cout << "item = " << item << endl;
    }

    cout << "-----------------------------" << endl;

    //array<double, numeric_limits<short>::max()> a;

    array<int, square(3,4)> b{0, 1, 2, 3, 4};
    cout << "b.size = " << b.size() << endl;

    cout << "-----------------------------" << endl;

    print("hello world", 100, 211.211);

    cout << "-----------------------------" << endl;



    return 0;
}