#include "_c_algTaskCenter_FuZhou.h"
#include "_c_algClass_0348_FuZhou.h"
#include "_c_algClass_0322_FuZhou.h"
#include "_c_algClass_0167_FuZhou.h"
#include "_c_algClass_0202_FuZhou.h"
#include "_c_algClass_0110_FuZhou.h"
#include "_c_algClass_0123_FuZhou.h"
#include "_c_algClass_0124_FuZhou.h"

_c_algTaskCenter_FuZhou::_c_algTaskCenter_FuZhou(CityType cityType, PREDIS_PARAM redisParam)
    :_c_algTaskCenter(cityType, redisParam) {

}

bool _c_algTaskCenter_FuZhou::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason) {
    UNUSED(pSession);
    UNUSED(sessionReason);

    return true;
}

_c_algBaseClass* _c_algTaskCenter_FuZhou::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    //printf("_c_algTaskCenter_FuZhou subClassLoadAlgBaseClassByPicType algName %s, %d \n", algName.c_str(), type);
    
     _c_algBaseClass* pReturn;
     switch (type) {
        case e0322:
            pReturn = new _c_algClass_0322_FuZhou();

            break;
        case e0348:
            pReturn = new _c_algClass_0348_FuZhou();

            break;
        case e0167:
            pReturn = new _c_algClass_0167_FuZhou();

            break;
        case e0202:
            pReturn = new _c_algClass_0202_FuZhou();

            break;
         case e0110:
             pReturn = new _c_algClass_0110_FuZhou();

             break;
         case e0158:
             pReturn = new _c_algClass_0124_FuZhou();

             break;

         case e0159:
             pReturn = new _c_algClass_0123_FuZhou();

             break;
//	     case e0113:
//		     pReturn = new _c_algClass_0113_FuZhou();
//
//		     break;
        default:
            //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
            return new _c_algBaseClass();
    }

    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();
    return pReturn;
}

E_ZZJG _c_algTaskCenter_FuZhou::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason) {
    UNUSED(baseResult);
    UNUSED(sessionReason);

    printf("%s \n", __PRETTY_FUNCTION__);

    _c_algTask *algTask0202 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0202));
	printf("11111111111111\n");
    if (algTask0202 && algTask0202->pClass && algTask0202->result != "4") {

	    printf("22222222222222\n");
        memberItem *pSuoShuJiGou = baseTool::getMemberItemByName(algTask0202->pClass->pResultMemberList,"suoShuJiGou");
        if (pSuoShuJiGou && pSuoShuJiGou->value->result) {

            printf("&&&&& E_JG::UNABLE_IDENTIFY \n");
            algTask0202->setAlgTaskResult((int)E_JG::UNABLE_IDENTIFY, pSuoShuJiGou->desc); //对0202的结果重新赋值
        }
    }

    return SOFT_PASS;
}

void _c_algTaskCenter_FuZhou::changeAlgVector() {
    printf("%s\n", __PRETTY_FUNCTION__);

    algItem item0167 = {"0167", true, "车辆前方照片-照片",   e0167, true, false, true, false, "无", NOPICEXAMPLE};
    algItem item0322 = {"0322", true, "一轴制动(滚筒)-照片", e0322, true, true,  true, false, "无", NOPICEXAMPLE};
    algItem item0348 = {"0348", true, "二轴制动(滚筒)-照片", e0348, true, true,  true, false, "无", NOPICEXAMPLE};
    algItem item0202 = {"0202", true, "牌证申请表-照片", e0202, true, false,  true, false, "无", NOPICEXAMPLE };
    algItem item0124 = {"0158", true, "车辆正后方(车牌特写)-照片", e0158, true, false, true, false, "无", NOPICEXAMPLE};
    algItem item0123 = {"0159", true, "车辆正前方(车牌特写)-照片", e0159, true, false, true, false, "无", NOPICEXAMPLE};
	//algItem item0113 = {"0113", true, "车辆识别(车架号)-照片", e0113, true, false, true, false, "无", NOPICEXAMPLE};

    changeAlgVectorByType(&item0167);
    changeAlgVectorByType(&item0322);
    changeAlgVectorByType(&item0348);
    changeAlgVectorByType(&item0202);
    changeAlgVectorByType(&item0124);
    changeAlgVectorByType(&item0123);
	//changeAlgVectorByType(&item0113);

    algItem item0110 = {"0110", true, "行驶证(正面)", e0110, true, false,  true, false, "无", NOPICEXAMPLE };

    addAlgVectorByItem(item0110);
}