#include "_c_algClass_0122.h"

bool _c_algClass_0122::seekMemberListPointer()
{
    mainPhotoType = e0122;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0122::InParamEdit()
{
    return true;
}

bool _c_algClass_0122::ResultEdit()
{
    return true;
}
