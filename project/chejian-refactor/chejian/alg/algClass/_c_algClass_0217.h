#ifndef _C_ALGCLASS_0217_H
#define _C_ALGCLASS_0217_H
#include "_c_algBaseClass.h"

class _c_algClass_0217 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangXingHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingZaiKeShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shiYongXingZhi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhiZaoRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faZhengRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"cheLiangXingHao", "车辆型号", &cheLiangXingHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"faDongJiHao", "发动机号", &faDongJiHao, true, CONFIG_DEFAULT},
        {"heDingZaiKeShu", "核定载客数", &heDingZaiKeShu, true, CONFIG_DEFAULT},
        {"shiYongXingZhi", "使用性质", &shiYongXingZhi, true, CONFIG_DEFAULT},
        {"zhiZaoRiQi", "出厂日期", &zhiZaoRiQi, true, CONFIG_DEFAULT},
        {"faZhengRiQi", "发证日期", &faZhengRiQi, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"cheLiangLeiXing", "车辆类型是否正确", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"cheLiangXingHao", "车辆型号是否正确", &cheLiangXingHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号是否正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"faDongJiHao", "发动机号是否正确", &faDongJiHao, true, CONFIG_DEFAULT},
        {"heDingZaiKeShu", "核定载客数是否正确", &heDingZaiKeShu, true, CONFIG_DEFAULT},
        {"shiYongXingZhi", "使用性质是否正确", &shiYongXingZhi, true, CONFIG_DEFAULT},
        {"zhiZaoRiQi", "出厂日期是否正确", &zhiZaoRiQi, true, CONFIG_DEFAULT},
        {"faZhengRiQi", "发证日期是否正确", &faZhengRiQi, true, CONFIG_DEFAULT},
        {"yinZhang", "印章是否正确", &yinZhang, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0217(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0217_H
