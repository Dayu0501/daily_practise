#include "_c_algTaskCenter_EErDuoSi.h"
#include "_c_algClass_0205_EErDuoSi.h"


_c_algTaskCenter_EErDuoSi::_c_algTaskCenter_EErDuoSi(CityType cityType,PREDIS_PARAM redisParam)
    :_c_algTaskCenter(cityType, redisParam) {

}

bool _c_algTaskCenter_EErDuoSi::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason) {
    UNUSED(pSession);
    UNUSED(sessionReason);

    return true;
}

_c_algBaseClass* _c_algTaskCenter_EErDuoSi::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    printf("_c_algTaskCenter_EErDuoSi subClassLoadAlgBaseClassByPicType algName %s, %d \n", algName.c_str(), type);
    
     _c_algBaseClass* pReturn;
     switch (type) {
        case e0205:
            pReturn = new _c_algClass_0205_EErDuoSi();

            break;
        default:
            //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
            return new _c_algBaseClass();
    }

    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();
    return pReturn;
}

E_ZZJG _c_algTaskCenter_EErDuoSi::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason) {
    UNUSED(baseResult);
    UNUSED(pSession);
    UNUSED(sessionReason);

    return SOFT_PASS;
}

void _c_algTaskCenter_EErDuoSi::changeAlgVector() {
    printf("%s\n", __PRETTY_FUNCTION__);

    algItem item0205{"0205", true, "查验记录表-照片", e0205, true, false, true, false, "无", NOPICEXAMPLE};

    changeAlgVectorByType(&item0205);

}