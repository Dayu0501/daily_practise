#ifndef _C_ALGCLASS_0296_H
#define _C_ALGCLASS_0296_H
#include "_c_algBaseClass.h"

class _c_algClass_0296 : public _c_algBaseClass {
public:
	ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER xingShiZhengXinBianHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER faZhengRiQi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER dangAnHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER heDingZaiKeShu = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER qiangZhiBaoFeiQiZhi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhaoPianLeiXing = ALG_PARAM_DEFAULT;

	std::vector <memberItem> inMemberList = {
		{"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"xingShiZhengXinBianHao", "行驶证(证芯)编号", &xingShiZhengXinBianHao, true, CONFIG_DEFAULT},
		{"faZhengRiQi", "发证日期", &faZhengRiQi, true, CONFIG_DEFAULT},
		{"dangAnHao", "档案号", &dangAnHao, true, CONFIG_DEFAULT},
		{"heDingZaiKeShu", "核定载客数", &heDingZaiKeShu, true, CONFIG_DEFAULT},
		{"cheLiangLeiXing", "车辆类型编码", &cheLiangLeiXing, true, CONFIG_DEFAULT},
		{"qiangZhiBaoFeiQiZhi", "强制报废日期", &qiangZhiBaoFeiQiZhi, true, CONFIG_NOCHECK},
	};

	std::vector <memberItem> resultMemberList = {
		{"zhaoPianLeiXing", "不是罚单", &zhaoPianLeiXing, true, CONFIG_DEFAULT},
	};

	virtual ~_c_algClass_0296() {}
	virtual bool seekMemberListPointer();
	virtual bool InParamEdit();
	virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0296_H