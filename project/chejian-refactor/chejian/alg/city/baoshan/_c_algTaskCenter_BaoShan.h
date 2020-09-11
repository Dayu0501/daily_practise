#ifndef _C_ALGTASKCENTER_BAOSHAN_H
#define _C_ALGTASKCENTER_BAOSHAN_H
#include "alg/_c_algTaskCenter.h"
#include "base/baseInc.h"
#include "alg/algTaskBase.h"
#include "base/dataCenter.h"
#include "base/_c_algTask.h"
#include "alg/algClass/_c_algBaseClass.h"
#include "alg/_c_algTaskResponse.h"
#include "alg/redis.h"

class  _c_algTaskCenter_BaoShan:public _c_algTaskCenter
{
public:
    _c_algTaskCenter_BaoShan(CityType cityType,PREDIS_PARAM redisParam);

protected:

    virtual void changeAlgVector();
    virtual _c_algBaseClass* subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type);
};

#endif