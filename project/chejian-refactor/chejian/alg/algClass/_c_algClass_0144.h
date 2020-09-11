#ifndef _C_ALGCLASS_0144_H
#define _C_ALGCLASS_0144_H
#include "_c_algBaseClass.h"

class _c_algClass_0144 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER gaiZhuang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qiGuan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER huoWu = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"gaiZhuang", "车辆有改装", &gaiZhuang, true, CONFIG_DEFAULT},
        {"qiGuan", "有气罐", &qiGuan, true, CONFIG_NOCHECK_UNABLE},
        {"huoWu", "有货物", &huoWu, true, CONFIG_NOCHECK_UNABLE},
    };

    virtual ~_c_algClass_0144(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0144_H
