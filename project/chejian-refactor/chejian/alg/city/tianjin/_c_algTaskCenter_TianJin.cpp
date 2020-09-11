#include "_c_algTaskCenter_TianJin.h"
#include "_c_algClass_0206_TianJin.h"
#include "db/dbquery/db_vehicleinfo.h"
#include "sessionService/chejian/tianJin/_c_fuJian.h"

_c_algTaskCenter_TianJin::_c_algTaskCenter_TianJin(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{
    
}

bool _c_algTaskCenter_TianJin::subBeforAlgCheck(_c_session *pSession, std::string& sessionReason)
{
    std::string isRepeat = "0";
    if(getFuJianCheLiangMode() == 1)
    {
        if(isFuHeVehicle(pSession))
        {
            isRepeat = "2";
        }

        objectMember* isRepeat_val = baseTool::getObjectItemByName(&pSession->paramVector, "isRepeat");
        *isRepeat_val->value = isRepeat;

        if(!checkFuJianCheLiang("1",isRepeat, &pSession->algTaskVector))
        {
            sessionReason = "复检车辆";
            return false;
        }
    }
    

//     std::map<std::string,std::string> map_zhuangtai_reason = {{"G","违法未处理"},{"I","事故未处理"}};
//     std::string zhuangtai = baseTool::getObjectItemValueByName(&pSession->paramVector, "jiDongCheZhuangTai");

//     if( (zhuangtai.find("G") != std::string::npos) || (zhuangtai.find("I") != std::string::npos) )
//     {
//         sessionReason = "车辆状态异常";

        //找到行驶证
//         _c_algTask *algTask0201 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0201));
//         if(!algTask0201)
//         {
//             return false;
//         }
//         std::string reason = "";
//         if(zhuangtai.find("G") != std::string::npos)
//         {
//             reason += "[" + map_zhuangtai_reason["G"] +"]"; 
//         }
        
//         if(zhuangtai.find("I") != std::string::npos)
//         {
//             reason += "[" + map_zhuangtai_reason["I"] +"]";
//         }

//         algTask0201->setAlgTaskResult(NOT_PASS, reason); //设置为不通过，且写上原因
//         sessionReason += ":"+reason;
//         return false;
//     }

    return true;
}

void _c_algTaskCenter_TianJin::changeAlgVector()
{
     printf("void _c_algTaskCenter_TianJin::changeAlgVector()\n");
    algItem item0206 = {"0206", false, "完税证明-照片", e0206, false, false, true, false, "无", NOPICEXAMPLE}; //0206开启使用子类逻辑开关

//    changeAlgVectorByType(&item0206);
}

_c_algBaseClass* _c_algTaskCenter_TianJin::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    _c_algBaseClass* pReturn;
    switch (type) {
       case e0206:
            pReturn = new _c_algClass_0206_TianJin();
            break;
        default:
            //默认返回(固定 不可返回NULL，如有递归继承关系可模仿父类实现方式)
            return new _c_algBaseClass();
        break;
    }
    pReturn->setBaseParam(cityType, type, algName);
    pReturn->initAlgClass();
    return pReturn;
}

bool _c_algTaskCenter_TianJin::isFuHeVehicle(_c_session *pSession)
{
    std::string chePai = "";
    std::string startTime = baseTool::getDangTianRiQi(-6);
    std::string endTime = baseTool::getDangTianRiQi() + " 23:59:59";
    std::string tableName = "fuJian_info";

    std::string chePaiHao = baseTool::getObjectItemValueByName(&pSession->paramVector, "chePaiHao");
    std::string cheJiaHao = baseTool::getObjectItemValueByName(&pSession->paramVector, "cheJiaHao");
    std::string cheLiangLeiXing = baseTool::getObjectItemValueByName(&pSession->paramVector, "cheLiangLeiXing");
//  std::string strSql = "SELECT liuShuiHao FROM " + tableName 
//                     +  " where DATE_SUB(CURDATE(), INTERVAL 6 DAY) <= date(created_at) "
//                     +  " and chaPaiHao = " + chePaiHao 
//                     +  " limit 1"; 

    time_t t_start;
    time_t t_end;
    db_fujian dbFuJian;
    std::vector<std::string> WhereVector;
    PDB_PARAM pConfig = loadSystemConfig()->getStructDbParam();
//    WhereVector.push_back("and DATE_SUB(CURDATE(), INTERVAL 6 DAY) <= date(inDbTime)");     
    WhereVector.push_back("and cheJiaHao = '" + cheJiaHao +"'");    
    WhereVector.push_back(" limit 1 ");
    time(&t_start);
    int result_size = dbFuJian.query(tableName, &WhereVector, pConfig->strHost.c_str(), pConfig->port, pConfig->strUserName.c_str(), pConfig->strPassword.c_str(), pConfig->strDbName.c_str());
    time(&t_end);
    LOG(DB,INFO,"query one in db cost:%ld",t_end - t_start);
    if(result_size > 0)
    {
        printf("vehicle:[%s,%s,%s] exist in database,need add this vehicle fuhe label ....\n",chePaiHao.c_str(),cheJiaHao.c_str(),cheLiangLeiXing.c_str());
         LOG(DB,INFO,"vehicle:[%s,%s,%s] exist in database,need add this vehicle fuhe label ....",chePaiHao.c_str(),cheJiaHao.c_str(),cheLiangLeiXing.c_str());
         return true;
    }           

    return false;
}

E_ZZJG _c_algTaskCenter_TianJin::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
{
    UNUSED(baseResult);
    std::string isRepeat = "0";
    if(getFuJianCheLiangMode() == 2)
    {
        if(isFuHeVehicle(pSession))
        {
            isRepeat = "2";
        }

        objectMember* isRepeat_val = baseTool::getObjectItemByName(&pSession->paramVector, "isRepeat");
        *isRepeat_val->value = isRepeat;
        
        if(!checkFuJianCheLiang("2",isRepeat, &pSession->algTaskVector))
        {
            sessionReason = "复检车辆";
            return SOFT_ERR;
        }
    }
    
    return SOFT_PASS;
}

// bool _c_algTaskCenter_TianJin::checkFuJianCheLiang(std::string mode, std::string isRepeat, std::vector<_c_algTask *> *algTaskVector)
// {
//     std::string isRepeat = "0";
//     if(isFuHeVehicle(pSession))
//     {
//         isRepeat = "2";
//     }
    
//     if(!_c_algTaskCenter::checkFuJianCheLiang(mode,isRepeat, algTaskVector))
//     {
//         return false;
//     }

//     return true;
// }