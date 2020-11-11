/* 面向对象的思想的模板方法模式
 * 库开发人员定好接口，定好稳定的模板，至于具体的接口的实现延迟到子类实现，是晚绑定的体现
 * */

#include "template2_lib.h"

/* 应用程序开发人员工作 */
class Application : public Library {
protected:
	bool Step2() override {
		//... 子类重写实现
		return false;
	}

	void Step4() override {
		//... 子类重写实现
	}
};


int main() {
	Library *pLib = new Application();
	pLib->Run();

	delete pLib;
}