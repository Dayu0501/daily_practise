#ifndef _C_ALGCLASS_0122_H
#define _C_ALGCLASS_0122_H
#include "_c_algBaseClass.h"

class _c_algClass_0122 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER xingCheJiLuYi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER tripleC = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER screenOn = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
    };

    std::vector<memberItem> resultMemberList = {
        {"xingCheJiLuYi", "没有行车记录仪", &xingCheJiLuYi, true, CONFIG_DEFAULT},
        {"tripleC", "没有3C", &tripleC, true, CONFIG_DEFAULT},
        {"screenOn", "屏幕不亮", &screenOn, true, CONFIG_DEFAULT},

    };

    virtual ~_c_algClass_0122(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0122_H
