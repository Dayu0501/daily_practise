#include "_c_algClass_0287.h"
#include "../base/baseTool.h"

bool _c_algClass_0287::seekMemberListPointer()
{
    mainPhotoType = e0287;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"def",&inMemberList});
    resultListVector.push_back({"def",&resultMemberList});

    return true;
}

bool _c_algClass_0287::InParamEdit()
{
    //新车不检测行驶证
    if(baseTool::checkIsNewCar(pAllParamVector))
    {
        //结果输出中所有项的结果判定为通过
        baseTool::checkMemberItemAndSetAllUnOutput(pResultMemberList, baseTool::getMemberItemByName(pResultMemberList,"xinChe"));
        return false;
    }

    //格式化发证日期
    faZhengRiQi.inData = baseTool::formatingDate(faZhengRiQi.inData);

    return true;
}

bool _c_algClass_0287::ResultEdit()
{
    //2008年10月1号之前的不检测发证日期
    try {
        if ( faZhengRiQi.inData != "" && faZhengRiQi.inData != "无数据") {
            printf("faZhengRiQi.inData :%s\n",faZhengRiQi.inData.c_str());
            int n_fzrq = baseTool::str2Int(faZhengRiQi.inData);
            if (n_fzrq < 20081001) {
                faZhengRiQi.result = true;
            }
        }
    } catch (const std::exception &e) {
        printf("fzrq formating fail: %s \n", faZhengRiQi.inData.c_str());
    }

    //如果照片清晰度为false 则只输出照片清晰度的错误信息其他信息不输出
    baseTool::checkMemberItemAndSetAllUnOutput(pResultMemberList, baseTool::getMemberItemByName(pResultMemberList,"zhaoPianQingXiDu"));

    return true;
}
std::string _c_algClass_0287::getPhotoName(std::string algcode)
{

    std::string defaultPhotoName = getPhotoBaseName(algcode);

    std::string xingShiZhengBianHao = getObjectItemValueByName("xingShiZhengBianHao");
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

    return defaultPhotoName;
}
