#ifndef _C_ALGCLASS_0228_FUYANG_H
#define _C_ALGCLASS_0228_FUYANG_H
#include "alg/algClass/_c_algBaseClass.h"

class _c_algClass_0228 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER name = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER isError = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER isFront = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER isBack = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER isDatevalid = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER isNameCorrect = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"name", "送检人姓名", &name, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"isError", "身份证证件不存在", &isError, true, CONFIG_DEFAULT},
        {"isFront", "是否是正面", &isFront, false, CONFIG_DEFAULT},
        {"isBack", "是否是反面", &isBack, false, CONFIG_DEFAULT},
        {"isDateValid", "是否在有效期内", &isDatevalid, false, CONFIG_DEFAULT},
        {"isNameCorrect", "姓名不正确", &isNameCorrect, false, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0228(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0228_FUYANG_H
