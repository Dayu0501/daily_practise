#include "_c_algClass_0321_XuanCheng.h"
#include "base/baseTool.h"

bool _c_algClass_0321_XuanCheng::ResultEdit()
{
    //获取左灯1、2的 memberitem
    memberItem *pZuoDeng1 = baseTool::getMemberItemByName(pResultMemberList,"zuoDeng1");
    memberItem *pZuoDeng2 = baseTool::getMemberItemByName(pResultMemberList,"zuoDeng2");

    bool all_result = pZuoDeng1->value->result | pZuoDeng2->value->result;
    if(!all_result) //如果都没亮,直接判定不通过。但是此时只需要对zuodeng1赋值
    {
        pZuoDeng1->value->result = false;
    }
    else //只要有一个通过
    {
        if(pZuoDeng1->config.isOpen || pZuoDeng2->config.isOpen) //如果配置开关有一个打开
        {
            pZuoDeng1->value->result = true; 
        } 
            
    }

    //新车不检车牌 后续加上
    if(baseTool::checkIsNewCar(pAllParamVector))
    {
        chePaiHao.result = true;
    }

    return true;
}
