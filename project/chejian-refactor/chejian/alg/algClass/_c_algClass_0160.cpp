#include "_c_algClass_0160.h"
#include "../base/baseTool.h"

bool _c_algClass_0160::seekMemberListPointer()
{
    mainPhotoType = e0160;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

void _c_algClass_0160::setAlgIds() {
	algIDs.push_back(alg0136);
}

bool _c_algClass_0160::InParamEdit()
{
    std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector,"cheLiangLeiXing");
    if((cllx.find("K2")))
    {
        _algType = alg0156;
        lunTaiGuiGe.inData = baseTool::formatFileNameLunTai(lunTaiGuiGe.inData);

        return true;
    }

    return false;
}

bool _c_algClass_0160::ResultEdit()
{
    return true;
}

std::string _c_algClass_0160::getPhotoName(std::string algcode)
{
	std::string defaultPhotoName = getPhotoBaseName(algcode);

	std::string lunTaiGuiGe = getObjectItemValueByName("lunTaiGuiGe");
	std::string ltgg = GetPhotoAttrValueFileNameLunTaiFormating(lunTaiGuiGe);
	ltgg = GetPhotoAttrValueFileNameFormating(ltgg);

	string result = "_" + ltgg;
	defaultPhotoName += result;

	return defaultPhotoName;
}
