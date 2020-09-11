#include "_c_algClass_0155.h"
#include "../base/baseTool.h"

bool _c_algClass_0155::seekMemberListPointer()
{
    mainPhotoType = e0155;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

void _c_algClass_0155::setAlgIds() {
	algIDs.push_back(alg0156);
}

bool _c_algClass_0155::InParamEdit()
{
    std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector,"cheLiangLeiXing");
    if((cllx.find("K2")))
    {
        lunTaiGuiGe.inData = baseTool::formatFileNameLunTai(lunTaiGuiGe.inData);

        return true;
    }

    return false;
}

bool _c_algClass_0155::ResultEdit()
{
    return true;
}

std::string _c_algClass_0155::getPhotoName(std::string algcode)
{
	std::string defaultPhotoName = getPhotoBaseName(algcode);

	std::string lunTaiGuiGe = getObjectItemValueByName("lunTaiGuiGe");
	std::string ltgg = GetPhotoAttrValueFileNameLunTaiFormating(lunTaiGuiGe);
	ltgg = GetPhotoAttrValueFileNameFormating(ltgg);

	string result = "_" + ltgg;
	defaultPhotoName += result;

	return defaultPhotoName;
}
