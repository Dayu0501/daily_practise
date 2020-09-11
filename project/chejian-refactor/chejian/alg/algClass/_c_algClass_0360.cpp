#include "_c_algClass_0360.h"
#include "../base/baseTool.h"

bool _c_algClass_0360::seekMemberListPointer()
{
    mainPhotoType = e0360;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;
    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});
    
    return true;
}

void _c_algClass_0360::setAlgIds() {
	algIDs.push_back(alg0324);
}

bool _c_algClass_0360::InParamEdit()
{
	zhiDongLeiXing.inData = "5";
	zhouLeiXing.inData = "2";

    return true;
}

bool _c_algClass_0360::ResultEdit()
{
    return true;
}
