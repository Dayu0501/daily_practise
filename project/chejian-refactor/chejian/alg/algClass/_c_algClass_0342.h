#ifndef _C_ALGCLASS_0342_H
#define _C_ALGCLASS_0342_H
#include "_c_algBaseClass.h"

class _c_algClass_0342 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheYiDong = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheTou = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER biaoZhi = ALG_PARAM_DEFAULT;

    ALG_PARM_MEMBER cunZai = ALG_PARAM_DEFAULT;
    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "水印日期", &shuiYinRiQi, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao_jieshu", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "照片水印日期过期", &shuiYinRiQi, true, CONFIG_NOCHECK},
        {"cheYiDong", "车未移动", &cheYiDong, true, CONFIG_NOCHECK},
        {"cheTou", "未检测到车头", &cheTou, true, CONFIG_NOCHECK},
        {"biaoZhi_jieshu", "未检测到标志", &biaoZhi, true, CONFIG_NOCHECK}
    };

    std::vector<memberItem> inMemberList_moTuo = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList_moTuo = {
        {"chePaiHao_jieshu", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheTou", "未检测到车头(已废弃)", &cheTou, false, CONFIG_NOCHECK},
        {"cunZai_jieshu", "车辆不存在", &cunZai, true, CONFIG_DEFAULT},
    };

    ALG_PARM_MEMBER shiYongXingZhi = ALG_PARAM_DEFAULT;
    std::vector<memberItem> inMemberList_video = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"shiYongXingZhi", "使用性质", &shiYongXingZhi, true, CONFIG_DEFAULT},
    };

    ALG_PARM_MEMBER shiJian = ALG_PARAM_DEFAULT;
    std::vector<memberItem> resultMemberList_video = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"shiJian", "检验时间不够", &shiJian, true, CONFIG_DEFAULT},
        {"cheYiDong", "车未移动", &cheYiDong, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0342(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0342_H
