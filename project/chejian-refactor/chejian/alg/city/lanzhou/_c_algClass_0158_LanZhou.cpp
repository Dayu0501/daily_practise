#include "_c_algClass_0158_LanZhou.h"
#include "../base/baseTool.h"

bool _c_algClass_0158_LanZhou::ResultEdit()
{
    const std::string strReferTime1 = "2013-03-01 00:00:00.0"; //13年3月1日以后螺丝为两个，16年3月1日以后螺丝为四个
    const std::string strReferTime2 = "2016-03-01 00:00:00.0";
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
    if(cjdjrq >= strReferTime2)  //16年3月1日以后螺丝为四个
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
    else if(cjdjrq >= strReferTime1)  //13年3月1日以后螺丝为两个
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
    else
    {
        luoSi->value->result = true;
    }
     
    
    
    return true;
}
