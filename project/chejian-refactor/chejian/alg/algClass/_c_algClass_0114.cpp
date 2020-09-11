#include "_c_algClass_0114.h"
#include "../base/baseTool.h"

bool _c_algClass_0114::seekMemberListPointer()
{
    mainPhotoType = e0114;
    _algType      = alg0114;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

//bool _c_algClass_0114::InParamEdit()
//{
//    return true;
//}

//bool _c_algClass_0114::ResultEdit()
//{
//    return true;
//}
