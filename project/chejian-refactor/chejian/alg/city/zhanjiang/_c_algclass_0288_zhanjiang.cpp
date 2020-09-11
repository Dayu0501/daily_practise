#include "_c_algclass_0288_zhanjiang.h"
#include "base/baseTool.h"

bool _c_algClass_0288_ZhanJiang::ResultEdit()
{
    //只有外地车检测行驶证背面，本地车一律通过
    if (isLocale(pAllParamVector))
        baseTool::setAllPass(pResultMemberList);

    return true;
}

bool _c_algClass_0288_ZhanJiang::isLocale(std::vector<objectMember *> *pCheLiangXinxi)
{
    //通过发证机关判断车辆是否为本地车辆
    std::string fzjg = baseTool::getObjectItemValueByName(pCheLiangXinxi,"faZhengJiGuan");
    return (fzjg == "粤G");           //湛江车牌以 粤G 开头
}
