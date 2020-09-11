#include "_c_algClass_0201.h"
#include "../base/baseTool.h"

bool _c_algClass_0201::seekMemberListPointer() {
    mainPhotoType = e0201;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    inListVector.push_back({"moTuo",&inMemberList_moTuo});
    resultListVector.push_back({"default",&resultMemberList});
    resultListVector.push_back({"moTuo",&resultMemberList_moTuo});

    return true;
}

void _c_algClass_0201::setAlgIds() {
	algIDs.push_back(_algType);
	algIDs.push_back(alg0228);
}

bool _c_algClass_0201::InParamEdit() {
    //格式化发证日期
    faZhengRiQi.inData = baseTool::formatingDate(faZhengRiQi.inData);

    //新车不检测行驶证
    if (baseTool::checkIsNewCar(pAllParamVector)) {
        //结果输出中所有项的结果判定为通过
        baseTool::setAllPass(pResultMemberList);
        return false;
    }

    if(baseTool::checkCllxIsMx(pAllParamVector) ){
        pInMemberList = &inMemberList_moTuo ;
        pResultMemberList =&resultMemberList_moTuo ;
    }

    return true;
}

bool _c_algClass_0201::ResultEdit() {
    //2008年10月1号之前的不检测发证日期
    try {
        if ( faZhengRiQi.inData != "" && faZhengRiQi.inData != "无数据") {
            printf("pAlgApi->faZhengRiQi.inData :%s\n", faZhengRiQi.inData.c_str());
            int n_fzrq = baseTool::str2Int(faZhengRiQi.inData);
            if (n_fzrq < 20081001) {
                faZhengRiQi.result = true;
            }
        }
    } catch (const std::exception &e) {
        printf("fzrq formating fail: %s \n", faZhengRiQi.inData.c_str());
    }

    //如果照片清晰度为false 则只输出照片清晰度的错误信息其他信息不输出
    baseTool::checkMemberItemAndSetAllUnOutput(pResultMemberList,
    	                           baseTool::getMemberItemByName(pResultMemberList, "zhaoPianQingXiDu"));

    //添加身份证结果判定逻辑
    memberItem* shenFenZhen_front = baseTool::getMemberItemByName(pResultMemberList, "isFront") ;
    memberItem* shenFenZhen_back = baseTool::getMemberItemByName(pResultMemberList, "isBack") ;

    if (shenFenZhen_front && shenFenZhen_back)
        shenFenZheng.result = shenFenZhen_front->value->result || shenFenZhen_back->value->result;

    if(xingShiZhengXinBianHao.inData == "无数据")
    {
        baseTool::closeMemberItemWriteResultByName(pResultMemberList, "xingShiZhengXinBianHao"); 
    }
    return true;
}

std::string _c_algClass_0201::getPhotoName(std::string algcode) {
    std::string defaultPhotoName = getPhotoBaseName(algcode);
    std::string xingShiZhengBianHao = getObjectItemValueByName("xingShiZhengXinBianHao");
    std::string xingShiZhengFaZhengRiQi = getObjectItemValueByName("faZhengRiQi");
    std::string chuCiDengJiRiQi = getObjectItemValueByName("chuCiDengJiRiQi");
    std::string qiangZhiBaoFeiQiZhi = getObjectItemValueByName("qiangZhiBaoFeiQiZhi");
    std::string heDingZaiKe = getObjectItemValueByName("heDingZaiKeShu");
    std::string xszbh =  GetPhotoAttrValue(xingShiZhengBianHao);
    std::string xszfzrq  = GetPhotoAttrValueDateFormting(xingShiZhengFaZhengRiQi);
    std::string  zcrq = GetPhotoAttrValueDateFormting(chuCiDengJiRiQi);
    std::string  qzbfqz = GetPhotoAttrValueDateFormting(qiangZhiBaoFeiQiZhi);
    std::string  hdzk = GetPhotoAttrValue(heDingZaiKe);
    string result = "_" + xszbh + "_" + xszfzrq + "_" + zcrq + "_" + qzbfqz + "_"  + hdzk;
    defaultPhotoName += result ;

    return defaultPhotoName ;
}

