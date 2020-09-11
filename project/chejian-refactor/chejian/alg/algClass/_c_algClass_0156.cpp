#include "_c_algClass_0156.h"
#include "../base/baseTool.h"

bool _c_algClass_0156::seekMemberListPointer()
{
    mainPhotoType = e0156;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0156::InParamEdit()
{
    lunTaiGuiGe.inData=baseTool::formatFileNameLunTai(lunTaiGuiGe.inData);

    return true;
}

bool _c_algClass_0156::ResultEdit()
{
    return true;
}

std::string _c_algClass_0156::getPhotoName(std::string algcode)
{
    std::string defaultPhotoName = getPhotoBaseName(algcode);


   std::string lunTaiGuiGe = getObjectItemValueByName("lunTaiGuiGe");
   std::string ltgg = GetPhotoAttrValueFileNameLunTaiFormating(lunTaiGuiGe);
   ltgg = GetPhotoAttrValueFileNameFormating(ltgg);

   string result =  "_" + ltgg;
   defaultPhotoName += result;

   return defaultPhotoName;
}
