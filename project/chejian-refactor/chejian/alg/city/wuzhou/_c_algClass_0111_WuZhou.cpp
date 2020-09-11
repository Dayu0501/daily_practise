#include "_c_algClass_0111_WuZhou.h"
#include "../base/baseTool.h"

bool _c_algClass_0111_WuZhou::subClassLoadNewResultMember()
{
    memberItem temp_item = {"houShiJing", "后视镜不存在", &houShiJing, true, CONFIG_DEFAULT};
    resultMemberList.push_back(temp_item);

    return true;
}
