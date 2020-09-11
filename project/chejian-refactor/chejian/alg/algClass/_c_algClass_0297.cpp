#include "_c_algClass_0297.h"
#include "../base/baseTool.h"

bool _c_algClass_0297::seekMemberListPointer()
{
    mainPhotoType = e0297;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;
    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

void _c_algClass_0297::setAlgIds() {
	algIDs.push_back(alg0297);
    algIDs.push_back(alg0113);
}

bool _c_algClass_0297::InParamEdit()
{
    jianYanJieShuShiJian.inData = dangTianRiQi.inData = baseTool::formatingDate(jianYanJieShuShiJian.inData);

    return true;
}

bool _c_algClass_0297::ResultEdit()
{
    //获取初次登记日期
    std::string cjdjrq = baseTool::getObjectItemValueByName(pAllParamVector,"chuCiDengJiRiQi");
    //如果车辆等级时间 > 10 年 则将 引车检验员 和 地盘检验员输出开启
    if(baseTool::isTenYears(cjdjrq))
    {
        baseTool::changeCheckAlgBaseParamElementByName(pResultMemberList, "qianZi_yinCheJianYanYuan", "", true);
        baseTool::changeCheckAlgBaseParamElementByName(pResultMemberList, "qianZi_diPanJianYanYuan", "", true);
    }

    return true;
}
