#include "_c_algTaskCenter_MaoMing.h"
#include "_c_algClass_0208_MaoMing.h"

_c_algTaskCenter_MaoMing::_c_algTaskCenter_MaoMing(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{
    
}

void _c_algTaskCenter_MaoMing::changeAlgVector()
{
     printf("void _c_algTaskCenter_MaoMing::changeAlgVector()\n");
    algItem item0208 = {"0208", false, "代理人授权书-照片", e0208, false, false, true, false, "无", NOPICEXAMPLE}; //0208开启使用子类逻辑开关

    changeAlgVectorByType(&item0208);
}

_c_algBaseClass* _c_algTaskCenter_MaoMing::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    _c_algBaseClass* pReturn;
    switch (type) {
       case e0208:
            pReturn = new _c_algClass_0208_MaoMing();
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