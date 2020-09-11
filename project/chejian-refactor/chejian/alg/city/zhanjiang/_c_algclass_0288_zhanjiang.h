#ifndef _C_ALGCLASS_0288_ZHANJIANG_H
#define _C_ALGCLASS_0288_ZHANJIANG_H
#include "alg/algClass/_c_algClass_0288.h"

class _c_algClass_0288_ZhanJiang:public _c_algClass_0288
{
public:
    virtual bool ResultEdit() override;

private:
    bool isLocale(std::vector<objectMember *> *pCheLiangXinxi);
};

#endif // _C_ALGCLASS_0288_ZHANJIANG_H
