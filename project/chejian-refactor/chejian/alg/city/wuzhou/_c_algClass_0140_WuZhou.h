#ifndef _C_ALGCLASS_0140_WUZHOU_H
#define _C_ALGCLASS_0140_WUZHOU_H
#include "alg/algClass/_c_algBaseClass.h"
#include "alg/algClass/_c_algClass_0111.h"

class _c_algClass_0140_WuZhou:public _c_algClass_0111{
public:

    ALG_PARM_MEMBER labelName = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yingJiChui = ALG_PARAM_DEFAULT;   

    std::vector<memberItem> inMemberList = {
        {"labelName", "标签名称", &labelName, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"yingJiChui", "副制动踏板不存在", &yingJiChui, true, CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0140_WuZhou(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
 
};

#endif // _C_ALGCLASS_0140_WUZHOU_H
