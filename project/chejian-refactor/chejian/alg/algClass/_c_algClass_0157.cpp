#include "_c_algClass_0157.h"
#include "../base/baseTool.h"

bool _c_algClass_0157::seekMemberListPointer()
{
    mainPhotoType = e0157;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

void _c_algClass_0157::setAlgIds() {
	algIDs.push_back(_algType);
	algIDs.push_back(algShuiYinRiQi);
}

bool _c_algClass_0157::InParamEdit()
{
    //格式化检验结束时间
    jianYanJieShuShiJian.inData = baseTool::formatingDate(jianYanJieShuShiJian.inData);

    return true;
}

bool _c_algClass_0157::ResultEdit()
{
    //判断检验结束时间是否正确
    if (baseTool::compareDate(jianYanJieShuShiJian.inData, jianYanJieShuShiJian.OutData)) {
        jianYanJieShuShiJian.result = true;
    }

    return true;
}
