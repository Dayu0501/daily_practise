#include "_c_algClass_0214.h"

bool _c_algClass_0214::seekMemberListPointer()
{
    mainPhotoType = e0214;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0214::InParamEdit()
{
    return true;
}

bool _c_algClass_0214::ResultEdit()
{
    return true;
}