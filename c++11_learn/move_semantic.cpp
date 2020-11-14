//
// Created by yulichao on 2020/11/12.
//
#include <iostream>

using namespace std;

class testObj {
public:
	testObj() {
		cout << "i am testObj con !" << endl;
	}

	testObj(const testObj &obj) {
		cout << "i am testObj copy con !" << endl;
	}

	void print() {
		cout << "hello testObj !" << endl;
	}
};

void print(testObj obj) {
	obj.print();
}

/* 专栏例子 */

class shape {
public:
	virtual ~shape() {}
};

class circle : public shape {
public:
	circle() { puts("circle()"); }

	~circle() { puts("~circle()"); }
};

class triangle : public shape {
public:
	triangle() { puts("triangle()"); }

	~triangle() { puts("~triangle()"); }
};

class result {
public:
	result() { puts("result()"); }

	~result() { puts("~result()"); }
};

result process_shape(const shape &shape1, const shape &shape2) {
	puts("process_shape()");
	return result();
}

/* 返回值优化和返回本地变量的移动语义 */
class Obj {
public:
	Obj() {
		cout << "Obj()" << endl;
	}

	Obj(const Obj &) {
		cout << "Obj(const Obj&)" << endl;
	}

	Obj(Obj &&) {
		cout << "Obj(Obj&&)" << endl;
	}
};

Obj simple() {
	Obj obj;
	// 简单返回对象；一般有 NRVO
	return obj;
}

Obj simple_with_move() {
	Obj obj;
	// move 会禁止 NRVO
	return std::move(obj);
}

Obj complicated(int n) {
	Obj obj1;
	Obj obj2;
	// 有分支，一般无 NRVO
	if (n % 2 == 0) {
		return obj1;
	} else {
		return obj2;
	}
}


void foo(const shape &) {
	puts("foo(const shape&)");
}

void foo(shape &&) {
	puts("foo(shape&&)");
}

/* 下面两个bar函数由下面的template函数来代替 */
//void bar(const shape &s) {
//	puts("bar(const shape&)");
//	foo(s);
//}
//
//void bar(shape &&s) {
//	puts("bar(shape&&)");
//	foo(s);                         //这个时候s作为左值引用，会调用foo(const shape &)
//
//	foo(static_cast<shape &&>(s));   //这个时候调用的是foo(shape &&)
//	foo(move(s));                   //这个时候调用的是foo(shape &&)
//}

template<typename T>
void bar(T &&s) {
	puts("template bar ");
	foo(std::forward<T>(s));
}

int main() {
	testObj kk;
	print(kk);

	std::cout << std::endl << "----- [ 直接调用testObj ] -----" << std::endl;

	print(testObj());

	std::cout << std::endl << "----- [ 专栏例子 ] -----" << std::endl;

	/* 下面的例子展示了临时对象在离开了表达式后（下面是函数调用）释放 */
	puts("main()");
	//process_shape(circle(), triangle());  //临时对象的释放例子

	//result && res = process_shape(circle(), triangle());    //延长临时对象的生命周期


	/* 虽然result调用了析构函数，但是这个时候的result并没有指向process_shape返回值，对一个将亡值的引用是无效的
	 * 也就是说一个变量进行move函数操作后，就变成了将亡值，在对他内部的操作是未定义的行为*/
	result &&r = std::move(process_shape(circle(), triangle()));

	//result & res = process_shape(circle(), triangle());   编译报错，因为process_shape返回的不是引用
	puts("something else");


	std::cout << std::endl << "----- [ 返回值优化 ] -----" << std::endl;
	cout << "*** 1 有返回值优化 ***" << endl;
	auto obj1 = simple();

	cout << "*** 2 使用move反而禁用了返回值的优化 ***" << endl;
	auto obj2 = simple_with_move();

	cout << "*** 3 ***没有返回值优化的情况下，编译器将试图把本地对象移动出去，而不是拷贝出去" << endl;
	auto obj3 = complicated(42);


	std::cout << std::endl << "----- [ 折叠引用（或成为引用坍缩） ] -----" << std::endl;
	bar(circle());


	std::cout << std::endl << "----- [ std::forward 转发引用] -----" << std::endl;
	/* 转发引用，保证了当前的值类别，是左值就是左值，是右值就是右值 */
	circle temp;
	bar(temp);
	bar(circle());

	return 0;
}