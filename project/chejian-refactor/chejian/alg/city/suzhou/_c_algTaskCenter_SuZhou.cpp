#include "_c_algTaskCenter_SuZhou.h"
#include "_c_algClass_0135_SuZhou.h"
#include "_c_algClass_0136_SuZhou.h"
#include "_c_algClass_0144_SuZhou.h"

_c_algTaskCenter_SuZhou::_c_algTaskCenter_SuZhou(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}

void _c_algTaskCenter_SuZhou::changeAlgVector()
{
//    algItem item0354 = {"0354", true, "车辆正前方(车牌特写)-照片", e0354, false, false, true, false, "无",NOPICEXAMPLE};
//    changeAlgVectorByType(&item0354);
        algItem item01 = {"01", true, "尾箱（第三方)", eH0001, true, false, true, false, "无",NOPICEXAMPLE};
        algItem item02 = {"02", true, "左前轮轮胎规格（第三方)", eH0002, true, false, true, false, "无",NOPICEXAMPLE};
        algItem item03 = {"03", true, "右前轮轮胎规格（第三方)", eH0003, true, false, true, false, "无",NOPICEXAMPLE};
        algItem item04 = {"04", true, "一轴轮胎花纹（第三方)", eH0004, true, false, true, false, "无",NOPICEXAMPLE};
        algItem item05 = {"05", true, "一轴轮胎花纹（第三方)", eH0005, true, false, true, false, "无",NOPICEXAMPLE};
        algItem item06 = {"06", true, "二轴轮胎花纹（第三方)", eH0006, true, false, true, false, "无",NOPICEXAMPLE};
        algItem item07 = {"07", true, "二轴轮胎花纹（第三方)", eH0007, true, false, true, false, "无",NOPICEXAMPLE};
        algItem item08 = {"08", true, "三轴轮胎花纹（第三方)", eH0008, true, false, true, false, "无",NOPICEXAMPLE};
        algItem item09 = {"09", true, "三轴轮胎花纹（第三方)", eH0009, true, false, true, false, "无",NOPICEXAMPLE};


       // changeAlgVectorByType(&item01);
        addAlgVectorByItem(item01);
        addAlgVectorByItem(item02);
        addAlgVectorByItem(item03);
        addAlgVectorByItem(item04);
        addAlgVectorByItem(item05);
        addAlgVectorByItem(item06);
        addAlgVectorByItem(item07);
        addAlgVectorByItem(item08);
        addAlgVectorByItem(item09);
}

_c_algBaseClass* _c_algTaskCenter_SuZhou::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
     _c_algBaseClass* pReturn;
     switch (type) {
        case eH0001:
            pReturn = new _c_algClass_0144_SuZhou();
            break;
        case eH0002:
        case eH0003:
            pReturn = new _c_algClass_0136_SuZhou();
        break;
        case eH0004:
        case eH0005:
        case eH0006:
        case eH0007:
        case eH0008:
        case eH0009:
            pReturn = new _c_algClass_0135_SuZhou();
        break;
        default:
            //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
            printf("++++++++++++++++++++++default+++++++++++++++++\n");
            return new _c_algBaseClass();
        break;
    }
    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();
    //重置图片类型
    pReturn->resetBaseParam(type);
   // pReturn->printAlgMsg();
    return pReturn;
}

