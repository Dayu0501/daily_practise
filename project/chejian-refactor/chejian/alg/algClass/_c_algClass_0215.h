#ifndef _C_ALGCLASS_0215_H
#define _C_ALGCLASS_0215_H
#include "_c_algBaseClass.h"

class _c_algClass_0215 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER haoPaiHaoMa = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangShiBieDaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER maiFang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "号牌号码", &haoPaiHaoMa, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheLiangShiBieDaiHao, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"maiFang", "是不是卖方", &maiFang, true, CONFIG_DEFAULT},
        {"chePaiHao", "号牌号码不正确", &haoPaiHaoMa, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheLiangShiBieDaiHao, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型不正确", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"yinZhang", "没有印章", &yinZhang, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0215(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0215_H
