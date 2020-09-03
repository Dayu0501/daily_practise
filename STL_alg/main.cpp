#include "algorithmUnity.h"
#include "myalloc.h"
#include <time.h>
#include <ctime>
#include <stdio.h>

void test_DY_remove () {
	cout << "test remove start !" << endl;
	string testData_0 = "465875906556";
	char b = '5';

	cout << "operation data is " << testData_0 << endl;
	cout << "Need to delete is " << b << endl;

    testData_0.erase(DY_remove(testData_0.begin(), testData_0.end(), b), testData_0.end());

	cout << "result = " << testData_0 << endl;
}

<<<<<<< HEAD
void test_DY_remove_if() {
    cout << "test remove_copy_if test" << endl;

    string testData_0 {"465 87 5906 556"};
    cout << "operation data is " << testData_0 << endl;

    testData_0.erase(DY_remove_if(testData_0.begin(), testData_0.end(), [](unsigned char x){ return std::isspace(x); }), testData_0.end());

    cout << "result = " << testData_0 << endl;
}

#define DY_REMOVE_IF
=======
std::string getNowDate()
{
	time_t t;
	char buf[64];

	/* 获取时间 */
	time(&t);
	strftime(buf, sizeof(buf), "%F", localtime(&t));
	return buf;
}

std::string getDangTianRiQi()
{
	std::string nowTime;
	std::time_t t = std::time(NULL);
	std::tm *st = std::localtime(&t);
	char tmpArray[64] = { 0 };
	sprintf(tmpArray, "%d-%02d-%02d", st->tm_year + 1900, st->tm_mon + 1, st->tm_mday);

	nowTime = tmpArray;

	return nowTime;
}
>>>>>>> fb49f2ad80ba9783d569153aa581cd8f4a7350b1

int main() {

#ifdef DY_REMOVE
	test_DY_remove();
#endif

<<<<<<< HEAD
#ifdef DY_REMOVE_IF
    test_DY_remove_if();
#endif
=======
	//vector<string, my_alloc::allocator<string>> ins {"hello", "world"};

	cout << "date is " << getNowDate() << endl;
	cout << "getDangTianRiQi is " << getDangTianRiQi() << endl;
>>>>>>> fb49f2ad80ba9783d569153aa581cd8f4a7350b1



	return 0;
}