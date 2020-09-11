#include "_c_algTaskCenter_QianDongNan.h"
#include "_c_algClass_0213_QianDongNan.h"

_c_algTaskCenter_QianDongNan::_c_algTaskCenter_QianDongNan(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}


//所有针对一辆车检测之后，图片与图片之间关联判定的逻辑就在此实现。
E_ZZJG _c_algTaskCenter_QianDongNan::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
{
    UNUSED(baseResult);UNUSED(pSession);UNUSED(sessionReason);
    return SOFT_PASS;
}

void _c_algTaskCenter_QianDongNan::changeAlgVector()
{
    printf("void _c_algTaskCenter_QianDongNan::changeAlgVector()\n");    
    algItem item0235 =  {"0235", false, "机动车制动检测曲线报告", e0235, false, false, false, false, "无", NOPICEXAMPLE};

    changeAlgVectorByType(&item0235);
}

_c_algBaseClass* _c_algTaskCenter_QianDongNan::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    _c_algBaseClass* pReturn;
    switch (type) {
    case e0235:
            pReturn = new _c_algClass_0213_QianDongNan();
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
