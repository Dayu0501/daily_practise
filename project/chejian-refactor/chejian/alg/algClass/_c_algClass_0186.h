#ifndef _C_ALGCLASS_0186_H
#define _C_ALGCLASS_0186_H
#include "_c_algBaseClass.h"

class _c_algClass_0186 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER paiLiang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhiZaoGuo = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhiZaoRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingZaiKe = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zongZhiLiang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangPinPai = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangXingHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhiZaoChangMingCheng = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiXingHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhaoPianLeiXing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"paiLiang", "排量", &paiLiang, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"zhiZaoGuo", "制造国", &zhiZaoGuo, true, CONFIG_DEFAULT},
        {"zhiZaoRiQi", "制造日期", &zhiZaoRiQi, true, CONFIG_DEFAULT},
        {"heDingZaiKeShu", "核定载客", &heDingZaiKe, true, CONFIG_DEFAULT},
        {"zongZhiLiang", "总质量", &zongZhiLiang, true, CONFIG_DEFAULT},
        {"cheLiangPinPai", "车辆品牌", &cheLiangPinPai, true, CONFIG_DEFAULT},
        {"cheLiangXingHao", "车辆型号", &cheLiangXingHao, true, CONFIG_DEFAULT},
        {"zhiZaoChangMingCheng", "制造厂名称", &zhiZaoChangMingCheng, true, CONFIG_DEFAULT},
        {"faDongJiXingHao", "发动机型号", &faDongJiXingHao, true, CONFIG_DEFAULT}
    };

    std::vector<memberItem> resultMemberList = {
        {"faDongJiXingHao", "发动机型号不正确", &faDongJiXingHao, true, CONFIG_DEFAULT},
        {"zhiZaoRiQi", "制造日期不正确", &zhiZaoRiQi, true, CONFIG_DEFAULT},
        {"paiLiang", "排量不正确", &paiLiang, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"zhaoPianLeiXing", "不是铭牌", &zhaoPianLeiXing, true, CONFIG_NOCHECK}
    };

    virtual ~_c_algClass_0186(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0186_H
