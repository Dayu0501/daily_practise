#ifndef _C_ALGCLASS_0214_H
#define _C_ALGCLASS_0214_H
#include "_c_algBaseClass.h"

class _c_algClass_0214 : public _c_algBaseClass {
public:
	ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER shenFenZhengZhengMian = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhaoPianLeiXing = ALG_PARAM_DEFAULT;

	std::vector <memberItem> inMemberList{
		{"cheJiaHao", "车架号", &cheJiaHao, false, CONFIG_DEFAULT},
		{"chePaiHao", "车牌号", &chePaiHao, false, CONFIG_DEFAULT}
	};

	std::vector <memberItem> resultMemberList{
		{"yinZhang", "没有印章", &yinZhang, true, CONFIG_DEFAULT},
		{"shenFenZhengZhengMian", "是否有有身份证正面", &shenFenZhengZhengMian, true, CONFIG_DEFAULT},
		{"zhaoPianLeiXing", "不是委托书", &zhaoPianLeiXing, true, CONFIG_NOCHECK}
	};

	virtual ~_c_algClass_0214() {}
	virtual bool seekMemberListPointer();
	virtual bool InParamEdit();
	virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0214_H
