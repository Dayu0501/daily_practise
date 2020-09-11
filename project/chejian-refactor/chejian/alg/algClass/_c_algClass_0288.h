#ifndef _C_ALGCLASS_0288_H
#define _C_ALGCLASS_0288_H
#include "_c_algBaseClass.h"

class _c_algClass_0288 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER faZhengRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dangAnHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER xingShiZhengXinBianHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingZaiKeShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhuYeFanMianCheLiang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER fuYeFanMian = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER yinZhangShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER qiangZhiBaoFeiQiZhi = ALG_PARAM_DEFAULT;
//    ALG_PARM_MEMBER yanSe = ALG_PARAM_DEFAULT;
//    ALG_PARM_MEMBER xingHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao_fuye_back = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heDingRenShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER fuYeZhangGeShu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhaoPianQingXiDu = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"faZhengRiQi", "发证日期", &faZhengRiQi, true, CONFIG_DEFAULT},
        {"dangAnHao", "档案号", &dangAnHao, true, CONFIG_DEFAULT},
        {"xingShiZhengXinBianHao", "行驶证(证芯)编号", &xingShiZhengXinBianHao, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型编码", &cheLiangLeiXing, true, CONFIG_NOCHECK},
        {"heDingZaiKeShu", "核定载客数", &heDingZaiKeShu, true, CONFIG_DEFAULT},
        {"qiangZhiBaoFeiQiZhi", "强制报废日期", &qiangZhiBaoFeiQiZhi, true, CONFIG_DEFAULT}
    };

    std::vector<memberItem> resultMemberList = {
    	{"zhuYeFanMianCheLiang", "未检测到行驶证主页反面车辆",   &zhuYeFanMianCheLiang, true,  CONFIG_DEFAULT},
        {"fuYeFanMian",          "未检测到行驶证副页反面",     &fuYeFanMian,          true,  CONFIG_NOCHECK},
        {"faZhengRiQi",          "发证日期不正确",          &faZhengRiQi,          true,  CONFIG_NOCHECK},
        {"yinZhangShu",          "行驶证副页背面印章数已超过5个", &yinZhangShu,          true,  CONFIG_NOCHECK},
        {"qiangZhiBaoFeiQiZhi",  "强制报废日期不正确",       &qiangZhiBaoFeiQiZhi,  true,  CONFIG_NOCHECK},
        {"chePaiHaoFuYeFanMian", "车牌号不正确",          &chePaiHao,            true,  CONFIG_NOCHECK},
        //{"yanSe",                "车辆颜色不一致",         &yanSe,                true,  CONFIG_NOCHECK},
        //{"xingHao",              "车辆型号不一致",         &xingHao,              false, CONFIG_NOCHECK},
        {"chePaiHao_fuye_back",  "车牌号副页反面不正确",      &chePaiHao_fuye_back,  true,  CONFIG_NOCHECK},
        {"heDingRenShu",         "核定人数不正确",         &heDingRenShu,         true,  CONFIG_NOCHECK},
        {"fuYeZhangGeShu",       "副页章个数",           &fuYeZhangGeShu,       true,  CONFIG_NOCHECK},
        {"zhaoPianQingXiDu",     "图片信息不规范",         &zhaoPianQingXiDu,     true,  CONFIG_NOCHECK_UNABLE}
    };

    virtual ~_c_algClass_0288(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    virtual std::string getPhotoName(std::string algcode);
};

#endif // _C_ALGCLASS_0288_H
