#include "_c_sessionTransCenter.h"
#include "base/soapApi/soapApi.h"
#include "base/dataCenter.h"
#include "base/baseTool.h"
#include <ctime>
#include "base/_c_chejian_init.h"

_c_sessionTransCenter::_c_sessionTransCenter()
{
    _timeOutMilliseconds = 1000 * 60 * 5;
    _threadSleepMilliseconds = 1000 * 10;

    __clearData = false;
}

bool _c_sessionTransCenter::isClose()
{
    return false;
}

void SessionTransCenter_QueryThread(_c_sessionTransCenter *pCenter)
{
    do{
        threadInfo *pInfo = pCenter->getSessionTransQueryThread();
        pInfo->updateCurCnt();
        pCenter->queryData();
    }while(!pCenter->isClose());
}

void SessionTransCenter_ReponseThread(_c_sessionTransCenter *pCenter)
{
    do{
        threadInfo *pInfo = pCenter->getSessionTransReponseThread();
        pInfo->updateCurCnt();
        pCenter->queryReponseData();
    }while(!pCenter->isClose());
}

bool _c_sessionTransCenter::startSessionTransCenter()
{
    //启动数据查询线程
//    __pSessionTransQueryThread = new std::thread(SessionTransCenter_QueryThread, this);
    SessionTransQueryThread.threadName = "SessionTransQueryThread";
    SessionTransQueryThread._pthread = new std::thread(SessionTransCenter_QueryThread, this);
    //启动回复任务查询线程
//    __pSessionTransReponseThread = new std::thread(SessionTransCenter_ReponseThread, this);
    SessionTransReponseThread.threadName = "SessionTransReponseThread";
    SessionTransReponseThread._pthread = new std::thread(SessionTransCenter_ReponseThread, this);
    return true;
}

bool _c_sessionTransCenter::clearData()
{
    // coredump 文件清除
    coreDumpFileClear();
    resetSoapFlag() ;
    return true;
}

bool _c_sessionTransCenter::queryData()
{
    //数据查询见相对应的派生类实现
   std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    return true;
}

bool _c_sessionTransCenter::queryReponseData()
{
    //获取待回复队列中object个数
    unsigned int queueSize = getReponsetQueueSize();
    //printf("reponse queueSize %u\n", queueSize);
    if(queueSize > 0)
    {
        //printf("queryReponseData queueSize:%d\n",queueSize);
        //获取一个待回复object
        _c_session *pSession = getReponseFromQueue();
        if(pSession != NULL)
        {
           //调用派生类回复接口
           reponseData(pSession);
        }
    }else {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return true;

}

bool _c_sessionTransCenter::pushQueue(_c_session *pSession)
{
    if(!__clearData)
    {
        //数据插入session队列
        return pushSessionQueue(pSession);
    }

    pSession->loadAlgTask();

    for (unsigned int i = 0; i < pSession->algTaskVector.size(); i++) {
        pSession->algTaskVector[i]->reason = "数据清理";
        pSession->algTaskVector[i]->result = "4";
    }

    return  reponseData(pSession);
}

bool _c_sessionTransCenter::pushDbQueue(_c_dbTask *pDbTask)
{
    //将db任务插入db处理队列
    pDbTask->dbWork();
    return true;
}

bool _c_sessionTransCenter::reponseData(_c_session *pSession)
{
    //回复接口派生类中实现
    UNUSED(pSession);
    return true;
}

bool _c_sessionTransCenter::clearDataOpen()
{
    __clearData = true;
    __threadSleep = _threadSleepMilliseconds;
    _threadSleepMilliseconds = 1;
    return __clearData;
}

bool _c_sessionTransCenter::clearDataClose()
{
    _threadSleepMilliseconds = __threadSleep;
    __clearData = false;
    return __clearData;
}

void _c_sessionTransCenter::setWorkMode(WorkMode mode)
{
    workMode = mode;
}

WorkMode _c_sessionTransCenter::getWorkMode()
{
    return workMode;
}
