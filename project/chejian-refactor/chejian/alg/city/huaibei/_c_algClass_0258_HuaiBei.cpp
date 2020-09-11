#include "_c_algClass_0258_HuaiBei.h"
#include "../base/baseTool.h"

bool _c_algClass_0258_HuaiBei::subClassLoadNewResultMember()
{
    LOG(ALG, INFO, "_c_algClass_0258_HuaiBei::subClassLoadNewResultMember() begin");
    _algType = alg0258;
    return true;
}

bool _c_algClass_0258_HuaiBei::seekMemberListPointer()
{
    mainPhotoType = e0258;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({ "default",&inMemberList });
    resultListVector.push_back({ "default",&resultMemberList });

    return true;
}

bool _c_algClass_0258_HuaiBei::InParamEdit()
{
    return true;
}

bool _c_algClass_0258_HuaiBei::ResultEdit()
{
    LOG(ALG, INFO, "_c_algClass_0258_HuaiBei::ResultEdit() begin");
    //车牌号不正确
    memberItem* chePaiHao = baseTool::getMemberItemByName(pResultMemberList, "chePaiHao");
    if (NULL != chePaiHao)
        LOG(ALG, INFO, "_c_algClass_0258_HuaiBei::ResultEdit() chePaiHao: %d", chePaiHao->value->result);

    //车架号不正确
    memberItem* cheJiaHao = baseTool::getMemberItemByName(pResultMemberList, "cheJiaHao");
    if (NULL != cheJiaHao)
        LOG(ALG, INFO, "_c_algClass_0258_HuaiBei::ResultEdit() cheJiaHao: %d", cheJiaHao->value->result);

    //发动机号不正确
    memberItem* faDongJiHao = baseTool::getMemberItemByName(pResultMemberList, "faDongJiHao");
    if (NULL != faDongJiHao)
        LOG(ALG, INFO, "_c_algClass_0258_HuaiBei::ResultEdit() faDongJiHao: %d", faDongJiHao->value->result);

    //检验结论是否合格
    memberItem* jianYanHeGe = baseTool::getMemberItemByName(pResultMemberList, "jianYanHeGe");
    if (NULL != jianYanHeGe)
        LOG(ALG, INFO, "_c_algClass_0258_HuaiBei::ResultEdit() jianYanHeGe: %d", jianYanHeGe->value->result);

    //检验日期是否正确
    memberItem* jianYanRiQi = baseTool::getMemberItemByName(pResultMemberList, "jianYanRiQi");
    if (NULL != jianYanRiQi)
        LOG(ALG, INFO, "_c_algClass_0258_HuaiBei::ResultEdit() jianYanRiQi: %d", jianYanRiQi->value->result);

    return true;
}
