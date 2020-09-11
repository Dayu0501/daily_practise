#include "_c_algClass_0212_FuYang.h"
#include "base/baseTool.h"

bool _c_algClass_0212_FuYang::seekMemberListPointer()
{
    mainPhotoType = e0228;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0212_FuYang::InParamEdit()
{
    name.inData = "";
    return true;
}

bool _c_algClass_0212_FuYang::ResultEdit()
{
    memberItem* pIsFront = baseTool::getMemberItemByName(pResultMemberList,"isFront");
    memberItem* pIsNameCorrect = baseTool::getMemberItemByName(pResultMemberList,"isNameCorrect");
    if(pIsFront->value->result) //身份证正面
    {
        if(!pIsNameCorrect->value->result) //正面时需要姓名正确
        {
            isError.result = true;
        }      
    }

    memberItem* pIsBack = baseTool::getMemberItemByName(pResultMemberList,"isBack");
    memberItem* pIsDateValid = baseTool::getMemberItemByName(pResultMemberList,"isDateValid");
    if(pIsBack->value->result)  //身份证反面
    {
        if(!pIsDateValid->value->result) //反面是需要有效日期正确
        {
             isError.result = true;
        }
    }

    return true;
}
