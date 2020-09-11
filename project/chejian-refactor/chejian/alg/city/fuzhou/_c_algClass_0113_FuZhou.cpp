#include "_c_algClass_0113_FuZhou.h"
#include "base/baseTool.h"

_c_algClass_0113_FuZhou::_c_algClass_0113_FuZhou() {
	inMemberList.push_back({"duiBiLeiXing", "对比类型", &duiBiLeiXing, false, CONFIG_DEFAULT});
}

bool _c_algClass_0113_FuZhou::InParamEdit() {

	//duiBiLeiXing.inData = "0";

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


