#include "_c_startUpParamConfig.h"

PDB_PARAM _c_startUpParamConfig::getStructDbParam()
{
    return dbConfigParam.getStructDbParam();
}

PREDIS_PARAM _c_startUpParamConfig::getStructRedisParam()
{
    return redisConfigParam.getStructRedisParam();
}

PSTARTUPPRARAM _c_startUpParamConfig::getSoapParam()
{
    return soapConfigParam.getSoapParam();
}

Json::Value _c_startUpParamConfig::getStartUpParamJson()
{
    Json::Value root;
    if (soapConfigParam.memberVector.size() > 0)
    {
        for (unsigned int j=0; j < soapConfigParam.memberVector.size(); j++)
        {
            root[soapConfigParam.memberVector[j].soapName] = *soapConfigParam.memberVector[j].value;
        }
    }
    //可以继续添加需要网页修改项
    root["endTime"] =baseTool::formatingTime(root["endTime"].asString() );
    root["startTime"] =baseTool::formatingTime(root["startTime"].asString() );;
    return root;
}

//这里取的值需要和getStartUpParamJson()相对应
void _c_startUpParamConfig::getStartUpParamNameList(std::map<std::string, std::string> &paramMap)
{
    if (soapConfigParam.memberVector.size() > 0)
    {
        for (unsigned int j=0; j < soapConfigParam.memberVector.size(); j++)
        {
            paramMap.insert(std::pair<std::string, std::string>(soapConfigParam.memberVector[j].soapName, ""));
        }
    }
}

void _c_startUpParamConfig::updateStartUpParamConfig(std::map<std::string, std::string> &paramMap)
{
    //当前只有soap参数允许网页设置
    std::map<std::string, std::string>::iterator it;
    for (it = paramMap.begin(); it != paramMap.end(); it++)
    {
        for (unsigned int j=0; j < soapConfigParam.memberVector.size(); j++)
        {
            if (it->first == soapConfigParam.memberVector[j].soapName)
            {
                 *soapConfigParam.memberVector[j].value = it->second;
            }
        }
    }

    saveConfig();
}
