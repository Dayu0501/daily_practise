#ifndef _C_ALGCLASS_0119_H
#define _C_ALGCLASS_0119_H
#include "_c_algBaseClass.h"

class _c_algClass_0119 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER faDongJiHao = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"faDongJiHao", "发动机号", &faDongJiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"faDongJiHao", "发动机号不正确", &faDongJiHao, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0119(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    virtual std::string getPhotoName(std::string algcode);
};

#endif // _C_ALGCLASS_0119_H
