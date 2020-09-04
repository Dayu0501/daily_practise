#include "algorithmUnity.h"
#include "myalloc.h"
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <string.h>

void test_DY_remove () {
	cout << "test remove start !" << endl;
	string testData_0 = "465875906556";
	char b = '5';

	cout << "operation data is " << testData_0 << endl;
	cout << "Need to delete is " << b << endl;

    testData_0.erase(DY_remove(testData_0.begin(), testData_0.end(), b), testData_0.end());

	cout << "result = " << testData_0 << endl;
}

void test_DY_remove_if() {
    cout << "test remove_copy_if test" << endl;

    string testData_0 {"465 87 5906 556"};
    cout << "operation data is " << testData_0 << endl;

    testData_0.erase(DY_remove_if(testData_0.begin(), testData_0.end(), [](unsigned char x){ return std::isspace(x); }), testData_0.end());

    cout << "result = " << testData_0 << endl;
}

#define DY_REMOVE_IF

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

void testPrint(string & param = (string &) "") {
	if (param == "hello") {
		cout << "param is " << param << endl;
	}
}

time_t strTime2unix(const std::string& time, const std::string& format) {
	struct tm tm{};
	memset(&tm, 0, sizeof(tm));

	int count = sscanf(time.c_str(), format.c_str(),
	                   &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
	                   &tm.tm_hour, &tm.tm_min, &tm.tm_sec);

	if (count != 6)    return (time_t)0;

	tm.tm_year -= 1900;
	tm.tm_mon--;

	return mktime(&tm);
}

void testDiffOneYear() {
	string kaiShiRiQiShuChu{"20200101"};
	kaiShiRiQiShuChu += " 00:00:00";

	string jieZhiRiQiShuChu{"20201231"};
	jieZhiRiQiShuChu += " 00:00:00";

	time_t kaiShiRiQiShuChuStamp = strTime2unix(kaiShiRiQiShuChu, "%4d%2d%2d %d:%d:%d");
	cout << "kaiShiRiQiShuChuStamp = " << kaiShiRiQiShuChuStamp << endl;

	time_t jieZhiRiQiShuChuStamp = strTime2unix(jieZhiRiQiShuChu, "%d%d%d %d:%d:%d");
	cout << "jieZhiRiQiShuChuStamp = " << jieZhiRiQiShuChuStamp << endl;

	int diff = (jieZhiRiQiShuChuStamp - kaiShiRiQiShuChuStamp)/(60  * 60 * 24) ;

	cout << "diff = " << diff << endl;
}

int main() {

#ifdef DY_REMOVE
	test_DY_remove();
#endif

#ifdef DY_REMOVE_IF
    test_DY_remove_if();
#endif
	//vector<string, my_alloc::allocator<string>> ins {"hello", "world"};

	cout << "date is " << getNowDate() << endl;
	cout << "getDangTianRiQi is " << getDangTianRiQi() << endl;

	//testPrint((string &) "1");

	//testPrint();

	cout << "---------------" << endl;
	testDiffOneYear();

	return 0;
}