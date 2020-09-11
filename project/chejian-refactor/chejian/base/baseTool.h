#ifndef _BASETOOL_H
#define _BASETOOL_H
#include "base/baseInc.h"
#include "alg/algTaskBase.h"
#include "_c_algTask.h"
#include "base/_c_video.h"
#include "base/md5/md5.h"

namespace ns_baseTool {
    template<typename T=int>
    std::string number2str(T number,const char *format ="%d"){
        char buf[32]={0};
        sprintf( buf ,format,number) ;
        string  data = buf ;
        return data ;
    }
    template<typename T=int>
    void str2number(const char *str,T* number,const char *format ="%d"){
        sscanf(str,format,number);
    }
}
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

extern const std::string VERSION;

class baseTool{
public:
    static std::string formatingTime(std::string strTime);
    static int strTime2Second(std::string str);
    static int str2Int(std::string str);
    static int CheckDir(std::string Path);
    static std::string newGuid();
    static void Crc16(const uint8_t* pDataIn, int iLenIn, uint16_t* pCRCOut);
    static std::string Crc16String(const uint8_t* pDataIn, int iLenIn);
    static std::string formatingDate(std::string date,unsigned int index = 0);
    static memberItem *getMemberItemByName(std::vector<memberItem> *pMemberList,std::string name);
    static std::string getObjectItemValueByName(std::vector<objectMember *> *paramList, std::string name);
    static std::string getObjectItemValueByName(std::vector<objectMember> *paramList, std::string name);
    static objectMember *getObjectItemByName(std::vector<objectMember> *paramList, std::string name);
    static objectMember *getObjectItemByName(std::vector<objectMember*> *paramList, std::string name);
    static bool checkIsNewCar(std::vector<objectMember *> *paramList);
    static bool checkMemberItemAndSetAllUnOutput(std::vector<memberItem> *pMemberList,memberItem *pMemberItem,bool isMust =false);
    static bool checkCllxIsK3xOrK4x(std::vector<objectMember *> *paramList);
	static bool checkCllxIsMx(std::vector<objectMember *> *paramList);
    static bool checkHaopaiIsXinNenYuan(string str_haopai);
    static bool checkRlzlIsXinNengYuan(string ranliao);
    static std::string getDangTianRiQi();
    static std::string getDangTianRiQi(int time_count);
    static bool convertDateFormat(const std::string& srcDate, std::string& desDate);
	static bool isNum(const std::string& str);
    static bool checkDateIsExpired(std::string date, std::string startDate, std::string endDate);
    static bool isTenYears(std::string cuCiDengJiRiQi);
    static bool isOverSomeYears(std::string cuCiDengJiRiQi,int numYear);
    static void changeCheckAlgBaseParamElementByName(std::vector<memberItem> *pResultMemberList, std::string name, std::string desc, bool output);
    static int isMobileNumber(std::string number);
    static void setAllPass(std::vector<memberItem> *pMemberList);
    static void openMemberItemWriteResultByName(std::vector<memberItem> *pMemberList,std::string name);
    static bool compareDate(std::string kssj, std::string PictureDate);
    static std::string formatFileNameLunTai(std::string name);
    static std::string formatFileName(std::string name) ;
    static std::string formatPhotoFileName(std::string name) ;
    static std::string getDestClpp(std::string srcClpp);
    static bool compareClpp(std::string srcClpp,std::string dstClpp) ;
    static void closeMemberItemWriteResultByName(std::vector<memberItem> *pMemberList,std::string name="");
    static std::string getAlgItemCodeByPicType(PicType type, void *p);
	static std::string getAlgItemCodeByPicType(PicType type, std::vector<algItem> *pAlgItemVector);
    static std::string getAlgItemNameByPicType(PicType type, std::vector<algItem> *pAlgItemVector);
    static _c_algTask *seachPhotoByZpType(std::vector<_c_algTask *> *pAlgTaskVector,std::string zpType);
    static bool photoIsExist(std::vector<_c_algTask *> *pAlgTaskVector,std::string algCode);
    static bool wirteResultByMemberList(std::string algName, _c_algTask *algTask, std::vector<memberItem> *pMemberList);
    static void writeResultByJGAndSM(_c_algTask *algTask, E_JG jg, std::string sm);
    static bool checkDateChange(int &day);
    static std::string getNowDate();
    static std::string setPassWord(std::string passWord);
    static std::string getDBPassWord(std::string passWord);
    static std::string getDangTianShiJian();
    static void saveConfigByJson(std::string fileName,Json::Value root);
    static int copyFile(std::string src, std::string des);
    static int copyFolder(std::string src, std::string des);
    static bool isFolder(std::string src);
    static std::string getCurTime();
    static std::string getCurVersion();
    static std::string getLocalIp();
    static bool isNeedCheckChePaiHao(std::vector<objectMember *> *paramList);
    static void split(const char* token, std::string &str, std::vector<std::string> &splitVector);
    static std::string checkAlgItemLinkIsValid(std::string link, std::vector<algItem> *pAlgItemVector);
    static E_JG checkAlgItemLinkResult(std::string curItemResult, std::string item, std::vector<_c_algTask *> *pAlgTaskVector);
    static void getFileList(std::string floderPath, std::vector<std::string> &vec);
    static void writeResultInExistAlg(std::vector<_c_algTask *> *pAlgTaskVector, E_JG jg, std::string reason, std::string algCode);
    static std::string getWangLuoJieKouReturnInfoBiaoShi(_c_object *obj);
    static bool checkWangLuoJieKouReturnInfoIsValid(_c_object *obj);
    static _c_video *getVideoObject(_c_algTask *pTask);
    static std::string Getfilepath(const char *path, const char *filename);
	//保留最新days 天的目录 <目录以日期格式命名 如:2020-10-10>
	static bool keepRecentSomeDaysDir(const char* path,int val,int days);
    static std::string formatingPath(const char *path) ;
	static std::string getMD5String(const string &str);
    static time_t strTime2unix(const std::string& time, const std::string& format);
    static time_t getTimeStamp();
	static std::string fun_write_new_file(const std::string& dir_path, const std::string& file_name, unsigned char *file_binary, int len);
	static std::string deleteMarks(string des, char x);
	static bool checkLicense(string & result, string & beginDate, string & endDate);
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // _BASETOOL_H
