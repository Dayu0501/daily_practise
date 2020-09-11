#ifndef _C_ALG_CLASS_324_H
#define _C_ALG_CLASS_324_H
#include "_c_algBaseClass.h"

class _c_algClass_0324 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLunWeiZhi = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_NOCHECK},
        {"cheLunWeiZhi", "车轮位置不正确", &cheLunWeiZhi, true, CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0324(){}
	virtual bool InParamEdit();
    virtual bool seekMemberListPointer();
	void setAlgIds() override;
};

#endif
