#ifndef _C_ALGCLASS_0205_WUZHOU_H
#define _C_ALGCLASS_0205_WUZHOU_H
#include "alg/algClass/_c_algBaseClass.h"
#include "alg/algClass/_c_algClass_0205.h"

class _c_algClass_0205_WuZhou:public _c_algClass_0205{
public:

    virtual ~_c_algClass_0205_WuZhou(){}
    virtual bool ResultEdit();  
    virtual bool subClassLoadNewResultMember(); 

private:
    ALG_PARM_MEMBER itemList = ALG_PARAM_DEFAULT;    
};

#endif // _C_ALGCLASS_0205_WUZHOU_H
