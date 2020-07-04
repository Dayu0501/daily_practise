//
// Created by yulichao on 2020/7/3.
//
#include <string>
#include <iostream>

using namespace std;

template<typename T, typename U>
struct A {
    T aa;
    U bb;
};

template<typename T>
struct B
{
    typedef A<T, int> type;
};

template<typename T>
using C = A<T, int>;

template<typename T>
using D = typename B<T>::type;

//typename B<T>::type 等价于 A<T, int>

int main() {

    C<string> insC{"hello", 100};
    cout << "insC.aa = " << insC.aa << endl;
    cout << "insC.bb = " << insC.bb << endl;

    B<string>::type insB{"world", 99};
    cout << "insB.aa = " << insB.aa << endl;
    cout << "insB.bb = " << insB.bb << endl;

    return 0;
}

