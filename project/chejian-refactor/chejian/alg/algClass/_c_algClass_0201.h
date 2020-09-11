#ifndef _C_ALGCLASS_0201_H
#define _C_ALGCLASS_0201_H
#include "_c_algBaseClass.h"

class _c_algClass_0201 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER xingShiZhengXinBianHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faZhengRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dangAnHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingZaiKeShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shenFenZheng = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhuYeFanMianCheLiang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhaoPianQingXiDu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qiangZhiBaoFeiQiZhi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheType = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingRenShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao_fuye = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shenFenZhen_front = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shenFenZhen_back = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shenFenZhen_validDate = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faDongJiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yanSe = ALG_PARAM_DEFAULT;       //暂时未使用
    ALG_PARM_MEMBER xingHao = ALG_PARAM_DEFAULT;     //暂时未使用
    ALG_PARM_MEMBER chePaiHao_fuye_back = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER fuYeZhangGeShu = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhuYe = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"xingShiZhengXinBianHao", "行驶证(证芯)编号", &xingShiZhengXinBianHao, true, CONFIG_DEFAULT},
        {"faZhengRiQi", "发证日期", &faZhengRiQi, true, CONFIG_DEFAULT},
        {"dangAnHao", "档案号", &dangAnHao, true, CONFIG_DEFAULT},
        {"heDingZaiKeShu", "核定载客数", &heDingZaiKeShu, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型编码", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"qiangZhiBaoFeiQiZhi", "强制报废日期", &qiangZhiBaoFeiQiZhi, true, CONFIG_NOCHECK},
        {"faDongJiHao", "发动机号", &faDongJiHao, true, CONFIG_NOCHECK}, //待工具支持，从车管所取得数据可能没有该项,所以"faDongJiHao"字段待定
    };

    std::vector<memberItem> resultMemberList = {
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"chePaiHao", "主页车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},/* 该字段算法当前填充的结果为主页车牌 */
        {"chePaiHao_fuye", "副页车牌号不正确", &chePaiHao_fuye, true, CONFIG_NOCHECK},
        {"xingShiZhengXinBianHao", "行驶证编号(条形码)不正确", &xingShiZhengXinBianHao, true, CONFIG_DEFAULT},
        {"faZhengRiQi", "行驶证发证日期不正确", &faZhengRiQi, true, CONFIG_DEFAULT},
        {"shenFenZheng", "未识别到身份证", &shenFenZheng, true, CONFIG_NOCHECK},
        {"zhuYeFanMianCheLiang", "未检测到行驶证主页反面车辆", &zhuYeFanMianCheLiang, true, CONFIG_NOCHECK},
        {"zhaoPianQingXiDu", "图片信息不规范", &zhaoPianQingXiDu, true, CONFIG_NOCHECK_UNABLE},
        {"qiangZhiBaoFeiQiZhi", "强制报废日期不正确", &qiangZhiBaoFeiQiZhi, true, CONFIG_NOCHECK},
        {"cheLiangLeiXing", "车辆类型不正确", &cheType, true, CONFIG_NOCHECK},
        {"heDingRenShu", "核定人数不正确", &heDingRenShu, true, CONFIG_NOCHECK},
        {"faDongJiHao", "发动机号不正确", &faDongJiHao, true, CONFIG_NOCHECK}, //待算法支持，"faDongJiHao"字段待定
        {"chePaiHao_fuye_back", "车牌号副页反面不正确", &chePaiHao_fuye_back, true, CONFIG_NOCHECK},
        {"fuYeZhangGeShu", "副页章个数", &fuYeZhangGeShu, true, CONFIG_NOCHECK},
        {"zhuYe", "不是行驶证主页", &zhuYe, true, CONFIG_NOCHECK},
        //{"yanSe", "车辆颜色", &yanSe, true, CONFIG_NOCHECK},
        //{"xingHao", "车辆型号", &xingHao, true, CONFIG_NOCHECK},

        //调用身份证接口
        {"isFront", "不是身份证正面", &shenFenZhen_front, false, CONFIG_NOCHECK},
        {"isBack", "不是身份证背面", &shenFenZhen_back, false, CONFIG_NOCHECK},
        {"isDateValid", "身份证有效期不正确", &shenFenZhen_validDate, false, CONFIG_NOCHECK}
    };

    std::vector<memberItem> inMemberList_moTuo = {
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"faZhengRiQi", "发证日期", &faZhengRiQi, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型编码", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"xingShiZhengXinBianHao", "行驶证(证芯)编号", &xingShiZhengXinBianHao, true, CONFIG_DEFAULT},
        //{"yanSe", "车辆颜色", &yanSe, true, CONFIG_DEFAULT},
        //{"xingHao", "车辆型号", &xingHao, true, CONFIG_DEFAULT}
    };

    std::vector<memberItem> resultMemberList_moTuo = {
        {"cheJiaHao", "车架号不正确", &cheJiaHao , true, CONFIG_DEFAULT},
        {"chePaiHao", "车牌号不正确", &chePaiHao , true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型不正确", &cheType, true, CONFIG_NOCHECK},
        {"faZhengRiQi", "行驶证发证日期不正确", &faZhengRiQi, true, CONFIG_DEFAULT},
        {"xingShiZhengXinBianHao", "行驶证编号(条形码)不正确", &xingShiZhengXinBianHao, true, CONFIG_DEFAULT},
        {"chePaiHao_fuye_back", "车牌号副页反面不正确", &chePaiHao_fuye_back, true, CONFIG_NOCHECK},
        {"zhuYeFanMianCheLiang", "未检测到行驶证主页反面车辆", &zhuYeFanMianCheLiang, true, CONFIG_NOCHECK},
        {"fuYeZhangGeShu", "副页章个数", &fuYeZhangGeShu, true, CONFIG_NOCHECK},
        {"zhaoPianQingXiDu", "图片信息不规范", &zhaoPianQingXiDu, true, CONFIG_NOCHECK_UNABLE},
        //{"yanSe", "车辆颜色", &yanSe, true, CONFIG_NOCHECK},
        //{"xingHao", "车辆型号", &xingHao, true, CONFIG_NOCHECK}
    };

    virtual ~_c_algClass_0201(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    virtual std::string getPhotoName(std::string algcode);
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0201_H
