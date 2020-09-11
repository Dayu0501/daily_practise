#include "_c_algTaskCenter_NanPing.h"

_c_algTaskCenter_NanPing::_c_algTaskCenter_NanPing(CityType cityType, PREDIS_PARAM redisParam)
    :_c_algTaskCenter(cityType,redisParam) {

}

bool _c_algTaskCenter_NanPing::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason) {
    UNUSED(pSession);
    UNUSED(sessionReason);

    return true;
}

//所有针对一辆车检测之后，图片与图片之间关联判定的逻辑就在此实现。
E_ZZJG _c_algTaskCenter_NanPing::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession  , std::string& sessionReason) {
	UNUSED(baseResult);
	UNUSED(sessionReason);

    printf("++++++ NanPing subAfterAlgCheck ! \n");

    _c_algTask *algTask0111 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0111));
    _c_algTask *algTask0112 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0112));

    //如果有一个为空，就没有必要在做联合赋值
    if (!algTask0111 || !algTask0111->pClass || !algTask0112 || !algTask0112->pClass ||
        algTask0111->result == "4" || algTask0112->result == "4")
        return SOFT_PASS;

    memberItem *pSanJiaoJia0111 = baseTool::getMemberItemByName(algTask0111->pClass->pResultMemberList, "sanJiaoJia");
    memberItem *pSanJiaoJia0112 = baseTool::getMemberItemByName(algTask0112->pClass->pResultMemberList,"sanJiaoJia");

    if (pSanJiaoJia0111 && pSanJiaoJia0111->value->result) { 
        if (pSanJiaoJia0112) {
            printf("++++++ NanPing e0111 override e0112 ! \n");

            pSanJiaoJia0112->value->result = pSanJiaoJia0111->value->result;

            std::string reason;
            E_JG result = algTask0112->pClass->getResult(&reason);
            algTask0112->setAlgTaskResult((int)result, reason); //对0112的结果重新赋值
        }
    }

    if (pSanJiaoJia0112 && pSanJiaoJia0112->value->result) {
        if (pSanJiaoJia0111) {
            printf("++++++ NanPing e0112 override e0111 ! \n");

            pSanJiaoJia0111->value->result = pSanJiaoJia0112->value->result;

            std::string reason;
            E_JG result = algTask0111->pClass->getResult(&reason);
            algTask0111->setAlgTaskResult((int)result, reason); //对0111的结果重新赋值
        }
    }
    
    return SOFT_PASS;
}

void _c_algTaskCenter_NanPing::changeAlgVector() {

}