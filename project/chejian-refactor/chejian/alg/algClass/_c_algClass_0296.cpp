#include "_c_algClass_0296.h"
#include "../base/baseTool.h"

bool _c_algClass_0296::seekMemberListPointer()
{
    mainPhotoType = e0296;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0296::InParamEdit()
{
    //格式化发证日期
    faZhengRiQi.inData = baseTool::formatingDate(faZhengRiQi.inData);

    return true;
}

bool _c_algClass_0296::ResultEdit()
{
    return true;
}
