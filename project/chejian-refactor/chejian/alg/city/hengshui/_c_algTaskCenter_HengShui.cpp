#include "_c_algTaskCenter_HengShui.h"
#include "_c_algClass_0354_HengShui.h"

_c_algTaskCenter_HengShui::_c_algTaskCenter_HengShui(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}

//bool _c_algTaskCenter_HengShui::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason)
//{
//    return true;
//}

////所有针对一辆车检测之后，图片与图片之间关联判定的逻辑就在此实现。
//E_ZZJG _c_algTaskCenter_HengShui::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
//{
//    return SOFT_PASS;
//}

void _c_algTaskCenter_HengShui::changeAlgVector()
{
    algItem item0354 = {"0354", true, "车辆正前方(车牌特写)-照片", e0354, false, false, true, false, "无",NOPICEXAMPLE};
    changeAlgVectorByType(&item0354);
}

_c_algBaseClass* _c_algTaskCenter_HengShui::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
     _c_algBaseClass* pReturn;
     switch (type) {
        case e0354:
            pReturn = new _c_algClass_0354_HengShui();
        default:
            //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
            return new _c_algBaseClass();
        break;
    }
    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();
    return pReturn;
}
