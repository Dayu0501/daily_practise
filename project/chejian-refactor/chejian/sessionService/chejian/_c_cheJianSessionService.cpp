#include "base/dataCenter.h"
#include "base/_c_systemInfo.h"
#include "_c_cheJianSessionService.h"
#include "base/soapApi/soapApi.h"
#include "base/soapApi/soapTmriOutAccessSoapBindingProxy.h"
#include "base/baseTool.h"
#include <ctime>

_c_cheJianSessionService::_c_cheJianSessionService(SESSIONSERVICE_PARAM *pSessionServiceParam)
{
    _cityCode = std::to_string((int)pSessionServiceParam->cityType);

    _cheJianStartUpParam = *static_cast<PSTARTUPPRARAM>(pSessionServiceParam->params["soapParam"]);
    _wangLuoJieKouInfo = static_cast<std::vector<wangLuoJieKouItem> *>(pSessionServiceParam->params["wangLuoJieKouParam"]);
    _videoCheckJyjgbhConfig = static_cast<std::vector<VIDEOJYJGBH> *>(pSessionServiceParam->params["videoCheckParam"]);

    printf("Initialize soap param: ip:%s ,port:%s\n", _cheJianStartUpParam.remoteIp.c_str(), _cheJianStartUpParam.soapPort.c_str());

    _cheJianStartUpParam.g_cjbh = "01";
    _cheJianStartUpParam.g_zdbs = baseTool::getLocalIp();

    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);
    _curDay = st->tm_mday;

    _threadSleepMilliseconds = (unsigned int)_cheJianStartUpParam.soapQueryInterval;
    pSoapApiHandle = soapApi_creatSoapApiHandle();
}

_c_cheJianSessionService::~_c_cheJianSessionService()
{
    if (pSoapApiHandle)
    {
        soapApi_closeSoapApiHandle(pSoapApiHandle);
        pSoapApiHandle = NULL;
    }
}

bool _c_cheJianSessionService::queryData()
{
    if (workMode != eHostMode)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(_threadSleepMilliseconds));
        return true;
    }

    if (!checkWorkTime())
    {
        printf("it's rest time!\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(_threadSleepMilliseconds));
        return true;
    }

    std::vector<std::string> lsh_vector;
    std::vector<std::string> newLsh_vector;

    TmriOutAccessSoapBindingProxy soapclient;
    soapclient.accept_timeout = 30;
    soapclient.connect_timeout = 30;
    soapclient.recv_timeout = 30;
    soapclient.send_timeout = 30;

    if (baseTool::checkDateChange(_curDay))
        clearCache();

    //查询待审核车辆流水号列表
    int queryNum = queryLiuShuiHao(&soapclient, &lsh_vector);
    int queryNewNum = 0;
    //流水号列表去重
    deRepeatLiuShuiHao(&lsh_vector,&newLsh_vector);
    queryNewNum = (int)newLsh_vector.size();
    printf("查询到[%d]个待检数据,其中[%d]个新增流水号\n",queryNum,queryNewNum);
    LOG(COMMON,INFO,"查询到[%d]个待检数据,其中[%d]个新增流水号\n",queryNum,queryNewNum);
    if(queryNum > 0 && queryNewNum ==0)
    {
       setDeviceState("接收监管平台数据:"+std::to_string(queryNum)+"条，其中新增数据0条");
    }

    LOG(COMMON,INFO,"新增流水号：\n");
    //遍历查询到的流水号
    for (unsigned int i = 0; i < newLsh_vector.size(); i++) {
       //查询流水号对应的车辆信息
       _c_vehicle *pVehicle = queryVehicleInfo(&soapclient, newLsh_vector[i]);
       if( getIsOpenFilterJianYanJiGou() && pVehicle && ( !filterJyjg(pVehicle->jianYanJiGouBianHao) ) )
       {
           delete pVehicle ;
           pVehicle = NULL ;
           continue ;
       }
       if(pVehicle != NULL)
       {
           pVehicle->setSessionInSystemTime();
           //获取本次车辆信息在程序内的唯一key（uuid码）
           pVehicle->loadUuid();
           LOG(COMMON,INFO,"uuid:%s lsh:%s\n", pVehicle->uuid.c_str(), pVehicle->liuShuiHao.c_str());
           _c_vehicleInfo _VehicleInfo(pVehicle);

           //车辆信息严格去重 0为第一此送审，2为复审，1 为重复数据
           int RepeatVehicleRet = deRepeatVehicleInfo(_VehicleInfo);
           printf("RepeatVehicleRet:%d\n", RepeatVehicleRet);
           pVehicle->isRepeat = std::to_string(RepeatVehicleRet);
           if( RepeatVehicleRet == RET_NORMAL || RepeatVehicleRet == RET_RECHECK)
           {
               //信息添加到_vehicleInfoVector队列
               _VehicleInfo.setGuid(pVehicle->uuid);
               _vehicleInfoVector.push_back(_VehicleInfo);

               //执行车辆额外的网络接口操作
               processWangLuoJieKouInfo(&soapclient, pVehicle);
               //请求视频信息
               if (_cheJianStartUpParam.queryVideo)
               {
                   pVehicle->videoCheckInfo.isNeedLoadVideoInfo = true;
                   pVehicle->cityCode = _cityCode;
                   pVehicle->videoJyjgbhConfig = _videoCheckJyjgbhConfig;
                   requestVideoInfo(pVehicle);
               }
               //将车辆信息插入object队列
               pushQueue(pVehicle);
           }
           else
           {
//               printf("repetitive vehicle info request %s \n", pVehicle->liuShuiHao.c_str());
               LOG(COMMON,INFO,"repetitive vehicle info request %s \n", pVehicle->liuShuiHao.c_str());
               pushReponseQueue(pVehicle);
           }
       }
    }

    _c_systemInfo *pInfo = new _c_systemInfo();
    pInfo->lshNum = std::to_string(_lshVector.size());
    pInfo->sessionDisponseNum = std::to_string(_vehicleInfoVector.size());
    pInfo->soapQueryNum = std::to_string(queryNum);
    pInfo->soapNewNum = std::to_string(queryNewNum);
    pInfo->sessionQueueNum = std::to_string(getSessionQueueSize());
    pInfo->sessionVectorNum = std::to_string(getSessionVectorSize());
    pInfo->sessionAlgQueueNum = std::to_string(getSessionAlgQueueSize());
    pInfo->reponseQueueNum = std::to_string(getReponsetQueueSize());
    pInfo->dbTaskQueueNum = std::to_string(getDbTaskQueueSize());
    printf("systemInfo:%s\n",pInfo->getSql().c_str());
    pInfo->dbWork();

    std::this_thread::sleep_for(std::chrono::milliseconds(_threadSleepMilliseconds));
    return true;
}

bool _c_cheJianSessionService::reponseData(_c_session *pSession)
{
    _c_vehicle *_pVehicle = (_c_vehicle *)pSession;

    //处理重复的车辆信息
    if(_pVehicle->isRepeat.compare(REPEAT) == 0)
    {
        //从_vehicleInfoVector中获取相应的重复车辆检测信息
        if(!repeatVehicleDisponse(pSession))
        {
            //处理无效车辆检测信息
            freeUnusefulRepeatedVehicleInfo(pSession);
            delete pSession;
            pSession = NULL;
            return false;
        }
    }
    else
    {
        //把车辆检测的结果填写到相应的_vehicleInfoVector中
        vehicleSetDisposeEnd(pSession);
    }

    //soap 回复车辆审核结果
    if(pSession != NULL)
    {
        if (workMode != eTestCaseMode)
        {
            if(_cheJianStartUpParam.isGroupResponse)
            {
                //一次性回复车辆检测结果信息
                photoResultGroupReply(pSoapApiHandle, _pVehicle, _cheJianStartUpParam.soapXlh, _cheJianStartUpParam.soapIp.c_str()
                                           , _cheJianStartUpParam.soapPort, _cheJianStartUpParam.soapUrl
                                           , _cheJianStartUpParam.g_cjbh, _cheJianStartUpParam.g_zdbs, _cheJianStartUpParam.g_dwjgdm);
            }
            else
            {
                //逐个回复车辆检测结果信息
                photoResultSingleReply(pSoapApiHandle, _pVehicle, _cheJianStartUpParam.soapXlh, _cheJianStartUpParam.soapIp.c_str()
                                           , _cheJianStartUpParam.soapPort, _cheJianStartUpParam.soapUrl
                                           , _cheJianStartUpParam.g_cjbh, _cheJianStartUpParam.g_zdbs, _cheJianStartUpParam.g_dwjgdm);
            }
        }
    }
    _pVehicle->setPushDbTaskQueueTime();
    _pVehicle->dbWork();
    extraWorkBeforReponse(pSession);
    return false;
}

std::string _c_cheJianSessionService::getBaseTableName()
{
    _c_vehicle object;
    return object.tableName;
}
