#ifndef _BASETOOL_H
#define _BASETOOL_H

#include <string>
#include <vector>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

extern const std::string VERSION;

using namespace std;

class baseTool {
public:
    static int str2Int(std::string str);

    static int CheckDir(std::string Path);

    static std::string newGuid();

    static void Crc16(const uint8_t *pDataIn, int iLenIn, uint16_t *pCRCOut);

    static std::string Crc16String(const uint8_t *pDataIn, int iLenIn);

    static std::string formatingDate(std::string date, unsigned int index = 0);

    static bool checkHaopaiIsXinNenYuan(string str_haopai);

    static bool checkRlzlIsXinNengYuan(string ranliao);

    static std::string getDangTianRiQi();

    static std::string getDangTianRiQi(int time_count);

    static bool checkDateIsExpired(std::string date, std::string startDate,
                                   std::string endDate);

    static bool isTenYears(std::string cuCiDengJiRiQi);

    static int isMobileNumber(std::string number);

    static bool compareDate(std::string kssj, std::string PictureDate);

    static std::string formatFileNameLunTai(std::string name);

    static std::string getDestClpp(std::string srcClpp);

    static bool checkDateChange(int &day);

    static std::string getNowDate();

    static std::string setPassWord(std::string passWord);

    static std::string getDBPassWord(std::string passWord);

    static std::string getDangTianShiJian();

    static int copyFile(std::string src, std::string des);

    static int copyFolder(std::string src, std::string des);

    static bool isFolder(std::string src);

    static std::string getCurTime();

    static std::string getLocalIp();

    static void split(const char *token, std::string &str,
                      std::vector<std::string> &splitVector);

    static void getFileList(std::string floderPath,
                            std::vector<std::string> &vec);
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // _BASETOOL_H
