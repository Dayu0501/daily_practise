#include "_c_algTaskCenter_NingBo.h"
#include "_c_algClass_0234_NingBo.h"

_c_algTaskCenter_NingBo::_c_algTaskCenter_NingBo(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{
    
}

bool _c_algTaskCenter_NingBo::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason)
{
    return true;
}

void _c_algTaskCenter_NingBo::changeAlgVector()
{
    printf("void _c_algTaskCenter_NingBo::changeAlgVector()\n");
    algItem item0208 = {"0208", false, "代理人授权书-照片", e0208, false, false, true, false, "无", NOPICEXAMPLE}; //0111开启使用子类逻辑开关

    changeAlgVectorByType(&item0208);
}

_c_algBaseClass* _c_algTaskCenter_NingBo::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    _c_algBaseClass* pReturn;
    switch (type) {
       case e0208:
            pReturn = new _c_algClass_0234_NingBo();
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

E_ZZJG _c_algTaskCenter_NingBo::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
{
    return SOFT_PASS;
}