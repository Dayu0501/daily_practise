//
// Created by yulichao on 2020/11/12.
//

#include <iostream>
#include <vector>

using namespace std;

class Obj1 {
public:
	Obj1() {
		cout << "Obj1()\n";
	}

	Obj1(const Obj1 &) {
		cout << "Obj1(const Obj1&)\n";
	}

	Obj1(Obj1 &&) {
		cout << "Obj1(Obj1&&)\n";
	}
};

class Obj2 {
public:
	Obj2() {
		cout << "Obj2()\n";
	}

	Obj2(const Obj2 &) {
		cout << "Obj2(const Obj2&)\n";
	}

	Obj2(Obj2 &&) noexcept {
		cout << "Obj2(Obj2&&)\n";
	}
};

/* 下面的是默认继承方式，默认的是私有继承 */
template<class T>
struct less : binary_function<T, T, bool> {
	bool operator()(const T &x, const T &y) const {
		return x < y;
	}
};


#include <algorithm>   // std::sort
#include <functional>  // std::less/greater/hash
#include <iostream>    // std::cout/endl
#include <string>      // std::string
#include <vector>      // std::vector
#include "output_container.h"


#include <complex>        // std::complex
#include <iostream>       // std::cout/endl
#include <unordered_map>  // std::unordered_map
#include <unordered_set>  // std::unordered_set
#include "output_container.h"

using namespace std;

//在std空间添加特化。
namespace std {

	template<typename T>
	struct hash<complex<T>> {
		size_t
		operator()(const complex<T> &v) const
		noexcept {
			hash<T> h;
			return h(v.real()) + h(v.imag());
		}
	};

}


int main() {
	vector<Obj1> v1;
	v1.reserve(2);
	v1.emplace_back();
	v1.emplace_back();
	v1.emplace_back();


//	vector<Obj2> v2;
//	v2.reserve(2);
//	v2.emplace_back();
//	v2.emplace_back();
//	v2.emplace_back();


	std::cout << std::endl << "----- [ 容器二 ] -----" << std::endl;

// 初始数组
	vector<int> v{13, 6, 4, 11, 29};
	cout << v << endl;

	// 从小到大排序
	sort(v.begin(), v.end());
	cout << v << endl;

	// 从大到小排序
	sort(v.begin(), v.end(),
	     greater<int>());
	cout << v << endl;

	cout << hex;

	auto hp = hash<int *>();
	cout << "hash(nullptr)  = "
	     << hp(nullptr) << endl;
	cout << "hash(v.data()) = "
	     << hp(v.data()) << endl;
	cout << "v.data()       = "
	     << static_cast<void *>(v.data())
	     << endl;

	auto hs = hash<string>();
	cout << "hash(\"hello\")  = "
	     << hs(string("hello")) << endl;
	cout << "hash(\"hellp\")  = "
	     << hs(string("hellp")) << endl;

	std::cout << std::endl << "----- [ 无序关联式容器 ] -----" << std::endl;

	unordered_set<int> s{
		1, 1, 2, 3, 5, 8, 13, 21
	};
	cout << s << endl;

	unordered_map<complex<double>,
		double>
		umc{{{1.0, 1.0}, 1.4142},
		    {{3.0, 4.0}, 5.0}};
	cout << umc << endl;

	return 0;
}

