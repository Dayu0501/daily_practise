#include "_c_algclass_0352_jiaxing.h"
#include "../base/baseTool.h"

bool _c_algClass_0352_JiaXing::ResultEdit()
{
    LOG(ALG, INFO, "%s", __PRETTY_FUNCTION__);
    //获取左灯1、2的 memberitem
    memberItem *pYouDeng1 = baseTool::getMemberItemByName(pResultMemberList,"youDeng1");
    memberItem *pYouDeng2 = baseTool::getMemberItemByName(pResultMemberList,"youDeng2");

    LOG(ALG, INFO, "%s pYouDeng1 = %d pYouDeng2 = %d", __PRETTY_FUNCTION__, pYouDeng1, pYouDeng2);
    //摩托车只有一个灯，灯光不需要特殊处理
    if (!baseTool::checkCllxIsMx(pAllParamVector))
    {
        //嘉兴左右灯有一个亮就都算亮
        if (pYouDeng1 && pYouDeng2)
        {
            LOG(ALG, INFO, "%s pYouDeng1->value->result = %d pYouDeng2->value->result = %d", __PRETTY_FUNCTION__,
                pYouDeng1->value->result, pYouDeng2->value->result);
            if (pYouDeng1->config.isOpen ^ pYouDeng2->config.isOpen)
            {
                LOG(ALG, INFO, "%s pYouDeng1->config.isOpen ^ pYouDeng2->config.isOpen", __PRETTY_FUNCTION__);
                pYouDeng1->value->result = pYouDeng2->value->result |= pYouDeng1->value->result;
            }
            LOG(ALG, INFO, "%s pYouDeng1->value->result = %d pYouDeng2->value->result = %d", __PRETTY_FUNCTION__,
                pYouDeng1->value->result, pYouDeng2->value->result);
        }
    }

    //新车不检车牌
    if(baseTool::checkIsNewCar(pAllParamVector))
        chePaiHao.result = true;

    return true;
}
