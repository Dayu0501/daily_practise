#include "dataCenter.h"
#include "NoBlockSessionVector.h"

BlockingQueue<_c_session *> reponse_queue;
BlockingQueue<_c_dbTask *> dbTask_queue;
BlockingQueue<_c_session *> session_queue;
BlockingQueue<_c_session *> sessionAlg_queue;
BlockingQueue<_c_algTask_Reponse *> algTaskResponse_queue;
NoBlockSessionVector sessionVector;
_c_configCenter *__pConfigCenter = NULL;
std::string _deviceState = "设备启动中";

NoBlockDeviceVector deviceHeartBeatVector;

void setDeviceHeartBeat(_c_device *pDevice)
{
    deviceHeartBeatVector.Put(pDevice);
}

Json::Value getDeviceHeartBeatJson()
{
    return deviceHeartBeatVector.getDeviceStateJson();
}


void setDeviceState(std::string deviceState)
{
    _deviceState = deviceState;
}

std::string getDeviceState()
{
    return _deviceState;
}

bool initConfigCenter(CityType cityType)
{
    if(__pConfigCenter != NULL)
        return false;

    __pConfigCenter = new _c_configCenter(cityType);
    __pConfigCenter->loadConfig();

    return true;
}

_c_configCenter *loadSystemConfig()
{
    if(__pConfigCenter == NULL)
    {
        initConfigCenter(eDEMO);
    }




    return __pConfigCenter;
}
std::string getDbSchemaName()
{
    if(__pConfigCenter == NULL)
    {
        initConfigCenter(eDEMO);
    }
    return __pConfigCenter->getDbName();
}

std::string getRedisRequstChan()
{
    if(__pConfigCenter == NULL)
    {
        initConfigCenter(eDEMO);
    }
    return __pConfigCenter->getStructRedisParam()->requstChan;
}


bool pushDbTaskQueue(_c_dbTask *pDbTask)
{
    dbTask_queue.Put(pDbTask);
    return true;
}

_c_dbTask *getDbTaskFromQueue()
{
    return dbTask_queue.Take();
}

unsigned int getDbTaskQueueSize()
{
    return dbTask_queue.Size();
}

bool pushSessionIntoSessionVector(_c_session *pSession)
{
    sessionVector.Put(pSession);
    return  true;
}

unsigned int getSessionVectorSize()
{
    return sessionVector.Size();
}

Json::Value getWorkSessionStateJson()
{
    return sessionVector.getWorkSessionStateJson();
}

_c_session *getWorkEndSession()
{
    _c_session *p = sessionVector.getWorkEndSession();
    //p->setSessionEndWorkTime();
    return p;
}

bool pushSessionQueue(_c_session *pSession)
{
    pSession->setPushSessionQueueTime();
    session_queue.Put(pSession);
    return true;
}

_c_session *getSessionFromQueue()
{
    _c_session *p = session_queue.Take();
    p->setGetSessionQueueTime();
    return p;
}

unsigned int getSessionQueueSize()
{
    return session_queue.Size();
}

bool pushAlgTaskResponseQueue(_c_algTask_Reponse *pAlgTaskResponse)
{
    algTaskResponse_queue.Put(pAlgTaskResponse);
    return true;
}

_c_algTask_Reponse *getAlgTaskResponseFromQueue()
{
    return algTaskResponse_queue.Take();
}

unsigned int getAlgTaskResponseQueueSize()
{
   return algTaskResponse_queue.Size();
}

bool pushSessionAlgQueue(_c_session *pSession)
{
    pSession->setPushAlgSessionQueueTime();
    sessionAlg_queue.Put(pSession);
    return true;
}

_c_session *getSessionAlgFromQueue()
{
    _c_session *p = sessionAlg_queue.Take();
    p->setGetAlgSessionQueueTime();
    return p;
}

unsigned int getSessionAlgQueueSize()
{
    return sessionAlg_queue.Size();
}

bool pushReponseQueue(_c_session *pSession)
{
    pSession->setPushReponseQueueTime();
    reponse_queue.Put(pSession);
    return true;
}

_c_session *getReponseFromQueue()
{
    _c_session *p = reponse_queue.Take();
    p->setGetReponseQueueTime();
    return p;
}

unsigned int getReponsetQueueSize()
{
    return reponse_queue.Size();
}



