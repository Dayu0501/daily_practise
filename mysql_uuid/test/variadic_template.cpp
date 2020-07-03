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

//正常的类
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

//模板类
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

//模板类的成员函数
template <typename T1, typename T2>
void myNewType<T1, T2>::print() {
    cout << "this val1 = " << val1 << endl;
    cout << "this val2 = " << val2 << endl;
}

//模板函数
template <typename T>
bool compareValue(const T& a, const T&b) {
    return a > b;
}

//模板形参常量
template <int *a>
class A{
public:
    void print() {
        cout << "A::*a = " << *a << endl;
    }
};
int b[1]{1000};

//模板函数
template <typename T, typename T1>
bool testFuc(T a, T1 b) {
    cout << "a + b" << a << "+" << b << endl;
}

//特化
template<> bool testFuc<myType>(myType a,myType b){}
//特化
template<> bool testFuc<int>(int a, int b) {}



/************************模板类实例化和特化*********************/
//默认形参类型的模板类
template<typename T1, typename T2 = int>
class helloTomorrow {
public:
    T1 kaka;
    T2 wuwu;
};

//模板类显示实例化
template class helloTomorrow<int, int>;

//模板类的特化 template<> 这种是全特化的，模板函数只有全特化，没有偏特化
template<> class helloTomorrow<string, string> {
public:
    string kaka;
    string wuwu;
};

//部分特化
template<typename T2> class helloTomorrow<string, T2> {
public:
    string Kaka;
    T2 wuwu;
};
/************************************************************/



/******************模板函数实例化和特化***********************/
template<typename T>
void func(T t) {
    cout << t << endl;
}

//这是特化，特化指的是现有的模板函数的函数体功能不能满足，需要特殊化定义函数体功能
template<>
void func<int>(int t) {
    cout << "a = " << t << endl;
}

//这段代码不能放到上面特化上面，因为都是int型的实例化，而且放在现在的位置，该实例化是没有任何作用的。
//template void func<int>(int t);

//这是显示实例化
template void func<string>(string t);

template void func<const double&>(const double& t);
//就不行
//template void func<float>(const float& t);
/***************************************************/

void printfLocal(const char *s)
{
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                throw std::runtime_error("invalid format string: missing arguments");
            }
        }
        std::cout << *s++;
    }
}

template<typename T, typename ...type>
void variadicPrint(T head, type... element) {
    cout << head << endl;
    variadicPrint(element...);
}

void variadicPrint() {
    cout << "end" << endl;
}


template <typename T, typename... Types>
void printLL(T firstArg, Types... args)
{
    std::cout << sizeof...(Types) << '\n';    //print number of remaining types
    std::cout << sizeof...(args) << '\n';    // print number of remaining types
}

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

    cout << "----------------------------" << endl;

    string str5{"kaka"};
    //printfLocal("wo hai %d shi \n", 10);

    cout << "----------------------------" << endl;
    printLL(10, "hello", "world", 100, "\n");


    return 0;
}