#include "_c_algTaskCenter_ZaoZhuang.h"

_c_algTaskCenter_ZaoZhuang::_c_algTaskCenter_ZaoZhuang(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}

bool _c_algTaskCenter_ZaoZhuang::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason)
{
    std::map<std::string,std::string> map_zhuangtai_reason = {{"Q","逾期未检验"},{"C","被盗抢车辆"},{"K","查封车辆"},{"L","暂扣车辆"}};
    std::string zhuangtai = baseTool::getObjectItemValueByName(&pSession->paramVector, "jiDongCheZhuangTai");

    // 这四种状态（zt）的车：逾期未检验，被盗抢车辆，查封车辆，暂扣车辆
    // 要把行驶证照片判定为不合格，并写上具体原因

    if( (zhuangtai.find("Q") != std::string::npos) || (zhuangtai.find("C") != std::string::npos) || 
        (zhuangtai.find("K") != std::string::npos) || (zhuangtai.find("L") != std::string::npos) 
      )
    {
        sessionReason = "车辆状态异常";
        //找到行驶证
        _c_algTask *algTask0201 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0201));
        if(!algTask0201)
        {
            return false;
        }

        std::string reason = "";
        if(zhuangtai.find("Q") != std::string::npos)
        {
            reason += "[" + map_zhuangtai_reason["Q"] +"]";
        }
        
        if(zhuangtai.find("C") != std::string::npos)
        {
            reason += "[" + map_zhuangtai_reason["C"] +"]";
        }

        if(zhuangtai.find("K") != std::string::npos)
        {
            reason += "[" + map_zhuangtai_reason["K"] +"]";
        }

        if(zhuangtai.find("L") != std::string::npos)
        {
            reason += "[" + map_zhuangtai_reason["L"] +"]";
        }

        algTask0201->setAlgTaskResult(NOT_PASS, reason); //设置为不通过，且写上原因
        sessionReason += ":"+reason;
        return false;
    }
    
    return true;
}

