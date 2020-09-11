#include "_c_algTaskCenter_LiangJiang.h"
#include "_c_algClass_0206_LiangJiang.h"

_c_algTaskCenter_LiangJiang::_c_algTaskCenter_LiangJiang(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}

//bool _c_algTaskCenter_LiangJiang::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason)
//{
//    return true;
//}

////所有针对一辆车检测之后，图片与图片之间关联判定的逻辑就在此实现。
//E_ZZJG _c_algTaskCenter_LiangJiang::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
//{
//    return SOFT_PASS;
//}

void _c_algTaskCenter_LiangJiang::changeAlgVector()
{
    algItem item0206 = {"0206", true, "交强险和完税证明", e0206, true, false, true, false, "无",NOPICEXAMPLE};
    printf("-------------------------------------------------0206 \n");
    changeAlgVectorByType(&item0206);
}

_c_algBaseClass* _c_algTaskCenter_LiangJiang::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
     _c_algBaseClass* pReturn;
     switch (type) {
        case e0206:
            pReturn = new _c_algClass_0206_LiangJiang();
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

