#include "_c_algTaskCenter_DongGuan.h"
#include "_c_algClass_0111_DongGuan.h"
#include "_c_algClass_0112_DongGuan.h"
#include "_c_algClass_0113_DongGuan.h"

_c_algTaskCenter_DongGuan::_c_algTaskCenter_DongGuan(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}



E_ZZJG _c_algTaskCenter_DongGuan::finalCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
{
    UNUSED(baseResult);
    std::string cuCiDengJiRiQi =  baseTool::getObjectItemValueByName(&pSession->paramVector, "chuCiDengJiRiQi") ;
    if ( baseTool::isOverSomeYears(cuCiDengJiRiQi,15))
    {
        LOG(COMMON,INFO,"需要人工审核！");
        sessionReason = "各检测项已通过,登记日期超过十五年,需要人工审核";
        return SOFT_ERR ;
    }
    return SOFT_PASS;
}

void _c_algTaskCenter_DongGuan::changeAlgVector()
{
    algItem item0111 = {"0111", true, "车辆左前方斜视45度-照片", e0111, true, false, true, false, "无", NOPICEXAMPLE};
    algItem item0112 = {"0112", true, "车辆右后方斜视45度-照片", e0112, true, false, true, false, "无", NOPICEXAMPLE};
    algItem item0113 = {"0113", true, "车辆识别(车架号)-照片", e0113, true, false, true, false, "无", NOPICEXAMPLE};
    changeAlgVectorByType(&item0111);
    changeAlgVectorByType(&item0112);
    changeAlgVectorByType(&item0113);

    addAlgVectorByItem({"eH0111", true, "左前方对比-照片", eH0111, false, false, false, false, "无",NOPICEXAMPLE});
    addAlgVectorByItem({"eH0112", true, "右后方对比-照片", eH0112, false, false, false, false, "无",NOPICEXAMPLE});
    addAlgVectorByItem({"eH0113", true, "车架号对比-照片", eH0113, false, false, false, false, "无",NOPICEXAMPLE});

}

_c_algBaseClass* _c_algTaskCenter_DongGuan::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
     _c_algBaseClass* pReturn;
     switch (type) {
         case e0111:
            pReturn = new _c_algClass_0111_DongGuan();
             break;
         case e0112:
             pReturn = new _c_algClass_0112_DongGuan();
              break;
         case e0113:
             pReturn = new _c_algClass_0113_DongGuan();
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

