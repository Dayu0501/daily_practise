#include "_c_algClass_0167.h"
#include "../base/baseTool.h"

bool _c_algClass_0167::seekMemberListPointer()
{
    mainPhotoType = e0167;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0167::InParamEdit()
{
    paiSheJiaoDu.inData = "2";
    //格式化水印日期
    shuiYinRiQi.inData = baseTool::formatingDate(shuiYinRiQi.inData);

    return true;
}

bool _c_algClass_0167::ResultEdit()
{
    return true;
}
