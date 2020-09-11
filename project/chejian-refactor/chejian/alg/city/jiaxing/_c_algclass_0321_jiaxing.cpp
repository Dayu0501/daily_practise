#include "_c_algclass_0321_jiaxing.h"
#include "../base/baseTool.h"

bool _c_algClass_0321_JiaXing::ResultEdit()
{
    LOG(ALG, INFO, "%s", __PRETTY_FUNCTION__);
    //获取左灯1、2的 memberitem
    memberItem *pZuoDeng1 = baseTool::getMemberItemByName(pResultMemberList,"zuoDeng1");
    memberItem *pZuoDeng2 = baseTool::getMemberItemByName(pResultMemberList,"zuoDeng2");

    LOG(ALG, INFO, "%s zuoDeng1 = %d zuoDeng2 = %d", __PRETTY_FUNCTION__, pZuoDeng1, pZuoDeng2);
    //摩托车只有一个灯，灯光不需要特殊处理
    if (!baseTool::checkCllxIsMx(pAllParamVector))
    {
        //嘉兴左右灯有一个亮就都算亮
        if (pZuoDeng1 && pZuoDeng2)
        {
            LOG(ALG, INFO, "%s pZuoDeng1->value->result = %d pZuoDeng2->value->result = %d", __PRETTY_FUNCTION__,
                pZuoDeng1->value->result, pZuoDeng2->value->result);
            if (pZuoDeng1->config.isOpen ^ pZuoDeng2->config.isOpen)
            {
                LOG(ALG, INFO, "%s (pZuoDeng1->config.isOpen ^ pZuoDeng2->config.isOpen) = true", __PRETTY_FUNCTION__);
                pZuoDeng1->value->result = pZuoDeng2->value->result |= pZuoDeng1->value->result;
            }
            LOG(ALG, INFO, "%s pZuoDeng1->value->result = %d pZuoDeng2->value->result = %d", __PRETTY_FUNCTION__,
                pZuoDeng1->value->result, pZuoDeng2->value->result);
        }
    }
    //新车不检车牌
    if(baseTool::checkIsNewCar(pAllParamVector))
        chePaiHao.result = true;

    return true;
}
