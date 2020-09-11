#ifndef _C_ALGTASKCENTER_DALI_H
#define _C_ALGTASKCENTER_DALI_H
#include "alg/_c_algTaskCenter.h"
#include "base/baseInc.h"
#include "alg/algTaskBase.h"
#include "base/dataCenter.h"
#include "base/_c_algTask.h"
#include "alg/algClass/_c_algBaseClass.h"
#include "alg/_c_algTaskResponse.h"
#include "alg/redis.h"

class  _c_algTaskCenter_DaLi:public _c_algTaskCenter
{
public:
    _c_algTaskCenter_DaLi(CityType cityType,PREDIS_PARAM redisParam);

protected:
#if 0    
    std::vector<std::string> vec_must_picTypes = {"0111","0112","0113","0157","0201","0261","0202","0204","0209","0210","0321","0322","0348","0352"};
    std::vector<std::string> vec_must_picTypes_tenYears = {"0323","0342","0344","0351"};                                    
    virtual E_ZZJG subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason);
 
    void getLackPicTypes(std::vector<std::string>& vec_must_picTypes,std::vector<_c_algTask *>* algTaskVector,
        std::vector<std::string>& vec_lack_pics);
#endif

    std::string getAlgCodeNameByCode(std::string& code);
    virtual bool checkComplete(bool isTenYears, _c_session *pSession, std::string& sessionReason);
};

#endif
