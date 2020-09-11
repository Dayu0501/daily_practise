#include "_c_algTaskCenter_NanChong.h"
#include "_c_algClass_0199_NanChong.h"
#include "_c_algClass_0186_NanChong.h"

_c_algTaskCenter_NanChong::_c_algTaskCenter_NanChong(CityType cityType, PREDIS_PARAM redisParam)
        : _c_algTaskCenter(cityType, redisParam) {
    printf("I am Nanchong : %s", __PRETTY_FUNCTION__ );
}

bool _c_algTaskCenter_NanChong::subBeforAlgCheck(_c_session *pSession, std::string &sessionReason) {
    UNUSED(pSession);
    UNUSED(sessionReason);

    return true;
}

_c_algBaseClass *_c_algTaskCenter_NanChong::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type) {
    printf("_c_algTaskCenter_NanChong subClassLoadAlgBaseClassByPicType algName %s, %d \n", algName.c_str(), type);

    _c_algBaseClass *pReturn{nullptr};
    switch (type) {
        case eH0199:
            pReturn = new _c_algClass_0199_NanChong();

            break;
	    case eH0186:
		    pReturn = new _c_algClass_0186_NanChong();

		    break;
        default:
            //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
            return new _c_algBaseClass();
    }

    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();
    return pReturn;
}

E_ZZJG _c_algTaskCenter_NanChong::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string &sessionReason) {
    UNUSED(baseResult);
    UNUSED(sessionReason);

    return SOFT_PASS;
}

void _c_algTaskCenter_NanChong::changeAlgVector() {
    printf("%s\n", __PRETTY_FUNCTION__);

    algItem item0199{"0199", true, "车架号远景30cm左右", eH0199, true, false, true, false, "无", NOPICEXAMPLE};
	algItem item0186{"0186", true, "检验员和车辆外观", eH0186, true, false, true, false, "无", NOPICEXAMPLE};

    addAlgVectorByItem(item0199);
	addAlgVectorByItem(item0186);
}