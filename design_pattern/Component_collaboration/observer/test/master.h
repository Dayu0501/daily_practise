//
// Created by yulichao on 2020/11/9.
//

#include "head.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <list>

using namespace std;

class master {
private:
	list<notifier *> pNotifierlist;

public:
	master() = default;

	void doWork() {
		cout << "master work : " << endl;
		for (int i = 0; i < 100; ++i) {
			cout << "do working !" << endl;
			for (auto item : pNotifierlist)
				item->notify(i + 1);

			sleep(1);
		}
		cout << "finish !" << endl;
	}

	void addObserver(notifier * p) {
		pNotifierlist.push_back(p);
	}

	void removeObserver(notifier *p) {
		pNotifierlist.remove(p);
	}
};