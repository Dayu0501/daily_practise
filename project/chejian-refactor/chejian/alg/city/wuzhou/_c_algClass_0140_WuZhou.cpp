#include "_c_algClass_0140_WuZhou.h"
#include "../base/baseTool.h"

bool _c_algClass_0140_WuZhou::seekMemberListPointer()
{
    mainPhotoType = e0140;
//    subPhotoType = eCLZQFXS45DZP_A;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0140_WuZhou::InParamEdit()
{
    labelName.inData = "taban";
    setAlgType(alg0121);
    return true;
}
