#ifndef _C_ALGCLASS_0186_NANCHONG_H
#define _C_ALGCLASS_0186_NANCHONG_H
#include "alg/algClass/_c_algBaseClass.h"

class _c_algClass_0186_NanChong : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanYuan = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"jianYanYuan", "没有检验员", &jianYanYuan, true, CONFIG_DEFAULT}
    };

    std::vector<memberItem> inMemberList_moTuo = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };

    ~_c_algClass_0186_NanChong() override{}
    bool seekMemberListPointer() override;
    bool InParamEdit() override;
    bool ResultEdit() override;
};

#endif // _C_ALGCLASS_0186_NANCHONG_H
