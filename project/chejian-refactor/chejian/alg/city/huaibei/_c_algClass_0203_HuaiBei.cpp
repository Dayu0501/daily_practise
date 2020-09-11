#include "_c_algClass_0203_HuaiBei.h"
#include "../base/baseTool.h"
#include <stdlib.h>

bool _c_algClass_0203_HuaiBei::InParamEdit()
{
    LOG(ALG, INFO, "_c_algClass_0203_HuaiBei::InParamEdit() begin");
    //格式化生效日期和终止日期
    shengXiaoRiQi.inData = baseTool::formatingDate(shengXiaoRiQi.inData);
    zhongZhiRiQi.inData = baseTool::formatingDate(zhongZhiRiQi.inData);
    LOG(ALG, INFO, "_c_algClass_0203_HuaiBei::InParamEdit() shengXiaoRiQi.inData: %s, zhongZhiRiQi.inData: %s", shengXiaoRiQi.inData.c_str(), zhongZhiRiQi.inData.c_str());

    //将终止日期提前一个月
    zhongZhiRiQi.inData = aheadOneMonthDate(zhongZhiRiQi.inData);
    //格式化检验结束时间
    jianYanJieShuShiJian.inData = baseTool::formatingDate(jianYanJieShuShiJian.inData);
    LOG(ALG, INFO, "_c_algClass_0203_HuaiBei::InParamEdit() zhongZhiRiQi.inData: %s, jianYanJieShuShiJian.inData: %s", zhongZhiRiQi.inData.c_str(), jianYanJieShuShiJian.inData.c_str());

    if (baseTool::checkCllxIsMx(pAllParamVector) )
    {
        pInMemberList = &inMemberList_moTuo;
        pResultMemberList = &resultMemberList_moTuo;
    }

    //如果存在电子保单 则不进行后面的redis流程
    if (pWangLuoJieKouReturnVector != NULL)
    {
        for (unsigned int i = 0; i < pWangLuoJieKouReturnVector->size(); i++)
        {
            std::string biaoShi = baseTool::getWangLuoJieKouReturnInfoBiaoShi((*pWangLuoJieKouReturnVector)[i]);
            if (biaoShi == "18C23")
            {
                //如果电子保单返回内容有效,则不需要在走算法流程
                if(baseTool::checkWangLuoJieKouReturnInfoIsValid((*pWangLuoJieKouReturnVector)[i]))
                    return false;
                break;
            }
        }
    }

    return true;
}

//将格式化时间例如20200506提前一个月20200406，满足检验时间距离截止日期至少1个月限制
std::string _c_algClass_0203_HuaiBei::aheadOneMonthDate(std::string date)
{
    if(date.length() == 8)
    {
        int year = atoi(date.substr(0,4).c_str());
        int month = atoi(date.substr(4,2).c_str());
        int day = atoi(date.substr(6,2).c_str());
        return minusDay(year,month,day,30);
    }
    else
    {
        return date;
    }
}

std::string _c_algClass_0203_HuaiBei::minusDay(int year,int month,int day,int subDays)
{
    struct tm tm;  
    memset(&tm, 0, sizeof(tm)); 
    char timeStamp[20]={0}; 
	tm.tm_year = year;
	tm.tm_mon = month;
	tm.tm_mday = day;
    
    tm.tm_year -= 1900;  
    tm.tm_mon--;  
    time_t time = mktime(&tm);
    time_t subTime = time-(subDays*60*60*24-28800);
    struct tm *p2=gmtime(&subTime);  
    char s2[10]={0};  
    strftime(s2, sizeof(s2), "%Y%m%d", p2);
    return s2;
}
