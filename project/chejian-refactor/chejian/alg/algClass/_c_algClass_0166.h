#ifndef _C_ALGCLASS_0166_H
#define _C_ALGCLASS_0166_H
#include "_c_algBaseClass.h"

class _c_algClass_0166 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER gaiZhuang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingZaiKeShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER paiSheGuiFan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zuoWeiShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER anQuanDai = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"heDingZaiKeShu", "核定载客人数", &heDingZaiKeShu, true, CONFIG_DEFAULT}
    };

    std::vector<memberItem> resultMemberList = {
        {"paiSheGuiFan", "不符合拍摄规范", &paiSheGuiFan, true, CONFIG_NOCHECK},
        {"gaiZhuang", "车辆有改装", &gaiZhuang, false, CONFIG_DEFAULT},
        {"zuoWeiShu", "座椅数不正确", &zuoWeiShu, false, CONFIG_NOCHECK},
        {"anQuanDai", "没有安全带", &anQuanDai, false, CONFIG_NOCHECK}
    };

    virtual ~_c_algClass_0166(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    virtual std::string getPhotoName(std::string algcode);
};

#endif // _C_ALGCLASS_0166_H
