#include <iostream>

using namespace std;

class A {
public:
    int a;
};

class B : virtual public A {
public :
    int bb;
};

class C : virtual public A {
public:
    int cc;
};

class D : public B, public C {
public :
    void print() {
        cout << "A::a = " << a << endl;
    }
};


int main() {
    cout << "----- [ 虚继承测试 ] ------" << endl;
    D ins;
    ins.print();

    return 0;
}