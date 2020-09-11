#ifndef _C_ALGTASKCENTER_ZHUHAI_H
#define _C_ALGTASKCENTER_ZHUHAI_H

#include "alg/_c_algTaskCenter.h"
#include "base/baseInc.h"
#include "alg/algTaskBase.h"
#include "base/dataCenter.h"
#include "base/_c_algTask.h"
#include "alg/algClass/_c_algBaseClass.h"
#include "alg/_c_algTaskResponse.h"
#include "alg/redis.h"

class  _c_algTaskCenter_ZhuHai : public _c_algTaskCenter
{
public:
    _c_algTaskCenter_ZhuHai(CityType cityType,PREDIS_PARAM redisParam);
    bool beforeSetResult(_c_session *pSession, std::string& sessionReason) override;
    
protected:
    bool subBeforAlgCheck(_c_session *pSession, std::string& sessionReason) override;
    E_ZZJG subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason) override;
    void changeAlgVector() override;
    _c_algBaseClass* subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type) override;
};

#endif
