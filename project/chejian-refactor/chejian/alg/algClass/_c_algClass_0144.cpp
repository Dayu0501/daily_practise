#include "_c_algClass_0144.h"
#include "../base/baseTool.h"

bool _c_algClass_0144::seekMemberListPointer()
{
    mainPhotoType = e0144;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0144::InParamEdit()
{
    return true;
}

bool _c_algClass_0144::ResultEdit()
{
    //燃料种类为 天然气的车辆不检测气罐
    std::string ranLiangZhongLei = baseTool::getObjectItemValueByName(pAllParamVector, "ranLiangZhongLei");
    if( ranLiangZhongLei == "E")
    {
        baseTool::closeMemberItemWriteResultByName(pResultMemberList,"qiGuan");
    }

    return true;
}
