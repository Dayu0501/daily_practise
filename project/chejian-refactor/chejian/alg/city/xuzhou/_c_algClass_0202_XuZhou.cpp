#include "_c_algClass_0202_XuZhou.h"
#include "../base/baseTool.h"

bool _c_algClass_0202_XuZhou::ResultEdit() {
	printf("%s", __PRETTY_FUNCTION__ );

	//所有人号码是否是手机
	int ret = baseTool::isMobileNumber(suoYouRenShouJiHao.OutData);
	if (ret == -1) {
		suoYouRenShouJiHao.result = false;
		memberItem *pMember = baseTool::getMemberItemByName(pResultMemberList,"suoYouRenShouJiHao");
		pMember->desc = "无所有人手机号码";
	} else if (ret == 0) {
		suoYouRenShouJiHao.result = false;
		memberItem *pMember = baseTool::getMemberItemByName(pResultMemberList,"suoYouRenShouJiHao");
		pMember->desc = "所有人手机号码不合法";
	}else {
		suoYouRenShouJiHao.result = true;
	}

	//判断代理人号码是否是手机号码
	ret = baseTool::isMobileNumber(daiLiRenShouJiHao.OutData);
	if (-1 == ret) {
		daiLiRenShouJiHao.result = false;
		memberItem* pMember = baseTool::getMemberItemByName(pResultMemberList, "daiLiRenShouJiHao");
		if(pMember){

			pMember->desc = "无代理人手机号码";
		}
	} else if (0 == ret) {
		daiLiRenShouJiHao.result = false;
		memberItem* pMember = baseTool::getMemberItemByName(pResultMemberList, "daiLiRenShouJiHao");
		if(pMember){
			pMember->desc = "代理人手机号码不合法";
		}
	} else {
		daiLiRenShouJiHao.result = true;
	}

	//新车不检车牌
	if (baseTool::checkIsNewCar(pAllParamVector)) {
		chePaiHao.result = true;
	}

	//所有人和代理人手机号做联合判定
	if (suoYouRenShouJiHao.result) {
		daiLiRenShouJiHao.result = true;
	} else if (daiLiRenShouJiHao.result) {
		suoYouRenShouJiHao.result = true;
	}

	//用来处理代理人和所有人签名的联合判定
	if (daiLiRenXingMing.OutData.empty() && !xingMing.result) {
		daiLiRenXingMing.result = false;
		xingMing.result = false;
	} else if (!daiLiRenXingMing.OutData.empty()) {
		daiLiRenXingMing.result = true;
		xingMing.result = true;
	} else if (xingMing.result) {
		daiLiRenXingMing.result = true;
		xingMing.result = true;
	}

	bool res = yinZhang.result || qianMing.result;
	yinZhang.result = qianMing.result = res;

	return true;
}