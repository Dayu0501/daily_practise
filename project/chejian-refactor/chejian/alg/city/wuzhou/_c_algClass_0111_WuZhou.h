#ifndef _C_ALGCLASS_0111_WUZHOU_H
#define _C_ALGCLASS_0111_WUZHOU_H
#include "alg/algClass/_c_algBaseClass.h"
#include "alg/algClass/_c_algClass_0111.h"

class _c_algClass_0111_WuZhou:public _c_algClass_0111{
public:

    virtual ~_c_algClass_0111_WuZhou(){}
    virtual bool subClassLoadNewResultMember();

private:
    ALG_PARM_MEMBER houShiJing = ALG_PARAM_DEFAULT;    
};

#endif // _C_ALGCLASS_0111_WUZHOU_H
