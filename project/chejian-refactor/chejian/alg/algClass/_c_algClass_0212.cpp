#include "_c_algClass_0212.h"

bool _c_algClass_0212::seekMemberListPointer()
{
    mainPhotoType = e0212;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0212::InParamEdit()
{
    return true;
}

bool _c_algClass_0212::ResultEdit()
{
    return true;
}
