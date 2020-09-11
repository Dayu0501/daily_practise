#include "_c_algTaskCenter_ZhuHai.h"
#include "_c_algClass_0202_ZhuHai.h"

_c_algTaskCenter_ZhuHai::_c_algTaskCenter_ZhuHai(CityType cityType,PREDIS_PARAM redisParam)
    :_c_algTaskCenter(cityType,redisParam) {

}

bool _c_algTaskCenter_ZhuHai::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason) {
    UNUSED(pSession);
    UNUSED(sessionReason);

    return true;
}

E_ZZJG _c_algTaskCenter_ZhuHai::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason) {
    UNUSED(baseResult);
    UNUSED(sessionReason);

    std::string fzjg = baseTool::getObjectItemValueByName(&pSession->paramVector, "faZhengJiGuan");
    if (fzjg.size() >=3 && "粤" == fzjg.substr(0, 3))    return SOFT_PASS;

    sessionReason = "非粤车辆";

    return SOFT_ERR;
}

_c_algBaseClass* _c_algTaskCenter_ZhuHai::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    printf("_c_algTaskCenter_FuZhou subClassLoadAlgBaseClassByPicType \n");

    _c_algBaseClass* pReturn;
    switch (type) {
        case e0202:
            pReturn = new _c_algClass_0202_ZhuHai();

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

void _c_algTaskCenter_ZhuHai::changeAlgVector() {
    algItem item0202 = {"0202", true, "牌证申请表-照片", e0202, true, false,  true, false, "无", NOPICEXAMPLE };
    changeAlgVectorByType(&item0202);
}

bool _c_algTaskCenter_ZhuHai::beforeSetResult(_c_session *pSession, std::string& sessionReason) {
    //pSession->setSessionResult(std::to_string(SOFT_ERR), sessionReason);

    return true;
}