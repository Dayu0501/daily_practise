#include "_c_algTaskCenter_ShenZhen.h"

_c_algTaskCenter_ShenZhen::_c_algTaskCenter_ShenZhen(CityType cityType,PREDIS_PARAM redisParam)
    :_c_algTaskCenter(cityType,redisParam) {

}

bool _c_algTaskCenter_ShenZhen::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason) {
    UNUSED(pSession);
    UNUSED(sessionReason);

    return true;
}

//所有针对一辆车检测之后，图片与图片之间关联判定的逻辑就在此实现。
E_ZZJG _c_algTaskCenter_ShenZhen::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason) {
    UNUSED(baseResult);
    UNUSED(sessionReason);

    _c_algTask *algTask0297 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0297));

    if(!algTask0297 || !algTask0297->pClass) {
        return SOFT_PASS;
    }

    memberItem *qianMing_waiGuanJianYanYuan = baseTool::getMemberItemByName(algTask0297->pClass->pResultMemberList,"qianZi_waiGuanJianYanYuan");
    memberItem *qianMing_yinCheJianYanYuan = baseTool::getMemberItemByName(algTask0297->pClass->pResultMemberList,"qianZi_yinCheJianYanYuan");
    memberItem *qianMing_diPanJianYanYuan = baseTool::getMemberItemByName(algTask0297->pClass->pResultMemberList,"qianZi_diPanJianYanYuan");

    if(qianMing_waiGuanJianYanYuan && qianMing_yinCheJianYanYuan && qianMing_diPanJianYanYuan) {
        printf("++++++ ShenZhen sign check 1 ! \n");
        bool lvalue = qianMing_waiGuanJianYanYuan->value->result || qianMing_yinCheJianYanYuan->value->result || qianMing_diPanJianYanYuan->value->result;

        qianMing_waiGuanJianYanYuan->value->result = lvalue;
        qianMing_yinCheJianYanYuan->value->result = lvalue;
        qianMing_diPanJianYanYuan->value->result = lvalue;
    }

    std::string reason;
    E_JG result = algTask0297->pClass->getResult(&reason);
    algTask0297->setAlgTaskResult((int)result, reason); //对0297的结果重新赋值
    
    return SOFT_PASS;
}

void _c_algTaskCenter_ShenZhen::changeAlgVector() { 

}