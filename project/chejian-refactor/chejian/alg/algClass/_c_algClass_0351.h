#ifndef _C_ALGCLASS_0351_H
#define _C_ALGCLASS_0351_H
#include "_c_algBaseClass.h"

class _c_algClass_0351 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhiDong = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhiDongDeng = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhiDongLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhouLeiXing = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER youDeng = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zuoDeng = ALG_PARAM_DEFAULT;
	
    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "水印日期", &shuiYinRiQi, true, CONFIG_DEFAULT},
        {"zhiDongLeiXing",  "制动类型", &zhiDongLeiXing,  true, CONFIG_DEFAULT},
        {"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
        {"zhouLeiXing",     "轴类型",  &zhouLeiXing,     true, CONFIG_DEFAULT}
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "照片水印日期过期", &shuiYinRiQi, true, CONFIG_NOCHECK_UNABLE},
        {"zhiDong", "车轮位置不对", &zhiDong, true, CONFIG_DEFAULT},
        {"zhiDongDeng", "制动灯亮", &zhiDongDeng, true, CONFIG_NOCHECK},
        {"zuoDeng", "左灯未亮", &zuoDeng, true, CONFIG_NOCHECK},
        {"youDeng", "右灯未亮", &youDeng, true, CONFIG_NOCHECK}
    };

    virtual ~_c_algClass_0351(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
    virtual std::string getPhotoName(std::string algcode);
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0351_H
