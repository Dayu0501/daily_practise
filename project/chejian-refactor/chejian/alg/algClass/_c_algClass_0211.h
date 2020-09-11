#ifndef _C_ALGCLASS_0211_H
#define _C_ALGCLASS_0211_H
#include "_c_algBaseClass.h"

class _c_algClass_0211 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER shiYongRen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yeWuLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER haoPaiZhongLei = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER haoPaiHaoMa = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangShiBieDaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shiYongXingZhi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhuCeShengQingBiao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"shiYongRen", "所有人", &shiYongRen, true, CONFIG_DEFAULT},
        {"yeWuLeiXing", "业务类别", &yeWuLeiXing, true, CONFIG_DEFAULT},
        {"haoPaiZhongLei", "号牌种类", &haoPaiZhongLei, true, CONFIG_DEFAULT},
        {"chePaiHao", "号牌号码", &haoPaiHaoMa, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车辆识别代号", &cheLiangShiBieDaiHao, true, CONFIG_DEFAULT},
        {"shiYongXingZhi", "使用性质", &shiYongXingZhi, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"zhuCeShengQingBiao", "是否是注册转移申请表", &zhuCeShengQingBiao, true, CONFIG_DEFAULT},
        {"yeWuLeiXing", "业务类别不正确", &yeWuLeiXing, true, CONFIG_DEFAULT},
        {"haoPaiZhongLei", "号牌种类不正确", &haoPaiZhongLei, true, CONFIG_DEFAULT},
        {"chePaiHao", "号牌号码不正确", &haoPaiHaoMa, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车辆识别代号不正确", &cheLiangShiBieDaiHao, true, CONFIG_DEFAULT},
        {"shiYongXingZhi", "使用性质不正确", &shiYongXingZhi, true, CONFIG_DEFAULT},
        {"qianMing", "没有签名", &qianMing, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0211(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0211_H
