#include "_c_configBaseClass.h"
#include "base/baseTool.h"

void _c_configBaseClass::loadConfig()
{
    if (!_configPath.empty())
    {
        std::ifstream fin;
        fin.open(_configPath);
        if (fin.is_open()) {
            Json::Value  root;
            Json::Reader reader;
            if (reader.parse(fin, root, false))
            {
               setConfigParam(root[_jsonRootName.c_str()]);
            }
        } else {
            saveConfig();
        }
        fin.close();
    }
}

//把所有的成员写成json文件
Json::Value _c_configBaseClass::getAllConfigParamJson()
{
    Json::Value root;
    if(allConfigVector.size() > 0) {
        for (unsigned int i = 0; i < allConfigVector.size(); i++) {
            Json::Value memberRoot;
            _c_dbTask *pDbTask = static_cast<_c_dbTask *>(allConfigVector[i]);
            for (unsigned int j=0; j < pDbTask->memberVector.size(); j++) {
                memberRoot[pDbTask->memberVector[j].soapName] = *pDbTask->memberVector[j].value;
                printf("%s:%s\n", pDbTask->memberVector[j].soapName.c_str(), pDbTask->memberVector[j].value->c_str());
            }
            root[pDbTask->tableName] = memberRoot;
        }
    }
    if (allJsonArrayVector.size() > 0) {
        for (unsigned int i = 0; i < allJsonArrayVector.size(); i++) {
            root[allJsonArrayVector[i]->_jsonNodeName] = allJsonArrayVector[i]->convertToJson();
        }
    }
    return root;
}

void _c_configBaseClass::saveConfig()
{
    std::ofstream ofs;
    Json::Value  root;
    std::string path = _configRoot;
    baseTool::CheckDir(path);

    root[_jsonRootName.c_str()] = getAllConfigParamJson();

    ofs.open(_configPath);
    ofs << root.toStyledString();
    ofs.close();

    if(allConfigVector.size() > 0) {
        for (unsigned int i = 0; i < allConfigVector.size(); i++) {
            Json::Value memberRoot;
            _c_dbTask *pDbTask = static_cast<_c_dbTask *>(allConfigVector[i]);
            pDbTask->dbWork();
        }
    }
}

//把启动参数写入到相应的成员中
void _c_configBaseClass::setConfigParam(Json::Value root)
{
    for (unsigned int i = 0; i < allConfigVector.size(); i++) {
        _c_dbTask *pDbTask = static_cast<_c_dbTask *>(allConfigVector[i]);
        if (!root[pDbTask->tableName].empty()) {
            Json::Value subRoot = root[pDbTask->tableName];
            for (unsigned int j = 0; j < pDbTask->memberVector.size(); j++) {
                if (!subRoot[pDbTask->memberVector[j].soapName].empty()) {
                    *pDbTask->memberVector[j].value = subRoot[pDbTask->memberVector[j].soapName].asString();
                    printf("%s:%s\n", pDbTask->memberVector[j].soapName.c_str(), pDbTask->memberVector[j].value->c_str());
                }
            }
        } else {
            printf("Item:%s in config file is null\n", pDbTask->tableName.c_str());
        }
    }

    //
    for (unsigned int i = 0; i < allJsonArrayVector.size(); i++)
    {
        _c_jsonSetArray *pArray = allJsonArrayVector[i];
        //加载前先统一释放默认项
        pArray->jsonArrayRelease();
        if (!root[pArray->_jsonNodeName].empty())
        {
            Json::Value subRoot = root[pArray->_jsonNodeName];
//            printf("JsonArray %s\n", subRoot.toStyledString().c_str());
            pArray->analyseJsonToArray(subRoot);
        }
    }
}

//获取某个子项的 Json格式 用于web交互
Json::Value _c_configBaseClass::getOneObjectParamJson(_c_object *obj)
{
    Json::Value root;
    if (obj->memberVector.size() > 0)
    {
        for (unsigned int j=0; j < obj->memberVector.size(); j++)
        {
            root[obj->memberVector[j].soapName] = *(obj->memberVector[j].value);
        }
    }

    return root;
}

//获取某个子项的参数名 用于web交互
void _c_configBaseClass::getOneObjectParamNameList(_c_object *obj, std::map<std::string, std::string> &paramMap)
{
    if (obj->memberVector.size() > 0)
    {
        for (unsigned int j=0; j < obj->memberVector.size(); j++)
        {
            paramMap.insert(std::pair<std::string, std::string>(obj->memberVector[j].soapName, ""));
        }
    }
}

//更新某个子项的参数 用于web交互
void _c_configBaseClass::updateOneObjectParamConfig(_c_object *obj, std::map<std::string, std::string> &paramMap)
{
    std::map<std::string, std::string>::iterator it;
    for (it = paramMap.begin(); it != paramMap.end(); it++)
    {
        for (unsigned int j=0; j < obj->memberVector.size(); j++)
        {
            if (it->first == obj->memberVector[j].soapName)
            {
                 *(obj->memberVector[j].value) = it->second;
            }
        }
    }

    saveConfig();
}

Json::Value _c_configBaseClass::getOneArrayParamJson(_c_jsonSetArray *array)
{
    return array->convertToJson();
}

void _c_configBaseClass::deleteOneArraySetByBaseItem(_c_jsonSetArray *array, _c_jsonArrayBaseItem *pItem)
{
    array->deleteSetItemByBaseItem(pItem);
}

void _c_configBaseClass::addOneArraySet(_c_jsonSetArray *array, _c_jsonArrayBaseSet *pSet)
{
    array->addSetItem(pSet);
}
