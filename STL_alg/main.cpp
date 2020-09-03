#include "algorithmUnity.h"
#include "myalloc.h"
#include <time.h>
#include <ctime>
#include <stdio.h>

void test_DY_remove () {
	cout << "test remove start !" << endl;
	string testDate_0 = "465875906556";
	char b = '5';

	cout << "operation data is " << testDate_0 << endl;
	cout << "Need to delete is " << b << endl;

	testDate_0.erase(DY_remove(testDate_0.begin(), testDate_0.end(), b), testDate_0.end());

	cout << "result = " << testDate_0 << endl;
}

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

int main() {

#ifdef DY_REMOVE
	test_DY_remove();
#endif

	//vector<string, my_alloc::allocator<string>> ins {"hello", "world"};

	cout << "date is " << getNowDate() << endl;
	cout << "getDangTianRiQi is " << getDangTianRiQi() << endl;



	return 0;
}