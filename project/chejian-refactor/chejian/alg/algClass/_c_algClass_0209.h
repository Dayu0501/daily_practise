#ifndef _C_ALGCLASS_0209_H
#define _C_ALGCLASS_0209_H
#include "_c_algBaseClass.h"

class _c_algClass_0209 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER weiQiJianCeShiJian = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiXingHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER huanBaoJianYanJieLun = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER huanBaoJianYanJieLun_waiguan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER huanBaoJianYanJieLun_OBD = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang_CMA = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianCeShiJian = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_caoZuoYuan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_jiaShiYuan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_piZhunRen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_shenHeRen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_shouQuanRen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dianZiBiaoGe = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER huanBaoDan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dangTianRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiBiaoHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER ranLiaoZhongLei = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER danJuBianHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER fangWeiMaShiFouYiZhi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanJieShuShiJian = ALG_PARAM_DEFAULT;

    std::vector<std::string> shiJianVector;

    std::vector<memberItem> inMemberList = {
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"weiQiJianCeShiJian", "尾气检测时间", &weiQiJianCeShiJian, true, CONFIG_DEFAULT},
        {"faDongJiXingHao", "发动机型号", &faDongJiXingHao, true, CONFIG_DEFAULT},
        {"dangTianRiQi", "当天日期", &dangTianRiQi, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"faDongJiHao","发动机/电动机号码",&faDongJiBiaoHao, true, CONFIG_DEFAULT},
        {"ranLiangZhongLei","燃料种类",&ranLiaoZhongLei, true, CONFIG_DEFAULT},
        {"jianYanJieShuShiJian", "检验结束时间", &jianYanJieShuShiJian, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"huanBaoJianYanJieLun_yiye", "检查结论不通过", &huanBaoJianYanJieLun, true, CONFIG_NOCHECK},
        {"huanBaoJianYanJieLun_waiguan_yiye", "外观检验结论不通过", &huanBaoJianYanJieLun_waiguan, true, CONFIG_NOCHECK},
        {"huanBaoJianYanJieLun_OBD", "OBD检查结果不通过", &huanBaoJianYanJieLun_OBD, true, CONFIG_NOCHECK},
        {"chePaiHao_yiye", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao_yiye", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"yinZhang_yiye", "没有印章", &yinZhang, true, CONFIG_DEFAULT},
        {"qianMing_yiye", "没有签名", &qianMing, true, CONFIG_DEFAULT},
        {"yinZhang_CMA_yiye", "没有\"CMA\"印章", &yinZhang_CMA, true, CONFIG_NOCHECK},
        {"weiQiJianCeShiJian_yiye", "检测日期不在有效期内", &weiQiJianCeShiJian, true, CONFIG_NOCHECK},
        {"faDongJiXingHao_yiye", "发动机型号不合格", &faDongJiXingHao, true, CONFIG_NOCHECK},
        {"jianCeShiJian_yiye", "检测时间不符合", &jianCeShiJian, true, CONFIG_NOCHECK},
        {"qianMing_caoZuoYuan_yiye", "没有操作员签名", &qianMing_caoZuoYuan, true, CONFIG_NOCHECK},
        {"qianMing_jiaShiYuan_yiye", "没有驾驶员签名", &qianMing_jiaShiYuan, true, CONFIG_NOCHECK},
        {"qianMing_piZhunRen_yiye", "没有批准人签字", &qianMing_piZhunRen, true, CONFIG_NOCHECK},
        {"qianMing_shenHeRen_yiye", "没有审核员签字", &qianMing_shenHeRen, true, CONFIG_NOCHECK},
        {"qianMing_shouQuanRen_yiye", "没有授权人签字", &qianMing_shouQuanRen, true, CONFIG_NOCHECK},
        {"dianZiBiaoGe_yiye", "不是电子表格", &dianZiBiaoGe, true, CONFIG_NOCHECK},
        {"huanBaoDan_yiye", "照片不是尾气检测报告", &huanBaoDan, true, CONFIG_NOCHECK},
        {"cheLiangLeiXing_yiye", "车辆类型不正确", &cheLiangLeiXing, true, CONFIG_NOCHECK},
        {"faDongJiHao_yiye", "发动机编号不合格", &faDongJiBiaoHao, true, CONFIG_NOCHECK},
        {"ranLiaoZhongLei_yiye", "燃料种类不正确", &ranLiaoZhongLei, true, CONFIG_NOCHECK},
        {"danJuBianHao", "单据编号不一致", &danJuBianHao, true, CONFIG_NOCHECK},
        {"fangWeiMaShiFouYiZhi", "防伪码不一致", &fangWeiMaShiFouYiZhi, true, CONFIG_NOCHECK}
    };

    std::vector<std::string> shiJianVector_erye;

    ALG_PARM_MEMBER cheJiaHao_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER weiQiJianCeShiJian_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dangTianRiQi_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiXingHao_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER huanBaoJianYanJieLun_erye = ALG_PARAM_DEFAULT;
   // ALG_PARM_MEMBER huanBaoJianYanJieLun_ODB = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang_CMA_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianCeShiJian_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_caoZuoYuan_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_jiaShiYuan_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_piZhunRen_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_shenHeRen_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qianMing_shouQuanRen_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dianZiBiaoGe_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER huanBaoDan_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangLeiXing_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiBiaoHao_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER ranLiaoZhongLei_erye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYiShunTaiGongKuangFa = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList_erye = {
        {"cheJiaHao", "车架号", &cheJiaHao_erye, true, CONFIG_DEFAULT},
        {"chePaiHao", "车牌号", &chePaiHao_erye, true, CONFIG_DEFAULT},
        {"jianYanJieShuShiJian", "检验结束时间", &jianYanJieShuShiJian, true, CONFIG_DEFAULT},
        {"weiQiJianCeShiJian_erye", "尾气检测时间", &weiQiJianCeShiJian_erye, true, CONFIG_DEFAULT},
        {"faDongJiXingHao", "发动机型号", &faDongJiXingHao_erye, true, CONFIG_DEFAULT},
        {"dangTianRiQi_erye", "当天日期", &dangTianRiQi_erye, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"faDongJiHao","发动机/电动机号码",&faDongJiBiaoHao, true, CONFIG_DEFAULT},
        {"ranLiaoZhongLei","燃料种类",&ranLiaoZhongLei, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList_erye = {
        {"huanBaoJianYanJieLun_erye", "检查结论不通过", &huanBaoJianYanJieLun_erye, true, CONFIG_NOCHECK},
        {"huanBaoJianYanJieLun_OBD", "OBD检查结果不通过", &huanBaoJianYanJieLun_OBD, true, CONFIG_NOCHECK},
        {"jianYiShunTaiGongKuangFa_erye","不是简易瞬态工况法", &jianYiShunTaiGongKuangFa ,true ,CONFIG_NOCHECK},
        {"chePaiHao_erye", "车牌号不正确", &chePaiHao_erye, true, CONFIG_DEFAULT},
        {"cheJiaHao_erye", "车架号不正确", &cheJiaHao_erye, true, CONFIG_DEFAULT},
        {"yinZhang_erye", "没有印章", &yinZhang_erye, true, CONFIG_DEFAULT},
        {"qianMing_erye", "没有签名", &qianMing_erye, true, CONFIG_DEFAULT},
        {"yinZhang_CMA_erye", "没有\"CMA\"印章", &yinZhang_CMA_erye, true, CONFIG_NOCHECK},
        {"weiQiJianCeShiJian_erye", "检测日期不在有效期内", &weiQiJianCeShiJian, true, CONFIG_NOCHECK},
        {"faDongJiXingHao_erye", "发动机型号不合格", &faDongJiXingHao, true, CONFIG_NOCHECK},
        {"jianCeShiJian_erye", "检测时间不符合", &jianCeShiJian_erye, true, CONFIG_NOCHECK},
        {"qianMing_caoZuoYuan_erye", "没有操作员签名", &qianMing_caoZuoYuan_erye, true, CONFIG_NOCHECK},
        {"qianMing_jiaShiYuan_erye", "没有驾驶员签名", &qianMing_jiaShiYuan_erye, true, CONFIG_NOCHECK},
        {"qianMing_piZhunRen_erye", "没有批准人签字", &qianMing_piZhunRen_erye, true, CONFIG_NOCHECK},
        {"qianMing_shenHeRen_erye", "没有审核员签字", &qianMing_shenHeRen_erye, true, CONFIG_NOCHECK},
        {"qianMing_shouQuanRen_erye", "没有授权人签字", &qianMing_shouQuanRen_erye, true, CONFIG_NOCHECK},
        {"dianZiBiaoGe_erye", "不是电子表格", &dianZiBiaoGe_erye, true, CONFIG_NOCHECK},
        {"huanBaoDan_erye", "照片不是尾气检测报告", &huanBaoDan_erye, true, CONFIG_NOCHECK},
        {"cheLiangLeiXing_erye", "车辆类型不正确", &cheLiangLeiXing_erye, true, CONFIG_NOCHECK},
        {"faDongJiHao_erye", "发动机编号不合格", &faDongJiBiaoHao_erye, true, CONFIG_NOCHECK},
        {"ranLiaoZhongLei_erye", "燃料种类不正确", &ranLiaoZhongLei_erye, true, CONFIG_NOCHECK}
    };

    virtual ~_c_algClass_0209(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    virtual std::string getPhotoName(std::string algcode);
};

#endif // _C_ALGCLASS_0209_H
