#ifndef _C_VIDEOCHECKJYJGBHCONFIG_H
#define _C_VIDEOCHECKJYJGBHCONFIG_H

#include "config/_c_configBaseClass.h"

//每个JSON数组(集合,非纯数组) 都需要这样一个类
class _c_videoCheckJyjgbhItem: public _c_jsonArrayBaseSet
{
public:
    _c_videoCheckJyjgbhItem(std::string jyjgbh, std::string portIp, std::string xieYiLeiXing, std::string tongXunFangShi)
    {
        _pJyjgbh = new _c_jsonArrayBaseItem("jyjgbh", jyjgbh);
        _pPortIp = new _c_jsonArrayBaseItem("portIp", portIp);;
        _pXieYiLeiXing = new _c_jsonArrayBaseItem("xieYiLeiXing", xieYiLeiXing);
        _pTongXunFangShi = new _c_jsonArrayBaseItem("tongXunFangShi", tongXunFangShi);;

        addBaseItem(_pJyjgbh);
        addBaseItem(_pPortIp);
        addBaseItem(_pXieYiLeiXing);
        addBaseItem(_pTongXunFangShi);

        //如果不是动态分配的,则不需要释放,最好统一动态分配
        _isNeedFree = true;
    }

public:
    _c_jsonArrayBaseItem *_pJyjgbh = NULL;
    _c_jsonArrayBaseItem *_pPortIp = NULL;
    _c_jsonArrayBaseItem *_pXieYiLeiXing = NULL;
    _c_jsonArrayBaseItem *_pTongXunFangShi = NULL;
};

class _c_videoCheckJyjgbhConfig: public _c_configBaseClass
{
public:
    _c_jsonSetArray _jyjgbhArray;

    _c_videoCheckJyjgbhConfig(CityType cityType)
    {
        _cityType = cityType;
        _configPath = _configRoot+"/videoCheckJyjgbhConfig_"+std::to_string(_cityType)+".json";
        _jsonRootName = "jyjgbhConfig";

        //JSON数组配置
        _jyjgbhArray.initNodeName("jyjgbhList");
        std::vector<std::string> nameVector = {"jyjgbh", "portIp", "xieYiLeiXing", "tongXunFangShi"};
        _jyjgbhArray.initMemberNameVectror(nameVector);

        //配置创建的默认值,如果配置文件已经存在则按配置内容为准
        _jyjgbhArray.addSetItem(newJyjgbhArrayBaseItem("3716000009", "172.18.253.2:80", "huayan", "local"));
        _jyjgbhArray.addSetItem(newJyjgbhArrayBaseItem("3716000002", "172.18.245.2:80", "huayan", "local"));
        _jyjgbhArray.addSetItem(newJyjgbhArrayBaseItem("3700000784", "172.18.236.2:80", "huayan", "local"));
        _jyjgbhArray.addSetItem(newJyjgbhArrayBaseItem("3716000011", "172.18.249.2:80", "huayan", "local"));
        _jyjgbhArray.addSetItem(newJyjgbhArrayBaseItem("3700000682", "172.18.250.3:80", "huayan", "local"));
        _jyjgbhArray.addSetItem(newJyjgbhArrayBaseItem("3716000032", "172.18.231.2:80", "huayan", "local"));
        _jyjgbhArray.addSetItem(newJyjgbhArrayBaseItem("3716000028", "172.18.232.2:8080", "linzhi", "local"));
        _jyjgbhArray.addSetItem(newJyjgbhArrayBaseItem("3716000073", "172.18.196.250:8080", "linzhi", "local"));

        allJsonArrayVector.clear();
        allJsonArrayVector.push_back(&_jyjgbhArray);

        videoJyjgbhVector.clear();
    }

    ~_c_videoCheckJyjgbhConfig()
    {
        _jyjgbhArray.jsonArrayRelease();
    }

    _c_jsonArrayBaseSet *newJyjgbhArrayBaseItem(std::string jyjgbh, std::string portIp, std::string xieYiLeiXing, std::string tongXunFangShi);

    //用于web交互
    Json::Value getVideoJyjgbhVectorJson();
    void deleteVideoJyjgbhVectorByBaseItem(_c_jsonArrayBaseItem *pItem);
    void addVideoJyjgbhArraySet(_c_jsonArrayBaseSet *pSet);

    std::vector<VIDEOJYJGBH> *getVideoJyjgbhConfigParam();
    void updateVideoJyjgbhVector();

public:
    std::vector<VIDEOJYJGBH> videoJyjgbhVector;//需要根据网页动态更新
};
#endif// _C_VIDEOCHECKJYJGBHLIST_H
