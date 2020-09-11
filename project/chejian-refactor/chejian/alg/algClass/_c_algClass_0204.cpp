#include "_c_algClass_0204.h"
#include "../base/baseTool.h"

bool _c_algClass_0204::seekMemberListPointer()
{
    mainPhotoType = e0204;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    inListVector.push_back({"moTuo",&inMemberList_moTuo});
    resultListVector.push_back({"default",&resultMemberList});
    resultListVector.push_back({"moTuo",&resultMemberList_moTuo});

    return true;
}

bool _c_algClass_0204::InParamEdit()
{
    //格式化检结束时间
    jianYanJieShuShiJian.inData = baseTool::formatingDate(jianYanJieShuShiJian.inData);
    if (baseTool::checkCllxIsMx(pAllParamVector) ){
        pInMemberList = &inMemberList_moTuo ;
        pResultMemberList =&resultMemberList_moTuo ;
    }

    return true;
}

bool _c_algClass_0204::ResultEdit()
{
    //新车不检车牌
    if(baseTool::checkIsNewCar(pAllParamVector))
    {
        chePaiHao.result = true;
    }

    //如果照片清晰度为true 则只输出照片清晰度的错误信息其他信息不输出
    baseTool::checkMemberItemAndSetAllUnOutput(pResultMemberList, baseTool::getMemberItemByName(pResultMemberList,"zhaoPianQingXiDu"));

    return true;
}
