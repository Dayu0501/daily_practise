#include "_c_videoCheckJyjgbhConfig.h"
#include "base/baseTool.h"

_c_jsonArrayBaseSet *_c_videoCheckJyjgbhConfig::newJyjgbhArrayBaseItem(std::string jyjgbh, std::string portIp, std::string xieYiLeiXing, std::string tongXunFangShi)
{
    _c_videoCheckJyjgbhItem *pItem = new _c_videoCheckJyjgbhItem(jyjgbh, portIp, xieYiLeiXing, tongXunFangShi);
    return pItem;
}

Json::Value _c_videoCheckJyjgbhConfig::getVideoJyjgbhVectorJson()
{
    return getOneArrayParamJson(&_jyjgbhArray);
}

void _c_videoCheckJyjgbhConfig::deleteVideoJyjgbhVectorByBaseItem(_c_jsonArrayBaseItem *pItem)
{
    deleteOneArraySetByBaseItem(&_jyjgbhArray, pItem);
    updateVideoJyjgbhVector();
}

void _c_videoCheckJyjgbhConfig::addVideoJyjgbhArraySet(_c_jsonArrayBaseSet *pSet)
{
    addOneArraySet(&_jyjgbhArray, pSet);
    updateVideoJyjgbhVector();
}

void _c_videoCheckJyjgbhConfig::updateVideoJyjgbhVector()
{
    videoJyjgbhVector.clear();

    for (auto iter = _jyjgbhArray._arrayList.begin(); iter != _jyjgbhArray._arrayList.end(); iter++)
    {
        _c_jsonArrayBaseSet *pSet = *iter;
        VIDEOJYJGBH item;
        for (unsigned int i = 0; i < pSet->_arrayItem.size(); i++)
        {
            if (pSet->_arrayItem[i]->_name == "jyjgbh")
                item.jyjgbh = pSet->_arrayItem[i]->_value;
            else if (pSet->_arrayItem[i]->_name == "portIp") {
                item.portIp = pSet->_arrayItem[i]->_value;
            }
            else if (pSet->_arrayItem[i]->_name == "xieYiLeiXing") {
                item.xieYiLeiXing = pSet->_arrayItem[i]->_value;
            }
            else if (pSet->_arrayItem[i]->_name == "tongXunFangShi") {
                item.tongXunFangShi = pSet->_arrayItem[i]->_value;
            }
        }
        videoJyjgbhVector.push_back(item);
    }
}

std::vector<VIDEOJYJGBH> *_c_videoCheckJyjgbhConfig::getVideoJyjgbhConfigParam()
{
    updateVideoJyjgbhVector();

    for (unsigned int i = 0;i < videoJyjgbhVector.size(); i++) {
        printf("%s %s %s %s\n", videoJyjgbhVector[i].jyjgbh.c_str(), videoJyjgbhVector[i].portIp.c_str(), videoJyjgbhVector[i].xieYiLeiXing.c_str(), videoJyjgbhVector[i].tongXunFangShi.c_str());
    }

    return &videoJyjgbhVector;
}
