#ifndef _C_ALGCLASS_0121_H
#define _C_ALGCLASS_0121_H
#include "_c_algBaseClass.h"

class _c_algClass_0121 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER labelName = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER muBiao = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"labelName", "目标名称", &labelName, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"muBiao", "没有应急锤", &muBiao, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0121(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0121_H
