#include "_c_algClass_0215.h"

bool _c_algClass_0215::seekMemberListPointer()
{
    mainPhotoType = e0215;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0215::InParamEdit()
{
    return true;
}

bool _c_algClass_0215::ResultEdit()
{
    return true;
}
