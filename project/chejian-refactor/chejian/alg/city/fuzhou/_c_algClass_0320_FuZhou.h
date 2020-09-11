/*
 * no used.
 * */

#ifndef _C_ALGCLASS_0320_FUZHOU_H
#define _C_ALGCLASS_0320_FUZHOU_H

#include "alg/algClass/_c_algBaseClass.h"

class _c_algClass_0320_FuZhou : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zuoDeng1 = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zuoDeng2 = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
            {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
            {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT}
    };

    std::vector<memberItem> resultMemberList = {
            {"zuoDeng", "左灯光不亮", &zuoDeng1, true, CONFIG_DEFAULT},
            {"youDeng", "右灯光不亮", &zuoDeng2, true, CONFIG_DEFAULT}
    };

    _c_algClass_0320_FuZhou();
    bool subClassLoadNewResultMember() override;
    bool InParamEdit() override;
    bool seekMemberListPointer() override;
};

#endif //_C_ALGCLASS_0320_FUZHOU_H
