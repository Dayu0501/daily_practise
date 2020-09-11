#ifndef _C_STARTUPPARAMCONFIG_H
#define _C_STARTUPPARAMCONFIG_H
#include "_c_dbConfig.h"
#include "_c_redisConfig.h"
#include "_c_soapConfig.h"
#include "config/_c_configBaseClass.h"
#include <map>

class _c_startUpParamConfig :public _c_configBaseClass {
public:
    _c_dbConfig dbConfigParam;
    _c_redisConfig redisConfigParam;
    _c_soapConfig soapConfigParam;

    _c_startUpParamConfig(CityType cityType) {
        _cityType = cityType;
        _configPath = _configRoot+"/startUpParamConfig_"+std::to_string(_cityType)+".json";
        _jsonRootName = "startUpParam";

        allConfigVector.clear();
        allConfigVector.push_back(&dbConfigParam);
        allConfigVector.push_back(&redisConfigParam);
        allConfigVector.push_back(&soapConfigParam);
        allJsonArrayVector.clear();
    }

    //获取数据库参数
    PDB_PARAM getStructDbParam();
    //获取redis参数
    PREDIS_PARAM getStructRedisParam();
    //获取soap参数
    PSTARTUPPRARAM getSoapParam();
    //获取启动参数 Json格式 用于web交互
    Json::Value getStartUpParamJson();
    //获取启动参数名 用于web交互
    void getStartUpParamNameList(std::map<std::string, std::string> &paramMap);
    //更新启动参数 用于web交互
    void updateStartUpParamConfig(std::map<std::string, std::string> &paramMap);

};

#endif// _C_STARTUPPARAMCONFIG_H
