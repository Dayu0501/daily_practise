#include "_c_algClass_0322.h"
#include "../base/baseTool.h"

bool _c_algClass_0322::seekMemberListPointer() {
    mainPhotoType = e0322;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;
    inListVector.push_back({"default",&inMemberList});
    inListVector.push_back({"moTuo",&inMemberList_moTuo});
    inListVector.push_back({"video",&inMemberList_video});

    resultListVector.push_back({"default",&resultMemberList});
    resultListVector.push_back({"moTuo",&resultMemberList_moTuo});
    resultListVector.push_back({"video",&resultMemberList_video});

    return true;
}

void _c_algClass_0322::setAlgIds() {
	algIDs.push_back(_algType);
	algIDs.push_back(alg0321);
	algIDs.push_back(algShuiYinRiQi);
}

bool _c_algClass_0322::InParamEdit() {
    zhiDongLeiXing.inData = "1";
    zhouLeiXing.inData = "1";
    //修正水印日期格式
    shuiYinRiQi.inData = baseTool::formatingDate(shuiYinRiQi.inData);

    //获取车辆类型，并判断是否为小车
    std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector,"cheLiangLeiXing");
    if(cllx.substr(0, 2) == "K3" || cllx.substr(0, 2) == "K4")
        cheLiangLeiXing.inData = "1";
    else if(cllx.substr(0, 1) == "M")
        cheLiangLeiXing.inData = "3";
    else
        cheLiangLeiXing.inData = "2";

    if (baseTool::checkCllxIsMx(pAllParamVector) ) {
        pInMemberList = &inMemberList_moTuo ;
        pResultMemberList = &resultMemberList_moTuo ;
    }

    if (isVideo) {
        pInMemberList = &inMemberList_video;
        pResultMemberList = &resultMemberList_video;
        _algType = alg0322;
    }

    return true;
}

bool _c_algClass_0322::ResultEdit() {
    if (!isVideo) {
        memberItem *zuo = baseTool::getMemberItemByName(pResultMemberList, "zuoDeng");
        memberItem *you = baseTool::getMemberItemByName(pResultMemberList, "youDeng");
        memberItem *zhi = baseTool::getMemberItemByName(pResultMemberList, "zhiDongDeng");
        if (zhi) {
            //短路逻辑
            zhi->value->result = (zuo && zuo->value->result) || (you && you->value->result);
        }

	    if(baseTool::checkCllxIsMx(pAllParamVector) ) {
		    bool val = zuoDeng.result || youDeng.result;
		    zuoDeng.result = youDeng.result = val;
	    }

        //新车不检车牌
        if (baseTool::checkIsNewCar(pAllParamVector)) {
            chePaiHao.result = true;
        }
    }

    return true;
}

std::string _c_algClass_0322::getPhotoName(std::string algcode) {
	std::string defaultPhotoName = getPhotoBaseName(algcode);

	std::string jianYanJiGouBianHao = getObjectItemValueByName("jianYanJiGouBianHao");
	std::string jyjgbh = GetPhotoAttrValue(jianYanJiGouBianHao);
	string result = "_" + jyjgbh;
	defaultPhotoName += result;

	return defaultPhotoName;
}
