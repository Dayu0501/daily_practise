#include "_c_algTaskCenter_XiangTan.h"
#include "_c_algclass_0321_xiangtan.h"
#include "_c_algclass_0352_xiangtan.h"

_c_algTaskCenter_XiangTan::_c_algTaskCenter_XiangTan(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}

E_ZZJG _c_algTaskCenter_XiangTan::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
{
    //左右灯光车牌联合判定，在此进行结果的修正
    setZuoYuoDengGuang(pSession);
    //一、二轴制动车牌联合判定
    //setYiErZhouZhiDong(pSession);
    //湘潭交强险和完税证明联合判定，规则如下：
    //1、若交强险 车船税 这一项通过则将完税证明图片结果设置为通过
    //2、若交强险 车船税 这一项不通过，则检查完税证明图片结果是否通过，若此时完税证明图片通过，则将交强险 车船税 设置为通过
    setJiaoQiangXian(pSession);
    UNUSED(baseResult);UNUSED(sessionReason);
    return SOFT_PASS;
}

void _c_algTaskCenter_XiangTan::changeAlgVector()
{
    LOG(ALG, INFO, "%s", __PRETTY_FUNCTION__);
    algItem item0321 = {"0321", true, "左灯光工位-照片", e0321, true, false, true, false, "无",NOPICEXAMPLE};
    algItem item0352 = {"0352", true, "右灯光工位-照片", e0352, true, false, true, false, "无", NOPICEXAMPLE};

    changeAlgVectorByType(&item0321);
    changeAlgVectorByType(&item0352);
}

_c_algBaseClass* _c_algTaskCenter_XiangTan::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    _c_algBaseClass* pReturn;
    switch (type) {
    case e0321:
    {
        pReturn = new _c_algClass_0321_XiangTan();
        break;
    }
    case e0352:
    {
        pReturn = new _c_algClass_0352_XiangTan();
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

void _c_algTaskCenter_XiangTan::setZuoYuoDengGuang(_c_session *pSession)
{
    LOG(ALG, INFO, "in %s", __PRETTY_FUNCTION__);
    //嘉兴设置车牌结果，左灯光照片和右灯光照片中车牌两者有一个通过则算全部通过
    _c_algTask *algTask0321 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0321));
    _c_algTask *algTask0352 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0352));
    if (!algTask0321 || !algTask0352 || !algTask0321->pClass || !algTask0352->pClass)
    {
        LOG(ALG, INFO, "lack 0321 OR 0352 quit", __PRETTY_FUNCTION__);
        return ;
    }
    if (algTask0321->result == "4" || algTask0352->result == "4")
    {
        LOG(ALG, INFO, "result_0321 = 4 OR result_0352 = 4 quit", __PRETTY_FUNCTION__);
        return ;
    }

    memberItem *pChePai0321 = baseTool::getMemberItemByName(algTask0321->pClass->pResultMemberList,"chePaiHao"); //拿到左灯光照片的车牌号结果
    memberItem *pChePai0352 = baseTool::getMemberItemByName(algTask0352->pClass->pResultMemberList,"chePaiHao"); //拿到右灯光照片的车牌号结果
    //0321车牌和0352车牌两者有一个正确则都算正确
    if (pChePai0321 && pChePai0352)
    {
        pChePai0321->value->result = pChePai0352->value->result |= pChePai0321->value->result;
        LOG(ALG, INFO, "%s chePai = [%d]", __PRETTY_FUNCTION__, pChePai0321->value->result);
    }

    resetAlgTaskResult(algTask0321);
    resetAlgTaskResult(algTask0352);
}

void _c_algTaskCenter_XiangTan::setYiErZhouZhiDong(_c_session *pSession)
{
    LOG(ALG, INFO, "in %s", __PRETTY_FUNCTION__);
    _c_algTask *algTask0322 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0322));
    _c_algTask *algTask0348 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0348));
    if (!algTask0322 || !algTask0348 || !algTask0322->pClass || !algTask0348->pClass)
    {
        LOG(ALG, INFO, "%s lack 0321 OR 0352 quit", __PRETTY_FUNCTION__);
        return ;
    }
    //已经判定结果为 4 的直接返回，不然可能将超时改成失败
    if (algTask0322->result == "4" || algTask0348->result == "4")
    {
        LOG(ALG, INFO, "%s result_0321 = 4 OR result_0352 = 4 quit", __PRETTY_FUNCTION__);
        return ;
    }

    memberItem *pChePai0322 = baseTool::getMemberItemByName(algTask0322->pClass->pResultMemberList,"chePaiHao"); //拿到一轴照片的车牌号结果
    memberItem *pChePai0348 = baseTool::getMemberItemByName(algTask0348->pClass->pResultMemberList,"chePaiHao"); //拿到二轴照片的车牌号结果
    if (pChePai0322 && pChePai0348)
    {
        pChePai0322->value->result = pChePai0348->value->result |= pChePai0322->value->result;
        LOG(ALG, INFO, "%s chePai = [%d]", __PRETTY_FUNCTION__, pChePai0322->value->result);
    }
    resetAlgTaskResult(algTask0322);
    resetAlgTaskResult(algTask0348);
}

void _c_algTaskCenter_XiangTan::resetAlgTaskResult(_c_algTask *algTask)
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

void _c_algTaskCenter_XiangTan::setJiaoQiangXian(_c_session *pSession)
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
