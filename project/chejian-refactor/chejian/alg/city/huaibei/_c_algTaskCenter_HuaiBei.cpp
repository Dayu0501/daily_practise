#include "_c_algTaskCenter_HuaiBei.h"
#include "_c_algClass_0203_HuaiBei.h"
#include "_c_algClass_0158_HuaiBei.h"
#include "_c_algClass_0159_HuaiBei.h"
//#include "_c_algClass_0164_HuaiBei.h"
#include "_c_algClass_0213_1_HuaiBei.h"
#include "_c_algClass_0258_HuaiBei.h"

_c_algTaskCenter_HuaiBei::_c_algTaskCenter_HuaiBei(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{
}

void _c_algTaskCenter_HuaiBei::changeAlgVector()
{
    printf("void _c_algTaskCenter_HuaiBei::changeAlgVector()\n");

    algItem item0203 = {"0203", false, "交强险-照片", e0203, false, false, true, false, "无", NOPICEXAMPLE}; //开启使用子类逻辑开关
    changeAlgVectorByType(&item0203);
    algItem item0158 = { "0171", true, "车辆正前方(车牌特写)-照片", e0158, false, false, true, false, "无",NOPICEXAMPLE };
    changeAlgVectorByType(&item0158);
    algItem item0159 = { "0172", true, "车辆正后方(车牌特写)-照片", e0159, false, false, true, false, "无",NOPICEXAMPLE };
    changeAlgVectorByType(&item0159);

    //algItem item0164 = { "0164", true, "发动机舱-照片", e0164, true, false,  true, false, "无", NOPICEXAMPLE };
    //addAlgVectorByItem(item0164);
    algItem item0213_1 = { "0213", true, "气瓶使用证1-照片", e0213_1, true, false,  true, false, "无", NOPICEXAMPLE };
    addAlgVectorByItem(item0213_1);
    algItem item0258 = { "0258", true, "气瓶使用证2-照片", e0258, true, false,  true, false, "无", NOPICEXAMPLE };
    addAlgVectorByItem(item0258);
}

_c_algBaseClass* _c_algTaskCenter_HuaiBei::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    _c_algBaseClass* pReturn = NULL;
    switch (type) {
    case e0203:    //交强险保单
        pReturn = new _c_algClass_0203_HuaiBei();
        break;
    case e0158:    //车辆正前方(车牌特写)-照片
        pReturn = new _c_algClass_0158_HuaiBei();
        break;
    case e0159:    //车辆正后方(车牌特写)-照片
        pReturn = new _c_algClass_0159_HuaiBei();
        break;
    //case e0164:    //发动机舱
    //    pReturn = new _c_algClass_0164_HuaiBei();
    //    break;
    case e0213_1:  //气瓶使用证1
        pReturn = new _c_algClass_0213_1_HuaiBei();
        break;
    case e0258:    //气瓶使用证2
        pReturn = new _c_algClass_0258_HuaiBei();
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
