#ifndef _C_CONFIGBASECLASS_H
#define _C_CONFIGBASECLASS_H
#include <vector>
#include "base/json/json.h"
#include "base/_c_object.h"
#include "config/_c_jsonArrayClass.h"

class _c_configBaseClass {
public:
    //加载配置文件
    virtual void loadConfig();
    //保存配置文件
    virtual void saveConfig();
    //获取所有参数返回json
    virtual Json::Value getAllConfigParamJson();
    virtual ~_c_configBaseClass(){}

    //获取某个子项的 Json格式 用于web交互
    Json::Value getOneObjectParamJson(_c_object *obj);
    //获取某个子项的参数名 用于web交互
    void getOneObjectParamNameList(_c_object *obj, std::map<std::string, std::string> &paramMap);
    //更新某个子项的参数 用于web交互
    void updateOneObjectParamConfig(_c_object *obj, std::map<std::string, std::string> &paramMap);

    Json::Value getOneArrayParamJson(_c_jsonSetArray *array);
    void deleteOneArraySetByBaseItem(_c_jsonSetArray *array, _c_jsonArrayBaseItem *pItem);
    void addOneArraySet(_c_jsonSetArray *array, _c_jsonArrayBaseSet *pSet);

    std::vector<_c_object *> allConfigVector;
    std::vector<_c_jsonSetArray *> allJsonArrayVector;
    void setConfigParam(Json::Value root);

protected:
    CityType _cityType = eDEMO;
    std::string _configRoot = "/opt/vehicle/program/CheJianConfig";
    std::string _configPath = "";
    std::string _jsonRootName = "";
};

#endif// _C_CONFIGBASECLASS_H
