#ifndef _C_ALGTASKCENTER_XUZHOU_H
#define _C_ALGTASKCENTER_XUZHOU_H
#include "alg/_c_algTaskCenter.h"
#include "base/baseInc.h"
#include "alg/algTaskBase.h"
#include "base/dataCenter.h"
#include "base/_c_algTask.h"
#include "alg/algClass/_c_algBaseClass.h"
#include "alg/_c_algTaskResponse.h"
#include "alg/redis.h"

#define RESULT_DESC_INFO_90 "超前90天审核"
#define RESULT_DESC_INFO_30 "该车辆“检验结束时间”距当天已超过30天"

class _c_algTaskCenter_XuZhou : public _c_algTaskCenter
{
public:
    _c_algTaskCenter_XuZhou(CityType cityType, PREDIS_PARAM redisParam);

protected:
    bool subBeforAlgCheck(_c_session *pSession, std::string& sessionReason) override;
    E_ZZJG subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason) override;
    bool beforeSetResult(_c_session *pSession, std::string& sessionReason) override;
    _c_algBaseClass* subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type) override ;
    void changeAlgVector() override ;
};

#endif