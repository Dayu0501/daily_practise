#include "_c_algClass_0157_WuZhou.h"
#include "../base/baseTool.h"

bool _c_algClass_0157_WuZhou::subClassLoadNewResultMember()
{
    memberItem temp_item = {"fangXiangPan", "方向盘不存在", &fangXiangPan, true, CONFIG_DEFAULT};
    resultMemberList.push_back(temp_item);

    return true;
}

bool _c_algClass_0157_WuZhou::ResultEdit()
{
    memberItem* anQuanDai = baseTool::getMemberItemByName(pResultMemberList,"anQuanDai");
    memberItem* fangXiangPan = baseTool::getMemberItemByName(pResultMemberList,"fangXiangPan");
    if(anQuanDai && fangXiangPan)
    {
        anQuanDai->value->result = anQuanDai->value->result & fangXiangPan->value->result;
    }

    return true;
}
