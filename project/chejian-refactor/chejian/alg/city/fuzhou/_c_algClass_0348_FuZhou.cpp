#include "_c_algClass_0348_FuZhou.h"
#include "base/baseTool.h"

bool _c_algClass_0348_FuZhou::ResultEdit()
{

    memberItem *zuo=baseTool::getMemberItemByName(pResultMemberList,"zuoDeng");
    memberItem *you=baseTool::getMemberItemByName(pResultMemberList,"youDeng");
    memberItem *zhi=baseTool::getMemberItemByName(pResultMemberList,"zhiDongDeng");
    if(zhi && zuo && you) {
        zhi->value->result = (zuo->value->result) && (you->value->result);
        printf("fuzhou 0348 weideng ! \n");
    }

	//新车不检车牌
    if(baseTool::checkIsNewCar(pAllParamVector))
    {
        chePaiHao.result = true;
    }
	
    return true;
}