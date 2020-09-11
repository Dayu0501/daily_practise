#include "_c_algClass_0222.h"

bool _c_algClass_0222::seekMemberListPointer()
{
    mainPhotoType = e0222;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0222::InParamEdit()
{
    return true;
}

bool _c_algClass_0222::ResultEdit()
{
    return true;
}
