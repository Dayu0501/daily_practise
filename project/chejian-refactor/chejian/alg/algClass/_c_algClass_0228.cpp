#include "_c_algClass_0228.h"
#include "base/baseTool.h"

bool _c_algClass_0228::seekMemberListPointer()
{
    mainPhotoType = e0228;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0228::InParamEdit()
{
    name.inData = "";

    return true;
}

bool _c_algClass_0228::ResultEdit()
{
    memberItem* pIsFront = baseTool::getMemberItemByName(pResultMemberList,"isFront");
    memberItem* pIsBack = baseTool::getMemberItemByName(pResultMemberList,"isBack");
    if(pIsFront->value->result || pIsBack->value->result) //不是正面，也不是反面，判定不是身份证
    {
        isError.result =true ;
    }

    return true;
}
