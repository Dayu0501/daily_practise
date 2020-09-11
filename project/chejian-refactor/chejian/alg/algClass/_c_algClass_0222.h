#ifndef _C_ALGCLASS_0222_H
#define _C_ALGCLASS_0222_H
#include "_c_algBaseClass.h"

class _c_algClass_0222 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER haoPaiHaoMa = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "号牌号码", &haoPaiHaoMa, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "号牌号码不正确", &haoPaiHaoMa, true, CONFIG_DEFAULT},
        {"yinZhang", "签名不正确", &yinZhang, true, CONFIG_DEFAULT},
        {"qianMing", "印章不正确", &qianMing, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0222(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0222_H
