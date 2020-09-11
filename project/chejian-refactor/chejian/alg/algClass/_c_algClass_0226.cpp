#include "_c_algClass_0226.h"

bool _c_algClass_0226::seekMemberListPointer()
{
    mainPhotoType = e0226;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0226::InParamEdit()
{
    shenFenZhengHao.inData = "";
    heGeZhengHao.inData = "";
    xiaoShouDanWei.inData = "";

    return true;
}

bool _c_algClass_0226::ResultEdit()
{
    return true;
}
