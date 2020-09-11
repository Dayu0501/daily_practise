#ifndef _C_ALGCLASS_0224_H
#define _C_ALGCLASS_0224_H
#include "_c_algBaseClass.h"

class _c_algClass_0224 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangShiBieDaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER waiKuoChiCun = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER riQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jieGuo = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheLiangShiBieDaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"waiKuoChiCun", "外廓尺寸是否正常", &waiKuoChiCun, true, CONFIG_DEFAULT},
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheLiangShiBieDaiHao, true, CONFIG_DEFAULT},
        {"yinZhang", "没有印章", &yinZhang, true, CONFIG_DEFAULT},
        {"qianMing", "没有签名", &qianMing, true, CONFIG_DEFAULT},
        {"riQi", "日期是否正确", &riQi, true, CONFIG_DEFAULT},
        {"jieGuo", "检测结果", &jieGuo, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0224(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0224_H
