//
// Created by yulichao on 2020/7/20.
//

#include <cstdio>
#include <memory.h>
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>

using namespace std;

/*
 * desc      : 获得当前时间的时间戳
 * return    : 返回当前时间的时间戳，单位秒
 */
time_t getTimeStamp() {
    std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto tmp=std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();

    return timestamp;
}


/*
 * desc      : 把输入的时间转换成时间戳的形式，时间戳单位为秒
 * time      : 需要转换成时间戳的时间
 * format    : 输入的time格式
 * return    : 返回输入参数的时间戳
 */
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

int main()
{
    //std::string str = "2020-05-20 20:04:00.0";
    std::string str = "09dh:89";
    time_t t = strTime2unix(str, "%d-%d-%d %d:%d:%d");

    std::cout << t << std::endl;
    std::cout << ctime(&t) << std::endl;

    std::cout << "--------------" << std::endl;

    std::cout << getTimeStamp() << std::endl;


    time_t srcStamp = t;
    time_t desStamp = getTimeStamp();

    cout << "desStamp - srcStamp = " << desStamp - srcStamp << endl;

    if ((desStamp - srcStamp) / (24 * 60 * 60) > 90) {
        cout << "not ok " << endl;
    } else {
        cout << "ok" << endl;
    }

    cout << "---------------------------------------" << endl;
    std::string str1{"2020年05月20日 20时04分00秒"};
    cout << strTime2unix(str1, "%d年%d月%d日 %d时%d分%d秒") << endl;


    return 0;
}

