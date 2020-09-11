#include "_c_algClass_0205_WuZhou.h"
#include "../base/baseTool.h"

bool _c_algClass_0205_WuZhou::subClassLoadNewResultMember()
{
    memberItem temp_item = {"panDing", "每一个检测项结论", &itemList, true, CONFIG_NOCHECK};
    resultMemberList.push_back(temp_item);   
}

bool _c_algClass_0205_WuZhou::ResultEdit()
{
    _c_algClass_0205::ResultEdit();

    memberItem* panDing=baseTool::getMemberItemByName(pResultMemberList,"panDing");
//    std::string item_list = "1_0_0_0_1_0_1";
    if(!panDing)
    {
        baseTool::closeMemberItemWriteResultByName(pResultMemberList,"panDing");
        return true;
    }
    
    std::string item_list = panDing->value->OutData;
    std::string item_list_left = "";
    std::string per_item_value = "";
    std::string error_reason = "";
    std::map<int,std::string> map_item_list;
    int npos_start = 0;
    int npos_end = 0;
    int index = 0;
    npos_end = item_list.find("_");
    while(npos_end != std::string::npos)
    {
        per_item_value = item_list.substr(npos_start,npos_end - npos_start);
        index ++;
        map_item_list[index] = per_item_value;
        if(per_item_value == "0")
        {
            std::string reason = "the " + std::to_string(index) +  " is not correct!" ;
            error_reason  = error_reason + "[" + reason + "],";
        }

        item_list_left = item_list.substr(npos_end + 1,item_list.size());
        item_list = item_list_left;
        npos_end = item_list.find("_");
    }

    if(error_reason != "")
    {
        panDing->desc = error_reason;
        panDing->value->result = false;
        baseTool::openMemberItemWriteResultByName(pResultMemberList,"panDing");
    }
    else
    {
        panDing->value->result = true;
    }
    

    return true;
}
