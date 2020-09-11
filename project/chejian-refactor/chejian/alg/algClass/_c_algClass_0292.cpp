#include "_c_algClass_0292.h"
#include "../base/baseTool.h"

bool _c_algClass_0292::seekMemberListPointer()
{
    mainPhotoType = e0292;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0292::InParamEdit()
{
    //格式化生效日期，终止日期，检验结束时间
    shengXiaoRiQi.inData = baseTool::formatingDate(shengXiaoRiQi.inData);
    zhongZhiRiQi.inData = baseTool::formatingDate(zhongZhiRiQi.inData);
    jianYanJieShuShiJian.inData = baseTool::formatingDate(jianYanJieShuShiJian.inData);

    return true;
}

bool _c_algClass_0292::ResultEdit()
{
    //新车不检车牌
    if(baseTool::checkIsNewCar(pAllParamVector))
    {
        chePaiHao.result = true;
    }
    //如果照片清晰度为false 则只输出照片清晰度的错误信息其他信息不输出
    baseTool::checkMemberItemAndSetAllUnOutput(pResultMemberList, baseTool::getMemberItemByName(pResultMemberList,"zhaoPianQingXiDu"));

    return true;
}
