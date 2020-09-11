/*
 * no used.
 * */

#ifndef _C_ALGCLASS_0113_FUZHOU_H
#define _C_ALGCLASS_0113_FUZHOU_H

#include "alg/algClass/_c_algClass_0113.h"

class _c_algClass_0113_FuZhou : public _c_algClass_0113 {
public:
	ALG_PARM_MEMBER duiBiLeiXing = ALG_PARAM_DEFAULT;

	_c_algClass_0113_FuZhou();
	bool InParamEdit() override ;
	~_c_algClass_0113_FuZhou() override = default;
};

#endif
