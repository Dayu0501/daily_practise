#ifndef _C_ALGTASKEREPONSE_H
#define _C_ALGTASKEREPONSE_H
#include "base/baseInc.h"
#include "base/_c_object.h"
#include "base/_c_algTask.h"

#define MAX_REPONSE_MEMBER   1000
#define TABLENAMEAPI         "999"
#define TABLENAME            "tableName"
#define JIAOQIANGXIAOAPI     "9"
#define WANSHUIZHENGMING     "27"

class _c_algTask_Reponse : public _c_dbTask{
public:
    std::string algTaskKeyCode;
    std::string algReturn;            //算法逻辑判定结果
    std::string photoDownTime;        //图片下载时间
    std::string algProcTime;          //算法计算时间
    std::string algRunTime;           //算法运行总时长
    std::string processIp;            //算法运行机器IP

    std::string getAlgResultByCodeName(std::string codeName);
    _c_algTask_Reponse(std::string redisStr);
    std::vector<objectMember> *getResultList();

    _c_algTask_Reponse(){
        reponseInit();
    }
    void beforDbWork();

private:
    std::string handleSpecilAlgIdS(Json::Value obj);

    std::string __Reponse[MAX_REPONSE_MEMBER];
    bool setMember(unsigned int index, std::string soapName, std::string codeName, std::string value);

    bool findItem(const std::string & soapName);
    void reponseInit();

    //目前只有0203（保单）与0206（完税证明），出现这种在传完税证明的时候，不一定传那种照片的情况。
    std::map<std::string, std::string> _tableNameAndAlgIdMap {{"税收完税证明", WANSHUIZHENGMING},
															  {"机动车交通事故责任强制保险单", JIAOQIANGXIAOAPI}};
};

#endif // _C_ALGTASKEREPONSE_H
