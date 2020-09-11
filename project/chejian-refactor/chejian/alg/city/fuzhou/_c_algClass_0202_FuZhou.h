#ifndef _C_ALGCLASS_0202_FUZHOU_H
#define _C_ALGCLASS_0202_FUZHOU_H
#include "alg/algClass/_c_algClass_0202.h"

class _c_algClass_0202_FuZhou : public _c_algClass_0202{
public:
    ALG_PARM_MEMBER suoShuJiGou = ALG_PARAM_DEFAULT;

    _c_algClass_0202_FuZhou();
    bool ResultEdit() override;
};

#endif // _C_ALGCLASS_0202_FUZHOU_H