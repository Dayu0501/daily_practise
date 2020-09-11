#include "_c_algClass_0158_HuaiBei.h"
#include "../base/baseTool.h"

bool _c_algClass_0158_HuaiBei::ResultEdit()
{
    LOG(ALG, INFO, "_c_algClass_0158_HuaiBei::ResultEdit() begin");
    memberItem* luoSiZuoShang = baseTool::getMemberItemByName(pResultMemberList,"luoSiZuoShang");
    memberItem* luoSiYouShang = baseTool::getMemberItemByName(pResultMemberList,"luoSiYouShang");
    memberItem* luoSiZuoXia   = baseTool::getMemberItemByName(pResultMemberList,"luoSiZuoXia");
    memberItem* luoSiYouXia   = baseTool::getMemberItemByName(pResultMemberList,"luoSiYouXia");
    std::vector<memberItem*> vec_luosi = {luoSiZuoShang,luoSiYouShang,luoSiZuoXia,luoSiYouXia};
    int luosi_count = 0; //统计螺丝个数
    for (size_t i = 0; i < vec_luosi.size(); i++)
    {
        LOG(ALG, INFO, "_c_algClass_0158_HuaiBei::ResultEdit() result[%d]: %d", i, vec_luosi[i]->value->result);
        if (vec_luosi[i]->value->result)
            luosi_count++;
    }

    memberItem* luoSi= baseTool::getMemberItemByName(pResultMemberList,"luoSi");
    std::string chuCiDengJiRiQi = baseTool::getObjectItemValueByName(pAllParamVector, "chuCiDengJiRiQi");
    const string begin_date = "2016-03-01 00:00:00.0";
    if (chuCiDengJiRiQi < begin_date)
    {   //需2颗螺丝
        LOG(ALG, INFO, "_c_algClass_0158_HuaiBei::ResultEdit() < begin_date");
        if (luosi_count >= 2)
            luoSi->value->result = true;
        else
            luoSi->value->result = false;
    } 
    else
    {   //需4颗螺丝
        LOG(ALG, INFO, "_c_algClass_0158_HuaiBei::ResultEdit() >= begin_date");
        if (luosi_count >= 4)
            luoSi->value->result = true;
        else
            luoSi->value->result = false;
    }
    
    LOG(ALG, INFO, "_c_algClass_0158_HuaiBei::ResultEdit() chuCiDengJiRiQi: %s, begin_date: %s", chuCiDengJiRiQi.c_str(), begin_date.c_str());
    LOG(ALG, INFO, "_c_algClass_0158_HuaiBei::ResultEdit() luosi_count: %d, result: %d", luosi_count, luoSi->value->result);
    return true;
}
