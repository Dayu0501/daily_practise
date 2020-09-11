#include "DateTime.h"
#include <stdio.h>
DateTime::DateTime(std::time_t seconds) :_seconds(seconds)
{
	if (_seconds == 0)
	{
		std::time(&_seconds);
	}
}
DateTime::DateTime(struct std::tm time_tm)
{
	_seconds = std::mktime(&time_tm);
}
DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
{
	struct tm time_tm;
	time_tm.tm_year = year - 1900;
	time_tm.tm_mon = month - 1;
	time_tm.tm_mday = day;
	time_tm.tm_hour = hour;
	time_tm.tm_min = minute;
	time_tm.tm_sec = second;
	time_tm.tm_isdst = 0;
	_seconds = std::mktime(&time_tm);
}
DateTime::DateTime(const std::string& datetimeStr)
{
	if (datetimeStr.length() == 19)
	{
		struct std::tm time_tm;
        sscanf(datetimeStr.c_str(), "%d-%d-%d %d:%d:%d", &time_tm.tm_year, &time_tm.tm_mon, &time_tm.tm_mday, &time_tm.tm_hour, &time_tm.tm_min, &time_tm.tm_sec);
		time_tm.tm_year -= 1900;
		time_tm.tm_mon -= 1;
		_seconds = std::mktime(&time_tm);
	}
    else if(datetimeStr.length() == 10)
    {
        struct tm time_tm;
        sscanf(datetimeStr.c_str(), "%4d-%2d-%2d", &time_tm.tm_year, &time_tm.tm_mon, &time_tm.tm_mday);
        time_tm.tm_year -= 1900;
        time_tm.tm_mon -= 1;
        time_tm.tm_hour = 0;
        time_tm.tm_min = 0;
        time_tm.tm_sec = 0;
        _seconds = std::mktime(&time_tm);
    }
	else if (datetimeStr.length() == 8)
	{
		struct tm time_tm;
		sscanf(datetimeStr.c_str(), "%4d%2d%2d", &time_tm.tm_year, &time_tm.tm_mon, &time_tm.tm_mday);
		time_tm.tm_year -= 1900;
		time_tm.tm_mon -= 1;
		time_tm.tm_hour = 0;
		time_tm.tm_min = 0;
		time_tm.tm_sec = 0;
		_seconds = std::mktime(&time_tm);
	}
	else
	{
		_seconds = 0;
	}
}

int DateTime::sec()
{
	return GetTm().tm_sec;
}
int DateTime::minu()
{
	return GetTm().tm_min;
}
int DateTime::hour()
{
	return GetTm().tm_hour;
}

int DateTime::mday()
{
	return GetTm().tm_mday;
}

int DateTime::mon()
{
	return GetTm().tm_mon + 1;
}

int DateTime::year()
{
	return GetTm().tm_year + 1900;
}

int DateTime::wday()
{
	return GetTm().tm_wday;
}

int DateTime::yday()
{
	return GetTm().tm_yday;
}

bool DateTime::isLeap(uint16_t year)
{
    //if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
    if (year % 4 == 0)
        return true;

	return false;
}
uint16_t DateTime::lastDayOfMonth(uint16_t year, uint16_t month)
{
	if (month == 0 || month > 12)return 0;
	short leep_year[2][12] = { { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };
	return leep_year[isLeap(year)][month - 1];
}
uint16_t DateTime::lastDayOfMonth()
{
    return lastDayOfMonth((uint16_t)year(), (uint16_t)mon());
}
DateTime DateTime::operator+(const Year& year)
{
    (void)year;
	return operator+(Month(12));
}
DateTime DateTime::operator+(const Month& month)
{
	struct std::tm time_tm = GetTm();
	time_tm.tm_year += (time_tm.tm_mon + month._month) / 12;
	time_tm.tm_mon = (time_tm.tm_mon + month._month) % 12;

	uint16_t last_day = lastDayOfMonth(time_tm.tm_year + 1900, time_tm.tm_mon + 1);
	if (time_tm.tm_mday > last_day)time_tm.tm_mday = last_day;
	return DateTime(mktime(&time_tm));
}
DateTime DateTime::operator+(const Day& day)
{
	return DateTime(_seconds + 24 * 60 * 60 * day._day);
}
DateTime DateTime::operator+(const Hour& hour)
{
	return DateTime(_seconds + 60 * 60 * hour._hour);
}
DateTime DateTime::operator+(const Minute& minute)
{
	return DateTime(_seconds + 60 * minute._minute);
}
DateTime DateTime::operator+(const Second& second)
{
	return DateTime(_seconds + second._second);
}
DateTime DateTime::operator-(const Year& year)
{
    (void)year;
	return operator-(Month(12));
}
DateTime DateTime::operator-(const Month& month)
{
	struct std::tm time_tm = GetTm();
	if (month._month <= time_tm.tm_mon)time_tm.tm_mon -= month._month;
	else
	{
		time_tm.tm_year -= ((month._month - time_tm.tm_mon) / 12 + 1);
		time_tm.tm_mon = 12 - (month._month - time_tm.tm_mon) % 12;
	}
	uint16_t last_day = lastDayOfMonth(time_tm.tm_year + 1900, time_tm.tm_mon + 1);
	if (time_tm.tm_mday > last_day)time_tm.tm_mday = last_day;
	return DateTime(mktime(&time_tm));
}
DateTime DateTime::operator-(const Day& day)
{
	return DateTime(_seconds - 24 * 60 * 60 * day._day);
}
DateTime DateTime::operator-(const Hour& hour)
{
	return DateTime(_seconds - 60 * 60 * hour._hour);
}
DateTime DateTime::operator-(const Minute& minute)
{
	return DateTime(_seconds - 60 * minute._minute);
}
DateTime DateTime::operator-(const Second& second)
{
	return DateTime(_seconds - second._second);
}

bool DateTime::operator>(const DateTime& rv)
{
	return _seconds > rv._seconds;
}
bool DateTime::operator==(const DateTime& rv)
{
	return _seconds == rv._seconds;
}
bool DateTime::operator<(const DateTime& rv)
{
	return _seconds < rv._seconds;
}
bool DateTime::operator>=(const DateTime& rv)
{
	return _seconds >= rv._seconds;
}
bool DateTime::operator<=(const DateTime& rv)
{
	return _seconds <= rv._seconds;
}
bool DateTime::operator!=(const DateTime& rv)
{
	return _seconds != rv._seconds;
}
std::string DateTime::ToDateString()
{
	char buffer[40] = { 0 };
	struct std::tm* time_tm;
	time_tm = std::localtime(&_seconds);
	sprintf(buffer,"%04d-%02d-%02d",time_tm->tm_year+1900, time_tm->tm_mon+1, time_tm->tm_mday);
	return std::string(buffer);
}
std::string DateTime::ToDateTimeString()
{
	char buffer[40] = { 0 };
	struct std::tm* time_tm;
	time_tm = std::localtime(&_seconds);
	sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", time_tm->tm_year+1900, time_tm->tm_mon+1, time_tm->tm_mday, time_tm->tm_hour, time_tm->tm_min, time_tm->tm_sec);
	return std::string(buffer);
}
struct tm DateTime::GetTm()
{
	struct std::tm* time_tm;
	time_tm = std::localtime(&_seconds);
	return *time_tm;
}
time_t DateTime::GetTotalSeconds()
{
	return _seconds;
}
