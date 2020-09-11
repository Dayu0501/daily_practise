#include "_c_algClass_0213_1_HuaiBei.h"
#include "../base/baseTool.h"

bool _c_algClass_0213_1_HuaiBei::subClassLoadNewResultMember()
{
    LOG(ALG, INFO, "_c_algClass_0213_1_HuaiBei::subClassLoadNewResultMember() begin");
    _algType = alg0258;
    return true;
}

bool _c_algClass_0213_1_HuaiBei::seekMemberListPointer()
{
    mainPhotoType = e0213_1;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0213_1_HuaiBei::InParamEdit()
{
    return true;
}

bool _c_algClass_0213_1_HuaiBei::ResultEdit()
{
    LOG(ALG, INFO, "_c_algClass_0213_1_HuaiBei::ResultEdit() begin");

    memberItem* chePaiHao = baseTool::getMemberItemByName(pResultMemberList, "chePaiHao");
    if (NULL != chePaiHao)
        LOG(ALG, INFO, "_c_algClass_0213_1_HuaiBei::ResultEdit() chePaiHao: %d", chePaiHao->value->result);
 
    memberItem* cheJiaHao = baseTool::getMemberItemByName(pResultMemberList, "cheJiaHao");
    if (NULL != cheJiaHao)
        LOG(ALG, INFO, "_c_algClass_0213_1_HuaiBei::ResultEdit() cheJiaHao: %d", cheJiaHao->value->result);

    return true;
}
