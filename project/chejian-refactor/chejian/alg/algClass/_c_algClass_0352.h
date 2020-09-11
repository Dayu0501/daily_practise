#ifndef _C_ALGCLASS_0352_H
#define _C_ALGCLASS_0352_H
#include "_c_algBaseClass.h"

class _c_algClass_0352 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zuoDeng = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER youDeng = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "水印日期", &shuiYinRiQi, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
    };
    std::vector<memberItem> resultMemberList = {

        {"zuoDeng", "右图左车灯不亮", &zuoDeng, true, CONFIG_DEFAULT},
        {"youDeng", "右图右车灯不亮", &youDeng, false, CONFIG_NOCHECK},
        {"shuiYinRiQi", "照片水印日期过期", &shuiYinRiQi, true, CONFIG_NOCHECK_UNABLE},
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> inMemberList_moTuo = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
    };
    std::vector<memberItem> resultMemberList_moTuo = {
        {"zuoDeng", "右车灯不亮", &zuoDeng, true, CONFIG_NOCHECK},
        {"youDeng", "右车灯2(逻辑使用)", &youDeng, false, CONFIG_NOCHECK},
    };

    ALG_PARM_MEMBER shiYongXingZhi = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList_video = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"shiYongXingZhi", "使用性质", &shiYongXingZhi, true, CONFIG_DEFAULT},
    };

    ALG_PARM_MEMBER shiJian = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dengGuang = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER renCunZai = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dengGuangJianCeYiYiDong = ALG_PARAM_DEFAULT;

    std::vector<memberItem> resultMemberList_video = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"shiJian", "检验时间不够", &shiJian, true, CONFIG_DEFAULT},
        {"dengGuang", "车灯不亮", &dengGuang, true, CONFIG_DEFAULT},
        {"renCunZai", "检测到人", &renCunZai, true, CONFIG_DEFAULT},
        {"dengGuangJianCeYiYiDong", "灯光检测仪不移动", &dengGuangJianCeYiYiDong, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0352(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0352_H
