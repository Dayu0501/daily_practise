/*
 * no used.
 * */

#ifndef _C_ALGCLASS_0325_FUZHOU_H
#define _C_ALGCLASS_0325_FUZHOU_H
#include "alg/algClass/_c_algBaseClass.h"

class _c_algClass_0325_FuZhou : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER yanSe = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER xingHao = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList{};

    std::vector<memberItem> resultMemberList = {
            {"yanSe", "车辆颜色不一致", &yanSe, true, CONFIG_DEFAULT},
            {"xingHao", "车辆型号不一致", &xingHao, true, CONFIG_DEFAULT}
    };

    _c_algClass_0325_FuZhou() = default;
    bool subClassLoadNewResultMember() override ;
    bool seekMemberListPointer() override;
    ~_c_algClass_0325_FuZhou() override = default;
};

#endif