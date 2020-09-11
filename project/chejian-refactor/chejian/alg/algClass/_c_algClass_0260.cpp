#ifndef _C_ALGCLASS_0260_CPP
#define _C_ALGCLASS_0260_CPP
#include "_c_algClass_0260.h"

bool _c_algClass_0260::seekMemberListPointer(){
    mainPhotoType = e0260;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0260::ResultEdit(){
    memberItem* pIsBack = baseTool::getMemberItemByName(pResultMemberList,"isBack");
    memberItem* pIsDateValid = baseTool::getMemberItemByName(pResultMemberList,"isDateValid");
     if(pIsBack->value->result)  //身份证反面
     {
         if(pIsDateValid->value->result) //反面是需要有效日期正确
         {
              isError.result = true;
         }
     }

     return true;
}
#endif // _C_ALGCLASS_0260_CPP
