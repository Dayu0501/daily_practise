#ifndef _C_ALGCLASS_0177_H
#define _C_ALGCLASS_0177_H
#include "_c_algBaseClass.h"

//该类的算法接口已经废除，具体核定载客数照片使用算法哪个接口，待定
class _c_algClass_0177 : public _c_algBaseClass{
public:
    ALG_PARM_MEMBER heDingZaiKeShuZi = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER cityCode = ALG_PARAM_DEFAULT;
    ALG_PARM_MEMBER heZaiShiBieJieGuo = ALG_PARAM_DEFAULT;

    std::vector<memberItem> inMemberList = {
        {"heDingZaiKeShuZi", "核定载客人数", &heDingZaiKeShuZi, true, CONFIG_DEFAULT},
        {"cityCode", "城市代码", &cityCode, true, CONFIG_DEFAULT},
    };

    std::vector<memberItem> resultMemberList = {
        {"heZaiShiBieJieGuo", "核定载客结果有误", &heZaiShiBieJieGuo, true, CONFIG_DEFAULT},
    };

    virtual ~_c_algClass_0177(){}
    virtual bool seekMemberListPointer();
    virtual bool InParamEdit();
    virtual bool ResultEdit();
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0177_H
