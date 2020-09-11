#ifndef _C_ALGCLASS_0135_H
#define _C_ALGCLASS_0135_H
#include "_c_algBaseClass.h"

class _c_algClass_0135 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER lunTaiHuaWen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_NOCHECK},
        {"lunTaiHuaWen", "轮胎花纹不一致", &lunTaiHuaWen, true,CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0135(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0135_H
