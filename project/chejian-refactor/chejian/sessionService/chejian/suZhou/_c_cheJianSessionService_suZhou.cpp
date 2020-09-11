#include "_c_cheJianSessionService_suZhou.h"
#include "alg/city/suzhou/_c_vehicle_SuZhou.h"
#include "db/mysql/MySQL_DB.h"
#include "alg/_c_algTaskCenter.h"
#include "base/dataCenter.h"

//查询流水号列表
extern int  queryLiuShuiHao_suzhou( std::vector<std::string>& lsh_vector);
extern _c_vehicle*  queryInputParameter_suzhou( string lsh) ;
extern bool  update_write_ispass_suzhou(_c_vehicle_SuZhou *pvehs) ;

_c_cheJianSessionService_suZhou::_c_cheJianSessionService_suZhou(SESSIONSERVICE_PARAM *pSessionServiceParam):_c_cheJianSessionService(pSessionServiceParam)
{

}

bool  _c_cheJianSessionService_suZhou::queryData()
{
    _c_cheJianSessionService::queryData();
    //TODO 如果开启第三方车检
    extraQueryData();
    return true;
}

bool _c_cheJianSessionService_suZhou::reponseData(_c_session *pSession)
{
    //TODO
    //最终响应给请求端处理结果
    printf("!!!!!!!!!!!reponseData \n");
    if(pSession->getSessionType() == SESS_DEFAULT )
    {
        _c_cheJianSessionService::reponseData(pSession);
    }else if(pSession->getSessionType() == SESS_3TH)
    {
        extraReponseData(pSession);
    }
    return true ;
}


 bool _c_cheJianSessionService_suZhou::extraReponseData(_c_session *pSession)
 {
    _c_vehicle_SuZhou* _pVehicle = (_c_vehicle_SuZhou*) pSession;

     // replace :旧算法 fun_write_each_result  更新结果
     vehicleSetDisposeEnd(pSession);
     //vehicle_info 中写入第三方审核结果
     _pVehicle->setPushDbTaskQueueTime();
     _pVehicle->dbWork();

    update_write_ispass_suzhou(_pVehicle);
    return true;
 }

 bool _c_cheJianSessionService_suZhou::extraQueryData()
 {
     //TODO
     //loop read from db then pushQueue
     std::vector<std::string> lsh_vector;
     std::vector<std::string> newLsh_vector;

     string response ;
     int requestlen = 0;
     if (KGRedisClient::get_instance().ExecuteCmdEx(response, "LLEN", getRedisRequstChan().c_str(), nullptr) )
     {
        requestlen = baseTool::str2Int(response);
        LOG(COMMON,INFO,"_c_cheJianSessionService_suZhou:LLEN:[%s]\n",response.c_str() );
     }

     if(requestlen > 9)
     {
         // 当前队列有未被消费的数据  等待下次车检任务入队检测
         return true ;
     }
     //查询待审核车辆流水号列表
    // int queryNum = queryLiuShuiHao(&soapclient, &lsh_vector);
     int queryNum = queryLiuShuiHao_suzhou(lsh_vector ) ;
     int queryNewNum = 0;
     //流水号列表去重
     deRepeatLiuShuiHao(&lsh_vector,&newLsh_vector);
     queryNewNum = (int)newLsh_vector.size();
     printf("苏州第三方接口车检");
     printf("查询到[%d]个待检数据,其中[%d]个新增流水号\n",queryNum,queryNewNum);
     LOG(COMMON,INFO,"查询到[%d]个待检数据,其中[%d]个新增流水号\n",queryNum,queryNewNum);

     LOG(COMMON,INFO,"新增流水号：\n");
     //遍历查询到的流水号
     for (unsigned int i = 0; i < newLsh_vector.size(); i++) {
        //查询流水号对应的车辆信息
        _c_vehicle *pVehicle = queryInputParameter_suzhou( newLsh_vector[i]);//queryVehicleInfo(&soapclient, newLsh_vector[i]);
        if(pVehicle != NULL)
        {

                        pVehicle->setSessionInSystemTime();
                        //获取本次车辆信息在程序内的唯一key（uuid码）
                        pVehicle->loadUuid();
                        LOG(COMMON,INFO,"uuid:%s lsh:%s\n", pVehicle->uuid.c_str(), pVehicle->liuShuiHao.c_str());
                        _c_vehicleInfo _VehicleInfo(pVehicle);
                        //车辆信息严格去重
                        int RepeatVehicleRet = deRepeatVehicleInfo(_VehicleInfo);
                        pVehicle->isRepeat = std::to_string(RepeatVehicleRet);
                        if( RepeatVehicleRet == RET_NORMAL || RepeatVehicleRet == RET_RECHECK)
                        {
                            //信息添加到_vehicleInfoVector队列
                            _VehicleInfo.setGuid(pVehicle->uuid);
                            _vehicleInfoVector.push_back(_VehicleInfo);
                            //将车辆信息插入object队列
                            pushQueue(pVehicle);
                        }
            //            else
            {
//                pVehicle->isRepeat = REPEAT;//重复车辆
//                printf("repetitive vehicle info request %s \n", pVehicle->liuShuiHao.c_str());
//                LOG(COMMON,INFO,"repetitive vehicle info request %s \n", pVehicle->liuShuiHao.c_str());
//                pushReponseQueue(pVehicle);
            }
        }
     }

//     _c_systemInfo *pInfo = new _c_systemInfo();
//     pInfo->lshNum = std::to_string(_lshVector.size());
//     pInfo->sessionDisponseNum = std::to_string(_vehicleInfoVector.size());
//     pInfo->soapQueryNum = std::to_string(queryNum);
//     pInfo->soapNewNum = std::to_string(queryNewNum);
//     pInfo->sessionQueueNum = std::to_string(getSessionQueueSize());
//     pInfo->sessionVectorNum = std::to_string(getSessionVectorSize());
//     pInfo->sessionAlgQueueNum = std::to_string(getSessionAlgQueueSize());
//     pInfo->reponseQueueNum = std::to_string(getReponsetQueueSize());
//     pInfo->dbTaskQueueNum = std::to_string(getDbTaskQueueSize());
//     printf("systemInfo:%s\n",pInfo->getSql().c_str());
//     pInfo->dbWork();
     std::this_thread::sleep_for(std::chrono::milliseconds(_threadSleepMilliseconds));
     return true ;
 }


 void _c_cheJianSessionService_suZhou::subClearCache()
 {
     baseTool::keepRecentSomeDaysDir(DIR_PATH,1,10) ;
 }
