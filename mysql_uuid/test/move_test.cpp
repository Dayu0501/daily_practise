//
// Created by Administrator on 2020/6/29.
//

#include <utility>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class myType {
public:
    myType() {
        cout << "I am default constructor !" << endl;
    }

    //此处调用string的move constructor
    explicit myType(string val) : _val(move(val)) {
        cout << "I am param constructor !" << endl;
    }

    myType(const myType& ins) : _val(ins._val) {
        cout << "I am copy constructor !" << endl;
    }

    myType(myType&& ins)  noexcept : _val(move(ins._val)) {
        cout << "I am move constructor !" << endl;
    }

    myType& operator=(const myType& ins) {
        cout << "I am operator= !" << endl;
        _val = ins._val;

        return *this;
    }

public:
    string _val{};
};

int main() {
    string hello{"hello tomorrow"};
    vector<string> strVec{};

    strVec.push_back(move(hello));

    for (const auto& item : strVec) {
        cout << "item = " << item << endl;
    }

    cout << "----------------------" << endl;

    hello = "life come on";
    cout << "hello = " << hello << endl;

    cout << "------------------------" << endl;

    myType instance{"buzhidao a"};
    vector<myType> vecMyType{};

    //此处调用myType的move constructor
    vecMyType.push_back(move(instance));

    for (const auto& item : vecMyType) {
        cout << "item = " << item.val << endl;
    }

    cout << "instance.val = " << instance.val << endl;
    instance = myType{"kaka"};

    cout << "instance.val = " << instance.val << endl;

    int aa = 100;
    move(aa);

    cout << "aa = " << aa << endl;



    return 0;
}