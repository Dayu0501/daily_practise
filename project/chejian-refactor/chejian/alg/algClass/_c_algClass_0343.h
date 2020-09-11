#ifndef _C_ALGCLASS_0343_H
#define _C_ALGCLASS_0343_H
#include "_c_algBaseClass.h"

class _c_algClass_0343 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER queShaoJieShuZhaoPian = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"queShaoJieShuZhaoPian", "缺少动态检验结束照片", &queShaoJieShuZhaoPian, true, CONFIG_DEFAULT},
        {"chePaiHao_jieshu", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT}
    };

    virtual ~_c_algClass_0343(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool loadExtAlgClass(std::vector<_c_algTask *> *pVector);
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0343_H
