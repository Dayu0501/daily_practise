#include "_c_algClass_0351.h"
#include "../base/baseTool.h"

bool _c_algClass_0351::seekMemberListPointer()
{
    mainPhotoType = e0351;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

void _c_algClass_0351::setAlgIds() {
	algIDs.push_back(_algType);
	algIDs.push_back(alg0321);
	algIDs.push_back(algShuiYinRiQi);
}

bool _c_algClass_0351::InParamEdit()
{
    shuiYinRiQi.inData = baseTool::formatingDate(shuiYinRiQi.inData);
    zhiDongLeiXing.inData = "2";
    zhouLeiXing.inData = "2";
	
	//获取车辆类型，并判断是否为小车
    std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector, "cheLiangLeiXing");
    if (cllx.substr(0, 2) == "K3" || cllx.substr(0, 2) == "K4")
        cheLiangLeiXing.inData = "1";
    else if (cllx.substr(0, 1) == "M")
        cheLiangLeiXing.inData = "3";
    else
        cheLiangLeiXing.inData = "2";
		
    return true;
}

bool _c_algClass_0351::ResultEdit()
{
	zhiDongDeng.result = !(zuoDeng.result && youDeng.result);

    //新车不检车牌
    if(baseTool::checkIsNewCar(pAllParamVector))
    {
        chePaiHao.result = true;
    }
	
    return true;
}

std::string _c_algClass_0351::getPhotoName(std::string algcode)
{
    std::string defaultPhotoName = getPhotoBaseName(algcode);
	
    std::string jianYanJiGouBianHao = getObjectItemValueByName("jianYanJiGouBianHao");
   std::string jyjgbh = GetPhotoAttrValue(jianYanJiGouBianHao);
   string result =   "_" + jyjgbh;
   defaultPhotoName += result;

   return defaultPhotoName;
}
