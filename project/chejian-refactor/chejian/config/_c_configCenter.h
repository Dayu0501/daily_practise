#ifndef _C_CONFIGCENTER_H
#define _C_CONFIGCENTER_H
#include "base/baseInc.h"
#include "config/startUpParamConfig/_c_startUpParamConfig.h"
#include "config/wangLuoJieKouConfig/_c_wangLuoJieKouConfig.h"
#include "config/videoCheckConfig/_c_videoCheckJyjgbhConfig.h"

class _c_configCenter {
public:
    static bool loadDeviceBootConfig(PDEVICE_BOOT_CONFIG pBootConfig);

    _c_configCenter(CityType cityType);
    ~_c_configCenter();

    void loadConfig();

    //获取数据库参数
    PDB_PARAM getStructDbParam();
    //获取redis参数
    PREDIS_PARAM getStructRedisParam();
    //获取soap参数
    PSTARTUPPRARAM getSoapParam();

    //获取数据库名称
    std::string getDbName();
    //获取打开的接口标识
    std::vector<wangLuoJieKouItem> *getOpenedJieKouInfo();

    //获取soap Json格式 用于web交互
    Json::Value getStartUpParamJson();
    //获取soap参数名 用于web交互
    void getStartUpParamNameList(std::map<std::string, std::string> &paramMap);
    //更新soap参数 用于web交互
    void updateStartUpParamConfig(std::map<std::string, std::string> &paramMap);

    //获取jqx Json格式 用于web交互
    Json::Value getJqxParamJson();
    //获取jqx参数名 用于web交互
    void getJqxParamNameList(std::map<std::string, std::string> &paramMap);
    //更新jqx参数 用于web交互
    void updateJqxParamConfig(std::map<std::string, std::string> &paramMap);

    //视频审核检验机构 保存配置
    void videoJyjgbhSaveConfig();
    //视频审核检验机构 获取配置(用于web交互)
    Json::Value getVideoJyjgbhVectorJson();
    //视频审核检验机构 匹配某个元素来删除某个集合(用于web交互)
    void deleteVideoJyjgbhVectorByBaseItem(_c_jsonArrayBaseItem *pItem);
    //视频审核检验机构 添加某个集合(用于web交互)
    void addVideoJyjgbhArraySet(_c_jsonArrayBaseSet *pSet);
    //视频审核检验机构 获取参数
    std::vector<VIDEOJYJGBH> *getVideoJyjgbhConfigParam();

    SESSIONSERVICE_PARAM *getSessionServiceParam();
private:
    _c_startUpParamConfig *pStartUpParamConfig = NULL;
    _c_wangLuoJieKouConfig *pWangLuoJieKouConfig = NULL;
    _c_videoCheckJyjgbhConfig *pVdeoCheckJyjgbhConfig = NULL;

    CityType _cityType;
    SESSIONSERVICE_PARAM _sessionServiceParam;
};

#endif// _C_CONFIGCENTER_H
