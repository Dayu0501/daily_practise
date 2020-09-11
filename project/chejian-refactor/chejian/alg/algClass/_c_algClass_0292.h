#ifndef _C_ALGCLASS_0292_H
#define _C_ALGCLASS_0292_H
#include "_c_algBaseClass.h"

class _c_algClass_0292 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shengXiaoRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhongZhiRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanJieShuShiJian = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingZaiKeShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER baoXianYouXiaoQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheChuanShui = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhengBenHuoFuBen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhaoPianQingXiDu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chaoBen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhuangTai = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dianZiBaoDan = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"shengXiaoRiQi", "生效日期", &shengXiaoRiQi, true, CONFIG_DEFAULT},
        {"zhongZhiRiQi", "终止日期", &zhongZhiRiQi, true, CONFIG_DEFAULT},
        {"jianYanJieShuShiJian", "检验结束时间", &jianYanJieShuShiJian, true, CONFIG_DEFAULT},
        {"faDongJiHao", "发动机号", &faDongJiHao, true, CONFIG_DEFAULT},
        {"heDingZaiKeShu", "核定载客数", &heDingZaiKeShu, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"baoXianYouXiaoQi", "检验日期不在保险有效期内", &baoXianYouXiaoQi, true, CONFIG_DEFAULT},
        {"cheChuanShui", "没有缴纳车船税", &cheChuanShui, true, CONFIG_NOCHECK},
        {"faDongJiHao", "发动机号不对", &faDongJiHao, true, CONFIG_NOCHECK},
        {"zhuangTai", "状态异常", &zhuangTai, true, CONFIG_NOCHECK},
        {"zhaoPianQingXiDu", "图片信息不规范", &zhaoPianQingXiDu, true, CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0292(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0292_H
