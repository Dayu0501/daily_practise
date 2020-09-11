#include "_c_algClass_0166.h"
#include "./base/baseTool.h"

bool _c_algClass_0166::seekMemberListPointer()
{
    mainPhotoType = e0166;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"keChe",&inMemberList});
    resultListVector.push_back({"keChe",&resultMemberList});

    return true;
}

bool _c_algClass_0166::InParamEdit()
{
    return true;
}

bool _c_algClass_0166::ResultEdit()
{
    baseTool::openMemberItemWriteResultByName(&resultMemberList,"gaiZhuang");
    baseTool::openMemberItemWriteResultByName(&resultMemberList,"zuoWeiShu");
    baseTool::openMemberItemWriteResultByName(&resultMemberList,"anQuanDai");

    return true;
}
std::string _c_algClass_0166::getPhotoName(std::string algcode)
{
    std::string defaultPhotoName = getPhotoBaseName(algcode);


   std::string heDingZaiKe = getObjectItemValueByName("heDingZaiKeShu");
   std::string  hdzk = GetPhotoAttrValue(heDingZaiKe);
   string result =  "_" + hdzk + "_" ;
   defaultPhotoName += result ;

   return defaultPhotoName;
}
