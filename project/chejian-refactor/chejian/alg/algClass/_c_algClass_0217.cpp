#include "_c_algClass_0217.h"

bool _c_algClass_0217::seekMemberListPointer()
{
    mainPhotoType = e0217;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0217::InParamEdit()
{
    return true;
}

bool _c_algClass_0217::ResultEdit()
{
    return true;
}
