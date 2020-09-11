#include "_c_algClass_0159.h"
#include "../base/baseTool.h"

bool _c_algClass_0159::seekMemberListPointer()
{
    mainPhotoType = e0159;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0159::InParamEdit()
{
    return true;
}

bool _c_algClass_0159::ResultEdit()
{
	//螺丝数量正确与否，需要根据城市具体判定
    return true;
}
