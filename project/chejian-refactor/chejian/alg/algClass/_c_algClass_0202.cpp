#include "_c_algClass_0202.h"
#include "../base/baseTool.h"

bool _c_algClass_0202::seekMemberListPointer() {
    mainPhotoType = e0202;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    inListVector.push_back({"moTuo",&inMemberList_moTuo});

    resultListVector.push_back({"default",&resultMemberList});
    resultListVector.push_back({"moTuo",&resultMemberList_moTuo});

    return true;
}

bool _c_algClass_0202::InParamEdit() {
    if (baseTool::checkCllxIsMx(pAllParamVector) ){
        pInMemberList = &inMemberList_moTuo ;
        pResultMemberList = &resultMemberList_moTuo  ;
    }

    return true;
}

bool _c_algClass_0202::ResultEdit() {
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

    //    if(diZhi.result)
    //    {
    //       diZhi.result = baseTool::isAddress(pAlgApi->diZhi.OutData);
    //    }

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

    //固定电话合法性判定 to do

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

    return true;
}
