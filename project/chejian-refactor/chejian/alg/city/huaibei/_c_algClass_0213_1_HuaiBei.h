#pragma once

#include "alg/algClass/_c_algBaseClass.h"

class _c_algClass_0213_1_HuaiBei : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiHao = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"faDongJiHao", "发动机号", &faDongJiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_NOCHECK},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_NOCHECK},
        //{"faDongJiHao", "发动机号不正确", &faDongJiHao, true, CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0213_1_HuaiBei(){}
    virtual bool subClassLoadNewResultMember();
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};
