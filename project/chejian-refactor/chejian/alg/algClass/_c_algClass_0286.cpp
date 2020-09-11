#include "alg/algClass/_c_algClass_0286.h"

bool _c_algClass_0286::seekMemberListPointer()
{
    mainPhotoType = e0286;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0286::ResultEdit()
{
    checkMemberItemAndSetAllUnOutput("jianYanBaoGao_YiQi");

    return true ;
}
