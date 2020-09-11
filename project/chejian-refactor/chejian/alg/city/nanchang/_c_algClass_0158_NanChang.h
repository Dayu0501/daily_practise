#ifndef _C_ALGCLASS_0158_NANCHANG_H
#define _C_ALGCLASS_0158_NANCHANG_H
#include "alg/algClass/_c_algBaseClass.h"
#include "alg/algClass/_c_algClass_0158.h"

class _c_algClass_0158_NanChang:public _c_algBaseClass{
public:

    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;

    ALG_PARM_MEMBER cheBiao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER sanJiaoJia = ALG_PARAM_DEFAULT;


    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheBiao", "车标不存在", &cheBiao, true, CONFIG_DEFAULT},
        {"sanJiaoJia", "没有三角架", &sanJiaoJia, true, CONFIG_DEFAULT},
    };

    
    virtual ~_c_algClass_0158_NanChang(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0158_XUANCHENG_H
