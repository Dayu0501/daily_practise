#include "_c_algClass_0203_XuZhou.h"
#include "../base/baseTool.h"

_c_algClass_0203_XuZhou::_c_algClass_0203_XuZhou() {
//	resultMemberList.push_back({"oneYearYouXiaoQi", "有效期小于1年", &oneYearYouXiaoQi, true, CONFIG_DEFAULT});
//	resultMemberList_dianZi.push_back({"oneYearYouXiaoQi", "有效期小于1年", &oneYearYouXiaoQi, true, CONFIG_DEFAULT});
}

bool _c_algClass_0203_XuZhou::InParamEdit() {
	//格式化生效日期，终止日期，检验结束时间
	shengXiaoRiQi.inData = baseTool::formatingDate(shengXiaoRiQi.inData);
	zhongZhiRiQi.inData = baseTool::formatingDate(zhongZhiRiQi.inData);
	jianYanJieShuShiJian.inData = baseTool::formatingDate(baseTool::getCurTime());

	printf("##### jianYanJieShuShiJian.inData is %s\n", jianYanJieShuShiJian.inData.c_str());

	if (baseTool::checkCllxIsMx(pAllParamVector)) {
		pInMemberList = &inMemberList_moTuo;
		pResultMemberList = &resultMemberList_moTuo;
	}

	//如果存在电子保单 则不进行后面的redis 流程
	if (pWangLuoJieKouReturnVector != NULL) {
		for (unsigned int i = 0; i < pWangLuoJieKouReturnVector->size(); i++) {
			std::string biaoShi = baseTool::getWangLuoJieKouReturnInfoBiaoShi((*pWangLuoJieKouReturnVector)[i]);
			if (biaoShi == "18C23") {
				if (baseTool::checkWangLuoJieKouReturnInfoIsValid((*pWangLuoJieKouReturnVector)[i])) {
					//如果电子保单返回内容有效,则不需要在走算法流程
//					kaiShiRiQiShuChu.OutData = baseTool::getObjectItemValueByName(
//						&((*pWangLuoJieKouReturnVector)[i]->memberVector), "shengXiaoRiQi");
//					jieZhiRiQiShuChu.OutData = baseTool::getObjectItemValueByName(
//						&((*pWangLuoJieKouReturnVector)[i]->memberVector), "zhongZhiRiQi");
//
//					printf("From 18C23 data kaiShiRiQiShuChu.OutData is %s, jieZhiRiQiShuChu.OutData is %s",
//					       kaiShiRiQiShuChu.OutData.c_str(), jieZhiRiQiShuChu.OutData.c_str());
//
//					baseTool::deleteMarks(kaiShiRiQiShuChu.OutData, '-');
//					baseTool::deleteMarks(jieZhiRiQiShuChu.OutData, '-');

					return false;
				}

				break;
			}
		}
	}

	return true;
}

//bool _c_algClass_0203_XuZhou::ResultEdit() {
//	printf("**************** %s, kaiShiRiQiShuChu.OutData is %s, jieZhiRiQiShuChu.OutData is %s\n", __PRETTY_FUNCTION__,
//	       kaiShiRiQiShuChu.OutData.c_str(), jieZhiRiQiShuChu.OutData.c_str());
//
//	_c_algClass_0203::ResultEdit();
//
//	//to do 可能需要加一个判断开始结束时间是否为空，来决定打开和关闭有效期一年选项
//
//	kaiShiRiQiShuChu.OutData += " 00:00:00";
//	jieZhiRiQiShuChu.OutData += " 00:00:00";
//
//	time_t kaiShiRiQiShuChuStamp = baseTool::strTime2unix(kaiShiRiQiShuChu.OutData, "%4d%2d%2d %d:%d:%d");
//	time_t jieZhiRiQiShuChuStamp = baseTool::strTime2unix(jieZhiRiQiShuChu.OutData, "%4d%2d%2d %d:%d:%d");
//
//	if (kaiShiRiQiShuChuStamp != 0 && jieZhiRiQiShuChuStamp != 0)
//		//因为保险生效日期是00:00:00，结束日期是24:00:00，所以+1
//		oneYearYouXiaoQi.result = (((jieZhiRiQiShuChuStamp - kaiShiRiQiShuChuStamp) / (60 * 60 * 24)) + 1) >= 365;
//	else {
//		oneYearYouXiaoQi.result = false;
//
//		printf("xuzhou 0203 time stamp error, algorithm output is null !\n");
//		LOG(COMMON, INFO, "xuzhou 0203 time stamp error, algorithm output is null ! %s\n", __func__);
//	}
//
//	printf("jieZhiRiQiShuChuStamp and kaiShiRiQiShuChuStamp diff is %lld\n",
//	       (jieZhiRiQiShuChuStamp - kaiShiRiQiShuChuStamp) / (60 * 60 * 24));
//
//	return true;
//}