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

//	void exec() {
//		cout << "observer exec :" << endl;
//		master ins;
//		ins.addObserver(this);
//		observer2 ins2;
//		ins.addObserver(&ins2);
//		ins.doWork();
//	}
};



int main() {
	observer1 ins;
	std::cout << std::endl << "----- [ ma doWork ] -----" << std::endl;
	//下面这种使用方式，类似于epoll的使用方式
	observer2 ins2;
	master ma;
	ma.addObserver(&ins);
	ma.addObserver(&ins2);

	ma.doWork();


	return 0;
}

