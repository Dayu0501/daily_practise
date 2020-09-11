#include "_c_algClass_0225.h"

bool _c_algClass_0225::seekMemberListPointer()
{
    mainPhotoType = e0225;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0225::InParamEdit()
{
    return true;
}

bool _c_algClass_0225::ResultEdit()
{
    return true;
}
