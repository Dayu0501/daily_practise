#include "_c_algClass_0206_LiangJiang.h"
#include "base/baseTool.h"

bool _c_algClass_0206_LiangJiang::subClassLoadNewResultMember()
{
    _algType = alg0203;
	return true;
}

bool _c_algClass_0206_LiangJiang::ResultEdit()
{
   // baseTool::closeMemberItemWriteResultByName(pResultMemberList,"wanShuiZhengMing");
    memberItem* pwanShuiPingZhengHao = baseTool::getMemberItemByName(pResultMemberList,"wanShuiPingZhengHao");
    memberItem* pkaiJuShuiWuJiGuan   = baseTool::getMemberItemByName(pResultMemberList,"kaiJuShuiWuJiGuan");
    memberItem* pcheChuanShui   = baseTool::getMemberItemByName(pResultMemberList,"cheChuanShui");

     if(pcheChuanShui)
     {
         pcheChuanShui->value->result = (pcheChuanShui->value->result)|| (pwanShuiPingZhengHao && pwanShuiPingZhengHao->value->result) || (pkaiJuShuiWuJiGuan && pkaiJuShuiWuJiGuan->value->result) ;
     }
    return true;
}

