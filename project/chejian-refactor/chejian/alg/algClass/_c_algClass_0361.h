#ifndef _C_ALGCLASS_0361_H
#define _C_ALGCLASS_0361_H
#include "_c_algClass_0360.h"

class _c_algClass_0361 : public _c_algClass_0360 {
public:
	virtual ~_c_algClass_0361() {}
	virtual bool subClassLoadNewResultMember();
	virtual bool InParamEdit();
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0361_H