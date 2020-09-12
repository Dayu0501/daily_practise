#include "algorithmUnity.h"
#include "myalloc.h"
#include <ctime>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

void test_DY_remove() {
	cout << "test remove start !" << endl;
	string testData_0 = "465875906556";
	char b = '5';

	cout << "operation data is " << testData_0 << endl;
	cout << "Need to delete is " << b << endl;

	testData_0.erase(DY::remove(testData_0.begin(), testData_0.end(), b), testData_0.end());

	cout << "result = " << testData_0 << endl;
}

void test_DY_remove_if() {
	cout << "test remove_copy_if test" << endl;

	string testData_0{"465 87 5906 556"};
	cout << "operation data is " << testData_0 << endl;

	testData_0.erase(
		DY::remove_if(testData_0.begin(), testData_0.end(), [](unsigned char x) { return std::isspace(x); }),
		testData_0.end());

	cout << "result = " << testData_0 << endl;
}

std::string getNowDate() {
	time_t t;
	char buf[64];

	/* 获取时间 */
	time(&t);
	strftime(buf, sizeof(buf), "%F", localtime(&t));
	return buf;
}

std::string getDangTianRiQi() {
	std::string nowTime;
	std::time_t t = std::time(NULL);
	std::tm *st = std::localtime(&t);
	char tmpArray[64] = {0};
	sprintf(tmpArray, "%d-%02d-%02d", st->tm_year + 1900, st->tm_mon + 1, st->tm_mday);

	nowTime = tmpArray;

	return nowTime;
}

void testPrint(string &param = (string &) "") {
	if (param == "hello") {
		cout << "param is " << param << endl;
	}
}

time_t strTime2unix(const std::string &time, const std::string &format) {
	struct tm tm{};
	memset(&tm, 0, sizeof(tm));

	int count = sscanf(time.c_str(), format.c_str(),
	                   &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
	                   &tm.tm_hour, &tm.tm_min, &tm.tm_sec);

	if (count != 6) return (time_t) 0;

	tm.tm_year -= 1900;
	tm.tm_mon--;

	return mktime(&tm);
}

void testDiffOneYear() {
	string kaiShiRiQiShuChu{"20200716"};
	kaiShiRiQiShuChu += " 00:00:00";

	string jieZhiRiQiShuChu{"20210715"};
	jieZhiRiQiShuChu += " 00:00:00";

	time_t kaiShiRiQiShuChuStamp = strTime2unix(kaiShiRiQiShuChu, "%4d%2d%2d %d:%d:%d");
	cout << "kaiShiRiQiShuChuStamp = " << kaiShiRiQiShuChuStamp << endl;

	time_t jieZhiRiQiShuChuStamp = strTime2unix(jieZhiRiQiShuChu, "%4d%2d%2d %d:%d:%d");
	cout << "jieZhiRiQiShuChuStamp = " << jieZhiRiQiShuChuStamp << endl;

	int diff = (jieZhiRiQiShuChuStamp - kaiShiRiQiShuChuStamp) / (60 * 60 * 24);

	cout << "diff = " << diff << endl;
}


//test parent child

class pClass {
public :
	virtual void print() {
		cout << "I am parent print !\n" << endl;
	}
};

class sClass : public pClass {
public :
	void print() override {
		pClass::print();
		cout << "I am testing !\n" << endl;
	}
};

void test_DY_replace() {
	string hello{"7289245892288"};
	cout << "hello is " << hello << endl;

	DY::replace(hello.begin(), hello.end(), '2', '0');
	cout << "DY_replace hello is " << hello << endl;

	DY::replace_if(hello.begin(), hello.end(), '1', [](char x) { return x == '9'; });
	cout << "DY_replace_if hello is " << hello << endl;
}

#define DY_REPLACE

int main() {

#ifdef DY_REMOVE
	test_DY_remove();
#endif

#ifdef DY_REMOVE_IF
	test_DY_remove_if();
#elif defined(DY_REPLACE)
	test_DY_replace();
#endif


	//vector<string, my_alloc::allocator<string>> ins {"hello", "world"};

	cout << "date is " << getNowDate() << endl;
	cout << "getDangTianRiQi is " << getDangTianRiQi() << endl;

	//testPrint((string &) "1");

	//testPrint();

	cout << "---------------" << endl;
	testDiffOneYear();

	cout << "---------------" << endl;

	sClass ins;
//	ins.print();

	pClass *pIns = &ins;
	pIns->print();

	cout << "----- lambda ---------" << endl;

	auto bb = []() {
		int aa = 0;
		aa++;
		return aa;
	};

	cout << "bb = " << bb << endl;

	cout << "----- assert ----------" << endl;

	int hehe = 1;

	assert(hehe == 1);



	cout << "test test test !" << endl;

	return 0;
}