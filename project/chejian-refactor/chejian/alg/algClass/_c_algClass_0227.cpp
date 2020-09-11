#include "_c_algClass_0227.h"

bool _c_algClass_0227::seekMemberListPointer()
{
    mainPhotoType = e0227;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0227::InParamEdit()
{
    return true;
}

bool _c_algClass_0227::ResultEdit()
{
    return true;
}
