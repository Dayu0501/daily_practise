/* 库开发人员工作 */
class Library {
public:
	//稳定 template method run稳定的，不需要声明为虚函数
	void Run() {

		Step1();

		if (Step2()) { //支持变化 ==> 虚函数的多态调用
			Step3();
		}

		for (int i = 0; i < 4; i++) {
			Step4(); //支持变化 ==> 虚函数的多态调用
		}

		Step5();

	}

	virtual ~Library() {} //基类的析构函数应该定义为虚函数，防止在delete子类对象的时候，不能完全的释放基类部分

protected:

	void Step1() { //稳定
		//.....
	}

	void Step3() { //稳定
		//.....
	}

	void Step5() { //稳定
		//.....
	}

	virtual bool Step2() = 0; //变化
	virtual void Step4() = 0;  //变化
};