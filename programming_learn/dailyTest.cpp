#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

std::string deleteMarks(string& des, char x) {
	des.erase(remove(des.begin(), des.end(), x), des.end());

	return des;
}

bool checkDateIsExpired(std::string date, std::string startDate, std::string endDate)
{
	int diffStart = 0, diffEnd = 0;
	int date_year = std::stoi(date.substr(0, 4));
	int date_month = std::stoi(date.substr(5, 2));
	int date_day = std::stoi(date.substr(8, 2));

	int startDate_year = std::stoi(startDate.substr(0, 4));
	int startDate_month = std::stoi(startDate.substr(5, 2));
	int startDate_day = std::stoi(startDate.substr(8, 2));

	int endDate_year = std::stoi(endDate.substr(0, 4));
	int endDate_month = std::stoi(endDate.substr(5, 2));
	int endDate_day = std::stoi(endDate.substr(8, 2));

	diffStart = (date_year - startDate_year) * 12 + date_month - startDate_month;
	diffEnd = (endDate_year - date_year) * 12 + endDate_month - date_month;

	if (diffStart > 0 && diffEnd > 0)
		return true;
	else if (diffStart == 0 && diffEnd > 0)
	{
		if ((date_day - startDate_day) >= 0)
			return true;
	}
	else if (diffStart > 0 && diffEnd == 0)
	{
		if ((endDate_day - date_day) >= 0)
			return true;
	}
	else if (diffStart == 0 && diffEnd == 0)
	{
		if ((date_day - startDate_day) >= 0 && (endDate_day - date_day) >= 0)
			return true;
	}

	return false;
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
	string curDate = getDangTianRiQi();
	cout << "curDate is " << curDate << endl;

	string startDate = "2021-03-17";
	string endDate = "2022-03-17";

	cout << checkDateIsExpired(curDate, startDate, endDate) << endl;

	//string hel = "hello world    china !   ";

	//cout << "res = " << deleteMarks(hel, ' ') << endl;
	//cout << "hel len = " << hel.length() << endl;

	return 0;
}