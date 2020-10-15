#include <iostream>
#include <string>

using namespace std;

int main() {
	string hello = "ni hao zhongguo !";
	string hahaa = hello;


	char * tmp = const_cast<char *>(hello.c_str());
	std::cout << "----- [ 测试转换后的字符串 ] -----" << std::endl;
	cout << "tmp   is -> " << tmp << endl;
	cout << "hello is -> " << hello << endl;
	cout << "hahaa is -> " << hahaa << endl;

	tmp[0] = 'a';
	tmp[1] = 'b';
	std::cout << "----- [ 修改后的 ] -----" << std::endl;
	cout << "tmp   is -> " << tmp << endl;
	cout << "hello is -> " << hello << endl;
	cout << "hahaa is -> " << hahaa << endl;

	/*
	 *结论 ：tmp是可以修改hello中的内容，但是不能修改hahaa中的内容。
	 * */

	return 0;
}