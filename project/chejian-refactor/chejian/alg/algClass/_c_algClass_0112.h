#ifndef _C_ALGCLASS_0112_H
#define _C_ALGCLASS_0112_H

#include "_c_algBaseClass.h"

class _c_algClass_0112 : public _c_algBaseClass {
public:
	ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheLiangYanSe = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheBiao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER paiQiKongShuLiang = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER sanJiaoJia = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER jiaoTaBan = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER jiaoTaBanRecord = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER weiYi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER weiYiRecord = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER baoWei = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER baoWeiRecord = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER gaiZhuang = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheBiaoMingCheng = ALG_PARAM_DEFAULT; // 车标名称2
	ALG_PARM_MEMBER paiSheJiaoDu = ALG_PARAM_DEFAULT; //拍摄角度 入参：0-左前，1-右后，2-正后，3-其它
	ALG_PARM_MEMBER dangAnZhaoPian = ALG_PARAM_DEFAULT;

	std::vector<memberItem> inMemberList = {
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"shuiYinRiQi", "照片水印日期", &shuiYinRiQi, true, CONFIG_DEFAULT},
		{"cheLiangYanSe", "车辆颜色", &cheLiangYanSe, true, CONFIG_DEFAULT},
		{"paiSheJiaoDu", "拍摄角度", &paiSheJiaoDu, true, CONFIG_DEFAULT}
	};

	std::vector<memberItem> resultMemberList = {
		{"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"shuiYinRiQi", "照片水印日期过期", &shuiYinRiQi, true, CONFIG_NOCHECK_UNABLE},
		{"cheBiao", "车标不存在", &cheBiao, true, CONFIG_DEFAULT},
		{"cheBiaoMingCheng", "车标名称不正确(暂不支持)", &cheBiaoMingCheng, true, CONFIG_NOCHECK},
		{"paiQiKongShuLiang", "排气孔数量过多", &paiQiKongShuLiang, true, CONFIG_NOCHECK},
		{"sanJiaoJia", "没有三角架", &sanJiaoJia, true, CONFIG_DEFAULT},
		{"jiaoTaBan", "没有脚踏板", &jiaoTaBan, false, CONFIG_NOCHECK},
		{"weiYi", "没有尾翼", &weiYi, false, CONFIG_NOCHECK},
		{"baoWei", "没有包围", &baoWei, false, CONFIG_NOCHECK},
		{"dangAnZhaoPian", "缺少档案照片,无法判定是否改装", &dangAnZhaoPian, true, CONFIG_NOCHECK_UNABLE},
		{"gaiZhuang", "有改装", &gaiZhuang, false, CONFIG_NOCHECK},
		{"jiaoTaBanRecord", "脚踏板(用于逻辑判断)", &jiaoTaBanRecord, false, CONFIG_NOCHECK},
		{"weiYiRecord", "尾翼(用于逻辑判断)", &weiYiRecord, false, CONFIG_NOCHECK},
		{"baoWeiRecord", "包围(用于逻辑判断)", &baoWeiRecord, false, CONFIG_NOCHECK}
	};

	ALG_PARM_MEMBER cheWaiKuoGao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER houCheShenFanGuangBiaoShi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER youCeCheShenFanGuangBiaoShi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER houXiaBuFangHuZhuangZhi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER youCeFangHuZhuangZhi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER penTuFangDaChePai = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheLiangWeiBuBiaoZhi = ALG_PARAM_DEFAULT;

	std::vector<memberItem> inMemberList_daChe = {
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheWaiKuoGao", "车外廓高", &cheWaiKuoGao, true, CONFIG_DEFAULT},
		{"cheLiangYanSe", "车辆颜色", &cheLiangYanSe, true, CONFIG_DEFAULT},
		{"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
		{"paiSheJiaoDu", "拍摄角度", &paiSheJiaoDu, true, CONFIG_DEFAULT}
	};

	std::vector<memberItem> resultMemberList_daChe = {
		{"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheBiao", "车标不存在", &cheBiao, true, CONFIG_DEFAULT},
		{"houCheShenFanGuangBiaoShi", "后部车身反光标识错误", &houCheShenFanGuangBiaoShi, true, CONFIG_NOCHECK},
		{"youCeCheShenFanGuangBiaoShi", "右侧面车身反光标识错误", &youCeCheShenFanGuangBiaoShi, true, CONFIG_NOCHECK},
		{"houXiaBuFangHuZhuangZhi", "后下部防护装置错误", &houXiaBuFangHuZhuangZhi, true, CONFIG_NOCHECK},
		{"youCeFangHuZhuangZhi", "右侧面防护装置错误", &youCeFangHuZhuangZhi, true, CONFIG_NOCHECK},
		{"penTuFangDaChePai", "车厢后部喷涂或粘贴的放大的号牌号码错误", &penTuFangDaChePai, true, CONFIG_NOCHECK},
		{"cheLiangWeiBuBiaoZhi", "车辆尾部标志板错误", &cheLiangWeiBuBiaoZhi, true, CONFIG_NOCHECK},
	};

	std::vector<memberItem> inMemberList_moTuo = {
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
		{"paiSheJiaoDu", "拍摄角度", &paiSheJiaoDu, true, CONFIG_DEFAULT}
	};

	std::vector<memberItem> resultMemberList_moTuo = {
		{"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"gaiZhuang", "有改装(不支持)", &gaiZhuang, true, CONFIG_NOCHECK},
		{"paiQiKongShuLiang", "排气孔数量过多", &paiQiKongShuLiang, true, CONFIG_NOCHECK},
	};

	ALG_PARM_MEMBER shiYongXingZhi = ALG_PARAM_DEFAULT;
	std::vector<memberItem> inMemberList_video = {
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
		{"shiYongXingZhi", "使用性质", &shiYongXingZhi, true, CONFIG_DEFAULT},
	};

	ALG_PARM_MEMBER shiJian = ALG_PARAM_DEFAULT;
	std::vector<memberItem> resultMemberList_video = {
		{"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"shiJian", "检验时间不够", &shiJian, true, CONFIG_DEFAULT},
	};

	virtual ~_c_algClass_0112() {}
	virtual bool seekMemberListPointer();
	virtual bool InParamEdit();
	virtual bool ResultEdit();
	virtual std::string getPhotoName(std::string algcode);
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0112_H
