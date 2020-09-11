#include "_c_algClass_0223.h"

bool _c_algClass_0223::seekMemberListPointer()
{
    mainPhotoType = e0223;
    subPhotoType = e0287;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0223::InParamEdit()
{
    return true;
}

bool _c_algClass_0223::ResultEdit()
{
    return true;
}
