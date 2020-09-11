#include "_c_algClass_0208.h"

bool _c_algClass_0208::seekMemberListPointer()
{
    mainPhotoType = e0208;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0208::InParamEdit()
{
    wenJianBiaoQian.inData = "道路交通安全承诺书";

    return true;
}

bool _c_algClass_0208::ResultEdit()
{
    checkMemberItemAndSetAllUnOutput("youXiaoZhengJian");

    return true;
}
