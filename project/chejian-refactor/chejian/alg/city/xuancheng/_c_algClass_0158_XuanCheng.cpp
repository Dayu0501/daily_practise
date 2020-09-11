#include "_c_algClass_0158_XuanCheng.h"
#include "../base/baseTool.h"

bool _c_algClass_0158_XuanCheng::ResultEdit()
{
    const std::string strReferTime = "2016-01-01 00:00:00.0";
    std::string cjdjrq = baseTool::getObjectItemValueByName(pAllParamVector,"chuCiDengJiRiQi");

    memberItem* luoSiZuoShang = baseTool::getMemberItemByName(pResultMemberList,"luoSiZuoShang");
    memberItem* luoSiYouShang = baseTool::getMemberItemByName(pResultMemberList,"luoSiYouShang");
    memberItem* luoSiZuoXia   = baseTool::getMemberItemByName(pResultMemberList,"luoSiZuoXia");
    memberItem* luoSiYouXia   = baseTool::getMemberItemByName(pResultMemberList,"luoSiYouXia");
    std::vector<memberItem*> vec_luosi = {luoSiZuoShang,luoSiYouShang,luoSiZuoXia,luoSiYouXia};
    int count = 0; // 记录螺丝通过的个数
    for(size_t i = 0; i < vec_luosi.size(); i ++)
    {
        if(vec_luosi[i]->value->result == true)
        {
            count ++;
        }
    }

    memberItem* luoSi= baseTool::getMemberItemByName(pResultMemberList,"luoSi");
    if(cjdjrq <= strReferTime)  //2016年之前的，需要两颗螺丝判定
    {
        if(count >= 2)
        {
            luoSi->value->result = true;
        }
        else
        {
            luoSi->value->result = false;
        }
        
    } 
    else  //2016年之后的，需要四颗螺丝判定
    {
        if(count == 4)
        {
            luoSi->value->result = true;
        }
        else
        {
            luoSi->value->result = false;
        }
        
    }
    
    return true;
}
