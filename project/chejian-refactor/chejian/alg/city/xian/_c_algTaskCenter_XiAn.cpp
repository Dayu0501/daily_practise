#include "_c_algTaskCenter_XiAn.h"
#include "alg/algClass/_c_algClass_0228.h"
#include "alg/algClass/_c_algClass_0260.h"
_c_algTaskCenter_XiAn::_c_algTaskCenter_XiAn(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}

//bool _c_algTaskCenter_XiAn::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason)
//{
//    return true;
//}

////所有针对一辆车检测之后，图片与图片之间关联判定的逻辑就在此实现。
//E_ZZJG _c_algTaskCenter_XiAn::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
//{
//    return SOFT_PASS;
//}

void _c_algTaskCenter_XiAn::changeAlgVector()
{
    addAlgVectorByItem({"0199", true, "身份证正面(linked by 228)",e0199 , false, false, true, false, "无",NOPICEXAMPLE});
    addAlgVectorByItem({"0120", true, "身份证背面(linked by 260)",e0200 , false, false, true, false, "无",NOPICEXAMPLE});
}

_c_algBaseClass* _c_algTaskCenter_XiAn::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
     _c_algBaseClass* pReturn;
     AlgType _algtp = algNULL ;
     switch (type) {
         case e0199:
            pReturn = new _c_algClass_0228();
            _algtp  = alg0228 ;
             break;
         case e0200:
             pReturn = new _c_algClass_0260();
             _algtp  = alg0228 ;
              break;
        default:
            //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
            return new _c_algBaseClass();
        break;
    }
    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();
    pReturn->resetBaseParam(type);
    pReturn->setAlgType( _algtp );
    return pReturn;
}

