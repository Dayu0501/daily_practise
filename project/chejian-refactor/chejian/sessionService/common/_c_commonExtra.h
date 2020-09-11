#ifndef _C_SESSIONSERVICEEXTRA_H
#define _C_SESSIONSERVICEEXTRA_H
#include <string>
#include <cstring>

typedef struct _PHOTOINFO
{
    std::string algCode;
    std::string result;
    std::string reason;
    std::string photoUrl;
    std::string localPath;
}PHOTOINFO, *PPHOTOINFO;

typedef struct _STARTUPPRARAM
{
    int qsrqOffset;//开始时间
    int zzrqOffset;//结束时间
    int startTime; //工作开始时间
    int endTime; //工作结束时间
    int soapQueryInterval;//soap请求间隔
    std::string soapIp;
    std::string soapPort;
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
}STARTUPPRARAM, *PSTARTUPPRARAM;

inline uint8_t toHex(const uint8_t &x)
{
    return x > 9 ? x - 10 + 'A' : x + '0';
}

inline uint8_t fromHex(const uint8_t &x)
{
    if (isdigit(x)) {
        return x - '0';
    } else if (isupper(x)) {
        return x - 'A' + 10;
    } else {
        return x - 'a' + 10;
    }
}

inline std::string URLDecode(const std::string &sIn)
{
    std::string sOut;
    for (size_t ix = 0; ix < sIn.size(); ix++)
    {
        uint8_t ch = 0;
        if (sIn[ix] == '%')
        {
            ch = (fromHex(sIn[ix + 1]) << 4);
            ch |= fromHex(sIn[ix + 2]);
            ix += 2;
        }
        else if (sIn[ix] == '+')
        {
            ch = ' ';
        }
        else
        {
            ch = sIn[ix];
        }
        sOut += (char)ch;
    }
    return sOut;
}


inline std::string URLEncode(const std::string &sIn)
{
    std::string sOut;
    for (size_t ix = 0; ix < sIn.size(); ix++)
    {
        uint8_t buf[4];
        memset(buf, 0, 4);
        if (isalnum((uint8_t)sIn[ix]))
        {
            buf[0] = sIn[ix];
        }

        //else if ( isspace( (BYTE)sIn[ix] ) ) //貌似把空格编码成%20或者+都可以
        //{
        //    buf[0] = '+';
        //}

        else
        {
            buf[0] = '%';
            buf[1] = toHex((uint8_t)sIn[ix] >> 4);
            buf[2] = toHex((uint8_t)sIn[ix] % 16);
        }
        sOut += (char *)buf;
    }

    return sOut;
}

inline std::string normalizeUriContent(const std::string &sIn)
{
    if (sIn == "无数据")
        return "";

    return URLEncode(sIn);
}
#endif // _C_SESSIONSERVICEEXTRA_H
