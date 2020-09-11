#include "_c_algClass_0121.h"

bool _c_algClass_0121::seekMemberListPointer()
{
    mainPhotoType = e0121;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0121::InParamEdit()
{
    labelName.inData = "yingjichui";

    return true;
}

bool _c_algClass_0121::ResultEdit()
{
    return true;
}
