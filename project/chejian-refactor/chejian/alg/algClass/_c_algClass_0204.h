#ifndef _C_ALGCLASS_0204_H
#define _C_ALGCLASS_0204_H
#include "_c_algBaseClass.h"

class _c_algClass_0204 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanJieShuShiJian = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanJieLun = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shuJuXiang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang_CMA = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang_queRen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhaoPianQingXiDu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER suoYouRen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhaoPianLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHaoShuChu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHaoShuChu = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"jianYanJieShuShiJian", "检验结束时间", &jianYanJieShuShiJian, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型编码", &cheLiangLeiXing, true, CONFIG_NOCHECK},
        {"faDongJiHao", "发动机号", &faDongJiHao, true, CONFIG_NOCHECK},
        {"suoYouRen", "所有人姓名", &suoYouRen, true, CONFIG_NOCHECK}
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型不正确", &cheLiangLeiXing, true, CONFIG_NOCHECK},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"jianYanJieLun", "结论不合格", &jianYanJieLun, true, CONFIG_DEFAULT},
        {"shuJuXiang", "数据项不正确", &shuJuXiang, true, CONFIG_NOCHECK},
        {"qianZi", "没有签名", &qianMing, true, CONFIG_DEFAULT},
        {"yinZhang", "没有印章", &yinZhang, true, CONFIG_DEFAULT},
        {"yinZhang_CMA", "没有CMA印章", &yinZhang_CMA, true, CONFIG_NOCHECK},
        {"yinZhang_queRen", "没有确认印章", &yinZhang_queRen, true, CONFIG_NOCHECK},
        {"zhaoPianQingXiDu", "图片信息不规范", &zhaoPianQingXiDu, true, CONFIG_NOCHECK_UNABLE},
        {"jianYanRiQi", "检验日期不正确", &jianYanRiQi, true, CONFIG_NOCHECK_UNABLE},
        {"faDongJiHao", "发动机号不正确", &faDongJiHao, true, CONFIG_NOCHECK},
        {"suoYouRen", "所有人姓名不正确", &suoYouRen, true, CONFIG_NOCHECK},
        {"zhaoPianLeiXing", "照片不是检验报告", &zhaoPianLeiXing, true, CONFIG_NOCHECK},
        {"cheJiaHaoShuChu", "车架号识别结果输出（用于逻辑判断）", &cheJiaHaoShuChu, true, CONFIG_NOCHECK},
        {"chePaiHaoShuChu", "车牌号识别结果输出（用于逻辑判断）", &chePaiHaoShuChu, true, CONFIG_NOCHECK}
    };

    std::vector<memberItem> inMemberList_moTuo = {
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList_moTuo = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"jianYanJieLun", "结论不合格", &jianYanJieLun, true, CONFIG_DEFAULT},
        {"shuJuXiang", "数据项不正确", &shuJuXiang, true, CONFIG_NOCHECK},
        {"qianZi", "没有签名", &qianMing, true, CONFIG_DEFAULT},
        {"yinZhang", "没有印章", &yinZhang, true, CONFIG_DEFAULT},
        {"zhaoPianLeiXing", "照片不是检验报告", &zhaoPianLeiXing, true, CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0204(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0204_H
