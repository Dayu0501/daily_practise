#include "_c_algClass_0219.h"
#include "../base/baseTool.h"

bool _c_algClass_0219::seekMemberListPointer()
{
    mainPhotoType = e0219;
    
    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0219::InParamEdit()
{
    return true;
}

bool _c_algClass_0219::ResultEdit()
{
    return true;
}
