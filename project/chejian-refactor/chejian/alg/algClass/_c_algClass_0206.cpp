#include "_c_algClass_0206.h"
#include "../base/baseTool.h"

bool _c_algClass_0206::seekMemberListPointer()
{
    mainPhotoType = e0206;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    inListVector.push_back({"moTuo",&inMemberList_moTuo});
    resultListVector.push_back({"default",&resultMemberList});
    resultListVector.push_back({"moTuo",&resultMemberList_moTuo});

    return true;
}

void _c_algClass_0206::setAlgIds() {
	algIDs.push_back(algTypeIdentify);
	algIDs.push_back(_algType);
	algIDs.push_back(alg0203);
}

bool _c_algClass_0206::InParamEdit()
{
    //格式化检验结束时间
    jianYanJieShuShiJian.inData = baseTool::formatingDate(jianYanJieShuShiJian.inData);
    if (baseTool::checkCllxIsMx(pAllParamVector) ){
        pInMemberList =&inMemberList_moTuo ;
        pResultMemberList =&resultMemberList_moTuo ;
    }

    return true;
}

bool _c_algClass_0206::ResultEdit()
{
    //如果wanShuiZhengMing 为false 则只输出wanShuiZhengMing对应信息
    bool isWanShuiZhengMing = !baseTool::checkMemberItemAndSetAllUnOutput(pResultMemberList, baseTool::getMemberItemByName(pResultMemberList,"zhaoPianLeiXing"));

    if(!baseTool::checkCllxIsMx(pAllParamVector)){
        if(isWanShuiZhengMing){
             baseTool::openMemberItemWriteResultByName(pResultMemberList,"wanShuiPingZhengHao");
             baseTool::openMemberItemWriteResultByName(pResultMemberList,"kaiJuShuiWuJiGuan");
        }
    }

    return true;
}

std::string _c_algClass_0206::getPhotoName(std::string algcode)
{
	std::string defaultPhotoName = getPhotoBaseName(algcode);

	std::string jianYanJieShuShiJian = getObjectItemValueByName("jianYanJieShuShiJian");
	std::string jssj = GetPhotoAttrValueDateFormting(jianYanJieShuShiJian);
	string result = "_" + jssj;
	defaultPhotoName += result;

	return defaultPhotoName;
}
