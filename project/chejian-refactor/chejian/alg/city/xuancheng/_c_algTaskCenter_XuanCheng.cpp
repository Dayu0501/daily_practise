#include "_c_algTaskCenter_XuanCheng.h"
#include "_c_algClass_0321_XuanCheng.h"
#include "_c_algClass_0158_XuanCheng.h"
#include "_c_algClass_0159_XuanCheng.h"

_c_algTaskCenter_XuanCheng::_c_algTaskCenter_XuanCheng(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}

bool _c_algTaskCenter_XuanCheng::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason)
{
    std::string zhuangtai = baseTool::getObjectItemValueByName(&pSession->paramVector, "jiDongCheZhuangTai");

    if(zhuangtai != "A" && zhuangtai != "G") //状态为正常或者违章未处理，可以自动通过审核。否则需要人工审核。
    {
        std::vector<_c_algTask *>* algTaskVector = &pSession->algTaskVector;
        for(unsigned int i = 0; i < algTaskVector->size(); i++)
        {
            baseTool::writeResultByJGAndSM((*algTaskVector)[i],UNABLE_IDENTIFY, "需人工审核");
        }
        sessionReason = "车辆状态异常(宣城)";

        if(zhuangtai == "Q")
        {
            //找到行驶证
            _c_algTask *algTask0201 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0201));
            if(!algTask0201)
            {
                return false;
            }

            algTask0201->setAlgTaskResult(NOT_PASS, "该车辆状态是逾期未检验"); //设置为不通过，且写上原因
        }
        return false;
    }

    return true;
}

//所有针对一辆车检测之后，图片与图片之间关联判定的逻辑就在此实现。
E_ZZJG _c_algTaskCenter_XuanCheng::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
{
    UNUSED(baseResult);UNUSED(pSession);UNUSED(sessionReason);
    return SOFT_PASS;
}

void _c_algTaskCenter_XuanCheng::changeAlgVector()
{
     printf("void _c_algTaskCenter_XuanCheng::changeAlgVector()\n");
    algItem item0321 = {"0321", true, "左灯光工位-照片", e0321, false, false, true, false, "无",NOPICEXAMPLE};
    algItem item0158 = {"0158", true, "车辆正后方(车牌特写)-照片", e0158, false, false, true, false, "无",NOPICEXAMPLE};
    algItem item0159 = {"0159", true, "车辆正前方(车牌特写)-照片", e0159, false, false, true, false, "无",NOPICEXAMPLE};

    changeAlgVectorByType(&item0321);
    changeAlgVectorByType(&item0158);
    changeAlgVectorByType(&item0159);
}

_c_algBaseClass* _c_algTaskCenter_XuanCheng::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    _c_algBaseClass* pReturn;
    switch (type) {
       case e0321:
            pReturn = new _c_algClass_0321_XuanCheng();
        break;
    case e0158:
            pReturn = new _c_algClass_0158_XuanCheng();
        break;
    case e0159:
            pReturn = new _c_algClass_0159_XuanCheng();
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
