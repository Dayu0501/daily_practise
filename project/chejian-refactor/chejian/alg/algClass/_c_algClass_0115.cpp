#include "_c_algClass_0115.h"
#include "../base/baseTool.h"

bool _c_algClass_0115::seekMemberListPointer()
{
    mainPhotoType = e0115;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"keChe",&inMemberList});
    inListVector.push_back({"huoChe",&inMemberList_huoChe});

    resultListVector.push_back({"keChe",&resultMemberList});
    resultListVector.push_back({"huoChe",&resultMemberList_huoChe});

    return true;
}

void _c_algClass_0115::setAlgIds() {
	algIDs.push_back(_algType);
}

bool _c_algClass_0115::InParamEdit()
{
    std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector,"cheLiangLeiXing");
    if((cllx.substr(0, 1)=="H"))
    {
        pInMemberList = &inMemberList_huoChe;
        pResultMemberList = &resultMemberList_huoChe;
    }
    else if((cllx.substr(0, 1)=="K"))
    {

    }else {
        buZaiJianCeFanWei.result = false;
        _algType = alg0115_dache;
    }

    return true;
}

bool _c_algClass_0115::ResultEdit()
{
    std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector,"cheLiangLeiXing");
    if((cllx.substr(0, 1)=="H"))
    {
        if(cllx.substr(2, 1) == "2")
        {
            baseTool::openMemberItemWriteResultByName(&resultMemberList_huoChe,"gaiZhuang_Kx2");
        }
        if(cllx.substr(2, 1) == "9")
        {
            baseTool::openMemberItemWriteResultByName(&resultMemberList_huoChe,"gaiZhuang_Kx9");
        }
    }
    else if((cllx.find("K39")))
    {
        baseTool::openMemberItemWriteResultByName(&resultMemberList,"cheXiangGaiZhuang");
        baseTool::openMemberItemWriteResultByName(&resultMemberList,"zuoWeiShu");
    }

    return true;
}
std::string _c_algClass_0115::getPhotoName(std::string algcode)
{
    std::string defaultPhotoName = getPhotoBaseName(algcode);

   std::string heDingZaiKe = getObjectItemValueByName("heDingZaiKeShu");
   std::string  hdzk = GetPhotoAttrValue(heDingZaiKe);
   string result =  "_" + hdzk + "_" ;
   defaultPhotoName += result ;

   return defaultPhotoName;
}
