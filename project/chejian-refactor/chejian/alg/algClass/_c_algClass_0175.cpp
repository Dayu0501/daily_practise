#include "_c_algClass_0175.h"
#include "../base/baseTool.h"

bool _c_algClass_0175::seekMemberListPointer()
{
    mainPhotoType = e0175;
    subPhotoType = eCLZQFXS45DZP_A;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"xiaoChe",&resultMemberList});

    return true;
}

bool _c_algClass_0175::InParamEdit()
{
    paiSheJiaoDu.inData = "3";
    //档案照片默认为false
    dangAnZhaoPian.result = false;
	dangAnZhaoPian.result = false;
	_c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector, baseTool::getAlgItemCodeByPicType(subPhotoType, pAllAlgItemVector));
	if(algTask)
	{
		dangAnZhaoPian.result = true;
	}

    return true;
}

bool _c_algClass_0175::ResultEdit()
{
    //如果广告返回值<=1 判定为true 否则为false
    if(atoi(guangGao.OutData.c_str()) <= 1)
    {
        guangGao.result = true;
    }

    if(dangAnZhaoPian.result)
    {
        baseTool::openMemberItemWriteResultByName(pResultMemberList,"cheLiangYanSe");
    }

    return true;
}
std::string _c_algClass_0175::getPhotoName(std::string algcode)
{
    std::string defaultPhotoName = getPhotoBaseName(algcode);


   string result = "";
   std::string zongZhiLiang = getObjectItemValueByName("zongZhiLiang");
   std::string huoXiangNeiBuGaoDu = getObjectItemValueByName("huoXiangNeiBuGaoDu");
   std::string heDingZaiKe = getObjectItemValueByName("heDingZaiKeShu");

   std::string zzl = GetPhotoAttrValue(zongZhiLiang);
   std::string hxnbgd = GetPhotoAttrValue(huoXiangNeiBuGaoDu);
   std::string  hdzk = GetPhotoAttrValue(heDingZaiKe);

   result += "_" + zzl + "_" + hxnbgd + "_" + hdzk ;

   std::string cheLiangPinPai = getObjectItemValueByName("cheLiangPinPai");
   std::string cheLiangXingHao = getObjectItemValueByName("cheLiangXingHao");
   std::string cheShenYanSe = getObjectItemValueByName("cheLiangYanSe");

   std::string clpp = GetPhotoAttrValue(cheLiangPinPai);
   std::string clxh = GetPhotoAttrValueFileNameFormating(cheLiangXingHao);
   std::string csys = GetPhotoAttrValue(cheShenYanSe);

   result +=  "_" + clxh + "_" +  "_" + csys + "_" + clpp;
   defaultPhotoName += result ;

   return defaultPhotoName;
}
