//
// Created by yulichao on 2020/6/24.
//

#include <iostream>
#include <vector>
#include <cstring>

class MyString {
private:
    char *_data{};
    size_t _len;

    void _init_data(const char *s) {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }

public:
    MyString() {
        _data = nullptr;
        _len = 0;
    }

    explicit MyString(const char *p) {
        _len = strlen(p);
        _init_data(p);

        std::cout << "char * Constructor " << std::endl;
    }

    MyString(const MyString &str) {
        _len = str._len;
        _init_data(str._data);
        std::cout << "Copy Constructor is called! source: " << str._data << std::endl;
    }

    MyString &operator=(const MyString &str) {
        if (this != &str) {
            _len = str._len;
            _init_data(str._data);
        }
        std::cout << "Copy Assignment is called! source: " << str._data << std::endl;
        return *this;
    }

//    MyString(MyString &&str) noexcept {
//        std::cout << "Move Constructor is called! source: " << str._data << std::endl;
//        _len = str._len;
//        _data = str._data;
//        str._len = 0;
//        str._data = nullptr;
//    }
//
//    MyString &operator=(MyString &&str)  noexcept {
//        std::cout << "Move Assignment is called! source: " << str._data << std::endl;
//        if (this != &str) {
//            _len = str._len;
//            _data = str._data;
//            str._len = 0;
//            str._data = nullptr;
//        }
//        return *this;
//    }

    virtual ~MyString() {
        if (_data) free(_data);
    }
};

/*
 * 拷贝构造函数调用的三个场景：
 * （1）值传递的函数入参，在push_back中也是同样会调用拷贝构造的，因为也是在调用push_back的时候传入了参数
 * （2）值传递的函数返回值
 * （3）用一个已有的变量初始化另一个变量
 *
 * vector的push_back的参数（c++11实现了两个push_back函数）：
 * （1）当参数是左值的时候，调用的是vector::push_back(const T &);
 * （2）当参数是右值的时候，调用的是vector::push_back(const T &&);
 * */

int main() {
    MyString a("kaka");                                 //调用char *参数的构造函数
    const MyString &b = a;                                         //调用拷贝构造函数

    std::cout << "---------------------" << std::endl;

    MyString c = "bubu";                                    //调用char *参数的构造函数

    std::cout << "-------------------" << std::endl;

    MyString d;                                             //默认构造函数
    d = "dada";                                             //先调用char *的构造函数构造值为dada的临时对象，然后调用赋值运算符

    std::cout << "++++++++++++++++++++++" << std::endl;


    /*
     *下面这段代码中，先是调用了构造函数，构造出临时变量，然后再调用拷贝构造函数
    std::vector<MyString> vec;
    vec.push_back("wodi"); */

    /*
     * 下面这段代码中，仅调用了拷贝构造函数
    std::vector<MyString> vec;
    vec.push_back(a); */

    /*
     * 下面代码是会把原str的内存区数据移动到v的相应元素中去
    std::string str = "Hello";
    std::vector<std::string> v;
    //调用常规的拷贝构造函数，新建字符数组，拷贝数据
    v.push_back(str);
    std::cout << "After copy, str is \"" << str << "\"\n";
    //调用移动构造函数，掏空str，掏空后，最好不要使用str
    v.push_back(std::move(str));
    std::cout << "After move, str is \"" << str << "\"\n";
    std::cout << "The contents of the vector are \"" << v[0]
              << "\", \"" << v[1] << "\"\n";*/


    //vec.emplace_back(std::move(a));

    //a = MyString("Hello");
//    std::vector<MyString> vec;
//    vec.push_back("World");
//
//    vec.emplace_back("World");
}