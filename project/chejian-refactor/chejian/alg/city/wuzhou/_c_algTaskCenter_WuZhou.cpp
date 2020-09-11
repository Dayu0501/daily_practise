#include "_c_algTaskCenter_WuZhou.h"
#include "_c_algClass_0111_WuZhou.h"
#include "_c_algClass_0112_WuZhou.h"
#include "_c_algClass_0140_WuZhou.h"
#include "_c_algClass_0157_WuZhou.h"
#include "_c_algClass_0205_WuZhou.h"

_c_algTaskCenter_WuZhou::_c_algTaskCenter_WuZhou(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{
    
}

bool _c_algTaskCenter_WuZhou::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason)
{
    return true;
}

void _c_algTaskCenter_WuZhou::changeAlgVector()
{
    printf("void _c_algTaskCenter_WuZhou::changeAlgVector()\n");
    algItem item0111 = {"0111", true, "车辆左前方斜视45度", e0111, true, false, true, false, "无", NOPICEXAMPLE}; //0111开启使用子类逻辑开关
    algItem item0112 = {"0112", true, "车辆右后方斜视45度", e0112, true, false, true, false, "无", NOPICEXAMPLE}; //0112开启使用子类逻辑开关
    algItem item0140 = {"0140", false, "副制动踏板（仅限教练车）", e0140, true, false, true, false, "无", NOPICEXAMPLE}; //0140开启使用子类逻辑开关
    algItem item0157 = {"0157", false, "安全带-照片", e0157, false, false, true, false, "无", NOPICEXAMPLE}; //0157开启使用子类逻辑开关
    algItem item0205 = {"0205", true, "查验记录表-照片", e0205, true, false, true, false, "无", NOPICEXAMPLE}; //0205开启使用子类逻辑开关

    changeAlgVectorByType(&item0111);
    changeAlgVectorByType(&item0112);
    changeAlgVectorByType(&item0140);
    changeAlgVectorByType(&item0157);
    changeAlgVectorByType(&item0205);
}

_c_algBaseClass* _c_algTaskCenter_WuZhou::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    _c_algBaseClass* pReturn;
    switch (type) {
       case e0111:
            pReturn = new _c_algClass_0111_WuZhou();
            break;
       case e0112:
            pReturn = new _c_algClass_0112_WuZhou();
            break; 
       case e0140:
            pReturn = new _c_algClass_0140_WuZhou();
            break; 
       case e0157:
            pReturn = new _c_algClass_0157_WuZhou();
            break; 
       case e0205:
            pReturn = new _c_algClass_0205_WuZhou();
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

E_ZZJG _c_algTaskCenter_WuZhou::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
{
    return SOFT_PASS;
}