#include "_c_algClass_0322_FuZhou.h"
#include "base/baseTool.h"

bool _c_algClass_0322_FuZhou::ResultEdit()
{
    memberItem *zuo = baseTool::getMemberItemByName(pResultMemberList,"zuoDeng");
    memberItem *you = baseTool::getMemberItemByName(pResultMemberList,"youDeng");
    memberItem *zhi = baseTool::getMemberItemByName(pResultMemberList,"zhiDongDeng");
    if(zhi && you && zuo) {
        zhi->value->result = (zuo->value->result) && (you->value->result) ;

        printf("fuzhou 0322 weideng !\n");

        if (zuo->value->result) printf("zuo deng ok\n");
        if (you->value->result) printf("you deng ok \n");

        if(zhi->value->result) {
        	printf("&&&&&&&&&&&&&&&&&&& zhidong is ok !\n");
        } else {
	        printf("&&&&&&&&&&&&&&&&&&& zhidong is not ok !\n");
        }
    }

    //新车不检车牌
    if(baseTool::checkIsNewCar(pAllParamVector))
    {
        chePaiHao.result = true;
    }

    return true;
}