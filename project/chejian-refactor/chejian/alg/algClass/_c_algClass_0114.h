#ifndef _C_ALGCLASS_0114_H
#define _C_ALGCLASS_0114_H
#include "_c_algBaseClass.h"

/*
算法未实现
*/
class _c_algClass_0114 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER touGuangLv = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };
    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_NOCHECK},
        {"touGuangLv", "玻璃透光率", &touGuangLv, true, CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0114(){}
    virtual bool seekMemberListPointer();
};
#endif // _C_ALGCLASS_0114_H
