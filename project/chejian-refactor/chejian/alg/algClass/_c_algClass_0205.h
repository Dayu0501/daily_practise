#ifndef _C_ALGCLASS_0205_H
#define _C_ALGCLASS_0205_H
#include "_c_algBaseClass.h"

class _c_algClass_0205 : public _c_algBaseClass{
public:
	ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER dangTianRiQi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER qianZi_waiGuanJianYanYuan = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER jianYanJieLun = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER qianZi_chaYanYuan = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER qianZi_yinCheJianYanYuan = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER qianZi_diPanJianYanYuan = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER jianYanXinXi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER dangAnZhaoPian = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER tuoMo = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER taYinMo = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER qianZi_fuhe = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhaoPianLeiXing = ALG_PARAM_DEFAULT;

    std::vector<int> jianYanXiang;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"dangTianRiQi", "当天日期", &dangTianRiQi, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"jianYanXinXi", "查验信息不正确", &jianYanXinXi, true, CONFIG_NOCHECK},
        {"qianZi_waiGuanJianYanYuan", "外观检验员未签字", &qianZi_waiGuanJianYanYuan, true, CONFIG_NOCHECK},
        {"jianYanJieLun", "结论不合格", &jianYanJieLun, true, CONFIG_NOCHECK},
        {"qianZi_chaYanYuan", "查验员未签字", &qianZi_chaYanYuan, true, CONFIG_NOCHECK},
        {"qianZi_yinCheJianYanYuan", "引车检验员未签字", &qianZi_yinCheJianYanYuan, false, CONFIG_NOCHECK},
        {"qianZi_diPanJianYanYuan", "底盘检验员未签字", &qianZi_diPanJianYanYuan, false, CONFIG_NOCHECK},
        {"dangAnZhaoPian", "缺少拓印膜照片，无法判定车架号是否更改", &dangAnZhaoPian, true, CONFIG_NOCHECK_UNABLE},
        {"tuoMo", "车架号拓印膜不正确", &tuoMo, false, CONFIG_NOCHECK},
        {"taYinMo", "车架号字型与拓印膜不符", &taYinMo, false, CONFIG_NOCHECK},
        {"qianZi_fuhe", "符合人员确认车辆通过", &qianZi_fuhe, false, CONFIG_NOCHECK},
        {"yinZhang", "没有印章", &yinZhang, true, CONFIG_NOCHECK},
        {"zhaoPianLeiXing", "不是检验表", &zhaoPianLeiXing, true, CONFIG_NOCHECK}
    };
    
    virtual ~_c_algClass_0205(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0205_H
