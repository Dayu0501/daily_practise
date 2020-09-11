#ifndef _C_ALGCLASS_0167_FUZHOU_H
#define _C_ALGCLASS_0167_FUZHOU_H
#include "alg/algClass/_c_algClass_0167.h"

class _c_algClass_0167_FuZhou : public _c_algClass_0167{
public:
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHaoKaiShi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHaoJieShu =  ALG_PARAM_DEFAULT;

    _c_algClass_0167_FuZhou();
    bool subClassLoadNewResultMember() override ;
    bool InParamEdit() override ;
    ~_c_algClass_0167_FuZhou() override = default;
    bool ResultEdit() override ;
};

#endif // _C_ALGCLASS_0167_FUZHOU_H

