/* template1 下面是结构化编程的思路 */

#include "template1_lib.h"

/* 应用程序开发人员工作 */
class Application {
public:
	bool Step2() {
		//...
		return false;
	}

	void Step4() {
		//...
	}
};

int main() {
	Library lib;
	Application app;

	lib.Step1();

	if (app.Step2()) {
		lib.Step3();
	}

	for (int i = 0; i < 4; i++) {
		app.Step4();
	}

	lib.Step5();
}
