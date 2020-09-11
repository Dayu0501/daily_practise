#ifndef _C_ALGTASKCENTER_BENGBU_H
#define _C_ALGTASKCENTER_BENGBU_H
#include "alg/_c_algTaskCenter.h"
#include "base/baseInc.h"
#include "alg/algTaskBase.h"
#include "base/dataCenter.h"
#include "base/_c_algTask.h"
#include "alg/algClass/_c_algBaseClass.h"
#include "alg/_c_algTaskResponse.h"
#include "alg/redis.h"

class  _c_algTaskCenter_BengBu:public _c_algTaskCenter
{
public:
    _c_algTaskCenter_BengBu(CityType cityType,PREDIS_PARAM redisParam);

protected:
    virtual void changeAlgVector() override;
    virtual _c_algBaseClass* subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type) override;
    virtual E_ZZJG subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason) override;

private:
    void setJiaoQiangXian(_c_session *pSession);
    void resetAlgTaskResult(_c_algTask *algTask);

};

#endif
