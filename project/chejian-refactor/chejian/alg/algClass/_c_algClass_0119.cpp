#include "_c_algClass_0119.h"
#include "base/baseTool.h"
bool _c_algClass_0119::seekMemberListPointer()
{
    mainPhotoType = e0119;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0119::InParamEdit()
{
    return true;
}

bool _c_algClass_0119::ResultEdit()
{
    return true;
}

std::string _c_algClass_0119::getPhotoName(std::string algcode)
{
	std::string defaultPhotoName = getPhotoBaseName(algcode);

	std::string faDongJiHao = getObjectItemValueByName("faDongJiHao");
	std::string fdjh = GetPhotoAttrValueFileNameFormating(faDongJiHao);
	string result = "_" + fdjh;
	defaultPhotoName += result;

	return defaultPhotoName;
}
