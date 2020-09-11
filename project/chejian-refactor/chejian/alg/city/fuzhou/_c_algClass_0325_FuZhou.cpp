#include "_c_algClass_0325_FuZhou.h"
#include "base/baseTool.h"

bool _c_algClass_0325_FuZhou::subClassLoadNewResultMember()
{
    printf("_c_algClass_0325_FuZhou subClassLoadNewResultMember 111\n");
    _algType = alg0325;

    return true;
}

bool _c_algClass_0325_FuZhou::seekMemberListPointer()
{
    mainPhotoType = e0111;
    subPhotoType = e0110;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}