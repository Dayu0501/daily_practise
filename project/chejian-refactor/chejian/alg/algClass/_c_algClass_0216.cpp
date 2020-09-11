#include "_c_algClass_0216.h"
#include "../base/baseTool.h"

bool _c_algClass_0216::seekMemberListPointer()
{
    mainPhotoType = e0216;
    
    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0216::InParamEdit()
{
    return true;
}

bool _c_algClass_0216::ResultEdit()
{
    return true;
}
