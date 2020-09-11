#include "_c_algClass_0113.h"
#include "../base/baseTool.h"

bool _c_algClass_0113::seekMemberListPointer()
{
    mainPhotoType = e0113;
    subPhotoType = eCLSBDHZP_TYM;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    inListVector.push_back({"moTuo",&inMemberList_moTuo});


    resultListVector.push_back({"default",&resultMemberList});
    resultListVector.push_back({"moTuo",&resultMemberList_moTuo});

    return true;
}

bool _c_algClass_0113::InParamEdit()
{
    shuiYinRiQi.inData = baseTool::formatingDate(shuiYinRiQi.inData);
    changShangPinPai.inData = zhiZaoChangMingCheng.inData+"/"+baseTool::getDestClpp(cheLiangPinPai.inData);
	dangAnZhaoPian.result = false;//默认值
	
	_c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector,baseTool::getAlgItemCodeByPicType(subPhotoType,
		                                               pAllAlgItemVector));
	if (algTask) {
		dangAnZhaoPian.result = true;
	}
	
    return true;
}

bool _c_algClass_0113::ResultEdit()
{
    if (baseTool::compareDate(shuiYinRiQi.inData, shuiYinRiQi.OutData)) {
        shuiYinRiQi.result = true;
    }

    //厂商VIN，0表示不符合，1表示符合，2表示不支持
    int brand = baseTool::str2Int(changShangPinPai.OutData);
    if(!brand)
    {
        changShangPinPai.result = false;
    }

    if(dangAnZhaoPian.result)
    {
        baseTool::openMemberItemWriteResultByName(pResultMemberList,"taYinMo");
        baseTool::openMemberItemWriteResultByName(pResultMemberList,"tuoMo");
    }

    baseTool::checkMemberItemAndSetAllUnOutput(pResultMemberList, baseTool::getMemberItemByName(pResultMemberList,"zhaoPianQingXiDu"));

    return true;
}
