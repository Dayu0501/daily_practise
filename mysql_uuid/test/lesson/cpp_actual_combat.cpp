//
// Created by yulichao on 2020/7/4.
//

#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

template<typename T>
class myType {
public:


private:
    T _array[10];
};


class Obj {
public:
    Obj() { puts("Obj()"); }

    ~Obj() { puts("~Obj()"); }
};

void foo(int n) {
    Obj obj;
    if (n == 42)
        throw "life, the universe and everything";
}

enum class shape_type {
    circle,
    triangle,
    rectangle
};

class shape {
public:
    virtual ~shape() {
        cout << "I am ~shape !" << endl;
    }

    virtual void print() {
        cout << "I am shape print !" << endl;
    }
};

class circle : public shape {
public:
    ~circle() override {
        cout << "I am ~circle !" << endl;
    }

    void print() override {
        cout << "I am circle print !" << endl;
    }
};

class triangle : public shape {

};

class rectangle : public shape {

};

shape *create_shape(shape_type type) {
    switch (type) {
        case shape_type::circle:
            return new circle();
        case shape_type::triangle:
            return new triangle();
        case shape_type::rectangle:
            return new rectangle();
    }
}

class shape_wrapper {
public:
    explicit shape_wrapper(shape *ptr = nullptr) : _ptr(ptr) {

    }

    ~shape_wrapper() {
        delete _ptr; // if (_ptr) 是没有必要的，因为delete 空指针是没有任何影响的。delete一个空指针是合法的。
    }

    shape *get() const { return _ptr; }

private:
    shape *_ptr;
};

void foo() {
    shape_wrapper ptr_wrapper(create_shape(shape_type::circle));
}

template <typename T>
class smart_ptr {
public:
    explicit smart_ptr(T *ptr = nullptr) : ptr_(ptr) {

    }

    T &operator*() const {
        cout << "operation * !" << endl;

        return *ptr_;
    }

    T *operator->() const {
        cout << "operation -> !" << endl;
        return ptr_;
    }

    explicit operator bool() const {
        cout << "operation bool !" << endl;
        return ptr_;
    }

    ~smart_ptr() {
        cout << "I am ~smart_ptr !" << endl;
        delete ptr_;
    }

    //禁止该类的拷贝构造和赋值运算
//    smart_ptr(const smart_ptr&) = delete ;
//    smart_ptr& operator=(const smart_ptr &) = delete ;

    smart_ptr(smart_ptr &other) {
        ptr_ = other.release();
    }

    smart_ptr &operator=(smart_ptr &rhs) {
        smart_ptr(rhs).swap(*this);
        return *this;
    }

    smart_ptr(smart_ptr &&other)  noexcept {
        ptr_ = other.release();
    }

    smart_ptr &operator=(smart_ptr rhs) {
        rhs.swap(*this);
        return *this;
    }

    T *release() {
        T *ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void swap(smart_ptr &rhs) {
        using std::swap;
        swap(ptr_, rhs.ptr_);
    }

    T *get() const { return ptr_; }

private:
    T *ptr_;
};


int main() {

// C++ 堆上分配内存（堆的子集free store）
    auto ptr = new vector<int>();
    try {
        foo(41);
        foo(42);
        //foo();
    }
    catch (const char *s) {
        puts(s);
    }

    cout << "-----------------------" << endl;
    {
        //下面这一段的，当把基类的析构函数和子类的析构函数设置为虚函数，就可以先调用子类的析构函数释放子类的资源，然后再调用基类的析构函数释放基类的资源
        smart_ptr<shape> tmpSmarShapPtr{create_shape(shape_type::circle)};
        *tmpSmarShapPtr;

        shape *temShapPtr = tmpSmarShapPtr.get();
        temShapPtr->print();

        if (tmpSmarShapPtr) {
            cout << "cout smart_ptr bool !" << endl;
        }
    }

    cout << "-----------------------" << endl;
    {

    }
}