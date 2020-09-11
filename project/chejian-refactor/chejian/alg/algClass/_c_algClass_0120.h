#ifndef _C_ALGCLASS_0120_H
#define _C_ALGCLASS_0120_H
#include "_c_algBaseClass.h"

class _c_algClass_0120 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER mieHuoQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yaLiBiao = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
    };

    std::vector<memberItem> resultMemberList = {
        {"mieHuoQi", "没有灭火器", &mieHuoQi, true, CONFIG_DEFAULT},
        {"yaLiBiao", "没有压力表", &yaLiBiao, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0120(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0120_H
