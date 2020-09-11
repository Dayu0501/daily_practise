#include "_c_algClass_0158.h"
#include "../base/baseTool.h"

bool _c_algClass_0158::seekMemberListPointer()
{
    mainPhotoType = e0158;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0158::InParamEdit()
{
    return true;
}

bool _c_algClass_0158::ResultEdit()
{
	//螺丝数量正确与否，需要根据城市具体判定
    return true;
}
