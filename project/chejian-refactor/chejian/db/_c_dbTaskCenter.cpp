#include "db/_c_dbTaskCenter.h"
#include "base/dataCenter.h"
#include "db/_c_dbTask_sqlOper.h"
#include <cstring>

void DbTaskCenter_QueryThread(_c_dbTaskCenter *pCenter)
{
    do{
        threadInfo *pInfo = pCenter->getDbTaskCenterQueryThread();
        pInfo->updateCurCnt();
        pCenter->queryData();
    }while(!pCenter->isClose());
}

bool _c_dbTaskCenter::stratDbTaskCenter()
{
    updateDb();
//    _pDbTaskCenterQueryThread = new std::thread(DbTaskCenter_QueryThread, this);
    DbTaskCenterQueryThread.threadName = "DbTaskCenterQueryThread";
    DbTaskCenterQueryThread._pthread = new std::thread(DbTaskCenter_QueryThread, this);
    return true;
}

bool _c_dbTaskCenter::queryData()
{
    unsigned int queueSize = getDbTaskQueueSize();
    if(queueSize > 0)
    {
        _c_dbTask *pDbTask = getDbTaskFromQueue();
        if(pDbTask != NULL)
        {
            if(checkNeedUpdate(pDbTask->getTableName()))
            {
               NoReturnDbWork(pDbTask->getCreatTableSql(),false);
               bool needUpdate = NoReturnDbWork(pDbTask->getUpdateTableSql(),true);
               std::this_thread::sleep_for(std::chrono::milliseconds(10000));
               if(needUpdate)
                    _updateVector.push_back(pDbTask->getTableName());
            }
            pDbTask->beforDbWork();
            NoReturnDbWork(pDbTask->getSql(),pDbTask->statrments());
            pDbTask->extraDbWork();
            if(pDbTask->needFree())
            {
                pDbTask->close();
                delete pDbTask;
                pDbTask = NULL;
            }
        }

    }else {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return true;
}

bool _c_dbTaskCenter::isClose()
{
    return false;
}

bool _c_dbTaskCenter::checkNeedUpdate(std::string tableName)
{
    bool needUpdate = true;
    for (unsigned int i = 0; i<_updateVector.size(); i++) {
        if(_updateVector[i] == tableName)
        {
            needUpdate=false;
        }
    }
    return needUpdate;
}

bool _c_dbTaskCenter::updateDb()
{
	return true;
}

bool _c_dbTaskCenter::initDb(PDB_PARAM dbParam)
{
    _param = *dbParam;
    _c_dbTaskSqlOper::getInstance().executeCreatDb(DB_MYSQL, &_param);

    return true;
}

bool _c_dbTaskCenter::NoReturnDbWork(std::string sqlStr, bool statrments)
{
    LOG(DB,INFO,"NoReturnDbWork statrments:%d SQL String:[%s]\n",statrments,sqlStr.c_str());
    return _c_dbTaskSqlOper::getInstance().executeSql(DB_MYSQL, &_param, sqlStr,statrments);
}
