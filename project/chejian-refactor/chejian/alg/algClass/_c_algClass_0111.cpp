#include "_c_algClass_0111.h"
#include "../base/baseTool.h"

bool _c_algClass_0111::seekMemberListPointer()
{
	mainPhotoType = e0111;
	subPhotoType = eCLZQFXS45DZP_A;

	pInMemberList = &inMemberList;
	pResultMemberList = &resultMemberList;

	inListVector.push_back({"xiaoChe", &inMemberList});
	inListVector.push_back({"daChe", &inMemberList_daChe});
	inListVector.push_back({"moTuo", &inMemberList_moTuo});
	inListVector.push_back({"video", &inMemberList_video});

	resultListVector.push_back({"xiaoChe", &resultMemberList});
	resultListVector.push_back({"daChe", &resultMemberList_daChe});
	resultListVector.push_back({"moTuo", &resultMemberList_moTuo});
	resultListVector.push_back({"video", &resultMemberList_video});

	return true;
}

void _c_algClass_0111::setAlgIds() {
	algIDs.push_back(_algType);
}

bool _c_algClass_0111::InParamEdit()
{
	dangAnZhaoPian.result = false;//默认值
	guangGaoLarge.result = true;
	guangGaoExist.result = true;
	paiSheJiaoDu.inData = "0";

    if(baseTool::checkCllxIsK3xOrK4x(pAllParamVector))
    {
		dangAnZhaoPian.result = false;
        _c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector, baseTool::getAlgItemCodeByPicType(subPhotoType, pAllAlgItemVector));
        if(algTask)
        {
			dangAnZhaoPian.result = true;
		}

    }else if(baseTool::checkCllxIsMx(pAllParamVector))
    {
		dangAnZhaoPian.result = false;
		pInMemberList = &inMemberList_moTuo;
		pResultMemberList = &resultMemberList_moTuo;
    }else
    {
	    _algType = alg0111_dache;

		pInMemberList = &inMemberList_daChe;
		pResultMemberList = &resultMemberList_daChe;
	    paiSheJiaoDu.inData = "0";
	}

    if (isVideo)
    {
		pInMemberList = &inMemberList_video;
		pResultMemberList = &resultMemberList_video;
		_algType = alg0111;
	}

	return true;
}

bool _c_algClass_0111::ResultEdit()
{
    if (!isVideo)
    {
		// 车辆颜色 有输入参数  不需要档案照片
		baseTool::openMemberItemWriteResultByName(pResultMemberList, "cheLiangYanSe");
		//cheBiao
		memberItem *pcheBiaoMingCheng = baseTool::getMemberItemByName(pResultMemberList, "cheBiaoMingCheng");
		memberItem *pcheBiao = baseTool::getMemberItemByName(pResultMemberList, "cheBiao");
		string cheBiaoIndata = baseTool::getObjectItemValueByName(pAllParamVector, "cheLiangPinPai");
		// 如果打开
        if( pcheBiaoMingCheng && pcheBiaoMingCheng->config.isOpen && pcheBiao && pcheBiao->value->result  )
        {
			pcheBiaoMingCheng->value->result = baseTool::compareClpp(cheBiaoIndata, pcheBiaoMingCheng->value->OutData);
			LOG(COMMON, INFO, "( chepai:[%s]  input_cheBiao:[%s]  output_cheBiao:[%s]   value:%d )",
                chePaiHao.inData.c_str(),  cheBiaoIndata.c_str(), pcheBiaoMingCheng->value->OutData.c_str() ,pcheBiaoMingCheng->value->result) ;
		}

		if (baseTool::checkCllxIsK3xOrK4x(pAllParamVector)) {
			if (baseTool::compareDate(shuiYinRiQi.inData, shuiYinRiQi.OutData)) {
				shuiYinRiQi.result = true;
			}

            if(dangAnZhaoPian.result)
            {
				memberItem *pxingLiJiaRecord = baseTool::getMemberItemByName(pResultMemberList, "xingLiJiaRecord");
				memberItem *pjiaoTaBanRecord = baseTool::getMemberItemByName(pResultMemberList, "jiaoTaBanRecord");
				memberItem *waiguanRecord = baseTool::getMemberItemByName(pResultMemberList, "waiguanRecord");

				baseTool::openMemberItemWriteResultByName(pResultMemberList, "xingLiJia");
				baseTool::openMemberItemWriteResultByName(pResultMemberList, "jiaoTaBan");
				baseTool::openMemberItemWriteResultByName(pResultMemberList, "guangGaoExist");
				baseTool::openMemberItemWriteResultByName(pResultMemberList, "guangGaoLarge");

				baseTool::openMemberItemWriteResultByName(pResultMemberList, "gaiZhuang");
				gaiZhuang.result = true;

				memberItem *cheLiangYanSe_ = baseTool::getMemberItemByName(pResultMemberList, "cheLiangYanSe");
				memberItem *jiaoTaBan_ = baseTool::getMemberItemByName(pResultMemberList, "jiaoTaBan");
				memberItem *xingLiJia_ = baseTool::getMemberItemByName(pResultMemberList, "xingLiJia");

				jiaoTaBan_->value->result = pjiaoTaBanRecord->value->result;
				xingLiJia_->value->result = pxingLiJiaRecord->value->result;

				bool ispass = true;
				ispass = cheLiangYanSe_->config.isOpen ? ispass && cheLiangYanSe_->value->result : ispass;
				ispass = jiaoTaBan_->config.isOpen ? ispass && jiaoTaBan_->value->result : ispass;
				ispass = xingLiJia_->config.isOpen ? ispass && xingLiJia_->value->result : ispass;
				gaiZhuang.result = ispass;
				// 车身是贴花判定
				memberItem *pguangGao = baseTool::getMemberItemByName(pResultMemberList, "guangGao");
				memberItem *pguangGaoLarge = baseTool::getMemberItemByName(pResultMemberList, "guangGaoLarge");
				memberItem *pguangGaoExist = baseTool::getMemberItemByName(pResultMemberList, "guangGaoExist");
				{
                    if ( pguangGao->value->OutData == "2" )
                    {
						pguangGaoLarge->value->result = false;
					}
                    if ( pguangGao->value->OutData != "0" )
                    {
						pguangGaoExist->value->result = false;
					}
				}
				//加入档案对比结论
				bool BwaiguanRecord = waiguanRecord && waiguanRecord->value->result;
				pguangGaoExist->value->result = (pguangGaoExist->value->result) || BwaiguanRecord;
			}
        }
        else if(baseTool::checkCllxIsMx(pAllParamVector))
        {
			baseTool::openMemberItemWriteResultByName(pResultMemberList, "anQuanMao");
		} else {
			std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector, "cheLiangLeiXing");
			std::string s_zzl = baseTool::getObjectItemValueByName(pAllParamVector, "zongZhiLiang");
			if (cllx.substr(0, 1)=="H") {
				int n_zzl = atoi(s_zzl.c_str());

                if(n_zzl > 3500)
                {
					baseTool::openMemberItemWriteResultByName(pResultMemberList, "zuoCeFangHuZhuangZhi");
				}
				baseTool::openMemberItemWriteResultByName(pResultMemberList, "zuoCeCheShenFanGuangBiaoShi");
			}
		}

        if(baseTool::checkIsNewCar(pAllParamVector))
        {
			baseTool::closeMemberItemWriteResultByName(pResultMemberList, "chePaiHao");
		}

        if (!baseTool::isNeedCheckChePaiHao(pAllParamVector))
        {
			baseTool::closeMemberItemWriteResultByName(pResultMemberList, "chePaiHao");
		}
	}

	return true;
}

std::string _c_algClass_0111::getPhotoName(std::string algcode)
{
	std::string defaultPhotoName = getPhotoBaseName(algcode);

	std::string cheLiangPinPai = getObjectItemValueByName("cheLiangPinPai");
	std::string cheLiangXingHao = getObjectItemValueByName("cheLiangXingHao");
	std::string cheShenYanSe = getObjectItemValueByName("cheLiangYanSe");

	std::string clpp = GetPhotoAttrValue(cheLiangPinPai);
	std::string clxh = GetPhotoAttrValueFileNameFormating(cheLiangXingHao);
	std::string csys = GetPhotoAttrValue(cheShenYanSe);

	string result = "_" + clxh + "_" + csys + "_" + clpp;
	defaultPhotoName += result;

	return defaultPhotoName;
}

