//
// Created by yulichao on 2020/11/9.
//

#include "head.h"
#include "master.h"

class observer2 : public notifier {
public:
	void notify(int val) override {
		cout << "From master info is " << val << endl;
	}
};

class observer1 : public notifier {
public:
	observer1() = default;
	void notify(int val) override{
		while (val--) { //注意此处只有为0的时候，会退出循环，为负数的时候，也是会进入循环的
			cout << ". ";
		}

		cout << endl;
	}
};



int main() {
	observer1 ins;
	std::cout << std::endl << "----- [ ma doWork ] -----" << std::endl;
	/* 下面这种使用方式，类似于epoll的使用方式，epoll中的回调函数的工作是，把注册了socket加到就绪队列中 */
	observer2 ins2;
	master ma;
	ma.addObserver(&ins);
	ma.addObserver(&ins2);

	ma.doWork();


	return 0;
}

