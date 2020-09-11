#ifndef _C_ALGCLASS_0115_H
#define _C_ALGCLASS_0115_H
#include "_c_algBaseClass.h"


class _c_algClass_0115 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER cheXiangGaiZhuang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingZaiKeShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER paiSheGuiFan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zuoWeiShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER anQuanDai = ALG_PARAM_DEFAULT;

    ALG_PARM_MEMBER buZaiJianCeFanWei = {"", "", true};

    std::vector<memberItem> inMemberList = {
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"heDingZaiKeShu", "核定载客人数", &heDingZaiKeShu, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"paiSheGuiFan", "不符合拍摄规范", &paiSheGuiFan, true, CONFIG_NOCHECK},
        {"cheXiangGaiZhuang", "车辆有改装", &cheXiangGaiZhuang, false, CONFIG_DEFAULT},
        {"zuoWeiShu", "座位数不正确", &zuoWeiShu, false, CONFIG_NOCHECK},
        {"anQuanDai", "没有安全带", &anQuanDai, false, CONFIG_NOCHECK},
    };

    ALG_PARM_MEMBER gaiZhuang_Kx2 = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER gaiZhuang_Kx9 = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheDing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList_huoChe = {
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"heDingZaiKeShu", "核定载客人数", &heDingZaiKeShu, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList_huoChe = {
        {"paiSheGuiFan", "摄角度不合要求", &paiSheGuiFan, true, CONFIG_NOCHECK},
        {"gaiZhuang_Kx2", "车厢内部有改装", &gaiZhuang_Kx2, false, CONFIG_DEFAULT},
        {"gaiZhuang_Kx9", "车厢内部有改装", &gaiZhuang_Kx9, false, CONFIG_NOCHECK},
        {"cheXiangGaiZhuang", "车厢有改装(客车)", &cheXiangGaiZhuang, false, CONFIG_DEFAULT},
        {"zuoWeiShu", "座位数不对", &zuoWeiShu, false, CONFIG_NOCHECK},
        {"cheDing", "车顶没有封闭", &cheDing, true, CONFIG_NOCHECK},
        {"buZaiJianCeFanWei", "不能处理除了客车和货车以外的车厢内部照片", &buZaiJianCeFanWei, true, {true, true, {}, UNABLE_IDENTIFY}},
    };

    virtual ~_c_algClass_0115(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    virtual std::string getPhotoName(std::string algcode);
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0115_H
