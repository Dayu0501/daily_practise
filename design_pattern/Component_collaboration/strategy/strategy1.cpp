/* 未采用策略模式，由于后期扩展功能，而导致之前代码的改动，破坏了开闭原则(对修改封闭，对扩展开放)
 * 打破了之前SalesOrder的封装的完整性，来增加新的条件功能
 * */

enum TaxBase {
	CN_Tax,
	US_Tax,
	DE_Tax,
	FR_Tax       //更改
};

class SalesOrder {
	TaxBase tax;
public:
	double CalculateTax() {
		//...

		if (tax == CN_Tax) {
			//CN***********
		} else if (tax == US_Tax) {
			//US***********
		} else if (tax == DE_Tax) {
			//DE***********
		} else if (tax == FR_Tax) {  //更改
			//...
		}

		//....
	}

};
