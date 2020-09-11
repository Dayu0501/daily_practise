#ifndef _C_ALGCLASS_0323_H
#define _C_ALGCLASS_0323_H
#include "_c_algBaseClass.h"

class _c_algClass_0323 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER diPan = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanYuan = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "水印日期", &shuiYinRiQi, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"diPan", "底盘不在工位", &diPan, true, CONFIG_NOCHECK},
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "照片水印日期过期", &shuiYinRiQi, true, CONFIG_NOCHECK},
        {"jianYanYuan", "没有检验员", &jianYanYuan, true, CONFIG_DEFAULT},

    };

    std::vector<memberItem> inMemberList_moTuo = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList_moTuo = {
        {"diPan", "底盘不在工位", &diPan, true, CONFIG_NOCHECK},
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
    };

    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shiYongXingZhi = ALG_PARAM_DEFAULT;
    std::vector<memberItem> inMemberList_video = {
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"shiYongXingZhi", "使用性质", &shiYongXingZhi, true, CONFIG_DEFAULT},
    };

    ALG_PARM_MEMBER renCunZai = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shiJian = ALG_PARAM_DEFAULT;
    std::vector<memberItem> resultMemberList_video = {
        {"renCunZai", "检测到人", &renCunZai, true, CONFIG_DEFAULT},
        {"shiJian", "检验时间不够", &shiJian, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0323(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0323_H
