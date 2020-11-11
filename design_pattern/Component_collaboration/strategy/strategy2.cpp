/* 使用策略模式，提出一个抽象类，供各个条件的子类继承，处理的类，只管调用操作方式，不关注使用的是哪一个条件类型 */


class Context {

};

class TaxStrategy {
public:
	virtual double Calculate(const Context &context) = 0;

	virtual ~TaxStrategy() {}
};

class StrategyFactory {
public:
	TaxStrategy *NewStrategy() {}
};

class CNTax : public TaxStrategy {
public:
	double Calculate(const Context &context) override {
		//***********
	}
};

class USTax : public TaxStrategy {
public:
	double Calculate(const Context &context) override {
		//***********
	}
};

class DETax : public TaxStrategy {
public:
	double Calculate(const Context &context) override {
		//***********
	}
};

//扩展
class FRTax : public TaxStrategy {
public:
	double Calculate(const Context &context) override {
		//.........
	}
};

class SalesOrder {
private:
	TaxStrategy *strategy;

public:
	SalesOrder(StrategyFactory *strategyFactory) {
		this->strategy = strategyFactory->NewStrategy();
	}

	~SalesOrder() {
		delete this->strategy;
	}

public:
	double CalculateTax() {
		//...
		Context context;

		double val = strategy->Calculate(context); //多态调用
		//...
	}
};