#include "_c_algClass_0206_BaoShan.h"
#include "../base/baseTool.h"

bool _c_algClass_0206_BaoShan::seekMemberListPointer()
{
    mainPhotoType = e0206;
//    subPhotoType = e0206;
    _algType = algTypeIdentify;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;
    inListVector.push_back({"default",&inMemberList});
    inListVector.push_back({"moTuo",&inMemberList_moTuo});

    resultListVector.push_back({"default",&resultMemberList});
    resultListVector.push_back({"moTuo",&resultMemberList_moTuo});
    resultListVector.push_back({"baodan",&resultMemberList_baodan});

    return true;
}

bool _c_algClass_0206_BaoShan::InParamEdit()
{
    //格式化检验结束时间
    jianYanJieShuShiJian.inData = baseTool::formatingDate(jianYanJieShuShiJian.inData);
    if (baseTool::checkCllxIsMx(pAllParamVector) ){
        pInMemberList =&inMemberList_moTuo ;
        pResultMemberList =&resultMemberList_moTuo ;
    }
    return true;
}

bool _c_algClass_0206_BaoShan::ResultEdit()
{
    memberItem* table_id = baseTool::getMemberItemByName(pResultMemberList,"tableID");
    if(table_id && table_id->value->OutData == "9") //baodan
    {
        pResultMemberList = &resultMemberList_baodan;
    }
    else if(table_id && table_id->value->OutData == "27")
    {
        pResultMemberList = &resultMemberList;
    }
    
    

    //如果wanShuiZhengMing 为false 则只输出wanShuiZhengMing对应信息
    bool isWanShuiZhengMing = !baseTool::checkMemberItemAndSetAllUnOutput(pResultMemberList, baseTool::getMemberItemByName(pResultMemberList,"wanShuiZhengMing"));

    if(!baseTool::checkCllxIsMx(pAllParamVector)){
        if(isWanShuiZhengMing){
             baseTool::openMemberItemWriteResultByName(pResultMemberList,"wanShuiPingZhengHao");
             baseTool::openMemberItemWriteResultByName(pResultMemberList,"kaiJuShuiWuJiGuan");
        }
    }

    return true;
}
