#ifndef _C_ALGCLASS_0212_H
#define _C_ALGCLASS_0212_H
#include "_c_algBaseClass.h"

class _c_algClass_0212 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER shenFenZheng = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
    };

    std::vector<memberItem> resultMemberList = {
        {"shenFenZheng", "身份证复印件信息不正确", &shenFenZheng, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0212(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0212_H
