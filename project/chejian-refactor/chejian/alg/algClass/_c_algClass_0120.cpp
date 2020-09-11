#include "_c_algClass_0120.h"

bool _c_algClass_0120::seekMemberListPointer()
{
    mainPhotoType = e0120;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0120::InParamEdit()
{
    return true;
}

bool _c_algClass_0120::ResultEdit()
{
    return true;
}
