#include "_c_chaYanSessionService.h"
#include "base/soapApi/soapTmriOutAccessSoapBindingProxy.h"
#include "base/dataCenter.h"
#include "base/soapApi/soapApi.h"
#include "base/_c_systemInfo.h"
#include "base/baseTool.h"
#include <ctime>

_c_chaYanSessionService::_c_chaYanSessionService(PSTARTUPPRARAM param)
{
    _chaYanStartUpParam = *param;
    printf("Initialize soap param: ip:%s ,port:%s queryInterVal:%d\n", _chaYanStartUpParam.soapIp.c_str(), _chaYanStartUpParam.soapPort.c_str(), _chaYanStartUpParam.soapQueryInterval);

    _chaYanStartUpParam.g_cjbh = "01";
    _chaYanStartUpParam.g_zdbs = baseTool::getLocalIp();

    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);
    curDay = st->tm_mday;

    _threadSleepMilliseconds = (unsigned int)_chaYanStartUpParam.soapQueryInterval;
//    pSoapApiHandle = soapApi_creatSoapApiHandle();
}

_c_chaYanSessionService::~_c_chaYanSessionService()
{
    if (pSoapApiHandle)
    {
        soapApi_closeSoapApiHandle(pSoapApiHandle);
        pSoapApiHandle = NULL;
    }
}

bool _c_chaYanSessionService::queryData()
{
    if (workMode != eHostMode)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(_threadSleepMilliseconds));
        return true;
    }

    if (!checkWorkTime())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(_threadSleepMilliseconds));
        printf("it's rest time!\n");
        return true;
    }

    std::vector<std::string> waiGuanLsh_vector;
    std::vector<std::string> zhengJianLsh_vector;
    std::vector<std::string> waiGuanNewLsh_vector;
    std::vector<std::string> zhengJianNewLsh_vector;

    TmriOutAccessSoapBindingProxy soapclient;
    int timeout = _chaYanStartUpParam.soapTimeOut;
    soapclient.accept_timeout = timeout;
    soapclient.connect_timeout = timeout;
    soapclient.recv_timeout = timeout;
    soapclient.send_timeout = timeout;

    if (baseTool::checkDateChange(curDay))
        clearCache();

    int waiGuanQueryNum = 0, zhengJianQueryNum = 0;
    int waiGuanQueryNewNum = 0, zhengJianQueryNewNum = 0;
    //只请求外观类流水号
    if (_chaYanStartUpParam.workMode == "1")
    {
        waiGuanQueryNum = queryWaiGuanLiuShuiHao(&soapclient, &waiGuanLsh_vector);
    }
    //只请求证件类流水号
    else if (_chaYanStartUpParam.workMode == "2")
    {
        zhengJianQueryNum = queryZhengJianLiuShuiHao(&soapclient, &zhengJianLsh_vector);
    }
    //同时请求外观类及证件类
    else if (_chaYanStartUpParam.workMode == "3")
    {
        waiGuanQueryNum = queryWaiGuanLiuShuiHao(&soapclient, &waiGuanLsh_vector);
        zhengJianQueryNum = queryZhengJianLiuShuiHao(&soapclient, &zhengJianLsh_vector);
    }

    //外观类流水号列表去重
    deRepeatLiuShuiHao(&waiGuanLsh_vector, &waiGuanNewLsh_vector, true);
    waiGuanQueryNewNum = (int)waiGuanNewLsh_vector.size();
    printf("外观 查询到[%d]个待检数据,其中[%d]个新增流水号\n",waiGuanQueryNum, waiGuanQueryNewNum);
    LOG(COMMON,INFO,"外观 查询到[%d]个待检数据,其中[%d]个新增流水号\n",waiGuanQueryNum, waiGuanQueryNewNum);

    //证件类流水号列表去重
    deRepeatLiuShuiHao(&zhengJianLsh_vector, &zhengJianNewLsh_vector, false);
    zhengJianQueryNewNum = (int)zhengJianNewLsh_vector.size();
    printf("证件 查询到[%d]个待检数据,其中[%d]个新增流水号\n",zhengJianQueryNum, zhengJianQueryNewNum);
    LOG(COMMON,INFO,"证件 查询到[%d]个待检数据,其中[%d]个新增流水号\n",zhengJianQueryNum, zhengJianQueryNewNum);

    _c_chaYanVehicle *pVehicle = NULL;
    for (unsigned int i = 0; i < waiGuanNewLsh_vector.size(); i++) {
        pVehicle = queryVehicleInfo(&soapclient, waiGuanNewLsh_vector[i], "1");

        if (pVehicle != NULL) {
            pVehicle->setSessionInSystemTime();
            //获取本次车辆信息在程序内的唯一key（uuid码）
            pVehicle->loadUuid();
            pVehicle->centerStatus = "0";
            pVehicle->redisChannel = redisRequstChan;
            pVehicle->greenChannel = "false";
            pVehicle->waiGuanBiaoDanBiaoZhi = "1";
            _c_chaYanVehicleInfo _VehicleInfo(pVehicle);
            //车辆信息严格去重
            if(deRepeatVehicleInfo(_VehicleInfo))
            {
                checkGreenChannel(pVehicle);
                //信息添加到_vehicleInfoVector队列
                _VehicleInfo.setGuid(pVehicle->uuid);
                _vehicleInfoVector.push_back(_VehicleInfo);
                //车辆信息不重复
                pVehicle->isRepeat = NOREPEAT;
                //将车辆信息插入object队列
                pushQueue(pVehicle);
            }
            else
            {
                pVehicle->isRepeat = REPEAT;//重复车辆
 //               printf("repetitive vehicle info request %s \n", pVehicle->liuShuiHao.c_str());
                LOG(COMMON,INFO,"repetitive vehicle info request %s \n", pVehicle->liuShuiHao.c_str());
                pushReponseQueue(pVehicle);
            }
        }
    }

    pVehicle = NULL;
    for (unsigned int i = 0; i < zhengJianNewLsh_vector.size(); i++) {
        pVehicle = queryVehicleInfo(&soapclient, zhengJianNewLsh_vector[i], "2");

        if (pVehicle != NULL) {
            pVehicle->setSessionInSystemTime();
            //获取本次车辆信息在程序内的唯一key（uuid码）
            pVehicle->loadUuid();
            pVehicle->centerStatus = "0";
            pVehicle->greenChannel = "false";
            pVehicle->waiGuanBiaoDanBiaoZhi = "2";
			pVehicle->redisChannel = redisRequstChan;
            _c_chaYanVehicleInfo _VehicleInfo(pVehicle);
            //车辆信息严格去重
            if(deRepeatVehicleInfo(_VehicleInfo))
            {
                //信息添加到_vehicleInfoVector队列
                _VehicleInfo.setGuid(pVehicle->uuid);
                _vehicleInfoVector.push_back(_VehicleInfo);
                //车辆信息不重复
                pVehicle->isRepeat = NOREPEAT;
                //将车辆信息插入object队列
                pushQueue(pVehicle);
            }
            else
            {
                pVehicle->isRepeat = REPEAT;//重复车辆
 //               printf("repetitive vehicle info request %s \n", pVehicle->liuShuiHao.c_str());
                LOG(COMMON,INFO,"repetitive vehicle info request %s \n", pVehicle->liuShuiHao.c_str());
                pushReponseQueue(pVehicle);
            }
        }
    }

    _c_systemInfo *pInfo = new _c_systemInfo();
    pInfo->lshNum = std::to_string(_waiGuanLshVector.size() + _zhengJianlshVector.size());
    pInfo->sessionDisponseNum = std::to_string(_vehicleInfoVector.size());
    pInfo->soapQueryNum = std::to_string(waiGuanQueryNum + zhengJianQueryNum);
    pInfo->soapNewNum = std::to_string(waiGuanQueryNewNum + zhengJianQueryNewNum);
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

bool _c_chaYanSessionService::reponseData(_c_session *pSession)
{
    _c_chaYanVehicle *_pVehicle = (_c_chaYanVehicle *)pSession;

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

    if(extraWorkBeforReponse(pSession))
    {
        if (workMode != eTestCaseMode)
        {
            //soap 回复车辆审核结果
            if(pSession != NULL)
            {
                //逐个回复车辆检测结果信息
                photoResultReply(pSoapApiHandle, _pVehicle, _chaYanStartUpParam.soapXlh, _chaYanStartUpParam.soapIp.c_str()
                                                   , _chaYanStartUpParam.soapPort, _chaYanStartUpParam.soapUrl
                                                   , _chaYanStartUpParam.g_zdbs, _chaYanStartUpParam.g_cjbh, _chaYanStartUpParam.g_dwjgdm);

            }
        }
        _pVehicle->setPushDbTaskQueueTime();
        _pVehicle->dbWork();
    }

    return false;
}

std::string _c_chaYanSessionService::getBaseTableName()
{
    _c_chaYanVehicle object;
    return object.tableName;
}
