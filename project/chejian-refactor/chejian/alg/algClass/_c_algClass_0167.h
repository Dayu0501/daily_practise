#ifndef _C_ALGCLASS_0167_H
#define _C_ALGCLASS_0167_H
#include "_c_algBaseClass.h"

class _c_algClass_0167 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER paiSheJiaoDu = ALG_PARAM_DEFAULT; //拍摄角度 入参：0-左前，1-右后，2-正后，3-其它

    std::vector<memberItem> inMemberList = {
        {"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
        {"shuiYinRiQi", "水印日期", &shuiYinRiQi, true, CONFIG_DEFAULT},
        {"paiSheJiaoDu", "拍摄角度", &paiSheJiaoDu, true, CONFIG_DEFAULT}
    };

    std::vector<memberItem> resultMemberList = {
        {"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0167(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
};

#endif // _C_ALGCLASS_0167_H
