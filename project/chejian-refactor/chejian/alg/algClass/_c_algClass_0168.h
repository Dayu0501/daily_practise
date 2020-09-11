#ifndef _C_ALGCLASS_0168_H
#define _C_ALGCLASS_0168_H
#include "_c_algBaseClass.h"

class _c_algClass_0168 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER sanJiaoJia = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "水印日期", &shuiYinRiQi, true, CONFIG_DEFAULT},
        {"sanJiaoJia", "三脚架", &sanJiaoJia, true, CONFIG_NOCHECK}
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"sanJiaoJia", "三脚架", &sanJiaoJia, true, CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0168(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0168_H
