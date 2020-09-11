﻿#ifndef _C_ALGCLASS_0227_H
#define _C_ALGCLASS_0227_H
#include "_c_algBaseClass.h"

//算法废除进口凭证
class _c_algClass_0227 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"yinZhang", "印章不正确", &yinZhang, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0227(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0227_H
