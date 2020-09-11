#ifndef _C_ALGCLASS_0157_H
#define _C_ALGCLASS_0157_H
#include "_c_algBaseClass.h"

class _c_algClass_0157 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER anQuanDai = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER jianYanJieShuShiJian = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER fangXiangPan = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"shuiYinRiQi", "检验结束时间", &jianYanJieShuShiJian, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"anQuanDai", "安全带卡扣未紧扣", &anQuanDai, true, CONFIG_DEFAULT},
        {"fangXiangPan", "方向盘不存在", &fangXiangPan, true, CONFIG_NOCHECK_UNABLE},
        {"shuiYinRiQi", "照片水印日期过期", &jianYanJieShuShiJian, true, CONFIG_NOCHECK_UNABLE}
    };

    virtual ~_c_algClass_0157(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0157_H
