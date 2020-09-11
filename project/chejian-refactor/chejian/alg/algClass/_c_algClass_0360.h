#ifndef _C_ALGCLASS_0360_H
#define _C_ALGCLASS_0360_H
#include "_c_algBaseClass.h"

class _c_algClass_0360 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhiDongLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhouLeiXing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
         {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
         {"zhiDongLeiXing", "制动类型", &zhiDongLeiXing, true, CONFIG_DEFAULT},
         {"zhouLeiXing", "轴类型", &zhouLeiXing, true, CONFIG_DEFAULT}
    };

    std::vector<memberItem> resultMemberList = {
         {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT}
    };

    virtual ~_c_algClass_0360(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0360_H
