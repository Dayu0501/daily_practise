#ifndef _C_ALGCLASS_0354_H
#define _C_ALGCLASS_0354_H

#include "_c_algBaseClass.h"

class _c_algClass_0354 : public _c_algBaseClass {
public:
	ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhiDong = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER gongWei = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhiDongLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhouLeiXing = ALG_PARAM_DEFAULT;

	std::vector <memberItem> inMemberList = {
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheLiangLeiXing", "车辆分类", &cheLiangLeiXing, true, CONFIG_DEFAULT},
		{"zhiDongLeiXing", "制动类型", &zhiDongLeiXing, true, CONFIG_DEFAULT},
		{"zhouLeiXing", "轴类型", &zhouLeiXing, true, CONFIG_DEFAULT}
	};

	std::vector <memberItem> resultMemberList = {
		{"zhiDong", "制动不正常", &zhiDong, true, CONFIG_DEFAULT},
		{"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"gongWei", "缺少工位", &gongWei, true, CONFIG_DEFAULT},
	};

	virtual ~_c_algClass_0354() {}
	virtual bool seekMemberListPointer();
	virtual bool InParamEdit();
	virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0119_H
