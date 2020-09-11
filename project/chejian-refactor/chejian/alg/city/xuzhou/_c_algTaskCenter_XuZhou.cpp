#include "_c_algTaskCenter_XuZhou.h"
#include "_c_algClass_0203_XuZhou.h"
#include "_c_algClass_0202_XuZhou.h"

_c_algTaskCenter_XuZhou::_c_algTaskCenter_XuZhou(CityType cityType,PREDIS_PARAM redisParam)
    :_c_algTaskCenter(cityType,redisParam) {

}

bool _c_algTaskCenter_XuZhou::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason) {
    if (!pSession) {
        printf("error param pSession is null !\n");

        return false;
    }

    bool result{true};

    std::string yxqz = baseTool::getObjectItemValueByName(&pSession->paramVector, "yanYnaYouXiaoQiZhi");
    printf("@@@@@ yxqz = %s\n", yxqz.c_str());

    time_t desStamp = baseTool::strTime2unix(yxqz, "%d-%d-%d %d:%d:%d");
    time_t curStamp = baseTool::getTimeStamp();
    if ((desStamp - curStamp) / (24 * 60 * 60) >= 90) {
        printf("yxqz Not pass current date diff is %lld\n", (desStamp - curStamp) / (24 * 60 * 60));
        sessionReason = RESULT_DESC_INFO_90;

        for (auto item : pSession->algTaskVector) {
            item->result = std::to_string(NOT_PASS);
            item->reason = sessionReason;
        }

        result &= false;
    }

    std::string jyjssj = baseTool::getObjectItemValueByName(&pSession->paramVector, "jianYanJieShuShiJian");
    printf("ooooo jyjssj = %s\n", jyjssj.c_str());

    desStamp = baseTool::strTime2unix(jyjssj, "%d-%d-%d %d:%d:%d");
    curStamp = baseTool::getTimeStamp();

    printf("date diff is %lld\n", (curStamp - desStamp) / (24 * 60 * 60));

    if ((curStamp - desStamp) / (24 * 60 * 60) >= 30) {
        printf("jyjssj Not pass current date diff is %lld\n", (curStamp - desStamp) / (24 * 60 * 60));

        if (!result)
            sessionReason += ",并且";

        sessionReason += RESULT_DESC_INFO_30;

        for (auto item : pSession->algTaskVector) {
            item->result = std::to_string(NOT_PASS);
            item->reason = sessionReason;
        }

        result &= false;
    }

    return result;
}

_c_algBaseClass* _c_algTaskCenter_XuZhou::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    printf("_c_algTaskCenter_XuZhou subClassLoadAlgBaseClassByPicType algName %s, %d \n", algName.c_str(), type);

    _c_algBaseClass* pReturn;
    switch (type) {
        case e0203:
            pReturn = new _c_algClass_0203_XuZhou();

            break;
	    case e0202:
		    pReturn = new _c_algClass_0202_XuZhou();

		    break;
        default:
            //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
            return new _c_algBaseClass();
    }

    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();

    return pReturn;
}

//所有针对一辆车检测之后，图片与图片之间关联判定的逻辑就在此实现。
E_ZZJG _c_algTaskCenter_XuZhou::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession  , std::string& sessionReason) {
	UNUSED(baseResult);
	UNUSED(sessionReason);

    printf("++++++ XuZhou subAfterAlgCheck ! \n");

    //一轴二轴驻车制动车牌号联合判定
    _c_algTask *algTask0322 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0322));
    _c_algTask *algTask0348 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0348));
    _c_algTask *algTask0351 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0351));

    if (!algTask0322 || !algTask0322->pClass || algTask0322->result == "4") {
        if (algTask0348 && algTask0348->pClass && algTask0348->result != "4" &&
            algTask0351 && algTask0351->pClass && algTask0351->result != "4") {

            LOG(COMMON, INFO, "algTask0322 not ok, algTask0348 ok, algTask0351 ok %s\n", __func__);

            memberItem *pChePaiHao0348 = baseTool::getMemberItemByName(algTask0348->pClass->pResultMemberList,"chePaiHao");
            memberItem *pChePaiHao0351 = baseTool::getMemberItemByName(algTask0351->pClass->pResultMemberList,"chePaiHao");
            if (pChePaiHao0348 && pChePaiHao0351) {

                bool bValue = pChePaiHao0348->value->result || pChePaiHao0351->value->result;
                pChePaiHao0348->value->result = pChePaiHao0351->value->result = bValue;

                std::string reason;
                E_JG result = algTask0348->pClass->getResult(&reason);
                algTask0348->setAlgTaskResult((int) result, reason);

                reason = "";
                result = algTask0351->pClass->getResult(&reason);
                algTask0351->setAlgTaskResult((int) result, reason);
            }
        }
    } else if (!algTask0348 || !algTask0348->pClass || algTask0348->result == "4") {
        if (algTask0322->pClass && algTask0322->result != "4" &&
            algTask0351 && algTask0351->pClass && algTask0351->result != "4") {

            LOG(COMMON, INFO, "algTask0348 not ok, algTask0322 ok, algTask0351 ok %s\n", __func__);

            memberItem *pChePaiHao0322 = baseTool::getMemberItemByName(algTask0322->pClass->pResultMemberList,"chePaiHao");
            memberItem *pChePaiHao0351 = baseTool::getMemberItemByName(algTask0351->pClass->pResultMemberList,"chePaiHao");
            if (pChePaiHao0322 && pChePaiHao0351) {

                bool bValue = pChePaiHao0322->value->result || pChePaiHao0351->value->result;
                pChePaiHao0322->value->result = pChePaiHao0351->value->result = bValue;

                std::string reason;
                E_JG result = algTask0322->pClass->getResult(&reason);
                algTask0322->setAlgTaskResult((int) result, reason);

                reason = "";
                result = algTask0351->pClass->getResult(&reason);
                algTask0351->setAlgTaskResult((int) result, reason);
            }
        }
    } else if (!algTask0351 || !algTask0351->pClass || algTask0351->result == "4") {
        if (algTask0322->pClass && algTask0322->result != "4" && algTask0348->pClass && algTask0348->result != "4") {

            LOG(COMMON, INFO, "algTask0351 not ok, algTask0322 ok, algTask0348 ok %s\n", __func__);

            memberItem *pChePaiHao0322 = baseTool::getMemberItemByName(algTask0322->pClass->pResultMemberList,"chePaiHao");
            memberItem *pChePaiHao0348 = baseTool::getMemberItemByName(algTask0348->pClass->pResultMemberList,"chePaiHao");
            if (pChePaiHao0322 && pChePaiHao0348) {

                bool bValue = pChePaiHao0322->value->result || pChePaiHao0348->value->result;
                pChePaiHao0322->value->result = pChePaiHao0348->value->result = bValue;

                std::string reason;
                E_JG result = algTask0322->pClass->getResult(&reason);
                algTask0322->setAlgTaskResult((int) result, reason);

                reason = "";
                result = algTask0348->pClass->getResult(&reason);
                algTask0348->setAlgTaskResult((int) result, reason);
            }
        }
    } else {
        LOG(COMMON, INFO, "algTask0348->localPath is %s\n", algTask0348->localPath.c_str());

        memberItem *pChePaiHao0322 = baseTool::getMemberItemByName(algTask0322->pClass->pResultMemberList, "chePaiHao");
        memberItem *pChePaiHao0348 = baseTool::getMemberItemByName(algTask0348->pClass->pResultMemberList,"chePaiHao");
        memberItem *pChePaiHao0351 = baseTool::getMemberItemByName(algTask0351->pClass->pResultMemberList,"chePaiHao");

        if (pChePaiHao0322 && pChePaiHao0322->value->result) {
            printf("pChePaiHao0322->value->result is true !\n");

            if (pChePaiHao0348) pChePaiHao0348->value->result = true;
            if (pChePaiHao0351) pChePaiHao0351->value->result = true;
        } else if (pChePaiHao0348 && pChePaiHao0348->value->result) {
            printf("pChePaiHao0348->value->result is true !\n");

            if (pChePaiHao0322) pChePaiHao0322->value->result = true;
            if (pChePaiHao0351) pChePaiHao0351->value->result = true;
        } else if (pChePaiHao0351 && pChePaiHao0351->value->result) {
            printf("pChePaiHao0351->value->result is true !\n");

            if (pChePaiHao0322) pChePaiHao0322->value->result = true;
            if (pChePaiHao0348) pChePaiHao0348->value->result = true;
        }

        LOG(COMMON, INFO, "algTask0322->result =  %s, algTask0322->reason = %s\n", algTask0322->result.c_str(), algTask0322->reason.c_str());
        LOG(COMMON, INFO, "algTask0348->result =  %s, algTask0348->reason = %s\n", algTask0348->result.c_str(), algTask0348->reason.c_str());
        LOG(COMMON, INFO, "algTask0351->result =  %s, algTask0351->reason = %s\n", algTask0351->result.c_str(), algTask0351->reason.c_str());

        if(algTask0322->result != "4") {
            std::string reason;
            E_JG result = algTask0322->pClass->getResult(&reason);
            algTask0322->setAlgTaskResult((int)result, reason);
        }

        if(algTask0348->result != "4") {
            std::string reason;
            E_JG result = algTask0348->pClass->getResult(&reason);
            algTask0348->setAlgTaskResult((int) result, reason);
        }

        if(algTask0351->result != "4") {
            std::string reason;
            E_JG result = algTask0351->pClass->getResult(&reason);
            algTask0351->setAlgTaskResult((int) result, reason);
        }

        LOG(COMMON, INFO, "111algTask0322->result =  %s, algTask0322->reason = %s\n", algTask0322->result.c_str(), algTask0322->reason.c_str());
        LOG(COMMON, INFO, "111algTask0348->result =  %s, algTask0348->reason = %s\n", algTask0348->result.c_str(), algTask0348->reason.c_str());
        LOG(COMMON, INFO, "111algTask0351->result =  %s, algTask0351->reason = %s\n", algTask0351->result.c_str(), algTask0351->reason.c_str());
    }


    //底盘动态开始结束的联合判定
	_c_algTask *algTask0342 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0342));
	_c_algTask *algTask0344 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0344));

	if(!algTask0342 || !algTask0342->pClass || !algTask0344 || !algTask0344->pClass ||
		algTask0342->result == "4" || algTask0344->result == "4") {
		return SOFT_PASS;
	}

	memberItem *pChePaihao0342 = baseTool::getMemberItemByName(algTask0342->pClass->pResultMemberList,"chePaiHao_jieshu");
	memberItem *pChePaihao0344 = baseTool::getMemberItemByName(algTask0344->pClass->pResultMemberList,"chePaiHao_kaishi");

	if (pChePaihao0342 && pChePaihao0342->value->result) {
		if (pChePaihao0344) {
			printf("++++++ XuZhou 0342 override 0344 ! \n");

			pChePaihao0344->value->result = pChePaihao0342->value->result;

			std::string reason;
			E_JG result = algTask0344->pClass->getResult(&reason);
			algTask0344->setAlgTaskResult((int)result, reason); //对0344的结果重新赋值
		}
	}

	if (pChePaihao0344 && pChePaihao0344->value->result) {
		if (pChePaihao0342) {
			printf("++++++ XuZhou 0344 override 0342 ! \n");

			pChePaihao0342->value->result = pChePaihao0344->value->result;

			std::string reason;
			E_JG result = algTask0342->pClass->getResult(&reason);
			algTask0342->setAlgTaskResult((int)result, reason); //对0342的结果重新赋值
		}
	}

	printf("XuZhou subAfterAlgCheck PASS !------  \n");

    return SOFT_PASS;
}

bool _c_algTaskCenter_XuZhou::beforeSetResult(_c_session *pSession, std::string& sessionReason) {
    if (sessionReason == RESULT_DESC_INFO_90 ||
        sessionReason == RESULT_DESC_INFO_30 ||
        sessionReason == std::string(RESULT_DESC_INFO_90) + RESULT_DESC_INFO_30)
        pSession->setSessionResult(std::to_string(SOFT_NOTPASS), sessionReason);

    return true;
}

void _c_algTaskCenter_XuZhou::changeAlgVector() {
    printf("%s\n", __PRETTY_FUNCTION__);

    algItem item0203 = {"0203", true, "交强险-照片", e0203, true, false, true, false, "无", NOPICEXAMPLE};
	algItem item0202 = {"0202", true, "牌证申请表-照片", e0202, true, false, true, false, "无", NOPICEXAMPLE};

    changeAlgVectorByType(&item0203);
	changeAlgVectorByType(&item0202);
}