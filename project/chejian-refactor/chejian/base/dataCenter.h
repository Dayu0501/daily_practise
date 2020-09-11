#ifndef _DATACENTER_H
#define _DATACENTER_H
#include "base/_c_dbTask.h"
#include "base/_c_session.h"
#include "base/_c_device.h"
#include "alg/_c_algTaskResponse.h"
#include "config/_c_configCenter.h"

void setDeviceHeartBeat(_c_device *pDevice);
Json::Value getDeviceHeartBeatJson();

void setDeviceState(std::string deviceState);
std::string getDeviceState();

bool initConfigCenter(CityType cityType);
_c_configCenter *loadSystemConfig();
std::string getDbSchemaName();
std::string getRedisRequstChan();

Json::Value getWorkSessionStateJson();

bool pushDbTaskQueue(_c_dbTask *pDbTask);
_c_dbTask *getDbTaskFromQueue();
unsigned int getDbTaskQueueSize();

bool pushSessionQueue(_c_session *pSession);
_c_session *getSessionFromQueue();
unsigned int getSessionQueueSize();

bool pushSessionIntoSessionVector(_c_session *pSession);
_c_session *getWorkEndSession();
unsigned int getSessionVectorSize();

bool pushAlgTaskResponseQueue(_c_algTask_Reponse *pAlgTaskResponse);
_c_algTask_Reponse *getAlgTaskResponseFromQueue();
unsigned int getAlgTaskResponseQueueSize();

bool pushSessionAlgQueue(_c_session *pSession);
_c_session *getSessionAlgFromQueue();
unsigned int getSessionAlgQueueSize();

bool pushReponseQueue(_c_session *pSession);
_c_session *getReponseFromQueue();
unsigned int getReponsetQueueSize();

#endif // _DATACENTER_H
