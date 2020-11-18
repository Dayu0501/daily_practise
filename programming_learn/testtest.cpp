#include <iostream>
#include <vector>
#include <string>
#include <ext/pool_allocator.h>
#include <regex>

using namespace std;

#define ALLSTATION "1111;2222;3333;"
using uint = unsigned int;


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

void split(const char* token, std::string &str, std::vector<std::string> &splitVector)
{
	std::regex reg(token);
	std::sregex_token_iterator begin(str.begin(), str.end(), reg ,-1), end;
	std::copy(begin, end, std::back_inserter(splitVector));
}

std::string deleteMarks(string& des, char x) {
	des.erase(remove(des.begin(), des.end(), x), des.end());

	return des;
}

int main() {
	cout << "----- [ 测试析构函数是否会被调用 ] -----" << endl;
	{
		AA * ptr = new AA; //临时指针变量，在离开作用空间的时候，是不会调用该指针指向的类型的析构函数的，必须显示调用delete。
		//delete ptr;
	}
	std::cout << "----- [ 测试 __pool_alloc ] -----" << std::endl;
	vector<string, __gnu_cxx::__pool_alloc<string>> testStr;

	std::cout << std::endl << "----- [ 测试字符串分割函数 ] -----" << std::endl;
	string tmp = "ALLSTATION;";

	std::string::size_type pos;
	if ((pos = tmp.find("ALLSTATION;")) != std::string::npos)
		tmp.replace(pos, std::string("ALLSTATION;").length(), ALLSTATION);

	cout << "tmp is " << tmp << endl;



	std::vector<std::string> splitVector;
	split(";", tmp, splitVector);

	for (const auto & item : splitVector) {
		cout << "item is " << item;
	}
	cout << "end" << endl;

	uint hello{100};
	cout << "hello is " << hello << endl;

	string faDongJiHao = "FP 081222121";
	deleteMarks(faDongJiHao, ' ');
	cout << "faDongJiHao = " << faDongJiHao << endl;

	return 0;
}