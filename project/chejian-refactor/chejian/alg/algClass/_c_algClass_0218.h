#ifndef _C_ALGCLASS_0218_H
#define _C_ALGCLASS_0218_H
#include "_c_algBaseClass.h"

class _c_algClass_0218 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER cheLiangPinPai = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangXingHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiXingHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER ranLiangZhongLei = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER lunTaiGuiGe = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingZaiKe = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhongZhiRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhaoPianLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER yinZhang = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"cheLiangPinPai", "车辆品牌", &cheLiangPinPai, true, CONFIG_DEFAULT},
        {"cheLiangXingHao", "车辆型号", &cheLiangXingHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"faDongJiXingHao", "发动机型号", &faDongJiXingHao, true, CONFIG_DEFAULT},
        {"faDongJiHao", "发动机号", &faDongJiHao, true, CONFIG_DEFAULT},
        {"ranLiangZhongLei", "燃料种类", &ranLiangZhongLei, true, CONFIG_DEFAULT},
        {"lunTaiGuiGe", "轮胎规格", &lunTaiGuiGe, true, CONFIG_DEFAULT},
        {"heDingZaiKeShu", "核定载客", &heDingZaiKe, true, CONFIG_DEFAULT},
        {"zhongZhiRiQi", "终止日期", &zhongZhiRiQi, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"cheLiangPinPai", "车辆品牌不正确", &cheLiangPinPai, true, CONFIG_DEFAULT},
        {"cheLiangXingHao", "车辆型号不正确", &cheLiangXingHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"faDongJiXingHao", "发动机型号不正确", &faDongJiXingHao, true, CONFIG_DEFAULT},
        {"faDongJiHao", "发动机号不正确", &faDongJiHao, true, CONFIG_DEFAULT},
        {"ranLiangZhongLei", "燃料种类不正确", &ranLiangZhongLei, true, CONFIG_DEFAULT},
        {"lunTaiGuiGe", "轮胎规格不正确", &lunTaiGuiGe, true, CONFIG_DEFAULT},
        {"heDingZaiKeShu", "核定载客不正确", &heDingZaiKe, true, CONFIG_DEFAULT},
        {"zhongZhiRiQi", "终止日期不正确", &zhongZhiRiQi, true, CONFIG_DEFAULT},
        {"yinZhang", "印章不正确", &yinZhang, true, CONFIG_DEFAULT},
        {"zhaoPianLeiXing", "不是出厂合格证", &zhaoPianLeiXing, true, CONFIG_NOCHECK}
    };

    virtual ~_c_algClass_0218(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    virtual std::string getPhotoName(std::string algcode);
};

#endif // _C_ALGCLASS_0218_H
