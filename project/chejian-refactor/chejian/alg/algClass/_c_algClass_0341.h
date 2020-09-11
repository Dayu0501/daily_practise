#ifndef _C_ALGCLASS_0341_H
#define _C_ALGCLASS_0341_H
#include "_c_algBaseClass.h"

class _c_algClass_0341 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER queShaoKaiShiZhaoPian = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"queShaoKaiShiZhaoPian", "缺少动态检验开始照片", &queShaoKaiShiZhaoPian, true, CONFIG_DEFAULT},
        {"chePaiHao_kaishi", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0341(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0341_H
