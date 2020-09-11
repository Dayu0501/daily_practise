#include "_c_algClass_0151.h"
#include "../base/baseTool.h"

bool _c_algClass_0151::seekMemberListPointer()
{
    mainPhotoType = e0151;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0151::InParamEdit()
{
    return true;
}

bool _c_algClass_0151::ResultEdit()
{
    return true;
}
