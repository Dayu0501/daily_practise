#include "_c_algClass_0205.h"
#include "../base/baseTool.h"

bool _c_algClass_0205::seekMemberListPointer()
{
    mainPhotoType = e0205;
    subPhotoType = eCLSBDHZP_TYM;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

void _c_algClass_0205::setAlgIds() {
	algIDs.push_back(_algType);

	memberItem *tuoMo = baseTool::getMemberItemByName(pResultMemberList, "tuoMo");
	if (tuoMo && tuoMo->config.isOpen)
		algIDs.push_back(alg0113);
}

bool _c_algClass_0205::InParamEdit()
{
    //获取当天时间
    dangTianRiQi.inData = baseTool::formatingDate(baseTool::getDangTianRiQi());

    return true;
}

bool _c_algClass_0205::ResultEdit()
{
    if(jianYanXiang.size() > 19)
    {
        jianYanXinXi.result = true;
        for(unsigned int i=0; i < 9; i++)
        {
            if(jianYanXiang[i] == 0)
            {
                jianYanXinXi.result = false;
                break;
            }
        }
        if(jianYanXiang[19] == 0)
        {
            jianYanXinXi.result = false;
        }

        std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector,"cheLiangLeiXing");
        //小车
        if(cllx.find("K") != std::string::npos)
        {
            for(unsigned int i = 9; i < 19; i++)
            {
                if(jianYanXiang[i] == 1)
                {
                    jianYanXinXi.result = false;
                    break;
                }
            }
        }
    }

	_c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector, baseTool::getAlgItemCodeByPicType(eCLSBDHZP_TYM, pAllAlgItemVector));
    if(algTask!=NULL)
    {
         dangAnZhaoPian.result = true;
		 memberItem* dangAnZhaoPian_=baseTool::getMemberItemByName(pResultMemberList, "dangAnZhaoPian") ;
	
		//打开		taYinMo
		//tuoMo	
		if ( dangAnZhaoPian_->config.isOpen )
		 {
			 baseTool::openMemberItemWriteResultByName(pResultMemberList , "taYinMo");
			 baseTool::openMemberItemWriteResultByName(pResultMemberList , "tuoMo") ;
		 }

    }else{
        dangAnZhaoPian.result = false;
	}

    //新车不检车牌
    if(baseTool::checkIsNewCar(pAllParamVector))
    {
        chePaiHao.result = true;
    }

    //获取初次登记日期
    std::string cjdjrq = baseTool::getObjectItemValueByName(pAllParamVector,"chuCiDengJiRiQi");
    //如果车辆等级时间 > 10 年 则将 引车检验员 和 地盘检验员输出开启
    if(baseTool::isTenYears(cjdjrq))
    {
        baseTool::changeCheckAlgBaseParamElementByName(pResultMemberList, "qianZi_yinCheJianYanYuan", "", true);
        baseTool::changeCheckAlgBaseParamElementByName(pResultMemberList, "qianZi_diPanJianYanYuan", "", true);
    }

    memberItem* qianZi_fuhe_Item=baseTool::getMemberItemByName(pResultMemberList, "qianZi_fuhe") ;
    if(qianZi_fuhe_Item != NULL)
    {
        if(qianZi_fuhe_Item->config.isOpen && qianZi_fuhe.result)
        {
            jianYanJieLun.result = true;
            qianZi_chaYanYuan.result = true;
        }
    }

    return true;
}
