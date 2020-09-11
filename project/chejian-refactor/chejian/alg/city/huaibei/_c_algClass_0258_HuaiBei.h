#pragma once

#include "alg/algClass/_c_algBaseClass.h"

class _c_algClass_0258_HuaiBei : public _c_algBaseClass {
public:
    //ALG_PARM_MEMBER qiPingShiYongZheng1 = ALG_PARAM_DEFAULT;
    //ALG_PARM_MEMBER qiPingShiYongZheng2 = ALG_PARAM_DEFAULT;

    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiHao = ALG_PARAM_DEFAULT;

    ALG_PARM_MEMBER jianYanHeGe = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanRiQi = ALG_PARAM_DEFAULT;
    //ALG_PARM_MEMBER zhaoPianQingXiDu = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"faDongJiHao", "发动机号", &faDongJiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        //{"qiPingShiYongZheng1", "是否是气瓶使用证1", &qiPingShiYongZheng1, true, CONFIG_NOCHECK},
        //{"qiPingShiYongZheng2", "是否是气瓶使用证2", &qiPingShiYongZheng2, true, CONFIG_NOCHECK},

        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_NOCHECK},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_NOCHECK},
        {"faDongJiHao", "发动机号不正确", &faDongJiHao, true, CONFIG_NOCHECK},

        {"jianYanHeGe", "检验结论是否合格", &jianYanHeGe, true, CONFIG_NOCHECK},
        {"jianYanRiQi", "检验日期是否在有效期内", &jianYanRiQi, true, CONFIG_NOCHECK},
        //{"zhaoPianQingXiDu", "照片清晰度", &zhaoPianQingXiDu, true, CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0258_HuaiBei() {}
    virtual bool subClassLoadNewResultMember();
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};
