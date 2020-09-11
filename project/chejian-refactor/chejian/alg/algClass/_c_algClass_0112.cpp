#include "_c_algClass_0112.h"
#include "../base/baseTool.h"

bool _c_algClass_0112::seekMemberListPointer()
{
	mainPhotoType = e0112;

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

void _c_algClass_0112::setAlgIds() {
	algIDs.push_back(_algType);
}

bool _c_algClass_0112::InParamEdit() {
	paiSheJiaoDu.inData = "1";

	jiaoTaBanRecord.result = true;
	baoWeiRecord.result = true;
	weiYiRecord.result = true;

	_c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector, baseTool::getAlgItemCodeByPicType(subPhotoType, pAllAlgItemVector));
	if(algTask)
	{
		dangAnZhaoPian.result = true;
	}

	//判定使用大小车接口
	if (baseTool::checkCllxIsK3xOrK4x(pAllParamVector)) {
	} else if (baseTool::checkCllxIsMx(pAllParamVector)) {
		pInMemberList = &inMemberList_moTuo;
		pResultMemberList = &resultMemberList_moTuo;
	} else {
		pInMemberList = &inMemberList_daChe;
		pResultMemberList = &resultMemberList_daChe;

		_algType = alg0112_dache;
	}

	if (isVideo) 
	{
		pInMemberList = &inMemberList_video;
		pResultMemberList = &resultMemberList_video;
		_algType = alg0112;
	}

	return true;
}

bool _c_algClass_0112::ResultEdit()
{
    if (!isVideo)
    {
        if (baseTool::checkCllxIsK3xOrK4x(pAllParamVector))
        {
            if (baseTool::compareDate(shuiYinRiQi.inData, shuiYinRiQi.OutData))
            {
				shuiYinRiQi.result = true;
			}

	        paiQiKongShuLiang.result = atoi(paiQiKongShuLiang.OutData.c_str()) <= 4;

			if (dangAnZhaoPian.result) {
				memberItem *jiaoTaBan_ = baseTool::getMemberItemByName(pResultMemberList, "jiaoTaBanRecord");
				memberItem *paiQiKongShuLiang_ = baseTool::getMemberItemByName(pResultMemberList, "paiQiKongShuLiang");
				memberItem *weiYi_ = baseTool::getMemberItemByName(pResultMemberList, "weiYiRecord");
				memberItem *baoWei_ = baseTool::getMemberItemByName(pResultMemberList, "baoWeiRecord");

				if(jiaoTaBan_->config.isOpen && paiQiKongShuLiang_->config.isOpen && weiYi_->config.isOpen && baoWei_->config.isOpen)
				{
					bool cond = jiaoTaBan_->value->result || paiQiKongShuLiang_->value->result
					            || weiYi_->value->result || baoWei_->value->result;
					gaiZhuang.result = cond;
				}
			}

		} else if (baseTool::checkCllxIsMx(pAllParamVector)) {
			memberItem *paiQiKongShuLiang_ = baseTool::getMemberItemByName(pResultMemberList, "paiQiKongShuLiang");
			if (paiQiKongShuLiang_->config.isOpen) {
				gaiZhuang.result = paiQiKongShuLiang_->value->result;
			}

		} else {
			std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector, "cheLiangLeiXing");
			std::string s_zzl = baseTool::getObjectItemValueByName(pAllParamVector, "zhongZhiLiang");
            if (cllx.substr(0, 1) == "H")
            {
				int n_zzl = atoi(s_zzl.c_str());
                if(n_zzl <= 3500)
                {
					baseTool::closeMemberItemWriteResultByName(pResultMemberList, "houXiaBuFangHuZhuangZhi");
					baseTool::closeMemberItemWriteResultByName(pResultMemberList, "youCeFangHuZhuangZhi");
					baseTool::closeMemberItemWriteResultByName(pResultMemberList, "penTuFangDaChePai");
                }
                else if(n_zzl <= 4500)
                {
					baseTool::closeMemberItemWriteResultByName(pResultMemberList, "penTuFangDaChePai");
				}

                if ((cllx.substr(0, 2)=="H1") || (cllx.substr(0, 2)=="H5"))
                {
					baseTool::closeMemberItemWriteResultByName(pResultMemberList, "cheLiangWeiBuBiaoZhi");
				}
			} else {
				baseTool::closeMemberItemWriteResultByName(pResultMemberList, "houXiaBuFangHuZhuangZhi");
				baseTool::closeMemberItemWriteResultByName(pResultMemberList, "youCeFangHuZhuangZhi");
				baseTool::closeMemberItemWriteResultByName(pResultMemberList, "penTuFangDaChePai");
				baseTool::closeMemberItemWriteResultByName(pResultMemberList, "houCheShenFanGuangBiaoShi");
				baseTool::closeMemberItemWriteResultByName(pResultMemberList, "youCeCheShenFanGuangBiaoShi");
				baseTool::closeMemberItemWriteResultByName(pResultMemberList, "cheLiangWeiBuBiaoZhi");
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

std::string _c_algClass_0112::getPhotoName(std::string algcode)
{
	std::string defaultPhotoName = getPhotoBaseName(algcode);

	std::string cheLiangPinPai = getObjectItemValueByName("cheLiangPinPai");
	std::string cheLiangXingHao = getObjectItemValueByName("cheLiangXingHao");
	std::string cheShenYanSe = getObjectItemValueByName("cheLiangYanSe");

	std::string clpp = GetPhotoAttrValue(cheLiangPinPai);
	std::string clxh = GetPhotoAttrValueFileNameFormating(cheLiangXingHao);
	std::string csys = GetPhotoAttrValue(cheShenYanSe);

	string result = "_" + clxh + "_" + "_" + csys + "_" + clpp;
	defaultPhotoName += result;

	return defaultPhotoName;
}
