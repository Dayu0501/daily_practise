#pragma once

#include "alg/algClass/_c_algClass_0203.h"

class _c_algClass_0203_HuaiBei : public _c_algClass_0203
{
public:
    virtual bool InParamEdit();

private:
    std::string aheadOneMonthDate(std::string date);
    std::string minusDay(int year,int month,int day,int subDays);
};
