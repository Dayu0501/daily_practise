#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class AA {
public :
	AA() {
		cout << "I am construct !" << endl;
	}

	~AA() {
		cout << "I am destruct !" << endl;
	}

	string aa;
    string bb;
};

int main() {
	cout << "----- [ 测试析构函数是否会被调用 ] -----" << endl;
	AA * ptr = new AA;

	//vector<AA, __gun_cxx::__pool_allo>
	vector<string, __gun_cxx::__pool_alloc<string>> testStr;



	return 0;
}