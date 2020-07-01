//
// Created by yulichao on 2020/6/28.
//

#include <string>
#include <vector>
#include <iostream>

using namespace std;

void print(initializer_list<int> vals) {
    for(int val : vals) {
        cout << val << endl;
    }
}

class myP {
public:
    myP(int a, int b) {
        cout << "i am myP(int, int) !" << endl;
    }

    myP(initializer_list<int> vals) {
        cout << "i am myP(initializer_list<int>) !" << endl;
    }

//    explicit myP(initializer_list<int> vals) {
//        cout << "i am explicit !" << endl;
//    }
};

class myC {
public:
//    explicit myC(const string& s) {
//        cout << "i am myC(const string& s) !" << endl;
//    }

    myC(const string& s) {
        cout << "i am myC(const string& s) !" << endl;
    }
};

int main() {
    int a{};
    int b[]{5, 6, 7};
    vector<int> vec{0, 1, 2, 3, 4};
    vector<string> strVec{"beijing", "shanghai", "haerbin", "chengdu"};
    int *p{};
    char c{7};

    if (p == nullptr) cout << "p == nullptr" << endl;
    else              cout << "p != nullptr" << endl;

    /*char d{789};
    vector<int> vec1{9, 10, 11.2, 22.5};*/ //error

    double e{5};

    print({1, 2, 3, 4, 5, 6, 7, 8, 9});

    cout << "------------------------------------" << endl;

    myP a1(1,2);
    myP a2{1, 2};
    myP a3{1, 2, 3};
    myP a4 = {1, 2};

    cout << "-------------------------------------" << endl;

    for (int item : {1, 2, 3, 4, 5, 6, 7}) {
        cout << "item = " << item << endl;
    }

    cout << "-----------------------------------" << endl;

    vector<double> doubleVec {1.0, 2.0, 3.0, 4.0, 5.0};
    for (auto& elem : doubleVec) {
        elem *= 3;
    }

    for (const auto& elem : doubleVec) {
        cout << "elem = " << elem << endl;
    }

    cout << "-----------------------------------" << endl;

    initializer_list<int> tempList{8, 9, 10, 11};
    for (const auto& item : tempList) {
        cout << "item = " << item << endl;
    }

    cout << "------------------------------------" << endl;

    int array[] = {10, 20, 30, 40, 50};
    for (auto item : array) {
        cout << "item = " << item << endl;
    }

    cout << "------------------------------------" << endl;

    vector<string> strVec2{"kobe", "james", "curry"};
    strVec2.push_back("maksi"); //更应该使用的是strVec2.emplace_back("maksi");

    for (const myC& item : strVec2) {
        //该for循环中是会调用myC的以const string为参数的构造函数的，来构造item
    }

    cout << "------------------------" << endl;

    string str11 = "粤";

    cout << "str11 = " << str11 << endl;

    cout << "char = " << str11.substr(0, 3) << endl;

    cout << "strlen = " << str11.size() << endl;
    return 0;
}