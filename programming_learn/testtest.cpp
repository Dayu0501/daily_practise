#include <iostream>
#include <vector>
#include <string>
#include <ext/pool_allocator.h>
#include <regex>
#include <sys/stat.h>
#include <unistd.h>

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

int testNoRet() {
	cout << "hhhhhhhhhhh" << endl;

	return 1;
}

int CreatDir(const char *pszDir)
{
	int iLen = strlen(pszDir);
	char des[iLen + 1];
	memcpy(des, pszDir, iLen);
	printf("des is %s\n", des);

	iLen = strlen(des);
	if (des[iLen - 1] != '\\' && des[iLen - 1] != '/') {
		des[iLen] = '/';
		des[iLen + 1] = '\0';
	}

	printf("des is %s\n", des);

	for (int i = 0; i <= iLen; ++i) {
		if ((des[i] == '\\' || des[i] == '/') && i != 0) {
			des[i] = '\0';
			printf("des is %s\n", des);
			if (access(des, 0) != 0) {
				if (mkdir(des, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
					perror("mkdir failed !\n");
					return -1;
				}
			}
			//支持linux,将所有\换成/
			des[i] = '/';
		}
	}
	return 0;
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

	std::cout << std::endl << "----- [ 测试字符串分割反向 ] -----" << std::endl;

	tmp = "/opt/vehicle/program/log/soap/soapinfo.log";
	pos = tmp.find_last_of('/');
	string allPath = tmp.substr(0, pos);
	cout << "allPath is " << allPath << endl;

	pos = allPath.find_last_of('/');
	string subPath = allPath.substr(pos + 1);

	cout << "subPath is " << subPath << endl;

	std::cout << std::endl << "----- [ 测试noreturn关键字 ] -----" << std::endl;
	testNoRet();

	std::cout << std::endl << "----- [ 测试mkdir函数 ] -----" << std::endl;
	string path = "./testlog/11/222/333";
	cout << mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) << endl;
	cout << "errno" << errno << endl;
	perror("mkdir failed");

	std::cout << std::endl << "----- [ 测试CreatDir ] -----" << std::endl;
	std::string hellok = "./testtesttest/111/222";
	CreatDir(hellok.c_str());

	return 0;
}