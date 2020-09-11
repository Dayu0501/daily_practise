#include "_c_algClass_0234.h"
#include "../base/baseTool.h"

bool _c_algClass_0234::seekMemberListPointer()
{
    mainPhotoType = e0234;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

void _c_algClass_0234::setAlgIds() {
	algIDs.push_back(alg0208);
}

bool _c_algClass_0234::InParamEdit()
{
    //_algType = alg0208;
    wenJianBiaoQian.inData = "定期检验告知书";
    chengShiDaiMa.inData = std::to_string((int)_cityType);

    return true;
}

bool _c_algClass_0234::ResultEdit()
{
    suoYouRenQianMing.result = suoYouRenQianMing.result | qianZi.result;
    jianCeJiGouQianMing.result = jianCeJiGouQianMing.result | qianZi.result;

    return true;
}
