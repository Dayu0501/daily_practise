#include "algorithmUnity.h"
#include "myalloc.h"
#include <ctime>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <set>
#include <utility>
#include "test.h"
#include <algorithm>

extern int gsi;
extern void staticTestPrint();

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
	string kaiShiRiQiShuChu{"20190826"};
	kaiShiRiQiShuChu += " 00:00:00";

	string jieZhiRiQiShuChu{"20200825"};
	jieZhiRiQiShuChu += " 00:00:00";

	time_t kaiShiRiQiShuChuStamp = strTime2unix(kaiShiRiQiShuChu, "%4d%2d%2d %d:%d:%d");
	cout << "kaiShiRiQiShuChuStamp = " << kaiShiRiQiShuChuStamp << endl;

	time_t jieZhiRiQiShuChuStamp = strTime2unix(jieZhiRiQiShuChu, "%4d%2d%2d %d:%d:%d");
	cout << "jieZhiRiQiShuChuStamp = " << jieZhiRiQiShuChuStamp << endl;

	int diff = (jieZhiRiQiShuChuStamp - kaiShiRiQiShuChuStamp) / (60 * 60 * 24);

	cout << "diff = " << diff << endl;
}

void testReverse() {
	std::string hel{"123456789"};
	DY::reverse(hel.begin(), hel.end());

	cout << "hel is " << hel << endl;
}

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

#define DY_REVERSE


//struct soapInfo {
//	std::string soapIp;
//	std::string soapPort;
//};

class objectMember{
public:
	std::string soapName;   //对应字段名称
	std::string codeName;
	std::string *value; //值地址
	std::string desc;   // 描述
};

struct soapInfo {
public:
	soapInfo(string param1, string param2) {
		soapIp = std::move(param1);
		soapPort = std::move(param2);
	}

	soapInfo() {
		soapIp = "";
		soapPort = "";
	}

	friend bool operator<(const soapInfo &infoObj1, const soapInfo & infoObj2) {
		return (infoObj1.soapIp + infoObj1.soapPort) < (infoObj2.soapIp + infoObj2.soapPort);
	}

	friend bool operator==(const soapInfo &infoObj1, const soapInfo & infoObj2) {
		return (infoObj1.soapIp + infoObj1.soapPort) == (infoObj2.soapIp + infoObj2.soapPort);
	}

	std::string soapIp;
	std::string soapPort;
};

typedef struct _STARTUPPRARAM
{
	int qsrqOffset;//开始时间
	int zzrqOffset;//结束时间
	int startTime; //工作开始时间
	int endTime; //工作结束时间
	int soapQueryInterval;//soap请求间隔
	std::string soapIp;
	std::string soapPort;
	std::set<soapInfo> soapInfoSet;
	std::string remoteIp;
	std::string remotePort;
	std::string soapUrl;
	int soapTimeOut; //soap超时时间
	std::string soapNum;  //soap流水号查询数量
	std::string soapXlh;  //soap序列号
	std::string soapPhotoUri;
	std::string workMode;  //工作模式
	std::string g_cjbh;
	std::string g_zdbs;
	std::string g_dwjgdm;
	bool isGroupResponse;//此参数暂时只有车检用
	bool queryVideo;

public:
	//切换到下一个可用的soap地址
	void switchCurSoapInfo() {
		auto iter = soapInfoSet.begin();
		soapInfo tmpInfo(soapIp, soapPort);
		for (; iter != soapInfoSet.end(); ++iter) {
			if (*iter == tmpInfo) {
				if (++iter != soapInfoSet.end()) {
					soapIp = iter->soapIp;
					soapPort = iter->soapPort;
				} else {
					soapIp = soapInfoSet.begin()->soapIp;
					soapPort = soapInfoSet.begin()->soapPort;
				}
			} else {
				soapIp = soapInfoSet.begin()->soapIp;
				soapPort = soapInfoSet.begin()->soapPort;
			}
		}
	}
}STARTUPPRARAM, *PSTARTUPPRARAM;

vector<string> stringSplit(string srcStr, const string& delim)
{
	vector<string> vec;
	if (srcStr.empty()) return vec;

	int nPos = 0;
	nPos = srcStr.find(delim);
	while(-1 != nPos)
	{
		string temp = srcStr.substr(0, nPos);
		vec.push_back(temp);
		srcStr = srcStr.substr(nPos+1);
		nPos = srcStr.find(delim);
	}

	vec.push_back(srcStr);

	return vec;
}

void testStatic() {
	static int aa = 100;

	cout << "aa = " << aa << endl;
}

int main() {

#ifdef DY_REMOVE
	test_DY_remove();
#endif

#ifdef DY_REMOVE_IF
	test_DY_remove_if();
#elif defined(DY_REPLACE)
	test_DY_replace();
#endif

#ifdef DY_REVERSE
	testReverse();
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

	DY::testCase(1);

	cout << "---------------" << endl;

	DY::testCase(2);

	cout << "---------------" << endl;

	//soapInfo soapIp {"192.168.20.59", "9083"};
//	vector<soapInfo> soapInfoSet {{"192.168.20.59", "9083"}};
//	objectMember obj;
//	obj.soapName = "hello";
//	obj.codeName = "world";
//	obj.value = (string *)&soapInfoSet;
//
//	cout << "soapName = " << obj.soapName << endl;
//	cout << "codeName = " << obj.codeName << endl;
//
//	for (const auto & item : *(vector<soapInfo>*)obj.value) {
//		cout << item.soapPort << endl;
//		cout << item.soapIp << endl;
//	}



	//	string ip = ((soapInfo *)obj.value)->soapIp;
//	string port = ((soapInfo *)obj.value)->soapPort;
//
//	cout << "ip = " << ip << endl;
//	cout << "port = " << port << endl;


	cout << "-------------------" << endl;
	string bubu = "bubu";
	string keke = "keke";
	if (bubu > keke) {
		cout << "bubu > keke" << endl;
	} else
		cout << "bubu < keke " << endl;

	cout << "---------------" << endl;

	string ip = "193.168.1.1";
	string port = "8888";

	//soapInfo tmp1 {ip, port};


	std::set<soapInfo> soapInfoSet;
	soapInfoSet.insert({ip, port}); //这种写法在c++14上是支持的，在c++11上是不支持的。

	cout << "1 soapInfoSet size is " << soapInfoSet.size() << endl;

	//soapInfoSet.insert(tmp1);

	cout << "2 soapInfoSet size is " << soapInfoSet.size() << endl;

	cout << "------------" << endl;

	vector<string> res = stringSplit("192.168.20.78:3000/192.168.20.55:6000/192.158.33.33:1111", "/");

	for (const auto & item : res) {
		cout << "item is " << item << endl;
		int nPos = item.find(':');
		if (nPos != -1 && item.length() > nPos + 1) {
			string ip = item.substr(0, nPos);
			string port = item.substr(nPos + 1, item.length());

			cout << "ip = " << ip << endl;
			cout << "port = " << port << endl;
		}
		cout << "-------------------------" << endl;

		set<string> testtest {"kaka", "haha", "keke", "dede", "gege"};

		auto iter = testtest.begin();
		for (; iter != testtest.end(); iter++) {
			cout << "test item is " << *iter << endl;
		}

		iter = testtest.begin();
		iter++;
		iter++;
		iter++;
		iter++;
		cout << "+4 item is " << *iter << endl;
		if (++iter == testtest.end())
			cout << "== testtest.end" << endl;

		//cout << "+3 item is " << *iter << endl;
	}

	soapInfo tmp1{"hello", "world"};
	soapInfo tmp2{"hello", "world"};

	if (tmp1 == tmp2)
		cout << "is the same " << endl;

	STARTUPPRARAM kaka;

	cout << "-------------------" << endl;
	testStatic();

	cout << "-------------------" << endl;

	cout << "gsi + 1 = " << gsi + 1 << endl;

	cout << "--------------------" << endl;

	cout << "head + 1 = " << head + 1 << endl;

	cout << "--------------------" << endl;
	staticTestPrint();

	/*
	 * set 存放自定义类型时，解决compare问题
	 *（1）给set传一个函数的参数：
	 *      1.传一个函数指针 set<stone, bool(*)(const stone & param1, const stone & param2)> stoneSet(compareStone);需要把指针类型放到<>中
	 *      2.传一个lambda表达式 set<stone, decltype(comp)> q(comp); comp为lambda表达式
	 *      3.传一个仿函数对象进来 set<stone, compareObj> stoneSet;
	 * (2)自定义类型内部运算符重载：
	 *      1.bool operator<(const stone& myType) const; const一定要带上，不然提示没有匹配的函数
	 *      2.friend bool operator<(const stone & param1, const stone & param2);或者定义友元函数的云算符重载
	 * */
	//set<stone, bool(*)(const stone & param1, const stone & param2)> stoneSet(compareStone);
	//set<stone> stoneSet;
	set<stone, compareObj> stoneSet;
	stoneSet.insert({10, "blue"});
	stoneSet.insert({20, "green"});
	stoneSet.insert({30, "gray"});
	stoneSet.insert({40, "red"});

	vector<stone> stoneVec{{40, "red"},
						   {10, "blue"},
	                       {20, "green"},
	                       {30, "gray"}
						  };

	//下面函数可以直接调用函数名字，因为sort是模板函数，具有类型推导功能，上面的set指定类型的时候就必须指定函数的类型，因为set是模板类没有参数类型推导的功能。
	//sort(stoneVec.begin(), stoneVec.end(), compareStone);
	sort(stoneVec.begin(), stoneVec.end(), compareObj());
	for (const auto & item : stoneVec) cout << "item is " << to_string(item.size) + item.color << endl;

	testObj aaa;
	testObj bbb;

	cout << "aaa < bbb = " << (aaa < bbb) <<endl;

	aaa.print();



	return 0;
}