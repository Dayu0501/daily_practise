#include "_c_algTaskCenter_QuJing.h"

_c_algTaskCenter_QuJing::_c_algTaskCenter_QuJing(CityType cityType,PREDIS_PARAM redisParam)
    :_c_algTaskCenter(cityType,redisParam) {

}

bool _c_algTaskCenter_QuJing::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason) {
    UNUSED(pSession);
    UNUSED(sessionReason);

    return true;
}

//所有针对一辆车检测之后，图片与图片之间关联判定的逻辑就在此实现。
E_ZZJG _c_algTaskCenter_QuJing::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason) {
    UNUSED(baseResult);
    UNUSED(sessionReason);

    printf("------ QuJing subAfterAlgCheck ! \n");
    _c_algTask *algTask0203 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0203));
    _c_algTask *algTask0206 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0206));

    if(!algTask0203 || !algTask0203->pClass || !algTask0206 || !algTask0206->pClass ||
        algTask0203->result == "4" || algTask0206->result == "4") {
        return SOFT_PASS;
    }

    memberItem *pCheChuanShui0203 = baseTool::getMemberItemByName(algTask0203->pClass->pResultMemberList,"cheChuanShui"); 
    memberItem *pCheChuanShui0206 = baseTool::getMemberItemByName(algTask0206->pClass->pResultMemberList,"cheChuanShui"); 

    if (pCheChuanShui0203 && pCheChuanShui0203->value->result) { 
        if (pCheChuanShui0206) {
            printf("++++++ QuJing 0203 override 0206 ! \n");

            pCheChuanShui0206->value->result = pCheChuanShui0203->value->result;

            std::string reason;
            E_JG result = algTask0206->pClass->getResult(&reason);
            algTask0206->setAlgTaskResult((int)result, reason); //对0206的结果重新赋值
        }
    }

    if (pCheChuanShui0206 && pCheChuanShui0206->value->result) {
            if (pCheChuanShui0203) {
                printf("++++++ QuJing 0206 override 0203 ! \n");

                pCheChuanShui0203->value->result = pCheChuanShui0206->value->result;

                std::string reason;
                E_JG result = algTask0203->pClass->getResult(&reason);
                algTask0203->setAlgTaskResult((int)result, reason); //对0203的结果重新赋值
            }
        }

    printf("QuJing subAfterAlgCheck TPASS !------  \n");
    return SOFT_PASS;
}

void _c_algTaskCenter_QuJing::changeAlgVector() { 

}
