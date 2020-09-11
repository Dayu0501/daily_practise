#include "_c_wangLuoJieKouConfig.h"

std::vector<wangLuoJieKouItem> *_c_wangLuoJieKouConfig::getOpenedJieKouInfo()
{
    updateOpenedJieKouInfo();

    return &openedJieKouInfo;
}

Json::Value _c_wangLuoJieKouConfig::getJqxParamJson()
{
    return getOneObjectParamJson(&jiaoQiangXianConfigParam);
}

void _c_wangLuoJieKouConfig::getJqxParamNameList(std::map<std::string, std::string> &paramMap)
{
    getOneObjectParamNameList(&jiaoQiangXianConfigParam, paramMap);
}

void _c_wangLuoJieKouConfig::updateJqxParamConfig(std::map<std::string, std::string> &paramMap)
{
    updateOneObjectParamConfig(&jiaoQiangXianConfigParam, paramMap);
    updateOpenedJieKouInfo();
}

void _c_wangLuoJieKouConfig::updateOpenedJieKouInfo()
{
    openedJieKouInfo.clear();

    for (unsigned int i = 0; i < allConfigVector.size(); i++)
    {
        bool isopened = false;
        wangLuoJieKouItem item;
        _c_dbTask *pDbTask = static_cast<_c_dbTask *>(allConfigVector[i]);
        for (unsigned int j = 0; j < pDbTask->memberVector.size(); j++)
        {
            if (pDbTask->memberVector[j].soapName == "isOpen")
            {
                if (*pDbTask->memberVector[j].value == "true")
                {
                    isopened = true;
                }
                else {
                    break;
                }
            }
            else if (pDbTask->memberVector[j].soapName == "jieKouBiaoShi")
            {
                item.biaoShi = *pDbTask->memberVector[j].value;
            }
            else if (pDbTask->memberVector[j].soapName == "shouQuanMa")
            {
                item.shouQuanMa = *pDbTask->memberVector[j].value;
            }
        }

        if (isopened)
        {
            openedJieKouInfo.push_back(item);
        }
    }

}



