#include "_c_algClass_0123.h"
#include "base/baseTool.h"

bool _c_algClass_0123::seekMemberListPointer()
{
    mainPhotoType = e0123;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0123::InParamEdit()
{
    zhiDongLeiXing.inData = "5";
    zhouLeiXing.inData = "2";
    std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector, "cheLiangLeiXing");
    if (cllx.substr(0, 2) == "K3" || cllx.substr(0, 2) == "K4")
        cheLiangLeiXing.inData = "1";
    else if (cllx.substr(0, 1)=="M")//摩托
        cheLiangLeiXing.inData = "3";
    else
        cheLiangLeiXing.inData = "2";

    return true;
}

bool _c_algClass_0123::ResultEdit()
{
    return true;
}
