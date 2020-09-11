#ifndef _C_ALGCLASS_0225_H
#define _C_ALGCLASS_0225_H
#include "_c_algBaseClass.h"

class _c_algClass_0225 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER luShiJianYan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jieGuo = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang_CMA = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
    };

    std::vector<memberItem> resultMemberList = {
        {"jieGuo", "检验结果不正确", &jieGuo, true, CONFIG_DEFAULT},
        {"yinZhang", "没有监测站印章", &yinZhang, true, CONFIG_NOCHECK},
        {"yinZhang_CMA", "没有\"CMA\"印章", &yinZhang_CMA, true, CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0225(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0225_H
