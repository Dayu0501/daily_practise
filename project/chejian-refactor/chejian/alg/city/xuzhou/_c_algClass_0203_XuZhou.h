#ifndef _C_ALGCLASS_0203_XUZHOU_H
#define _C_ALGCLASS_0203_XUZHOU_H

#include "alg/algClass/_c_algBaseClass.h"
#include "alg/algClass/_c_algClass_0203.h"

class _c_algClass_0203_XuZhou : public _c_algClass_0203{
public:
	ALG_PARM_MEMBER oneYearYouXiaoQi  = ALG_PARAM_DEFAULT;

	_c_algClass_0203_XuZhou();
    bool InParamEdit() override;
	//bool ResultEdit() override;
	~_c_algClass_0203_XuZhou() override = default;
};
#endif
