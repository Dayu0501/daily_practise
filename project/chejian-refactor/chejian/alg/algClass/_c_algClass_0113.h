#ifndef _C_ALGCLASS_0113_H
#define _C_ALGCLASS_0113_H
#include "_c_algBaseClass.h"

class _c_algClass_0113 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER zhaoPianQingXiDu = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheJiaHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER taYinMo = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER tuoMo = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER dangAnZhaoPian = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER zhiZaoChangMingCheng = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cheLiangPinPai = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER changShangPinPai = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "水印日期", &shuiYinRiQi, true, CONFIG_DEFAULT},
        {"zhiZaoChangMingCheng", "制造厂名称", &zhiZaoChangMingCheng, true, CONFIG_DEFAULT},
        {"cheLiangPinPai", "车辆品牌", &cheLiangPinPai, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"zhaoPianQingXiDu", "图片信息不规范", &zhaoPianQingXiDu, false, CONFIG_DEFAULT_UNABLE},
        {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "水印日期过期", &shuiYinRiQi, true, CONFIG_NOCHECK_UNABLE},
        {"taYinMo", "车架号字型与拓印膜不符", &taYinMo, false, CONFIG_NOCHECK},
        {"tuoMo", "车架号拓印膜不正确", &tuoMo, false, CONFIG_NOCHECK},
        {"dangAnZhaoPian", "缺少拓印膜照片，无法判定车架号是否更改", &dangAnZhaoPian, true, CONFIG_NOCHECK_UNABLE},
        {"changShangPinPai", "厂商车架号篡改检测", &changShangPinPai, true, CONFIG_NOCHECK_UNABLE},
    };

    std::vector<memberItem> inMemberList_moTuo= {
         {"cheJiaHao", "车架号", &cheJiaHao, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList_moTuo = {
         {"cheJiaHao", "车架号不正确", &cheJiaHao, true, CONFIG_DEFAULT},
         {"taYinMo", "车架号字型与拓印膜不符", &taYinMo, false, CONFIG_NOCHECK},
    };

    virtual ~_c_algClass_0113(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0113_H
