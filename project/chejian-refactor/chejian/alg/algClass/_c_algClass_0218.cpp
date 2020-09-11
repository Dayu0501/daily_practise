#include "_c_algClass_0218.h"
#include "../base/baseTool.h"

bool _c_algClass_0218::seekMemberListPointer()
{
    mainPhotoType = e0218;
    
    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0218::InParamEdit()
{
    return true;
}

bool _c_algClass_0218::ResultEdit()
{
    return true;
}

std::string _c_algClass_0218::getPhotoName(std::string algcode)
{
    std::string defaultPhotoName = getPhotoBaseName(algcode);
   std::string faDongJiHao = getObjectItemValueByName("faDongJiHao");
   std::string cheLiangXingHao = getObjectItemValueByName("cheLiangXingHao");
   std::string faDongJiXingHao = getObjectItemValueByName("faDongJiXingHao");
   std::string lunTaiGuiGe = getObjectItemValueByName("lunTaiGuiGe");
   std::string ranLiangZhongLei = getObjectItemValueByName("ranLiangZhongLei");
   std::string fdjh = GetPhotoAttrValueFileNameFormating(faDongJiHao);
   std::string clxh = GetPhotoAttrValueFileNameFormating(cheLiangXingHao);
   std::string fdjxh = GetPhotoAttrValueFileNameFormating(faDongJiXingHao);
   std::string ltgg = GetPhotoAttrValueFileNameLunTaiFormating(lunTaiGuiGe);
   std::string rlzl =  GetPhotoAttrValueFileNameFormating(ranLiangZhongLei);
   string result =  "_" + rlzl +"_" + ltgg + "_" + fdjxh + "_" + fdjh + "_" + clxh;
   defaultPhotoName += result ;

   return defaultPhotoName;
}
