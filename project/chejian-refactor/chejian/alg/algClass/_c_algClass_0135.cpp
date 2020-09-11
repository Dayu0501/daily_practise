#include "_c_algClass_0135.h"
#include "../base/baseTool.h"

bool _c_algClass_0135::seekMemberListPointer()
{
    mainPhotoType = e0135;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0135::InParamEdit()
{
    return true;
}

bool _c_algClass_0135::ResultEdit()
{
    return true;
}
