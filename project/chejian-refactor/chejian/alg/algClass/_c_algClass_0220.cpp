#include "_c_algClass_0220.h"

bool _c_algClass_0220::seekMemberListPointer()
{
    mainPhotoType = e0220;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0220::InParamEdit()
{
    return true;
}

bool _c_algClass_0220::ResultEdit()
{
    return true;
}
