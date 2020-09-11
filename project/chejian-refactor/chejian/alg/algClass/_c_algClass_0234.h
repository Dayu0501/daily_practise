#ifndef _C_ALGCLASS_0234_H
#define _C_ALGCLASS_0234_H
#include "_c_algBaseClass.h"

class _c_algClass_0234 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER wenJianBiaoQian = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chengShiDaiMa = ALG_PARAM_DEFAULT;

    ALG_PARM_MEMBER qianZi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yingZhang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER suoYouRenQianMing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianCeJiGouQianMing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"wenJianBiaoQian", "表格名称", &wenJianBiaoQian, true, CONFIG_DEFAULT},
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"chengShiDaiMa", "城市代码", &chengShiDaiMa, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"qianZi", "签名不正确", &qianZi, false, CONFIG_NOCHECK},
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"yingZhang", "印章不正确", &yingZhang, true, CONFIG_DEFAULT},
        {"suoYouRenQianMing", "所有人签名不正确", &suoYouRenQianMing, true, CONFIG_DEFAULT},
        {"jianCeJiGouQianMing", "检测机构签名不正确", &jianCeJiGouQianMing, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0234(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    void setAlgIds() override;
};

#endif // _C_ALGCLASS_0234_H
