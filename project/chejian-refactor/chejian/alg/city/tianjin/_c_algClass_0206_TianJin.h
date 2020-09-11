#ifndef _C_ALGCLASS_0206_TIANJIN_H
#define _C_ALGCLASS_0206_TIANJIN_H
#include "alg/algClass/_c_algBaseClass.h"

class _c_algClass_0206_TianJin:public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanJieShuShiJian = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheChuanShui = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shuiKuanSuoShuRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER wanShuiZhengMing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;

    ALG_PARM_MEMBER wanShuiPingZhengHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER kaiJuShuiWuJiGuan = ALG_PARAM_DEFAULT;

    ALG_PARM_MEMBER dianZiBaoDan = ALG_PARAM_DEFAULT; 
    ALG_PARM_MEMBER zhengBenHuoFuBen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER baoXianYouXiaoQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhaoPianQingXiDu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingZaiKeShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhiZhiBaoDan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chaoBen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhaoPianLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER tableID = ALG_PARAM_DEFAULT;


    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"jianYanJieShuShiJian", "检验结束时间", &jianYanJieShuShiJian, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_NOCHECK},
        {"cheChuanShui", "车船税不合格", &cheChuanShui, true, CONFIG_DEFAULT},
        {"shuiKuanSuoShuRiQi", "税款所属日期不是整年", &shuiKuanSuoShuRiQi, true, CONFIG_NOCHECK},
        {"jianYanJieShuShiJian", "日期不正确", &jianYanJieShuShiJian, true, CONFIG_NOCHECK},
        {"yinZhang", "印章是否存在", &yinZhang, false, CONFIG_NOCHECK},
        {"wanShuiPingZhengHao", "完税凭证号错误", &wanShuiPingZhengHao, false, CONFIG_NOCHECK},
        {"kaiJuShuiWuJiGuan", "税务机关错误", &kaiJuShuiWuJiGuan, false, CONFIG_NOCHECK},
        {"zhaoPianLeiXing", "照片不是完税证明", &zhaoPianLeiXing, true, CONFIG_NOCHECK},
        {"tableID", "表单种类id", &tableID, false, CONFIG_NOCHECK},
    };

    std::vector<memberItem> resultMemberList_baodan = {
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
        {"zhaoPianLeiXing", "不是交强险保单", &zhaoPianLeiXing, false, CONFIG_NOCHECK}
    };


    std::vector<memberItem> inMemberList_moTuo = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList_moTuo = {
        {"cheChuanShui", "车船税不合格", &cheChuanShui, true, CONFIG_DEFAULT},
        {"shuiKuanSuoShuRiQi", "税款所属日期不是整年", &shuiKuanSuoShuRiQi, true, CONFIG_NOCHECK},
        {"jianYanJieShuShiJian", "日期不正确", &jianYanJieShuShiJian, true, CONFIG_NOCHECK},
        {"wanShuiZhengMing", "照片不是完税证明", &wanShuiZhengMing, true, CONFIG_NOCHECK},
    };


    virtual ~_c_algClass_0206_TianJin(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0206_H
