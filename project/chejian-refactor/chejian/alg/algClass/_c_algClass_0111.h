#ifndef _C_ALGCLASS_0111_H
#define _C_ALGCLASS_0111_H

#include "_c_algBaseClass.h"

class _c_algClass_0111 : public _c_algBaseClass {
 public:
	ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheLiangShiBieDaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheBiao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER sanJiaoJia = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheLiangYanSe = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER dangAnZhaoPian = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER xingLiJia = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER jiaoTaBan = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER lunTaiHuaWen = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER anQuanMao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER jianYanYuan = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER guangGaoLarge = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER guangGaoExist = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER guangGao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER gaiZhuang = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER jiaoTaBanRecord = ALG_PARAM_DEFAULT; //和档案对比的结果输出 是否有 脚踏板
	ALG_PARM_MEMBER xingLiJiaRecord = ALG_PARAM_DEFAULT; //和档案对比的结果输出 是否有行李架
	ALG_PARM_MEMBER waiguanRecord = ALG_PARAM_DEFAULT; //和档案对比的结果输出  是否贴花
	ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER isOpenSanJiaoJiaJoin = ALG_PARAM_DEFAULT;// 开启左前 右后 三脚架是否存在的联合判定
	ALG_PARM_MEMBER cheBiaoMingCheng = ALG_PARAM_DEFAULT; // 车标名称
	ALG_PARM_MEMBER paiSheJiaoDu = ALG_PARAM_DEFAULT; //拍摄角度 入参：0-左前，1-右后，2-正后，3-其它

	std::vector<memberItem> inMemberList = {
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheJiaHao", "车架号", &cheLiangShiBieDaiHao, true, CONFIG_DEFAULT},
		{"shuiYinRiQi", "照片水印日期", &shuiYinRiQi, true, CONFIG_DEFAULT},
		{"cheLiangYanSe", "车辆颜色", &cheLiangYanSe, true, CONFIG_DEFAULT},
		{"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
		{"paiSheJiaoDu", "拍摄角度", &paiSheJiaoDu, true, CONFIG_DEFAULT}
	};

	std::vector<memberItem> resultMemberList = {
		{"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"shuiYinRiQi", "照片水印日期过期", &shuiYinRiQi, true, CONFIG_NOCHECK_UNABLE},
		{"cheBiao", "车标不存在", &cheBiao, true, CONFIG_DEFAULT},
		{"cheBiaoMingCheng", "车标不正确", &cheBiaoMingCheng, true, CONFIG_NOCHECK},
		{"sanJiaoJia", "没有三角架", &sanJiaoJia, true, CONFIG_NOCHECK},
		{"cheLiangYanSe", "车辆颜色有变化", &cheLiangYanSe, false, CONFIG_NOCHECK},
		{"xingLiJia", "行李架有变化", &xingLiJia, false, CONFIG_NOCHECK},
		{"jiaoTaBan", "迎宾牌有变化", &jiaoTaBan, false, CONFIG_NOCHECK},
		{"lunTaiHuaWen", "轮胎花纹", &lunTaiHuaWen, false, CONFIG_NOCHECK},
		{"dangAnZhaoPian", "缺少档案照片,无法判定是否改装", &dangAnZhaoPian, true, CONFIG_NOCHECK_UNABLE},
		{"anQuanMao", "是否存在安全帽", &anQuanMao, false, CONFIG_NOCHECK},
		{"jianYanYuan", "没有检验人员", &jianYanYuan, false, CONFIG_NOCHECK},
		{"guangGaoLarge", "广告面积大于三分之一", &guangGaoLarge, false, CONFIG_NOCHECK},
		{"guangGaoExist", "车身有广告", &guangGaoExist, false, CONFIG_NOCHECK},
		{"guangGao", "车身广告检测", &guangGao, false, CONFIG_NOCHECK},
		{"gaiZhuang", "有改装", &gaiZhuang, false, CONFIG_NOCHECK},
		{"isOpenSanJiaoJiaJoin", "开启左前/右后三脚架联合判定(用于逻辑判断)", &isOpenSanJiaoJiaJoin, false, CONFIG_NOCHECK},
		{"xingLiJiaRecord", "行李架(用于逻辑判断)", &xingLiJiaRecord, false, CONFIG_NOCHECK},
		{"jiaoTaBanRecord", "脚踏板(用于逻辑判断)", &jiaoTaBanRecord, false, CONFIG_NOCHECK},
		{"waiguanRecord", "广告(用于逻辑判断)", &waiguanRecord, false, CONFIG_NOCHECK},
	};

	ALG_PARM_MEMBER zuoCeCheShenFanGuangBiaoShi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zuoCeFangHuZhuangZhi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zuoCeJiaShiShiPenTuZongZhiLiang = ALG_PARAM_DEFAULT;

	std::vector<memberItem> inMemberList_daChe = {
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheLiangYanSe", "车辆颜色", &cheLiangYanSe, true, CONFIG_DEFAULT},
		{"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
		{"paiSheJiaoDu", "拍摄角度", &paiSheJiaoDu, true, CONFIG_DEFAULT}
	};

	std::vector<memberItem> resultMemberList_daChe = {
		{"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheBiao", "车标不存在", &cheBiao, true, CONFIG_DEFAULT},
		{"cheBiaoMingCheng", "车标名称不正确(暂不支持)", &cheBiaoMingCheng, true, CONFIG_NOCHECK},
		{"zuoCeJiaShiShiPenTuZongZhiLiang", "驾驶室左侧喷涂的总质量错误", &zuoCeJiaShiShiPenTuZongZhiLiang, false,
		 CONFIG_NOCHECK},
		{"zuoCeCheShenFanGuangBiaoShi", "左侧车身反光标识错误", &zuoCeCheShenFanGuangBiaoShi, false, CONFIG_NOCHECK},
		{"zuoCeFangHuZhuangZhi", "左侧防护装置错误", &zuoCeFangHuZhuangZhi, false, CONFIG_NOCHECK},
	};

	std::vector<memberItem> inMemberList_moTuo = {
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheLiangYanSe", "车辆颜色", &cheLiangYanSe, true, CONFIG_DEFAULT},
		{"paiSheJiaoDu", "拍摄角度", &paiSheJiaoDu, true, CONFIG_DEFAULT}
	};

	std::vector<memberItem> resultMemberList_moTuo = {
		{"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheLiangYanSe", "车辆颜色(不支持)", &cheLiangYanSe, true, CONFIG_NOCHECK},
		{"cheBiao", "车标不正确(不支持)", &cheBiao, true, CONFIG_NOCHECK},
		{"anQuanMao", "没有安全帽", &anQuanMao, true, CONFIG_DEFAULT},
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

	virtual ~_c_algClass_0111() {}
	virtual bool seekMemberListPointer(); //查找子图，如档案照片等。
	virtual bool InParamEdit(); //入参编辑，可以定制输入参数的默认值。
	virtual bool ResultEdit();
	virtual std::string getPhotoName(std::string algcode);
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0111_H
