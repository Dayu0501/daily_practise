#ifndef _C_ALGCLASS_0226_H
#define _C_ALGCLASS_0226_H
#include "_c_algBaseClass.h"

class _c_algClass_0226 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER shiYongRen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shenFenZhengHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heGeZhengHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER xiaoShouDanWei = ALG_PARAM_DEFAULT;

    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHaoShuChu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiHaoShuChu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heGeZhengHaoShuChu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shenFenZhengHaoShuChu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER changPaiXingHaoShuChu = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"shiYongRen", "所有人", &shiYongRen, true, CONFIG_DEFAULT},
        {"shenFenZhengHao", "身份证号", &shenFenZhengHao, true, CONFIG_DEFAULT},
        {"heGeZhengHao", "合格证号", &heGeZhengHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"faDongJiHao", "发动机号", &faDongJiHao, true, CONFIG_DEFAULT},
        {"xiaoShouDanWei", "销售单位名称", &xiaoShouDanWei, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"shiYongRen", "所有人不正确", &shiYongRen, true, CONFIG_DEFAULT},
        {"shenFenZhengHao", "身份证号不正确", &shenFenZhengHao, true, CONFIG_DEFAULT},
        {"heGeZhengHao", "合格证号不正确", &heGeZhengHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"faDongJiHao", "发动机号不正确", &faDongJiHao, true, CONFIG_DEFAULT},
        {"xiaoShouDanWei", "销售单位名称不正确", &xiaoShouDanWei, true, CONFIG_DEFAULT},
        {"yinZhang", "没有印章", &yinZhang, true, CONFIG_DEFAULT},
        {"cheJiaHaoShuChu", "输出车架号识别结果输出（用于逻辑判断）", &yinZhang, true, CONFIG_NOCHECK},
        {"faDongJiHaoShuChu", "输出发动机号识别结果输出（用于逻辑判断）", &yinZhang, true, CONFIG_NOCHECK},
        {"heGeZhengHaoShuChu", "输出合格证号识别结果（用于逻辑判断）", &yinZhang, true, CONFIG_NOCHECK},
        {"shenFenZhengHaoShuChu", "输出所有人身份证号识别结果（用于逻辑判断）", &yinZhang, true, CONFIG_NOCHECK},
        {"changPaiXingHaoShuChu", "输出厂牌型号识别结果（用于逻辑判断）", &yinZhang, true, CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0226(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0226_H
