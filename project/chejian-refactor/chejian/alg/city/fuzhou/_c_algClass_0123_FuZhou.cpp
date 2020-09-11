#include "_c_algClass_0123_FuZhou.h"
#include "../base/baseTool.h"

bool _c_algClass_0123_FuZhou::ResultEdit() {
    printf("*****%s \n", __PRETTY_FUNCTION__);

    const std::string strReferTime = "2016-03-01 00:00:00.0";
    std::string cjdjrq = baseTool::getObjectItemValueByName(pAllParamVector, "chuCiDengJiRiQi");

    memberItem *luoSiZuoShang = baseTool::getMemberItemByName(pResultMemberList, "luoSiZuoShang");
    memberItem *luoSiYouShang = baseTool::getMemberItemByName(pResultMemberList, "luoSiYouShang");
    memberItem *luoSiZuoXia = baseTool::getMemberItemByName(pResultMemberList, "luoSiZuoXia");
    memberItem *luoSiYouXia = baseTool::getMemberItemByName(pResultMemberList, "luoSiYouXia");
    std::vector<memberItem *> vec_luosi = {luoSiZuoShang, luoSiYouShang, luoSiZuoXia, luoSiYouXia};
    int count = 0; // 记录螺丝通过的个数
    for (auto & i : vec_luosi) {
        if (i->value->result)   count++;
    }

    memberItem *luoSi = baseTool::getMemberItemByName(pResultMemberList, "luoSi");
    if (cjdjrq <= strReferTime)    luoSi->value->result = count >= 2; //2016年3月之前的，需要两颗螺丝判定
    else    luoSi->value->result = count == 4; //2016年3月之后的，需要四颗螺丝判定

    printf("_mainPhoto is %s\n", _mainPhoto.c_str());
    printf("_c_algClass_0123_FuZhou chuCiDengJiRiQi is %s, count = %d, result is %d \n", cjdjrq.c_str(), count, luoSi->value->result);

    return true;
}
