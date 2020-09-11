#include "_c_algClass_0168.h"
#include "../base/baseTool.h"

bool _c_algClass_0168::seekMemberListPointer()
{
    mainPhotoType = e0168;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0168::InParamEdit()
{
    //格式化水印日期
    shuiYinRiQi.inData = baseTool::formatingDate(shuiYinRiQi.inData);

    return true;
}

bool _c_algClass_0168::ResultEdit()
{
    return true;
}
