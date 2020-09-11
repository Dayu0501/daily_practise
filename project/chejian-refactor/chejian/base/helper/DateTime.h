#ifndef DATETIME_H
#define DATETIME_H
#include <ctime>
#include <string>
#include <stdint.h>

//#pragma  warning(disable:4996)
class Year;
class Month;
class Day;
class Hour;
class Minute;
class Second;
class DateTime
{
public:
	DateTime(std::time_t seconds = 0);
	DateTime(struct std::tm time_tm);
	DateTime(int year, int month = 0, int day = 0, int hour = 0, int minute = 0, int second = 0);
	DateTime(const std::string& datetimeStr);//(yyyy-mm-dd hh:mm:ss) or (yyyymmdd)

	int sec();
	int minu();
	int hour();
	int mday();
	int mon();
	int year();
	int wday();
	int yday();

	DateTime operator+(const Year& year);
	DateTime operator+(const Month& month);
	DateTime operator+(const Day& day);
	DateTime operator+(const Hour& hour);
	DateTime operator+(const Minute& minute);
	DateTime operator+(const Second& second);
	DateTime operator-(const Year& year);
	DateTime operator-(const Month& month);
	DateTime operator-(const Day& day);
	DateTime operator-(const Hour& hour);
	DateTime operator-(const Minute& minute);
	DateTime operator-(const Second& second);

	bool operator>(const DateTime& rv);
	bool operator==(const DateTime& rv);
	bool operator<(const DateTime& rv);
	bool operator>=(const DateTime& rv);
	bool operator<=(const DateTime& rv);
	bool operator!=(const DateTime& rv);

	static bool isLeap(uint16_t year);
	static uint16_t lastDayOfMonth(uint16_t year, uint16_t month);
	uint16_t lastDayOfMonth();
	std::string ToDateString();
	std::string ToDateTimeString();
	struct std::tm GetTm();
	std::time_t GetTotalSeconds();
private:
	std::time_t _seconds;//自1970-01-01 08:00:00起的秒数;
};

class Year
{
public:
	Year(uint16_t year) :_year(year){}
	uint16_t _year;
};

class Month
{
public:
	Month(uint16_t month) :_month(month){}
	uint16_t _month;
};
class Day
{
public:
	Day(uint16_t day) :_day(day){}
	uint16_t _day;
};
class Hour
{
public:
	Hour(uint16_t hour) :_hour(hour){}
	uint16_t _hour;
};
class Minute
{
public:
	Minute(uint16_t minute) :_minute(minute){}
	uint16_t _minute;
};
class Second
{
public:
	Second(uint16_t second) :_second(second){}
	uint16_t _second;
};
#endif