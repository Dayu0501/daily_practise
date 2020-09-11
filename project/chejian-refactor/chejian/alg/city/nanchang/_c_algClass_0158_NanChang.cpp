#include "_c_algClass_0158_NanChang.h"
#include "../base/baseTool.h"


bool _c_algClass_0158_NanChang::seekMemberListPointer()
{
    mainPhotoType = e0158;
//    subPhotoType = e0112;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0158_NanChang::InParamEdit()
{
    _algType = alg0112;
    return true;
}

bool _c_algClass_0158_NanChang::ResultEdit()
{
    return true;
}
