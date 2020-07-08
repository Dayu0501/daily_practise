//
// Created by yulichao on 2020/7/8.
//

#include <string>
#include <iostream>

using namespace std;


class newType {
public:
    newType() {
        cout << "I am newType constructor !" << endl;
    }

    newType(const newType& val) {
        cout << "I am newType copy constructor !" << endl;
    }

    virtual void print() {
        cout << "I am newType print !" << endl;
    }
};

class newSubType : public newType {
public:
    void print() override {
        newType::print();
        cout << "I am newSubType print !" << endl;
    }
};


int main() {
    newType ins{};

    newType ins1 = {};

    newSubType childHaha1;

    newType& haha1 = childHaha1;
    haha1.print();

    return 0;
}