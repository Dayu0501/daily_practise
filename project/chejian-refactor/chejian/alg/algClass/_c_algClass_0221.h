#ifndef _C_ALGCLASS_0221_H
#define _C_ALGCLASS_0221_H
#include "_c_algBaseClass.h"

class _c_algClass_0221 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER haoPaiZhongLei = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER haoPaiHaoMa = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yeWuLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER diYaShenQingBiao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER suoYouRenQianMing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER diYaQuanRen = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER diYaQuanRenQianMing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"haoPaiZhongLei", "号牌种类", &haoPaiZhongLei, true, CONFIG_DEFAULT},
        {"chePaiHao", "号牌号码", &haoPaiHaoMa, true, CONFIG_DEFAULT},
        {"yeWuLeiXing", "业务类型", &yeWuLeiXing, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        //{"diYaShenQingBiao", "是否是抵押/质押申请表", &diYaShenQingBiao, true, CONFIG_DEFAULT}, 算法没有这一项
        {"haoPaiZhongLei", "号牌种类不正确", &haoPaiZhongLei, true, CONFIG_DEFAULT},
        {"chePaiHao", "号牌号码不正确", &haoPaiHaoMa, true, CONFIG_DEFAULT},
        {"yeWuLeiXing", "业务类型不正确", &yeWuLeiXing, true, CONFIG_DEFAULT},
        {"qianMing", "没有所有人签字", &suoYouRenQianMing, true, CONFIG_DEFAULT},
        {"diYaRenXingMingShuChu", "没有抵押权人", &diYaQuanRen, true, CONFIG_DEFAULT},
        //{"diYaQuanRenQianMing", "没有抵押权人签字", &diYaQuanRenQianMing, true, CONFIG_DEFAULT} 算法没有这一项
    };

    virtual ~_c_algClass_0221(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0221_H
