#include "_c_algTaskCenter_BengBu.h"

_c_algTaskCenter_BengBu::_c_algTaskCenter_BengBu(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}

void _c_algTaskCenter_BengBu::changeAlgVector()
{
    LOG(ALG, INFO, "%s", __PRETTY_FUNCTION__);
}

_c_algBaseClass* _c_algTaskCenter_BengBu::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    _c_algBaseClass* pReturn;
    switch (type) {
    default:
        //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
        return new _c_algBaseClass();
        break;
    }
    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();
    return pReturn;
}

E_ZZJG _c_algTaskCenter_BengBu::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
{
    if (baseTool::getObjectItemValueByName(&pSession->paramVector, "isRepeat") == "0") //0表示正常车辆
    {
        //左右灯光车牌联合判定，在此进行结果的修正
        //setZuoYuoDengGuang(pSession);
        //一、二轴制动车牌联合判定
        //setYiErZhouZhiDong(pSession);
        //湘潭交强险和完税证明联合判定，规则如下：
        //1、若交强险 车船税 这一项通过则将完税证明图片结果设置为通过
        //2、若交强险 车船税 这一项不通过，则检查完税证明图片结果是否通过，若此时完税证明图片通过，则将交强险 车船税 设置为通过
        setJiaoQiangXian(pSession);
    }
    else //2表示复检车辆
    {
        pSession->setSessionResult("-1", "复检车辆");
        sessionReason = "复检车辆";
        return SOFT_NOTPROCESS;
    }
    UNUSED(baseResult);UNUSED(sessionReason);
    return SOFT_PASS;
}

void _c_algTaskCenter_BengBu::setJiaoQiangXian(_c_session *pSession)
{
    _c_algTask *algTask0203 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0203));
    _c_algTask *algTask0206 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0206));
    //缺少交强险和完税证明其中任意一张则返回
    if (!algTask0203 || !algTask0206 || !algTask0203->pClass || !algTask0206->pClass)
    {
        LOG(ALG, INFO, "%s lack 0203 OR 0206 quit", __PRETTY_FUNCTION__);
        return ;
    }
    //避免覆盖超时等异常结果
    if (algTask0203->result == "4" || algTask0206->result == "4")
    {
        LOG(ALG, INFO, "result_0203 = 4 OR result_0206 = 4 quit", __PRETTY_FUNCTION__);
        return ;
    }

    memberItem *pCheChuanShui = baseTool::getMemberItemByName(algTask0203->pClass->pResultMemberList,"cheChuanShui"); //拿到交强险车船税结果
    if (pCheChuanShui)
    {
        //如果车船税通过，则将完税证明图片结果设置为通过
        if (pCheChuanShui->value->result)
        {
            baseTool::setAllPass(algTask0206->pClass->pResultMemberList);
            resetAlgTaskResult(algTask0206);
        }
        else  //如果车船税不通过，则检查完税证明图片结果，若结果为通过，则设置车船税通过，并重写交强险图片结果
        {
            if (algTask0206->result == "1")
            {
                pCheChuanShui->value->result = true;
                resetAlgTaskResult(algTask0203);
            }
        }
    }
}

void _c_algTaskCenter_BengBu::resetAlgTaskResult(_c_algTask *algTask)
{
    if (algTask && algTask->pClass)
    {
        std::string reason = "";
        E_JG result = algTask->pClass->getResult(&reason);
        algTask->setAlgTaskResult((int)result, reason); //对照片结果重新赋值
        LOG(ALG, INFO, "%s algTask%s reset : result=[%d] reason = [%s]", __PRETTY_FUNCTION__, algTask->algCode.c_str(),
            static_cast<int>(result), reason.c_str()) ;
    }
}
