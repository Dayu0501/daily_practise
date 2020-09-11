#ifndef _C_ALGCLASS_0220_H
#define _C_ALGCLASS_0220_H
#include "_c_algBaseClass.h"

class _c_algClass_0220 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER haoPaiZhongLei = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER haoPaiHaoMa = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yeWuLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yeWuYuanYin = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER bianGengLeiXing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"haoPaiZhongLei", "号牌种类", &haoPaiZhongLei, true, CONFIG_DEFAULT},
        {"chePaiHao", "号牌号码", &haoPaiHaoMa, true, CONFIG_DEFAULT},
        {"yeWuLeiXing", "业务类型", &yeWuLeiXing, true, CONFIG_DEFAULT},
        {"yeWuYuanYin", "业务原因", &yeWuYuanYin, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"haoPaiZhongLei", "号牌种类", &haoPaiZhongLei, true, CONFIG_DEFAULT},
        {"chePaiHao", "号牌号码", &haoPaiHaoMa, true, CONFIG_DEFAULT},
        {"bianGengLeiXing", "变更类型不正确", &bianGengLeiXing, true, CONFIG_DEFAULT},

    };

    virtual ~_c_algClass_0220(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0220_H
