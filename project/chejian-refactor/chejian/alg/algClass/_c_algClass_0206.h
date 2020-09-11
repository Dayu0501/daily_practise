#ifndef _C_ALGCLASS_0206_H
#define _C_ALGCLASS_0206_H
#include "_c_algBaseClass.h"

class _c_algClass_0206 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanJieShuShiJian = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheChuanShui = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shuiKuanSuoShuRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER wanShuiPingZhengHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER kaiJuShuiWuJiGuan = ALG_PARAM_DEFAULT;
    //ALG_PARM_MEMBER baoXianYouXiaoQi = ALG_PARAM_DEFAULT; 废弃
    ALG_PARM_MEMBER zhaoPianLeiXing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"jianYanJieShuShiJian", "检验结束时间", &jianYanJieShuShiJian, true, CONFIG_DEFAULT}
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_NOCHECK},
        {"cheChuanShui", "车船税不合格", &cheChuanShui, true, CONFIG_DEFAULT},
        {"shuiKuanSuoShuRiQi", "税款所属日期不是整年", &shuiKuanSuoShuRiQi, true, CONFIG_NOCHECK},
        {"jianYanJieShuShiJian", "检验日期不在保险有效期内", &jianYanJieShuShiJian, true, CONFIG_NOCHECK},
        {"yinZhang", "印章是否存在", &yinZhang, false, CONFIG_NOCHECK},
        //{"baoXianYouXiaoQi", "检验日期不在保险有效期内", &baoXianYouXiaoQi, true, CONFIG_NOCHECK}, 已废弃
        {"wanShuiPingZhengHao", "完税凭证号错误", &wanShuiPingZhengHao, false, CONFIG_NOCHECK},
        {"kaiJuShuiWuJiGuan", "税务机关错误", &kaiJuShuiWuJiGuan, false, CONFIG_NOCHECK},
        {"zhaoPianLeiXing", "照片不是完税证明", &zhaoPianLeiXing, false, CONFIG_NOCHECK}
    };

    std::vector<memberItem> inMemberList_moTuo = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList_moTuo = {
        {"cheChuanShui", "车船税不合格", &cheChuanShui, true, CONFIG_DEFAULT},
        {"shuiKuanSuoShuRiQi", "税款所属日期不是整年", &shuiKuanSuoShuRiQi, true, CONFIG_NOCHECK},
        {"jianYanJieShuShiJian", "日期不正确", &jianYanJieShuShiJian, true, CONFIG_NOCHECK},
        {"zhaoPianLeiXing", "照片不是完税证明", &zhaoPianLeiXing, true, CONFIG_NOCHECK}
    };

    virtual ~_c_algClass_0206(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    virtual std::string getPhotoName(std::string algcode);
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0206_H
