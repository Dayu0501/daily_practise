#ifndef _C_ALGCLASS_0203_H
#define _C_ALGCLASS_0203_H
#include "_c_algBaseClass.h"

class _c_algClass_0203 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shengXiaoRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhongZhiRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanJieShuShiJian = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingZaiKeShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER haoPaiZhongLei = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER baoXianYouXiaoQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheChuanShui = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhengBenHuoFuBen = ALG_PARAM_DEFAULT;//该字段 当下算法返回结果含义为：是否是副本
    ALG_PARM_MEMBER zhaoPianQingXiDu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chaoBen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhuangTai = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dianZiBaoDan = ALG_PARAM_DEFAULT; // 这个字段的含义是  联网查询图片 不是纸质的电子保单
    ALG_PARM_MEMBER zhiZhiBaoDan = ALG_PARAM_DEFAULT; // 标题是 电子保单的图片  也属于纸质保单
    ALG_PARM_MEMBER lianWangChaXun = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER wanShuiPingZhengHao  = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER kaiJuShuiWuJiGuan   = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhaoPianLeiXing   = ALG_PARAM_DEFAULT; //是否为交强险保单（含纸质、电子等所有类型的交强险保单）

	ALG_PARM_MEMBER kaiShiRiQiShuChu  = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER jieZhiRiQiShuChu  = ALG_PARAM_DEFAULT;

    /*
    FROM:zhoujiamin
    zhiZhiBaoDan 对应的是 b_baodan ,
    但实际b_baodan 不单单是指 纸质保单 ， 哪怕 是联网的那种电子保单，b_baoban也是true
    。 所以只有当dianzibaodan 是false，zhizhibaodan是true的时候，这张图片它才确实是纸质保单
    */
    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"shengXiaoRiQi", "生效日期", &shengXiaoRiQi, true, CONFIG_DEFAULT},
        {"zhongZhiRiQi", "终止日期", &zhongZhiRiQi, true, CONFIG_DEFAULT},
        {"jianYanJieShuShiJian", "检验结束时间", &jianYanJieShuShiJian, true, CONFIG_DEFAULT},
        {"faDongJiHao", "发动机号", &faDongJiHao, true, CONFIG_DEFAULT},
        {"heDingZaiKeShu", "核定载客数", &heDingZaiKeShu, true, CONFIG_DEFAULT},
        {"haoPaiZhongLei", "号牌种类", &haoPaiZhongLei, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"dianZiBaoDan", "不是联网查询图片", &dianZiBaoDan,  false, CONFIG_NOCHECK},
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"zhengBenHuoFuBen", "不是合格的保单<正/副本/复印件>文件", &zhengBenHuoFuBen, true, CONFIG_NOCHECK_UNABLE},
        {"baoXianYouXiaoQi", "检验日期不在保险有效期内", &baoXianYouXiaoQi, true, CONFIG_DEFAULT_UNABLE},
        {"yinZhang", "没有印章", &yinZhang, true, CONFIG_DEFAULT},
        {"cheChuanShui", "没有缴纳车船税", &cheChuanShui, true, CONFIG_NOCHECK},
        {"faDongJiHao", "发动机号不对", &faDongJiHao, true, CONFIG_NOCHECK},
        {"zhaoPianQingXiDu", "图片信息不规范", &zhaoPianQingXiDu, true, CONFIG_NOCHECK_UNABLE},
        {"heDingZaiKeShu", "核定载客人数不正确", &heDingZaiKeShu, true, CONFIG_NOCHECK},
        {"zhiZhiBaoDan", "不是合格纸质保单", &zhiZhiBaoDan,  false, CONFIG_NOCHECK},
        {"chaoBen", "是否开启抄件不通过(逻辑判定)", &chaoBen, false, CONFIG_NOCHECK},
        {"wanShuiPingZhengHao", "(免税)完税凭证号错误", &wanShuiPingZhengHao, false, CONFIG_NOCHECK},
        {"kaiJuShuiWuJiGuan", "税务机关错误", &kaiJuShuiWuJiGuan, false, CONFIG_NOCHECK},
        {"zhaoPianLeiXing", "不是交强险保单", &zhaoPianLeiXing, false, CONFIG_NOCHECK},
        {"kaiShiRiQiShuChu", "保险生效日期无答案输出(用于逻辑判断)", &kaiShiRiQiShuChu, false, CONFIG_NOCHECK},
        {"jieZhiRiQiShuChu", "保险截止日期无答案输出(用于逻辑判断)", &jieZhiRiQiShuChu, false, CONFIG_NOCHECK}
    };

    std::vector<memberItem> resultMemberList_dianZi = {
        {"dianZiBaoDan", "不是电子保单", &dianZiBaoDan,  false, CONFIG_NOCHECK},
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"baoXianYouXiaoQi", "检验日期不在保险有效期内", &baoXianYouXiaoQi, true, CONFIG_DEFAULT_UNABLE},
        {"cheChuanShui", "没有缴纳车船税", &cheChuanShui, true, CONFIG_NOCHECK},
        {"faDongJiHao", "发动机号不对", &faDongJiHao, true, CONFIG_NOCHECK},
        {"zhuangTai", "状态异常", &zhuangTai, true, CONFIG_NOCHECK},
        {"zhaoPianQingXiDu", "图片信息不规范", &zhaoPianQingXiDu, true, CONFIG_NOCHECK_UNABLE},
    };


    std::vector<memberItem> inMemberList_moTuo = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"shengXiaoRiQi", "生效日期", &shengXiaoRiQi, true, CONFIG_DEFAULT},
        {"zhongZhiRiQi", "终止日期", &zhongZhiRiQi, true, CONFIG_DEFAULT},
        {"jianYanJieShuShiJian", "检验结束时间", &jianYanJieShuShiJian, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList_moTuo = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"dianZiBaoDan", "不是电子保单", &dianZiBaoDan,  false, CONFIG_NOCHECK},
        {"zhengBenHuoFuBen", "不是合格的保单<正/副本/复印件>文件", &zhengBenHuoFuBen, true, CONFIG_NOCHECK_UNABLE},
        {"baoXianYouXiaoQi", "检验日期不在保险有效期内", &baoXianYouXiaoQi, true, CONFIG_DEFAULT_UNABLE},
        {"yinZhang", "没有印章", &yinZhang, true, CONFIG_DEFAULT},
        {"cheChuanShui", "没有缴纳车船税", &cheChuanShui, true, CONFIG_NOCHECK},
        {"chaoBen", "是否开启抄件不通过(逻辑判定)", &chaoBen, false, CONFIG_NOCHECK},

    };

    std::vector<memberItem> resultMemberList_moTuo_dianZi = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"dianZiBaoDan", "不是电子保单", &dianZiBaoDan,  false, CONFIG_NOCHECK},
        {"zhengBenHuoFuBen", "不是副本文件", &zhengBenHuoFuBen, true, CONFIG_NOCHECK_UNABLE},
        {"baoXianYouXiaoQi", "检验日期不在保险有效期内", &baoXianYouXiaoQi, true, CONFIG_DEFAULT_UNABLE},
        {"yinZhang", "没有印章", &yinZhang, true, CONFIG_DEFAULT},
        {"cheChuanShui", "没有缴纳车船税", &cheChuanShui, true, CONFIG_NOCHECK},

    };

    virtual ~_c_algClass_0203(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    virtual std::string getPhotoName(std::string algcode);
};

#endif // _C_ALGCLASS_0203_H
