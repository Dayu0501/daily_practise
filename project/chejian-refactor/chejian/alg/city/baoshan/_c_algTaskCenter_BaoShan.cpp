#include "_c_algTaskCenter_BaoShan.h"
#include "_c_algClass_0206_BaoShan.h"
#include "db/dbquery/db_vehicleinfo.h"
#include "sessionService/chejian/tianJin/_c_fuJian.h"

_c_algTaskCenter_BaoShan::_c_algTaskCenter_BaoShan(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{
    
}

void _c_algTaskCenter_BaoShan::changeAlgVector()
{
     printf("void _c_algTaskCenter_BaoShan::changeAlgVector()\n");
    algItem item0206 = {"0206", false, "完税证明-照片", e0206, false, false, true, false, "无", NOPICEXAMPLE}; //0206开启使用子类逻辑开关

    changeAlgVectorByType(&item0206);
}

_c_algBaseClass* _c_algTaskCenter_BaoShan::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    _c_algBaseClass* pReturn;
    switch (type) {
       case e0206:
            pReturn = new _c_algClass_0206_BaoShan();
            break;
        default:
            //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
            return new _c_algBaseClass();
        break;
    }
    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();
    return pReturn;
}