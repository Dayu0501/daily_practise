#include "_c_algTaskCenter_FuYang.h"
#include "_c_algClass_0212_FuYang.h"

_c_algTaskCenter_FuYang::_c_algTaskCenter_FuYang(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}

bool _c_algTaskCenter_FuYang::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason)
{
    UNUSED(pSession);UNUSED(sessionReason);
    return true;
}

//所有针对一辆车检测之后，图片与图片之间关联判定的逻辑就在此实现。
E_ZZJG _c_algTaskCenter_FuYang::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
{
    UNUSED(baseResult);UNUSED(pSession);UNUSED(sessionReason);
    return SOFT_PASS;
}

void _c_algTaskCenter_FuYang::changeAlgVector()
{
    //  printf("void jiangMen_processclass::changeAlgVector()\n");
    // algItem item0321 = {"0321", true, "左灯光工位-照片", e0321, false, false, true, false, "无"};
    // algItem item0158 = {"0158", true, "车辆正后方(车牌特写)-照片", e0158, false, false, true, false, "无"};
    // algItem item0159 = {"0159", true, "车辆正前方(车牌特写)-照片", e0159, false, false, true, false, "无"};

    // changeAlgVectorByType(&item0321);
    // changeAlgVectorByType(&item0158);
    // changeAlgVectorByType(&item0159);

    //printf("void _c_algTaskCenter_FuYang::changeAlgVector()\n");
    // algItem item0212 = {"0212", true, "送检人身份证-照片", e0228, false, false, true, false, "无"};
    // changeAlgVectorByType(&item0212);
    
}

_c_algBaseClass* _c_algTaskCenter_FuYang::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
     _c_algBaseClass* pReturn;
     switch (type) {
        // case e0228:
        //      pReturn = new _c_algClass_0212_FuYang();
        //  break;   
        default:
            //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
            return new _c_algBaseClass();
        break;
    }
    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();
    return pReturn;
}
