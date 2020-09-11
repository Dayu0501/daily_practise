#ifndef _C_ALGCLASS_0110_FUZHOU_H
#define _C_ALGCLASS_0110_FUZHOU_H
#include "alg/algClass/_c_algClass_0287.h"

class _c_algClass_0110_FuZhou : public _c_algClass_0287{
public:
    ALG_PARM_MEMBER cheLiangYiZhi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER yanSe = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER xingHao = ALG_PARAM_DEFAULT;

    _c_algClass_0110_FuZhou();
    bool subClassLoadNewResultMember() override ;
    bool seekMemberListPointer() override;
    ~_c_algClass_0110_FuZhou() override = default;
	void setAlgIds() override;
	bool ResultEdit() override;
};

#endif