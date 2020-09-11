#include "_c_yingXiangSessionService.h"
#include "base/soapApi/soapTmriOutAccessSoapBindingProxy.h"
#include "base/dataCenter.h"
#include "base/soapApi/soapApi.h"
#include "base/_c_systemInfo.h"
#include "base/baseTool.h"
#include <ctime>

_c_yingXiangSessionService::_c_yingXiangSessionService(PSTARTUPPRARAM param)
{
    _yingXiangStartUpParam = *param;
    printf("Initialize soap param: ip:%s ,port:%s\n", _yingXiangStartUpParam.soapIp.c_str(), _yingXiangStartUpParam.soapPort.c_str());

    _yingXiangStartUpParam.g_cjbh = baseTool::getLocalIp();
    _yingXiangStartUpParam.g_zdbs = "01";

    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);
    _curDay = st->tm_mday;

    _threadSleepMilliseconds = (unsigned int)_yingXiangStartUpParam.soapQueryInterval;
//    pSoapApiHandle = soapApi_creatSoapApiHandle();
}

_c_yingXiangSessionService::~_c_yingXiangSessionService()
{
    if (pSoapApiHandle)
    {
        soapApi_closeSoapApiHandle(pSoapApiHandle);
        pSoapApiHandle = NULL;
    }
}

bool _c_yingXiangSessionService::queryData()
{
    std::vector<std::string> lsh_vector;
    std::vector<std::string> newLsh_vector;

    TmriOutAccessSoapBindingProxy soapclient;
    soapclient.accept_timeout = 30;
    soapclient.connect_timeout = 30;
    soapclient.recv_timeout = 30;
    soapclient.send_timeout = 30;

    if (baseTool::checkDateChange(_curDay))
        clearCache();

    //查询待审核档案流水号列表
    int queryNum = queryLiuShuiHao(&lsh_vector);
//    int queryNum = queryLiuShuiHao(&newLsh_vector);
    int queryNewNum = 0;
    //流水号列表去重
    deRepeatLiuShuiHao(&lsh_vector,&newLsh_vector);
    queryNewNum = (int)newLsh_vector.size();
    printf("查询到[%d]个待检数据,其中[%d]个新增流水号\n",queryNum,queryNewNum);
    LOG(COMMON,INFO,"查询到[%d]个待检数据,其中[%d]个新增流水号\n",queryNum,queryNewNum);

    LOG(COMMON,INFO,"新增流水号：\n");
    //遍历查询到的流水号
    for (unsigned int i = 0; i < newLsh_vector.size(); i++) {
       //查询流水号对应的档案影像化信息
       _c_yingXiangVehicle *pVehicle = queryVehicleInfo(newLsh_vector[i]);
       if(pVehicle != NULL)
       {
           pVehicle->setSessionInSystemTime();
           //获取本次车辆信息在程序内的唯一key（uuid码）
           pVehicle->loadUuid();
           LOG(COMMON,INFO,"uuid:%s lsh:%s\n", pVehicle->uuid.c_str(), pVehicle->liuShuiHao.c_str());
           _c_yingXiangLshInfo _VehicleInfo(pVehicle);
           //车辆信息严格去重
           if(deRepeatVehicleInfo(_VehicleInfo))
           {
               //信息添加到_vehicleInfoVector队列
               _VehicleInfo.setGuid(pVehicle->uuid);
               _yxLshInfoVector.push_back(_VehicleInfo);
               cout << "vector[0] guid is:" << _yxLshInfoVector[0].getGuid() << endl;
               //车辆信息不重复
               pVehicle->isRepeat = NOREPEAT;
               //将车辆信息插入object队列
               pushQueue(pVehicle);
           }
           else
           {
               pVehicle->isRepeat = REPEAT;//重复车辆
               //printf("repetitive vehicle info request %s \n", pVehicle->liuShuiHao.c_str());
               LOG(COMMON,INFO,"repetitive vehicle info request %s \n", pVehicle->liuShuiHao.c_str());
               pushReponseQueue(pVehicle);
           }
       }
    }
    if (newLsh_vector.size() > 0)
    {
        _c_systemInfo *pInfo = new _c_systemInfo();
        pInfo->lshNum = std::to_string(_lshVector.size());
        pInfo->sessionDisponseNum = std::to_string(_yxLshInfoVector.size());
        pInfo->soapQueryNum = std::to_string(queryNum);
        pInfo->soapNewNum = std::to_string(queryNewNum);
        pInfo->sessionQueueNum = std::to_string(getSessionQueueSize());
        pInfo->sessionVectorNum = std::to_string(getSessionVectorSize());
        pInfo->sessionAlgQueueNum = std::to_string(getSessionAlgQueueSize());
        pInfo->reponseQueueNum = std::to_string(getReponsetQueueSize());
        pInfo->dbTaskQueueNum = std::to_string(getDbTaskQueueSize());
        printf("systemInfo:%s\n",pInfo->getSql().c_str());
        pInfo->dbWork();

    }

    std::this_thread::sleep_for(std::chrono::milliseconds(_threadSleepMilliseconds));
    return true;
}

bool _c_yingXiangSessionService::reponseData(_c_session *pSession)
{
    _c_yingXiangVehicle *_pVehicle = (_c_yingXiangVehicle *)pSession;

#if 1
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
#endif

    if(extraWorkBeforReponse(pSession))
    {
        //soap 回复车辆审核结果
        if(pSession != NULL)
        {
            //逐个回复车辆检测结果信息
            photoResultReply(_pVehicle);

        }
        _pVehicle->setPushDbTaskQueueTime();
        _pVehicle->dbWork();
    }

    return false;
}

std::string _c_yingXiangSessionService::getBaseTableName()
{
    _c_yingXiangVehicle object;
    return object.tableName;
}
