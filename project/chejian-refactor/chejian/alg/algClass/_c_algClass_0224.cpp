#include "_c_algClass_0224.h"

bool _c_algClass_0224::seekMemberListPointer()
{
    mainPhotoType = e0224;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0224::InParamEdit()
{
    return true;
}

bool _c_algClass_0224::ResultEdit()
{
    return true;
}
