#ifndef _C_DBTASKCENTER_H
#define _C_DBTASKCENTER_H
#include "base/_c_dbTask.h"

class _c_dbTaskCenter{
public:
    //初始化数据库模块
    bool initDb(PDB_PARAM dbParam);
    //启动数据库任务处理线程
    bool stratDbTaskCenter();
    //任务查询处理接口
    bool queryData();
    //数据库任务线程是否关闭
    bool isClose();
    //数据库更新接口
    bool updateDb();


    explicit _c_dbTaskCenter(PDB_PARAM dbParam)
	{
		initDb(dbParam);
	}

    threadInfo *getDbTaskCenterQueryThread() {return &DbTaskCenterQueryThread;}

private:
//    std::thread *_pDbTaskCenterQueryThread;
    threadInfo DbTaskCenterQueryThread;

    std::vector<std::string> _updateVector;
    DB_PARAM _param;

    //表格是否需要更新检测接口
    bool checkNeedUpdate(std::string tableName);
    //无返回数据库任务执行
    bool NoReturnDbWork(std::string sqlStr, bool statrments);
};

#endif // _C_DBTASKCENTER_H
