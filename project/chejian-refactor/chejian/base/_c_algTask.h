#ifndef _C_ALGTASK_H
#define _C_ALGTASK_H
#include "_c_dbTask.h"
#include "alg/algClass/_c_algBaseClass.h"
#include "base/_c_video.h"

#define RESULTDEF -9

class _c_algTask:public _c_dbTask{
public:
    std::string algCode;
    std::string algName;
    std::string photoUrl; //照片的url
    std::string localPath; //照片从url下载下来到的本地路径
    std::string result;
    std::string reason;
    std::string photoDownTime;//图片下载时间
    std::string algProcTime;//算法计算时间
    std::string algRunTime;//算法运行总时长
    std::string runTime;//任务存活时长
    std::string sendRedisDate;
    std::string readRedisDate;
    std::string processDeviceIp;
    //视频相关
    bool processReponseIsDone = false;
    PVIDEOCHECK_INFO pVideoCheckInfo = NULL;
    VideoProcessState videoProcessState = videoProcessUnInit;

    _c_algBaseClass *pClass = NULL;

    //是用来存放从算法返回来的task，因为有可能是需要多个任务联合判定，所以使用了vector。
    std::vector<_c_algTask *> algTaskVector; 
    virtual ~_c_algTask(){
        freeAlgBaseClass();
    } //用于释放内存（必须）
    bool algTaskInit();
    bool setEndWork();
    bool clearEndWork();
    bool checkIsEndWork();
    bool checkResult();
    bool freeAlgBaseClass();
    unsigned int getInSystemTime();
    bool setAlgTaskResult(int result, std::string reason, bool isVideo = false);
    Json::Value getParamSendJson(unsigned int timeOut, std::string reponseChan, bool isVideo = false);
    bool loadAlgTaskInParam(std::vector<objectMember *> *pVector, std::vector<algItem> *pItemVector, std::vector<_c_algTask *> *pAlgTaskVector, std::vector<_c_object *> *pWangluoJieKouVector);
    bool loadAlgTaskResult(std::string redisRet, std::vector<objectMember> *pVector, bool isVideo = false);
    Json::Value getTaskJson();
private:
    bool __endWork;
    std::chrono::time_point<std::chrono::system_clock> __inTime;
};
#endif // _C_ALGTASK_H
