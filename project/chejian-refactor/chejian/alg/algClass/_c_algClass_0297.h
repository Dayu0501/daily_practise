#ifndef _C_ALGCLASS_0297_H
#define _C_ALGCLASS_0297_H
#include "_c_algBaseClass.h"

class _c_algClass_0297 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dangTianRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanBiao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_waiGuanJianYanYuan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_yinCheJianYanYuan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_diPanJianYanYuan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanJieGuoDiWuXiang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanJieShuShiJian = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER jianYanJieLun = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"dangTianRiQi", "当前日期", &dangTianRiQi, true, CONFIG_DEFAULT},
        {"jianYanJieShuShiJian", "检验结束日期", &jianYanJieShuShiJian, true, CONFIG_DEFAULT},

    };
    // 引车检验员  底盘检验员  十年以上才需要检查 默认应关闭
    std::vector<memberItem> resultMemberList = {
        {"jianYanBiao", "检验表不符合标准", &jianYanBiao, true, CONFIG_NOCHECK},
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_NOCHECK},
        {"qianZi_waiGuanJianYanYuan", "外观检验员未签字", &qianMing_waiGuanJianYanYuan, true, CONFIG_DEFAULT},
        {"qianZi_yinCheJianYanYuan", "引车检验员未签字", &qianMing_yinCheJianYanYuan, false, CONFIG_DEFAULT},
        {"qianZi_diPanJianYanYuan", "底盘检验员未签字", &qianMing_diPanJianYanYuan, false, CONFIG_DEFAULT},
        {"dangTianRiQi", "检验日期不是当天", &dangTianRiQi, true, CONFIG_NOCHECK},
        {"jianYanJieGuoDiWuXiang", "检验结果第5项不是“合格”", &jianYanJieGuoDiWuXiang, true, CONFIG_NOCHECK},
        {"yinZhang", "没有印章", &yinZhang, true, CONFIG_NOCHECK},
        {"jianYanJieLun", "结论不合格", &jianYanJieLun, true, CONFIG_NOCHECK}
    };

    virtual ~_c_algClass_0297(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0297_H
