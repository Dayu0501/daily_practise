#ifndef _C_ALGCLASS_0213_H
#define _C_ALGCLASS_0213_H
#include "_c_algBaseClass.h"

class _c_algClass_0213 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER juZhuZhengMing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
    };

    std::vector<memberItem> resultMemberList = {
        {"juZhuZhengMing", "居住证明不正确", &juZhuZhengMing, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0213(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0213_H
