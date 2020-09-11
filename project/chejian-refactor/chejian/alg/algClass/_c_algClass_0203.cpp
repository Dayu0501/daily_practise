#include "_c_algClass_0203.h"
#include "../base/baseTool.h"

bool _c_algClass_0203::seekMemberListPointer()
{
    mainPhotoType = e0203;
    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"zhiZhi",&resultMemberList});
    resultListVector.push_back({"dianZi",&resultMemberList_dianZi});

    inListVector.push_back({"moTuo",&inMemberList_moTuo});
    resultListVector.push_back({"moTuo_zhiZhi",&resultMemberList_moTuo});
    resultListVector.push_back({"moTuo_dianZi",&resultMemberList_moTuo_dianZi});

    return true;
}

bool _c_algClass_0203::InParamEdit()
{
    //格式化生效日期，终止日期，检验结束时间
    shengXiaoRiQi.inData = baseTool::formatingDate(shengXiaoRiQi.inData);
    zhongZhiRiQi.inData = baseTool::formatingDate(zhongZhiRiQi.inData);
    jianYanJieShuShiJian.inData = baseTool::formatingDate(jianYanJieShuShiJian.inData);

    if( baseTool::checkCllxIsMx(pAllParamVector) ){
        pInMemberList = &inMemberList_moTuo ;
        pResultMemberList = &resultMemberList_moTuo ;
     }

    //如果存在电子保单 则不进行后面的redis 流程
    if(pWangLuoJieKouReturnVector != NULL)
    {
        for (unsigned int i = 0; i < pWangLuoJieKouReturnVector->size(); i++)
        {
            std::string biaoShi = baseTool::getWangLuoJieKouReturnInfoBiaoShi((*pWangLuoJieKouReturnVector)[i]);
            if (biaoShi == "18C23")
            {
                //如果电子保单返回内容有效,则不需要在走算法流程
                if(baseTool::checkWangLuoJieKouReturnInfoIsValid((*pWangLuoJieKouReturnVector)[i]))
                    return false;
                break;
            }
        }
    }

    return true;
}

bool _c_algClass_0203::ResultEdit()
{
    //判断是电子保单还是纸质保单，如果未电子保单则切换到电子保单输出结果集
    if(dianZiBaoDan.result)
    {
	    if (baseTool::checkCllxIsMx(pAllParamVector))
	    {
		    pResultMemberList = &resultMemberList_moTuo_dianZi;
	    } else {

		    pResultMemberList = &resultMemberList_dianZi;
	    }
    }
    //电子保单  抄件  副本  正本   联网查询结果   完税证明
    //baoDan
    memberItem* pzhengBenHuoFuBen = baseTool::getMemberItemByName(pResultMemberList,"zhengBenHuoFuBen");
    memberItem* pchaoBen = baseTool::getMemberItemByName(pResultMemberList,"chaoBen");
    memberItem* pzhiZhiBaoDan = baseTool::getMemberItemByName(pResultMemberList,"zhiZhiBaoDan");

    if(pzhengBenHuoFuBen)
    {
        pzhengBenHuoFuBen->value->result = pzhengBenHuoFuBen->value->result   || (pzhiZhiBaoDan && pzhiZhiBaoDan->value->result );
    }

    // 如果是抄本 检测项(zhengBenHuoFuBen:正本或副本 ) 不通过
    if(pchaoBen && pchaoBen->config.isOpen &&  pchaoBen->value->result )
    {
        pzhengBenHuoFuBen->value->result = false ;
    }

   memberItem* pwanShuiPingZhengHao = baseTool::getMemberItemByName(pResultMemberList,"wanShuiPingZhengHao");
   memberItem* pkaiJuShuiWuJiGuan   = baseTool::getMemberItemByName(pResultMemberList,"kaiJuShuiWuJiGuan");
   memberItem* pcheChuanShui   = baseTool::getMemberItemByName(pResultMemberList,"cheChuanShui");

    if(pcheChuanShui)
    {
        pcheChuanShui->value->result = (pcheChuanShui->value->result)|| (pwanShuiPingZhengHao && pwanShuiPingZhengHao->value->result) || (pkaiJuShuiWuJiGuan && pkaiJuShuiWuJiGuan->value->result) ;
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

std::string _c_algClass_0203::getPhotoName(std::string algcode)
{
    std::string defaultPhotoName = getPhotoBaseName(algcode);

   std::string heDingZaiKe = getObjectItemValueByName("heDingZaiKeShu");
   std::string jianYanJieShuShiJian = getObjectItemValueByName("jianYanJieShuShiJian");
   std::string shengXiaoRiQi = getObjectItemValueByName("shengXiaoRiQi");
   std::string zhongZhiRiQi = getObjectItemValueByName("zhongZhiRiQi");
   std::string faDongJiHao = getObjectItemValueByName("faDongJiHao");

   std::string jssj = GetPhotoAttrValueDateFormting(jianYanJieShuShiJian);
   std::string hdzk = GetPhotoAttrValue(heDingZaiKe);
   std::string sxrq = GetPhotoAttrValueDateFormting(shengXiaoRiQi);
   std::string zzrq = GetPhotoAttrValueDateFormting(zhongZhiRiQi);
   std::string fdjh = GetPhotoAttrValueFileNameFormating(faDongJiHao);
   string result =   "_" + sxrq + "_" + zzrq + "_" + jssj + "_" + fdjh + "_" + hdzk;
   defaultPhotoName += result ;

   return defaultPhotoName;
}
