#include "_c_algClass_0202_FuZhou.h"
#include "../base/baseTool.h"

_c_algClass_0202_FuZhou::_c_algClass_0202_FuZhou() {
    resultMemberList.push_back({"suoShuJiGou", "未知-无法处理类型，请人工审核", &suoShuJiGou, false, CONFIG_DEFAULT});
}

bool _c_algClass_0202_FuZhou::ResultEdit()
{
    printf("_c_algClass_0202_FuZhou !!!\n");

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
    } else {
        suoYouRenShouJiHao.result = true;
    }

    //固定电话
    if (guDingDianHua.OutData.empty())
        baseTool::closeMemberItemWriteResultByName(pResultMemberList, "guDingDianHua");
    else {
        guDingDianHua.result = guDingDianHua.OutData.size() >= 7;
    }

    //签名日期3个月内有效判定  
    memberItem *qianMingRiQiSuoYouRen = baseTool::getMemberItemByName(pResultMemberList, "qianMingRiQiSuoYouRen");
    if (qianMingRiQiSuoYouRen) {
        printf("%s : qianMingRiQiSuoYouRen = %s \n", __PRETTY_FUNCTION__, qianMingRiQiSuoYouRen->value->OutData.c_str());

        std::string srcDate;
		if (baseTool::convertDateFormat(qianMingRiQiSuoYouRen->value->OutData, srcDate)) {
			printf("111 srcDate is %s \n", srcDate.c_str());

			std::string curDate = baseTool::getNowDate();
			std::string endDate = curDate.substr(0, curDate.find(' '));
			int pos1 = endDate.find('-');
			int pos2 = endDate.rfind('-');
			int year = stoi(endDate.substr(0, pos1));
			int month = stoi(endDate.substr(pos1 + 1, pos2));
			int day = stoi(endDate.substr(pos2 + 1));
			if (month > 3)
				month -= 3;
			else {
				month = 12 + month - 3;
				--year;
			}

			char buf[64];
			sprintf(buf, "%04d-%02d-%02d", year, month, day);
			std::string startDate = std::string(buf);

			printf("222 startDate is %s, endDate is %s \n", startDate.c_str(), endDate.c_str());
			
            if (baseTool::checkDateIsExpired(srcDate, startDate, endDate)) {
            	printf("ok \n");
	            qianMingRiQiSuoYouRen->value->result = true;
            }
            else {
	            printf("no ok \n");
            	qianMingRiQiSuoYouRen->value->result = false;
            }
        } else {
            printf ("%s, date format %s is incorrect \n", __PRETTY_FUNCTION__, qianMingRiQiSuoYouRen->value->OutData.c_str());

            qianMingRiQiSuoYouRen->value->result = false;
        }

        qianMing.result = qianMingRiQiSuoYouRen->value->result && qianMing.result;
    }

    //判定所属机构是否为公司
    if (suoYouRenShouJiHao.OutData.empty() && !daiLiRenXingMing.OutData.empty() &&
        !daiLiRenShouJiHao.OutData.empty()) {
        //公司
        suoShuJiGou.result = true;
        printf("_c_algClass_0202_FuZhou::ResultEdit() not personal !\n");
    } else {
        //个人
        baseTool::closeMemberItemWriteResultByName(pResultMemberList, "daiLiRenShouJiHao");
        baseTool::closeMemberItemWriteResultByName(pResultMemberList, "daiLiRenXingMingShuChu");
    }

    //新车不检车牌
    if(baseTool::checkIsNewCar(pAllParamVector))
    {
        chePaiHao.result = true;
    }

    //如果照片清晰度为false 则只输出照片清晰度的错误信息其他信息不输出
    baseTool::checkMemberItemAndSetAllUnOutput(pResultMemberList, baseTool::getMemberItemByName(pResultMemberList,"zhaoPianQingXiDu"));
    return true;
}
