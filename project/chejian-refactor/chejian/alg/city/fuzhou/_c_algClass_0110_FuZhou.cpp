#include "_c_algClass_0110_FuZhou.h"
#include "base/baseTool.h"

_c_algClass_0110_FuZhou::_c_algClass_0110_FuZhou() {
    resultMemberList.push_back({"cheLiangYiZhi", "与左前方照片车辆不一致", &cheLiangYiZhi, true, CONFIG_DEFAULT});
	resultMemberList.push_back({"yanSe", "颜色不一致", &yanSe, false, CONFIG_DEFAULT});
	resultMemberList.push_back({"xingHao", "型号不一致", &xingHao, false, CONFIG_DEFAULT});
}

bool _c_algClass_0110_FuZhou::subClassLoadNewResultMember()
{
    printf("_c_algClass_0110_FuZhou subClassLoadNewResultMember 111\n");
    _algType = alg0201;

    return true;
}

void _c_algClass_0110_FuZhou::setAlgIds() {
	algIDs.push_back(_algType);
	algIDs.push_back(alg0325);
}

bool _c_algClass_0110_FuZhou::seekMemberListPointer()
{
    mainPhotoType = e0110;
    subPhotoType = e0111;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}
bool _c_algClass_0110_FuZhou::ResultEdit() {
	_c_algClass_0287::ResultEdit();

	cheLiangYiZhi.result = yanSe.result && xingHao.result;
}