#ifndef _C_SESSION_H
#define _C_SESSION_H
#include "_c_dbTask.h"
#include "_c_algTask.h"
#include "_c_runTime.h"
#include "alg/redis.h"
typedef enum {
    SESS_DEFAULT  ,//默认的 车检查验业务
    SESS_3TH , //第三方会话
}_e_session_type;

class _c_session:public _c_dbTask{
public:
    std::vector<_c_algTask *> algTaskVector; //存放的是一辆车的所有算法任务，每一个任务就是一张图片
    std::vector<objectMember *> paramVector; //存的是某一类型算法需要处理的参数项,参数的value来自从车管所的每一辆车的信息。
    std::vector<_c_object *> *pWangLuoJieKouReturnVector;

    _c_runTime *pRunTime;
    std::string sessionResult;
    std::string sessionReason;
    RedisChannelType redisChannel = redisRequstChan;
    std::string greenChannel;

    virtual ~_c_session(){} //用于释放内存（必须）
    virtual bool isEndWork();
    virtual bool processWangLuoJieKou();
    virtual bool wangLuoJieKouResultEdit(void *pAlgVector);
    virtual bool loadAllParam();
    virtual bool loadAlgTask();
    virtual _e_session_type getSessionType(){ return SESS_DEFAULT;}
	virtual bool subLoadAlgTask();
    virtual void setSessionResult(std::string result,std::string reason){sessionResult = result;sessionReason=reason;}
    bool getPhotoByCode(std::string code, std::string *pUrl, std::string *pLoaclPath);
    Json::Value getSessionJson();


    void setSessionInSystemTime();

    void setPushSessionQueueTime();
    void setGetSessionQueueTime();

    void setPushAlgSessionQueueTime();
    void setGetAlgSessionQueueTime();

    void setPushReponseQueueTime();
    void setGetReponseQueueTime();

    void setPushDbTaskQueueTime();

};
#endif // _C_SESSION_H
