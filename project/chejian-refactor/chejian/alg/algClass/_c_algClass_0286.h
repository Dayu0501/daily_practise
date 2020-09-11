#ifndef _C_ALGCLASS_0286_H
#define _C_ALGCLASS_0286_H
#include "_c_algBaseClass.h"

class _c_algClass_0286 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangShiBieDaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanJieLun = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhaoPianLeiXing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheLiangShiBieDaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePai", "车牌不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheLiangShiBieDaiHao, true, CONFIG_DEFAULT},
        {"yinZhang", "没有红章", &yinZhang, false, CONFIG_NOCHECK},
        {"jianYanJieLun", "检验结论不通过", &jianYanJieLun, false, CONFIG_NOCHECK},
        {"zhaoPianLeiXing", "传入照片不是“检验报告仪器”的表单", &zhaoPianLeiXing, false, CONFIG_NOCHECK}
    };

    virtual ~_c_algClass_0286(){}
    virtual bool seekMemberListPointer();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0213_H
