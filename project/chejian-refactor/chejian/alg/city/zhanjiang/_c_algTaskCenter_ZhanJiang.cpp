#include "_c_algTaskCenter_ZhanJiang.h"
#include "_c_algclass_0288_zhanjiang.h"

_c_algTaskCenter_ZhanJiang::_c_algTaskCenter_ZhanJiang(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}

void _c_algTaskCenter_ZhanJiang::changeAlgVector()
{
    LOG(ALG, INFO, "%s", __PRETTY_FUNCTION__);
    algItem item0288 = {"0288", false, "行驶证(背面)-照片", e0288, false, false, false, false, "无", NOPICEXAMPLE};
    item0288.subAlgClass = true;

    changeAlgVectorByType(&item0288);
}

_c_algBaseClass* _c_algTaskCenter_ZhanJiang::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    _c_algBaseClass* pReturn;
    switch (type) {
    case e0288:
    {
        pReturn = new _c_algClass_0288_ZhanJiang();
        break;
    }
    default:
        //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
        return new _c_algBaseClass();
        break;
    }
    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();
    return pReturn;
}
