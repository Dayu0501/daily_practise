#ifndef _C_ALGCLASS_0157_WUZHOU_H
#define _C_ALGCLASS_0157_WUZHOU_H
#include "alg/algClass/_c_algBaseClass.h"
#include "alg/algClass/_c_algClass_0157.h"

class _c_algClass_0157_WuZhou:public _c_algClass_0157{
public:

    virtual ~_c_algClass_0157_WuZhou(){}
    virtual bool subClassLoadNewResultMember();
    virtual bool ResultEdit();
 
private:
    ALG_PARM_MEMBER fangXiangPan = ALG_PARAM_DEFAULT;
};

#endif // _C_ALGCLASS_0157_WUZHOU_H
