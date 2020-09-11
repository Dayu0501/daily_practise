#include "_c_algClass_0202_ZhuHai.h"
#include "base/baseTool.h"

_c_algClass_0202_ZhuHai::_c_algClass_0202_ZhuHai() {

}

bool _c_algClass_0202_ZhuHai::ResultEdit() {
    printf("***** %s\n", __PRETTY_FUNCTION__ );

    if (!suoYouRenShouJiHao.OutData.empty() || !daiLiRenShouJiHao.OutData.empty()) {
        suoYouRenShouJiHao.result = true;
        daiLiRenShouJiHao.result = true;
    } else {
        suoYouRenShouJiHao.result = false;
        daiLiRenShouJiHao.result = false;
    }

    if (!daiLiRenXingMing.OutData.empty() || xingMing.result) {
        daiLiRenXingMing.result = true;
        xingMing.result = true;
    } else {
        daiLiRenXingMing.result = false;
        xingMing.result = false;
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