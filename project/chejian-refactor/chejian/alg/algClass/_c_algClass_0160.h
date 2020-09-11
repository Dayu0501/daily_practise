#ifndef _C_ALGCLASS_0160_H
#define _C_ALGCLASS_0160_H
#include "_c_algBaseClass.h"

class _c_algClass_0160 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER lunTaiGuiGe = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"lunTaiGuiGe", "轮胎规格", &lunTaiGuiGe, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"lunTaiGuiGe", "轮胎规格有误", &lunTaiGuiGe, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0160(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    virtual std::string getPhotoName(std::string algcode);
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0160_H
