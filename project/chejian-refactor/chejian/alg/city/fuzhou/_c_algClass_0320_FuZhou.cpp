#include "_c_algClass_0320_FuZhou.h"
#include "base/baseTool.h"

_c_algClass_0320_FuZhou::_c_algClass_0320_FuZhou() {
    printf("_c_algClass_0320_FuZhou subClassLoadNewResultMember 111\n");
}

bool _c_algClass_0320_FuZhou::subClassLoadNewResultMember()
{
    printf("_c_algClass_0320_FuZhou subClassLoadNewResultMember 111\n");
    _algType = alg0321;

    return true;
}

bool _c_algClass_0320_FuZhou::seekMemberListPointer()
{
    mainPhotoType = eH3020;
//    subPhotoType = e0167;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0320_FuZhou::InParamEdit() {
    printf("_c_algClass_0320_FuZhou :: %s 111\n", __PRETTY_FUNCTION__);

    cheLiangLeiXing.inData = "1";
    return true;
}

