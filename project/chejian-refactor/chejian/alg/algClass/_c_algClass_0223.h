#ifndef _C_ALGCLASS_0223_H
#define _C_ALGCLASS_0223_H
#include "_c_algBaseClass.h"

class _c_algClass_0223 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER isSame = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
    };

    std::vector<memberItem> resultMemberList = {
        {"isSame", "是否是本人", &isSame, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0223(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0223_H
