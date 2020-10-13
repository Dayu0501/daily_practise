#include <iostream>

using namespace std;

class AA {
public :
	AA() {
		cout << "I am construct !" << endl;
	}

	~AA() {
		cout << "I am destruct !" << endl;
	}
};

int main() {
	cout << "----- [ 测试析构函数是否会被调用 ] -----" << endl;
	AA * ptr = new AA;



	return 0;
}

