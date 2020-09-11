#include "_c_algClass_0186.h"
#include "../base/baseTool.h"

bool _c_algClass_0186::seekMemberListPointer()
{
    mainPhotoType = e0186;
    
    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0186::InParamEdit()
{
    return true;
}

bool _c_algClass_0186::ResultEdit()
{
    return true;
}
