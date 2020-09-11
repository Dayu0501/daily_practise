#include "_c_algClass_0199_NanChong.h"
#include "../base/baseTool.h"

bool _c_algClass_0199_NanChong::seekMemberListPointer() {
    mainPhotoType = eH0199;
    subPhotoType = eCLSBDHZP_TYM;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default", &inMemberList});
    inListVector.push_back({"moTuo", &inMemberList_moTuo});


    resultListVector.push_back({"default", &resultMemberList});
    resultListVector.push_back({"moTuo", &resultMemberList_moTuo});

    return true;
}

bool _c_algClass_0199_NanChong::subClassLoadNewResultMember()
{
    printf("_c_algClass_0199_NanChong subClassLoadNewResultMember 111\n");

    algIDs.clear();
    algIDs.push_back(alg0113);

    return true;
}

