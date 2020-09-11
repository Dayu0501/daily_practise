#include "_c_algClass_0354_HengShui.h"
#include "base/baseTool.h"

bool _c_algClass_0354_HengShui::ResultEdit()
{
    std::string syxz = baseTool::getObjectItemValueByName(pAllParamVector, "shiYongXingZhi");
    std::string chuCiDengJiRiQi = baseTool::getObjectItemValueByName(pAllParamVector, "chuCiDengJiRiQi");
    bool isoverTenYear = baseTool::isTenYears(chuCiDengJiRiQi);
    //超过十年 或者 营运车辆 必须检,否则通过
    if ( !(isoverTenYear || syxz != "A") )
    {
        //TODO 设置结果通过
        for (int i = 0 ; i < pResultMemberList->size(); i++)
        {
            ((memberItem)( (*pResultMemberList)[i]) ).value->result = true ;
        }
    }
    return true;
}
