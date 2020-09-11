#ifndef _C_WANGLUOJIEKOUCONFIG_H
#define _C_WANGLUOJIEKOUCONFIG_H

#include "config/_c_configBaseClass.h"
#include "_c_jiaoQiangXianConfig.h"

class _c_wangLuoJieKouConfig :public _c_configBaseClass{
public:
    _c_jiaoQiangXianConfig jiaoQiangXianConfigParam;

    _c_wangLuoJieKouConfig(CityType cityType) {
        _cityType = cityType;
        _configPath = _configRoot+"/wangLuoJieKouConfig_"+std::to_string(_cityType)+".json";
        _jsonRootName = "wangLuoJieKou";

        allConfigVector.clear();
        allConfigVector.push_back(&jiaoQiangXianConfigParam);

        allJsonArrayVector.clear();
    }

    //获取所有打开的网络接口相关
    std::vector<wangLuoJieKouItem> *getOpenedJieKouInfo();
    //更新网络接口信息 和网页配置同步
    void updateOpenedJieKouInfo();


    //获取jqx Json格式 用于web交互
    Json::Value getJqxParamJson();
    //获取jqx参数名 用于web交互
    void getJqxParamNameList(std::map<std::string, std::string> &paramMap);
    //更新jqx参数 用于web交互
    void updateJqxParamConfig(std::map<std::string, std::string> &paramMap);

private:
    std::vector<wangLuoJieKouItem> openedJieKouInfo;
};

#endif// _C_WANGLUOJIEKOUCONFIG_H
