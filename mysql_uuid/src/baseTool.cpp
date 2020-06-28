#include "baseTool.h"
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <vector>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#include <algorithm>
#include <regex>

#include <uuid.h>

class cheBiaoItem {
public:
    std::string src;
    std::string dest;
};

int baseTool::str2Int(std::string str)
{
    if(str.empty())
    {
        return 0;
    }

    unsigned int strSize = str.size();
    const char *pStr = str.c_str();
    for(unsigned int i = 0; i < strSize; i++)
    {
        if(pStr[i] < 48 && pStr[i] > 57)
        {
            if(pStr[i] != '-')
            {
                return 0;
            }
        }
    }

    return stoi(str);
}

int CreatDir(char *pszDir)
{
    int i = 0;
    int iRet;
    int iLen = strlen(pszDir);
    if (pszDir[iLen - 1] != '\\' && pszDir[iLen - 1] != '/')
    {
        pszDir[iLen] = '/';
        pszDir[iLen + 1] = '\0';
    }
    for (i = 0; i <= iLen; i++)
    {
        if ((pszDir[i] == '\\' || pszDir[i] == '/')&&i!=0)
        {
            pszDir[i] = '\0';
            iRet = access(pszDir, 0);
            if (iRet != 0)
            {
                iRet = mkdir(pszDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                if (iRet != 0)
                {
                    return -1;
                }
            }
            //支持linux,将所有\换成/
            pszDir[i] = '/';
        }
    }
    return 0;
}

int baseTool::CheckDir(std::string Path)
{

    if (access(Path.c_str(), 0) != 0)
    {
        char c_Path[2048] = { 0 };
        sprintf(c_Path,"%s", Path.c_str());
        printf("creat path:%s\n",Path.c_str());
        CreatDir(c_Path);
    }else {
         printf("is path:%s\n",Path.c_str());
    }
    return 1;
}

std::string baseTool::newGuid()
{
    char uuid_str[37];
    uuid_t uuid;

    uuid_clear(uuid);
    uuid_generate_time_safe(uuid);

    uuid_unparse(uuid, uuid_str);

    memcpy(uuid_str + 8, uuid_str + 9, 4);
    memcpy(uuid_str + 12, uuid_str + 14, 4);
    memcpy(uuid_str + 16, uuid_str + 19, 4);
    memcpy(uuid_str + 20, uuid_str + 24, 13);

    return uuid_str;
}

static unsigned short const wCRC16Table[256] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040};

void baseTool::Crc16(const uint8_t* pDataIn, int iLenIn, uint16_t* pCRCOut)
{
    uint16_t wResult = 0;
    uint16_t wTableNo = 0;
    int i = 0;
    for( i = 0; i < iLenIn; i++)
    {
        wTableNo = ((wResult & 0xff) ^ (pDataIn[i] & 0xff));
        wResult = ((wResult >> 8) & 0xff) ^ wCRC16Table[wTableNo];
    }

    *pCRCOut = wResult;
}

std::string baseTool::Crc16String(const uint8_t* pDataIn, int iLenIn)
{
    uint16_t wResult = 0;
    uint16_t wTableNo = 0;
    int i = 0;
    for( i = 0; i < iLenIn; i++)
    {
        wTableNo = ((wResult & 0xff) ^ (pDataIn[i] & 0xff));
        wResult = ((wResult >> 8) & 0xff) ^ wCRC16Table[wTableNo];
    }

    return std::to_string(wResult);
}

std::string baseTool::formatingDate(std::string date,unsigned int index)
{
    if (date == "无数据") {
        return std::string("");
    }

    if (date.length() < 8) {
        return std::string("");
    }

    unsigned int count = 0;
    char tmp1[16] = { 0 };
    for (char i : date) {
        if ((i >= '0') && (i <= '9')) {

            tmp1[count] = i;
            count++;
            if( index == 0 && count == 8)
            {
                break;
            }
            if( index == 1 && count == 15)
            {
                break;
            }
            else if(index == 1 && count == 8)
            {
                tmp1[count] = '_';
                count++;
            }
        }
    }

    if (count == 8 || count == 15) {
        return std::string(tmp1);
    } else {
        return std::string("");
    }
}


bool baseTool::checkHaopaiIsXinNenYuan(string str_haopai)
{
    /*
     * 51   大型新能源汽车
       52   小型新能源汽车
    */
    bool flag = false ;
    if( str_haopai == "51"  || str_haopai == "52" ){
        flag = true ;
    }
    return flag ;
}
bool baseTool::checkRlzlIsXinNengYuan(string ranliao)
{
    /*
     A		汽油
     B		柴油
     C		电（以电能驱动的汽车）
     D		混合油
     E		天然气
     F		液化石油气
     L		甲醇
     M		乙醇
     N		太阳能
     O		混合动力
     Y		无（仅限全挂车等无动力的）
     Z		其他
    */
   if (ranliao.length() != 1  ){
        std::cerr<<"燃料类型:"<<ranliao<<"长度错误！"<<endl;
        return false ;
    }
    char c_ranliao = ranliao[0];
    bool result = false ;
    switch (c_ranliao) {
    case 'C':
    case 'E':
    case 'L':
    case 'M':
    case 'N':
    {
        result = true ;
        break;
    }
    case 'A':
    case 'B':
    case 'D':
    case 'F':
    case 'O':
    case 'Y':
    case 'Z':
    {
        result = true ;
        break;
    }
    default:
    {
        std::cerr<<"燃料类型: "<<ranliao<< " 未知！"<<endl;
        break;
    }
    }
    return result ;

}


std::string baseTool::getDangTianRiQi()
{
    std::string nowTime;
    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);
    char tmpArray[64] = { 0 };
    sprintf(tmpArray, "%d-%02d-%02d", st->tm_year + 1900, st->tm_mon + 1, st->tm_mday);

    nowTime = tmpArray;

    return nowTime;
}

std::string baseTool::getDangTianRiQi(int time_count)
{
    time_t timeinfo = time(nullptr);

    timeinfo += (time_count*86400);

    tm* t_tm = localtime(&timeinfo);

    char current_time[256];
    sprintf(current_time,"%d-%02d-%02d",t_tm->tm_year+1900,t_tm->tm_mon+1,t_tm->tm_mday);

    return  static_cast<std::string>(current_time);
}

std::string baseTool::getCurTime()
{
    std::string nowTime;
    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);
    char tmpArray[64] = { 0 };
    sprintf(tmpArray, "%04d-%02d-%02d %02d:%02d:%02d", st->tm_year+1900,st->tm_mon + 1, st->tm_mday, st->tm_hour, st->tm_min, st->tm_sec);

    nowTime = tmpArray;

    return nowTime;
}

bool baseTool::isTenYears(std::string cuCiDengJiRiQi)
{
    std::string djrq = baseTool::formatingDate(cuCiDengJiRiQi);
    if (djrq.empty()) {	/* 未能获取“初次登记日期” */
        return false;
    }
    printf("cuCiDengJiRiQi:%s\n",cuCiDengJiRiQi.c_str());
    int djrq_year = std::stoi(djrq.substr(0, 4));
    int djrq_month = std::stoi(djrq.substr(4, 2));
    int djrq_day = std::stoi(djrq.substr(6, 2));

    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);

    /* 先判断年，年相同的情况下，判断月；月相同的情况下，判断日 */
    if ((st->tm_year + 1900 - djrq_year) > 10) {
        return true;
    } else if ((st->tm_mon + 1 - djrq_year) < 10) {
        return false;
    } else if ((st->tm_year + 1900 - djrq_year) == 10) {
        if ((st->tm_mon + 1- djrq_month) > 0) {
            return true;
        } else if ((st->tm_mon + 1- djrq_month) < 0) {
            return false;
        } else if ((st->tm_mon + 1 - djrq_month) == 0) {
            if ((st->tm_mday - djrq_day) > 0) {
                return true;
            } else if ((st->tm_mday- djrq_day) < 0) {
                return false;
            } else if ((st->tm_mday - djrq_day) == 0) {
                return true;	/* 当天刚好10年也算10年以上车型 */
            }
        }
    }
    return false;
}

//针对2020-04-10 这样的日期
bool baseTool::checkDateIsExpired(std::string date, std::string startDate, std::string endDate)
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

int baseTool::isMobileNumber(std::string number)
{
    if (number.length() == 0) {
        return -1;
    }

    if (number.length() == 8) {
        return 1;   /* 8位直接按固定电话处理，不做其他判定 */
    }

    if (number.length() != 11) {
        return 0;
    }

    for (unsigned int i = 0; i < number.length(); i++) {
        if ((number[i] < '0') || (number[i] > '9')) {
            return 0;
        }
    }

    /*
        以下手机号段取自百度百科“手机号码”（更新时间：2017-09-13）
    */
    std::vector<std::string> YiDong = { "134", "135", "136", "137", "138", "139", "147", "150",
                                        "151", "152", "157", "158", "159", "178", "182", "183", "184", "187", "188", "198" };
    std::vector<std::string> LianTong = { "130", "131", "132", "155", "156", "145", "175", "176", "185", "186", "166" };
    std::vector<std::string> DianXin = { "133", "149", "153", "173", "177", "180", "181", "189", "199" };

    unsigned int i;
    for (i = 0; i < YiDong.size(); i++) {
        if (number.find(YiDong[i]) != std::string::npos) {
            break;
        }
    }

    if (i < YiDong.size()) {
        return 1;
    }

    for (i = 0; i < LianTong.size(); i++) {
        if (number.find(LianTong[i]) != std::string::npos) {
            break;
        }
    }

    if (i < LianTong.size()) {
        return 1;
    }

    for (i = 0; i < DianXin.size(); i++) {
        if (number.find(DianXin[i]) != std::string::npos) {
            break;
        }
    }

    if (i < DianXin.size()) {
        return 1;
    }

    return 0;
}

bool baseTool::compareDate(std::string kssj, std::string PictureDate)
{
    if (kssj == "无数据") {
        return true;
    }

    if ((kssj.length() < 8) || (PictureDate.length() < 8)) {
        return true;
    }

    /* 取出"开始时间"有效日期字段 */
    unsigned int count = 0;
    char tmp1[8] = { 0 };
    for (unsigned int i = 0; i < kssj.length(); i++) {
        if ((kssj[i] >= '0') && (kssj[i] <= '9')) {
            tmp1[count] = kssj[i];
            count++;

            if (count == 8) {
                break;
            }
        }
    }

    /* 未能获取完整日期信息 */
    if (count != 8) {
        return true;
    }

    /* 取出"照片日期"有效日期字段 */
    count = 0;
    char tmp2[8] = { 0 };
    for (unsigned int i = 0; i < PictureDate.length(); i++) {
        if ((PictureDate[i] >= '0') && (PictureDate[i] <= '9')) {
            tmp2[count] = PictureDate[i];
            count++;

            if (count == 8) {
                break;
            }
        }
    }

    /* 未能获取完整日期信息 */
    if (count != 8) {
        return true;
    }

    for (unsigned int i = 0; i < 8; i++) {
        if (tmp1[i] != tmp2[i]) {
            return false;
        }
    }

    return true;
}

std::string baseTool::formatFileNameLunTai(std::string name)
{
    std::string name_buf = name;
    try {
        for (unsigned int i = 0; i < name.size(); i++) {
            if (name_buf[i] == ',' || name_buf[i] == ' ' || name_buf[i] == ';') {
                name_buf.erase(i);
                break;
            }
        }
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return "";
    }

    return name_buf;
}


bool baseTool::checkDateChange(int &day)
{
    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);

    if (st->tm_mday == day)//[1-31]
        return false;
    else
    {
        day = st->tm_mday;
        return true;
    }
}

std::string baseTool::getNowDate()
{
    time_t t;
    char buf[64];

    /* 获取时间 */
    time(&t);
    strftime(buf, sizeof(buf), "%F %T", localtime(&t));
    return buf;
}

char _key[10] = {5,8,6,1,8,6,3,4,2};
std::string baseTool::setPassWord(std::string passWord)
{
    char pwd[1024] = {0};
    char outPwd[1024] = {0};

    sprintf(pwd,"%s",passWord.c_str());
    unsigned int pwdLen = strlen(pwd);

    for (unsigned int i = 0; i < pwdLen; i++) {
        char subKey = _key[i%10];

        if(128 - pwd[i] > subKey)
        {
            outPwd[i] = pwd[i] + subKey;
        }
        else
        {
            outPwd[i] = subKey;
        }
    }
    return outPwd;
}

std::string baseTool::getDBPassWord(std::string passWord)
{
    char pwd[1024] = {0};
    char outPwd[1024] = {0};

    sprintf(pwd,"%s",passWord.c_str());
    unsigned int pwdLen = strlen(pwd);

    for (unsigned int i = 0; i < pwdLen; i++) {
        char subKey = _key[i%10];

        if(subKey + pwd[i] <= 128)
        {
            outPwd[i] = pwd[i] - subKey;
        }
        else
        {
            outPwd[i] = pwd[i];
        }
    }
    return outPwd;
}

std::string baseTool::getDangTianShiJian()
{
    std::string nowTime;
    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);
    char tmpArray[64] = { 0 };
    sprintf(tmpArray, "%d%02d%02d%02d%02d%02d", st->tm_year + 1900, st->tm_mon + 1, st->tm_mday,st->tm_hour,st->tm_min,st->tm_sec);

    nowTime = tmpArray;

    return nowTime;
}

//void baseTool::saveConfigByJson(std::string fileName,Json::Value root)
//{
//    std::ofstream ofs;
//    ofs.open(fileName);
//    ofs << root.toStyledString();
//    ofs.close();
//}

int baseTool::copyFile(std::string src, std::string des)
{
    printf("copyFile %s >> %s   ",src.c_str(),des.c_str());

    int nRet = 0;
    FILE* pSrc = NULL, *pDes = NULL;
    pSrc = fopen(src.c_str(), "r");
    pDes = fopen(des.c_str(), "w+");


    if (pSrc && pDes)
    {
        int nLen = 0;
        char szBuf[1024] = {0};
        while((nLen = fread(szBuf, 1, sizeof szBuf, pSrc)) > 0)
        {
            fwrite(szBuf, 1, nLen, pDes);
        }
        printf("\033[32m OK \033[0m\n");
    }
    else
    {
        nRet = -1;
        printf("\033[31m ERR\033[0m\n");
    }


    if (pSrc)
        fclose(pSrc), pSrc = NULL;

    if (pDes)
        fclose(pDes), pDes = NULL;

    return nRet;
}

int baseTool::copyFolder(std::string src, std::string des)
{
    struct dirent* ent = NULL;
    DIR *pDir;
    pDir=opendir(src.c_str());
    while (NULL != (ent=readdir(pDir)))
    {
        if( ent->d_name[0]!='.')
        {
            std::string fileName = ent->d_name;
            std::string srcPath = src+"/"+fileName;
            std::string desPath = des+"/"+fileName;
            if(ent->d_type == 4)
            {
                baseTool::CheckDir(desPath);
                baseTool::copyFolder(srcPath, desPath);
            }else if(ent->d_type == 8){
                baseTool::copyFile(srcPath, desPath);
            }else {
                printf("error type:%d name:%s \n",ent->d_type,ent->d_name);
            }
        }
    }
    closedir(pDir);
    return 1;
}

bool baseTool::isFolder(std::string src)
{
    bool isFolder = false;
    DIR *pDir = opendir(src.c_str());
    if(pDir!=NULL)
    {
        isFolder = true;
    }
    closedir(pDir);

    return isFolder;
}

std::string baseTool::getLocalIp()
{
    int                 sockfd;
    struct sockaddr_in  sin;
    struct ifreq        ifr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket error");
        exit(1);
    }
    strncpy(ifr.ifr_name, "enp3s0", IFNAMSIZ);      //Interface name

    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == 0) {    //SIOCGIFADDR 获取interface address
        memcpy(&sin, &ifr.ifr_addr, sizeof(ifr.ifr_addr));
        return inet_ntoa(sin.sin_addr);
    }
    return "0.0.0.0";
}

void baseTool::split(const char* token, std::string &str, std::vector<std::string> &splitVector)
{
    std::regex reg(token);
    std::sregex_token_iterator begin(str.begin(), str.end(), reg ,-1), end;
    std::copy(begin, end, std::back_inserter(splitVector));
}

void baseTool::getFileList(std::string dirName, std::vector<std::string> &vec)
{
    struct dirent * filename;
    DIR * pDir;
    pDir = opendir(dirName.c_str());
    while( ( filename = readdir(pDir) ) != NULL )
    {
        if( strcmp( filename->d_name , "." ) == 0 || strcmp( filename->d_name , "..") == 0)
            continue;

        char wholePath[128] = {0};
        sprintf(wholePath, "%s/%s", dirName.c_str(), filename->d_name);
        printf("wholePath：%s\n", wholePath);

        std::string filePath = wholePath;
        vec.push_back(filePath);
    }

    closedir(pDir);
}
