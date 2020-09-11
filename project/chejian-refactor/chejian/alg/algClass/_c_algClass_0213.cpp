#include "_c_algClass_0213.h"

bool _c_algClass_0213::seekMemberListPointer()
{
    mainPhotoType = e0213;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0213::InParamEdit()
{
    return true;
}

bool _c_algClass_0213::ResultEdit()
{
    return true;
}
