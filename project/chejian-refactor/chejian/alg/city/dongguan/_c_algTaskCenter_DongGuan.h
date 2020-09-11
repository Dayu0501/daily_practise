#ifndef _C_ALGTASKCENTER_DONGGUA_H
#define _C_ALGTASKCENTER_DONGGUA_H
#include "alg/_c_algTaskCenter.h"
#include "base/baseInc.h"
#include "alg/algTaskBase.h"
#include "base/dataCenter.h"
#include "base/_c_algTask.h"
#include "alg/algClass/_c_algBaseClass.h"
#include "alg/_c_algTaskResponse.h"
#include "alg/redis.h"

class  _c_algTaskCenter_DongGuan:public _c_algTaskCenter
{
public:
    _c_algTaskCenter_DongGuan(CityType cityType,PREDIS_PARAM redisParam);

protected:

   // virtual bool subBeforAlgCheck(_c_session *pSession, std::string& sessionReason);
   // virtual E_ZZJG subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason);
    virtual void changeAlgVector();
    virtual _c_algBaseClass* subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type);
    virtual E_ZZJG finalCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason);
};

#endif

