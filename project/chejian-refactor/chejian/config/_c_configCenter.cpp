#include "_c_configCenter.h"
#include "base/baseTool.h"

bool _c_configCenter::loadDeviceBootConfig(PDEVICE_BOOT_CONFIG pBootConfig)
{
    bool ret = false;
    std::ifstream fin;
    std::string algconfigpath = "/opt/vehicle/program/CheJianConfig/deviceConfig.json";

    fin.open(algconfigpath);
    if (fin.is_open()) {
        Json::Value  root;
        Json::Reader reader;
        if (reader.parse(fin, root, false))
        {
            pBootConfig->cityType = (CityType)atoi(root["cityCode"].asString().c_str());;
            pBootConfig->deviceType = (DeviceType)root["deviceType"].asInt();
            pBootConfig->masterAddress = root["redisIp"].asString();
            ret = true;
        }
    }
    fin.close();

    return ret;
}

_c_configCenter::_c_configCenter(CityType cityType)
{
    _cityType = cityType;
    pStartUpParamConfig = new _c_startUpParamConfig(cityType);
    pWangLuoJieKouConfig = new _c_wangLuoJieKouConfig(cityType);
    pVdeoCheckJyjgbhConfig = new _c_videoCheckJyjgbhConfig(cityType);
}

void _c_configCenter::loadConfig()
{
    pStartUpParamConfig->loadConfig();
    pWangLuoJieKouConfig->loadConfig();
    pVdeoCheckJyjgbhConfig->loadConfig();
}

PDB_PARAM _c_configCenter::getStructDbParam()
{
    return pStartUpParamConfig->getStructDbParam();
}

PREDIS_PARAM _c_configCenter::getStructRedisParam()
{
    return pStartUpParamConfig->getStructRedisParam();
}

PSTARTUPPRARAM _c_configCenter::getSoapParam()
{
   return pStartUpParamConfig->getSoapParam();
}

Json::Value _c_configCenter::getStartUpParamJson()
{
    return pStartUpParamConfig->getStartUpParamJson();
}

void _c_configCenter::getStartUpParamNameList(std::map<std::string, std::string> &paramMap)
{
    pStartUpParamConfig->getStartUpParamNameList(paramMap);
}

void _c_configCenter::updateStartUpParamConfig(std::map<std::string, std::string> &paramMap)
{
    pStartUpParamConfig->updateStartUpParamConfig(paramMap);
}

Json::Value _c_configCenter::getJqxParamJson()
{
    return pWangLuoJieKouConfig->getJqxParamJson();
}

void _c_configCenter::getJqxParamNameList(std::map<std::string, std::string> &paramMap)
{
    pWangLuoJieKouConfig->getJqxParamNameList(paramMap);
}

void _c_configCenter::updateJqxParamConfig(std::map<std::string, std::string> &paramMap)
{
    pWangLuoJieKouConfig->updateJqxParamConfig(paramMap);
}

std::string _c_configCenter::getDbName()
{
    return pStartUpParamConfig->dbConfigParam.dbName;
}

std::vector<wangLuoJieKouItem> *_c_configCenter::getOpenedJieKouInfo()
{
    return pWangLuoJieKouConfig->getOpenedJieKouInfo();
}

Json::Value _c_configCenter::getVideoJyjgbhVectorJson()
{
    return pVdeoCheckJyjgbhConfig->getVideoJyjgbhVectorJson();
}

void _c_configCenter::deleteVideoJyjgbhVectorByBaseItem(_c_jsonArrayBaseItem *pItem)
{
    pVdeoCheckJyjgbhConfig->deleteVideoJyjgbhVectorByBaseItem(pItem);
}

void _c_configCenter::videoJyjgbhSaveConfig()
{
    pVdeoCheckJyjgbhConfig->saveConfig();
}

void _c_configCenter::addVideoJyjgbhArraySet(_c_jsonArrayBaseSet *pSet)
{
    pVdeoCheckJyjgbhConfig->addVideoJyjgbhArraySet(pSet);
}

std::vector<VIDEOJYJGBH> *_c_configCenter::getVideoJyjgbhConfigParam()
{
    pVdeoCheckJyjgbhConfig->getVideoJyjgbhConfigParam();
}

SESSIONSERVICE_PARAM *_c_configCenter::getSessionServiceParam()
{
    _sessionServiceParam.cityType = _cityType;
    PSTARTUPPRARAM pStartParam = getSoapParam();
    _sessionServiceParam.params.insert(std::pair<std::string, void *>("soapParam", (void *)pStartParam));

    std::vector<wangLuoJieKouItem> *pWljk = getOpenedJieKouInfo();
    _sessionServiceParam.params.insert(std::pair<std::string, void *>("wangLuoJieKouParam", (void *)pWljk));

    std::vector<VIDEOJYJGBH> *pVideoJyjgbh = getVideoJyjgbhConfigParam();
    _sessionServiceParam.params.insert(std::pair<std::string, void *>("videoCheckParam", (void *)pVideoJyjgbh));

    return &_sessionServiceParam;
}
