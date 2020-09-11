#ifndef _C_ALGCLASS_0208_H
#define _C_ALGCLASS_0208_H
#include "_c_algBaseClass.h"

class _c_algClass_0208 : public _c_algBaseClass {
public:
	ALG_PARM_MEMBER youXiaoZhengJian = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER chengShiDaiMa = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER wenJianBiaoQian = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER yingZhang = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER qianZi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhaoPianLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheJiaHaoShuChu = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER faDongJiHaoShuChu = ALG_PARAM_DEFAULT;

	std::vector <memberItem> inMemberList = {
		{"chengShiDaiMa", "城市代码", &chengShiDaiMa, true, CONFIG_NOCHECK}, //此参数暂时不用
		{"wenJianBiaoQian", "文件标签", &wenJianBiaoQian, true, CONFIG_NOCHECK},
	};

	std::vector <memberItem> resultMemberList = {
		{"youXiaoZhengJian", "无有效证件照片", &youXiaoZhengJian, true, CONFIG_NOCHECK}, //是否是该文本
		{"chePaiHao", "车牌号不正确", &chePaiHao, false, CONFIG_NOCHECK}, //车牌
		{"cheJiaHao", "车架号不正确", &cheJiaHao, false, CONFIG_NOCHECK}, //车架号
		{"yingZhang", "没有印章", &yingZhang, false, CONFIG_NOCHECK},      //印章
		{"qianZi", "没有签字", &qianZi, true, CONFIG_NOCHECK},          //签名
		{"zhaoPianLeiXing", "传入照片与给定的表单标题不一致", &zhaoPianLeiXing, true, CONFIG_NOCHECK},
		{"cheJiaHaoShuChu", "输出车架号识别结果(用于逻辑判断)", &cheJiaHaoShuChu, true, CONFIG_NOCHECK},
		{"faDongJiHaoShuChu", "输出发动机号识别结果(用于逻辑判断)", &faDongJiHaoShuChu, true, CONFIG_NOCHECK}
	};

	virtual ~_c_algClass_0208() {}
	virtual bool seekMemberListPointer();
	virtual bool InParamEdit();
	virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0208_H
