#include "_c_algClass_0211.h"

bool _c_algClass_0211::seekMemberListPointer()
{
    mainPhotoType = e0211;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0211::InParamEdit()
{
    return true;
}

bool _c_algClass_0211::ResultEdit()
{
    return true;
}
