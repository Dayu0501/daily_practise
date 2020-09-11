#include "_c_algClass_0177.h"
#include "../base/baseTool.h"

bool _c_algClass_0177::seekMemberListPointer()
{
    mainPhotoType = e0177;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

void _c_algClass_0177::setAlgIds() {
	algIDs.push_back(alg0177);
}

bool _c_algClass_0177::InParamEdit()
{
    cityCode.inData = std::to_string((int)_cityType);
    std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector,"cheLiangLeiXing");
    if((cllx.find("K20")) || (cllx.find("K21")) || (cllx.find("K30")) || (cllx.find("K31")) || (cllx.find("K32")) || (cllx.find("K34")) || (cllx.find("K39"))
        || (cllx.find("K40")) || (cllx.find("K41")) || (cllx.find("K42")))
    {
        //_algType = alg0177;
        heDingZaiKeShuZi.inData = "";
        return true;
    }

    return false;
}

bool _c_algClass_0177::ResultEdit()
{

    if(heZaiShiBieJieGuo.OutData != "" && stoi(heZaiShiBieJieGuo.OutData) > 0 )
    {
        heZaiShiBieJieGuo.result = true;
    }

    return true;
}
