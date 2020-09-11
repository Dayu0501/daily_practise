#ifndef _C_ALGCLASS_0159_H
#define _C_ALGCLASS_0159_H
#include "_c_algBaseClass.h"

class _c_algClass_0159 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER luoSi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER luoSiZuoShang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER luoSiYouShang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER luoSiZuoXia = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER luoSiYouXia = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
         {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"luoSi", "螺丝数量不正确", &luoSi, true, CONFIG_DEFAULT},
        {"luoSiZuoShang", "缺失左上螺丝", &luoSiZuoShang, true, CONFIG_NOCHECK_UNABLE},
        {"luoSiYouShang", "缺失右上螺丝", &luoSiYouShang, true, CONFIG_NOCHECK_UNABLE},
        {"luoSiZuoXia", "缺失左下螺丝", &luoSiZuoXia, true, CONFIG_NOCHECK_UNABLE},
        {"luoSiYouXia", "缺失右下螺丝", &luoSiYouXia, true, CONFIG_NOCHECK_UNABLE},
    };

    virtual ~_c_algClass_0159(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0159_H
