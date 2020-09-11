#ifndef _C_ALGCLASS_0202_H
#define _C_ALGCLASS_0202_H

#include "_c_algBaseClass.h"

class _c_algClass_0202 : public _c_algBaseClass {
public:
	ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER suoYouRenShouJiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER qianMing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER xingMing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER diZhi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER haoPaiZhongLei = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER jianYanHeGeBiaoZhi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER daiLiRenShouJiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhaoPianQingXiDu = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER riQi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER guDingDianHua = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER qianMingRiQiSuoYouRen = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER daiLiRenXingMing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhaoPianLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;


	std::vector<memberItem> inMemberList = {
		{"chePaiHao",      "车牌号",  &chePaiHao,      true, CONFIG_DEFAULT},
		{"cheJiaHao",      "车架号",  &cheJiaHao,      true, CONFIG_DEFAULT},
		{"haoPaiZhongLei", "号牌种类", &haoPaiZhongLei, true, CONFIG_DEFAULT},
	};

	std::vector<memberItem> resultMemberList = {
		{"chePaiHao",              "车牌号不正确",     &chePaiHao,             true, CONFIG_DEFAULT},
		{"suoYouRenShouJiHao",     "无所有人手机号码",   &suoYouRenShouJiHao,    true, CONFIG_NOCHECK},
		{"qianMing",               "没有签名",       &qianMing,              true, CONFIG_DEFAULT},
		{"xingMing",               "没有填写所有人姓名",  &xingMing,              true, CONFIG_NOCHECK},
		{"diZhi",                  "联系地址未填写",    &diZhi,                 true, CONFIG_NOCHECK},
		{"riQi",                   "没有日期",       &riQi,                  true, CONFIG_NOCHECK},
		{"haoPaiZhongLei",         "号牌种类不正确",    &haoPaiZhongLei,        true, CONFIG_NOCHECK},
		{"jianYanHeGeBiaoZhi",     "检验合格标志未勾选",  &jianYanHeGeBiaoZhi,    true, CONFIG_NOCHECK},
		{"daiLiRenShouJiHao",      "代理人手机号码不合法", &daiLiRenShouJiHao,     true, CONFIG_NOCHECK},
		{"zhaoPianQingXiDu",       "图片信息不规范",    &zhaoPianQingXiDu,      true, CONFIG_NOCHECK_UNABLE},
		{"guDingDianHua",          "固定电话号码不合法",  &guDingDianHua,         true, CONFIG_NOCHECK_UNABLE},
		{"qianMingRiQiSuoYouRen",  "所有人签名日期",    &qianMingRiQiSuoYouRen, true, CONFIG_NOCHECK_UNABLE},
		{"daiLiRenXingMingShuChu", "没有填写代理人姓名",  &daiLiRenXingMing,      true, CONFIG_NOCHECK},
		{"zhaoPianLeiXing",        "照片不是牌证申请表",  &zhaoPianLeiXing,       true, CONFIG_NOCHECK},
		{"yinZhang",               "印章不存在",  &yinZhang,              true, CONFIG_NOCHECK}
	};

	std::vector<memberItem> inMemberList_moTuo = {
		{"chePaiHao",      "车牌号",  &chePaiHao,      true, CONFIG_DEFAULT},
		{"haoPaiZhongLei", "号牌种类", &haoPaiZhongLei, true, CONFIG_DEFAULT},
	};

	std::vector<memberItem> resultMemberList_moTuo = {
		{"chePaiHao",          "车牌号不正确",    &chePaiHao,          true, CONFIG_DEFAULT},
		{"haoPaiZhongLei",     "号牌种类不正确",   &haoPaiZhongLei,     true, CONFIG_NOCHECK},
		{"suoYouRenShouJiHao", "无所有人手机号码",  &suoYouRenShouJiHao, true, CONFIG_NOCHECK},
		{"qianMing",           "没有签名",      &qianMing,           true, CONFIG_DEFAULT},
		{"xingMing",           "姓名不正确",     &xingMing,           true, CONFIG_NOCHECK},
		{"diZhi",              "联系地址未填写",   &diZhi,              true, CONFIG_NOCHECK},
		{"riQi",               "没有日期",      &riQi,               true, CONFIG_NOCHECK},
		{"jianYanHeGeBiaoZhi", "检验合格标志未勾选", &jianYanHeGeBiaoZhi, true, CONFIG_NOCHECK},
		{"zhaoPianLeiXing",    "照片不是牌证申请表", &zhaoPianLeiXing,    true, CONFIG_NOCHECK}
	};

	virtual ~_c_algClass_0202() {}

	virtual bool seekMemberListPointer();
	virtual bool InParamEdit();
	virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0202_H
