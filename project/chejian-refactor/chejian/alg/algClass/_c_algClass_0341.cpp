#include "_c_algClass_0341.h"
#include "base/baseTool.h"
bool _c_algClass_0341::seekMemberListPointer()
{
    mainPhotoType = e0343;
    subPhotoType  = e0341;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;
    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

void _c_algClass_0341::setAlgIds() {
	algIDs.push_back(alg0344);
}

bool _c_algClass_0341::InParamEdit()
{
    return false;
}

bool _c_algClass_0341::ResultEdit()
{
    return true;
}
