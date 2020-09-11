#include "_c_algClass_0221.h"

bool _c_algClass_0221::seekMemberListPointer()
{
    mainPhotoType = e0221;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

void _c_algClass_0221::setAlgIds() {
	algIDs.push_back(alg0202);
}

bool _c_algClass_0221::InParamEdit()
{
	yeWuLeiXing.inData = "G";

    return true;
}

bool _c_algClass_0221::ResultEdit()
{
	diYaQuanRen.result = !diYaQuanRen.OutData.empty();

    return true;
}
