﻿#include "_c_algClass_0154_NanChang.h"
#include "../base/baseTool.h"

bool _c_algClass_0154_NanChang::InParamEdit()
{
    std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector,"cheLiangLeiXing");
    if((cllx.find("K2")))
    {
        lunTaiGuiGe.inData = baseTool::formatFileNameLunTai(lunTaiGuiGe.inData);
        return true;
    }
    
    return false;
}

bool _c_algClass_0154_NanChang::ResultEdit()
{
    return true;
}