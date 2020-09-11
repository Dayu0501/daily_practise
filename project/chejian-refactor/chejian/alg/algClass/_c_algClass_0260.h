#ifndef _C_ALGCLASS_0260_H
#define _C_ALGCLASS_0260_H

#include "_c_algBaseClass.h"
#include "_c_algClass_0228.h"
#include "../base/baseTool.h"

class _c_algClass_0260 : public _c_algClass_0228
{
public:
    virtual ~_c_algClass_0260(){}

    virtual bool seekMemberListPointer();
    virtual bool InParamEdit(){
       return _c_algClass_0228::InParamEdit();
    }
    virtual bool ResultEdit();
};


#endif // _C_ALGCLASS_0260_H
