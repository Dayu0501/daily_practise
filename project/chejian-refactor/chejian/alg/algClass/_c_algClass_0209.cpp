#include "_c_algClass_0209.h"
#include "../base/baseTool.h"

bool _c_algClass_0209::seekMemberListPointer()
{
    mainPhotoType = e0209;
    subPhotoType = eWQDZP2;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;
    inListVector.push_back({"yiye",&inMemberList});
    inListVector.push_back({"erye",&inMemberList_erye});

    resultListVector.push_back({"yiye",&resultMemberList});
    resultListVector.push_back({"erye",&resultMemberList_erye});

    return true;
}

bool _c_algClass_0209::InParamEdit()
{
    // 格式化尾气检测时间
    weiQiJianCeShiJian.inData = baseTool::formatingDate(weiQiJianCeShiJian.inData);
    //判断当天日期是否为空
    if(dangTianRiQi.inData.empty())
    {
        //获取当天日期
        dangTianRiQi.inData = baseTool::formatingDate(baseTool::getDangTianRiQi());
    }
    //将尾气检测时间添加到shiJianVector中
    shiJianVector.push_back(weiQiJianCeShiJian.inData);

    //格式化尾气检测时间
    weiQiJianCeShiJian_erye.inData = baseTool::formatingDate(weiQiJianCeShiJian_erye.inData);
    //判断当天日期是否为空
    if(dangTianRiQi_erye.inData.empty())
    {
        //获取当天日期
        dangTianRiQi_erye.inData = baseTool::formatingDate(baseTool::getDangTianRiQi());
    }
    //将尾气检测时间添加到shiJianVector中
    shiJianVector_erye.push_back(weiQiJianCeShiJian_erye.inData);
    weiQiJianCeShiJian.inData = weiQiJianCeShiJian_erye.inData = baseTool::formatingDate(jianYanJieShuShiJian.inData);

    return true;
}


#define SET_OR_VELUE(_a_,_b_) ((_a_) = (_b_) = ((_a_ ) || (_b_)) )
#define SET_OR_VELUE_RESULT(_a_,_b_)  SET_OR_VELUE(_a_.result , _b_.result)

bool _c_algClass_0209::ResultEdit()
{
    memberItem* phaoPaiZhongLei = baseTool::getMemberItemByName(pInMemberList,"haoPaiZhongLei");
    memberItem* pranliaozhonglei = baseTool::getMemberItemByName(pInMemberList,"ranLiangZhongLei");
    if(phaoPaiZhongLei && pranliaozhonglei)
    {
        //新能源全部通过
        if(baseTool::checkRlzlIsXinNengYuan(phaoPaiZhongLei->value->inData) || baseTool::checkHaopaiIsXinNenYuan(pranliaozhonglei->value->inData) )
        {

            for(unsigned int i = 0 ; i < pResultMemberList->size() ; i++ ){
                ( (memberItem)(*pResultMemberList)[i]).value->result = true ;
            }

            std::string algName = baseTool::getAlgItemNameByPicType(eWQDZP2, pAllAlgItemVector);
            _c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector, baseTool::getAlgItemCodeByPicType(eWQDZP2, pAllAlgItemVector));
            if(algTask)
            {
                baseTool::writeResultByJGAndSM(algTask,PASS, "[通过]");
            }

            return  true;
        }
    }

    //尾气单照片一结果 || 尾气单照片二结果
    SET_OR_VELUE_RESULT(huanBaoJianYanJieLun_erye,huanBaoJianYanJieLun);
    SET_OR_VELUE_RESULT(chePaiHao_erye,chePaiHao);
    SET_OR_VELUE_RESULT(cheJiaHao_erye,cheJiaHao);
    SET_OR_VELUE_RESULT(yinZhang_erye,yinZhang);
    SET_OR_VELUE_RESULT(qianMing_erye,qianMing);
    SET_OR_VELUE_RESULT(yinZhang_CMA_erye,yinZhang_CMA);
    SET_OR_VELUE_RESULT(weiQiJianCeShiJian_erye,weiQiJianCeShiJian);
    SET_OR_VELUE_RESULT(faDongJiXingHao_erye,faDongJiXingHao);
    SET_OR_VELUE_RESULT(jianCeShiJian_erye,jianCeShiJian);
    SET_OR_VELUE_RESULT(qianMing_caoZuoYuan_erye,qianMing_caoZuoYuan);
    SET_OR_VELUE_RESULT(qianMing_jiaShiYuan_erye,qianMing_jiaShiYuan);
    SET_OR_VELUE_RESULT(qianMing_piZhunRen_erye,qianMing_piZhunRen);
    SET_OR_VELUE_RESULT(qianMing_shenHeRen_erye,qianMing_shenHeRen);
    SET_OR_VELUE_RESULT(dianZiBiaoGe_erye,dianZiBiaoGe);
    //SET_OR_VELUE_RESULT(huanBaoDan_erye,huanBaoDan);
    //新车不检车牌
    if(baseTool::checkIsNewCar(pAllParamVector))
    {
        chePaiHao.result = true;
        chePaiHao_erye.result = true;
    }

    //如果huanBaoDan 结果为true 则只输出huanBaoDan
    checkMemberItemAndSetAllUnOutput("huanBaoDan_yiye",true);

	std::string algName = baseTool::getAlgItemNameByPicType(eWQDZP2, pAllAlgItemVector);
	_c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector, baseTool::getAlgItemCodeByPicType(eWQDZP2, pAllAlgItemVector));
	if(algTask)
    {
	    checkMemberItemAndSetAllUnOutput("huanBaoDan_erye",true,&resultMemberList_erye) ;
	    baseTool::wirteResultByMemberList(algName, algTask, &resultMemberList_erye);
    }

    return true;
}

std::string _c_algClass_0209::getPhotoName(std::string algcode)
{
	std::string defaultPhotoName = getPhotoBaseName(algcode);

	std::string jianYanJieShuShiJian = getObjectItemValueByName("jianYanJieShuShiJian");
	std::string faDongJiHao = getObjectItemValueByName("faDongJiHao");
	std::string cheLiangXingHao = getObjectItemValueByName("cheLiangXingHao");
	std::string faDongJiXingHao = getObjectItemValueByName("faDongJiXingHao");

	std::string jssj = GetPhotoAttrValueDateFormting(jianYanJieShuShiJian);
	std::string fdjh = GetPhotoAttrValueFileNameFormating(faDongJiHao);
	std::string clxh = GetPhotoAttrValueFileNameFormating(cheLiangXingHao);
	std::string fdjxh = GetPhotoAttrValueFileNameFormating(faDongJiXingHao);
	string result = "_" + jssj + "_" + fdjxh + "_" + fdjh + "_" + clxh;
	defaultPhotoName += result;

	return defaultPhotoName;
}
