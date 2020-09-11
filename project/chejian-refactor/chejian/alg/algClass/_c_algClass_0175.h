#ifndef _C_ALGCLASS_0175_H
#define _C_ALGCLASS_0175_H
#include "_c_algBaseClass.h"

class _c_algClass_0175 : public _c_algBaseClass {
public:
	ALG_PARM_MEMBER guangGao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheLiangYanSe = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER dangAnZhaoPian = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER paiSheJiaoDu = ALG_PARAM_DEFAULT; //拍摄角度 入参：0-左前，1-右后，2-正后，3-其它

	std::vector <memberItem> inMemberList = {
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheLiangYanSe", "车辆颜色", &cheLiangYanSe, true, CONFIG_DEFAULT},
		{"paiSheJiaoDu", "拍摄角度", &paiSheJiaoDu, true, CONFIG_DEFAULT}
	};

	std::vector <memberItem> resultMemberList = {
		{"guangGao", "车辆有广告", &guangGao, true, CONFIG_DEFAULT},
		{"cheLiangYanSe", "车辆颜色有变化", &cheLiangYanSe, false, CONFIG_DEFAULT},
		{"dangAnZhaoPian", "缺少档案照片，无法判定是否改装", &dangAnZhaoPian, true, CONFIG_NOCHECK_UNABLE}
	};

	virtual ~_c_algClass_0175() {}
	virtual bool seekMemberListPointer();
	virtual bool InParamEdit();
	virtual bool ResultEdit();
	virtual std::string getPhotoName(std::string algcode);
};

#endif // _C_ALGCLASS_0175_H
