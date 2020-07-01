//
// Created by yulichao on 2020/7/1.
//

#include <string>
#include <vector>
#include <iostream>
using namespace std;

//template<typename... Elements> class tuple;
//template<typename Head, typename... Tail>
//class tuple<Head, Tail...> : private tuple<Tail...> {
//    Head head;
//public:
//    /* implementation */
//};
//
//template<>
//class tuple<> {
//    /* zero-tuple implementation */
//};

class myType {
public:
    explicit myType(int val) : aa(val) {}
    bool operator>(const myType& b) const {
        return aa > b.aa;
    }
    myType& operator=(const myType& val) {
        if (this != &val) {
            aa = val.aa;
        }

        return *this;
    }

private:
    int aa;
};


template <typename T1, typename T2>
class myNewType {
public:
    myNewType() {
        cout << "I am default constructor !" << endl;
    }

    myNewType(const T1& a, const T2& b) : val1(a), val2(b) {
        cout << "I am constructor !" << endl;
    }

    myNewType(const myNewType<T1, T2>& a) {
        cout << "I am copy constructor !" << endl;

        val1 = a.val1;
        val2 = a.val2;
    }

    myNewType& operator=(const myNewType<T1, T2>& a) {
        cout << "I am operator= !" << endl;

        if (this != &a) {
            val1 = a.val1;
            val2 = a.val2;
        }

        return *this;
    }

    void print();

public:
//    T1 val1{10};
//    T2 val2{20};
//    T1 val1{"hello"};
//    T2 val2{"world"};
    T1 val1{};
    T2 val2{};
};

template <typename T1, typename T2>
void myNewType<T1, T2>::print() {
    cout << "this val1 = " << val1 << endl;
    cout << "this val2 = " << val2 << endl;
}


template <typename T>
bool compareValue(const T& a, const T&b) {
    return a > b;
}

template <typename T, typename T1>
bool testFuc(T a, T1 b) {
    cout << "a + b" << a << "+" << b << endl;
}

template <int *a>
class A{
public:
    void print() {
        cout << "A::*a = " << *a << endl;
    }
};
int b[1]{1000};



template<typename T1, typename T2 = int>
class helloTomorrow {
public:
    T1 kaka;
    T2 wuwu;
};

template<> bool testFuc<myType>(myType a,myType b){}
template<> bool testFuc<int>(int a, int b) {}


template <typename T>
void func(T t){
    cout << t << endl;
}
template void func<int>(const int); //显示实例化模板函数

int main() {
    cout << "test start ..." << endl;

    if (compareValue(1.0, 2.0)) cout << "a > b" << endl;
    else                                cout << "a !> b" << endl;

    if (compareValue(1, 2)) cout << "a > b" << endl;
    else                            cout << "a !> b" << endl;


    myType a1{10};
    myType b1{20};
    if (compareValue(a1, b1)) cout << "a1 > b1" << endl;
    else                       cout << "a1 !> b1" << endl;

    //testFuc(10, string{"hello all over the world !"});
    testFuc(10, "hello world");

    cout << "----------------------------" << endl;

    myNewType<double, double> testDoubleIns{10, 100};
    //myNewType<double, double> testDoubleIns{};
    cout << "testDoubleIns.val1 = " << testDoubleIns.val1 << endl;
    cout << "testDoubleIns.val2 = " << testDoubleIns.val2 << endl;

    cout << "------------------------------" << endl;

    myNewType<double, double> testNewIns{};

    cout << "------------------------------" << endl;

    myNewType<string, string> testStringIns{"hello", "world"};
    cout << "testStringIns.val1 = " << testStringIns.val1 << endl;
    cout << "testStringIns.val2 = " << testStringIns.val2 << endl;

    cout << "-----------------------------" << endl;

    myNewType<double, double> kk{5.5, 6.6};
    myNewType<double, double> dd{kk};
    cout << "dd.val1 = " << dd.val1 << endl;
    cout << "dd.val2 = " << dd.val2 << endl;

    dd.print();

    cout << "-----------------------------" << endl;
    A<b> m;
    m.print();

    testFuc<int, int>(10,20); //隐式实例化
    testFuc(100, 200); //隐式实例化

    testFuc<myType>(a1, b1);

    cout << "----------------------------" << endl;

    func(10);
    func("hello");



    return 0;
}