#include "_c_algClass_0288.h"
#include "../base/baseTool.h"

bool _c_algClass_0288::seekMemberListPointer() {
    mainPhotoType = e0288;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0288::InParamEdit() {
    //格式化发证日期
    faZhengRiQi.inData = baseTool::formatingDate(faZhengRiQi.inData);
    qiangZhiBaoFeiQiZhi.inData = baseTool::formatingDate(qiangZhiBaoFeiQiZhi.inData ) ;
    return true;
}

bool _c_algClass_0288::ResultEdit() {
    //如果印章数<=5 则判定通过否则不通过
    if (atoi(yinZhangShu.OutData.c_str()) <= 5) {
        yinZhangShu.result = true;
    }
    
    return true;
}

std::string _c_algClass_0288::getPhotoName(std::string algcode) {

    std::string defaultPhotoName = getPhotoBaseName(algcode);
    std::string xingShiZhengBianHao = getObjectItemValueByName("xingShiZhengBianHao");
    std::string xingShiZhengFaZhengRiQi = getObjectItemValueByName("faZhengRiQi");
    std::string chuCiDengJiRiQi = getObjectItemValueByName("chuCiDengJiRiQi");
    std::string qiangZhiBaoFeiQiZhi = getObjectItemValueByName("qiangZhiBaoFeiQiZhi");
    std::string heDingZaiKe = getObjectItemValueByName("heDingZaiKe");
    std::string xszbh =  GetPhotoAttrValue(xingShiZhengBianHao);
    std::string xszfzrq  = GetPhotoAttrValueDateFormting(xingShiZhengFaZhengRiQi);
    std::string  zcrq = GetPhotoAttrValueDateFormting(chuCiDengJiRiQi);
    std::string  qzbfqz = GetPhotoAttrValueDateFormting(qiangZhiBaoFeiQiZhi);
    std::string  hdzk = GetPhotoAttrValue(heDingZaiKe);
    string result = "_" + xszbh + "_" + xszfzrq + "_" + zcrq + "_" + qzbfqz + "_"  + hdzk;
    defaultPhotoName += result ;
	
    return defaultPhotoName;
}

