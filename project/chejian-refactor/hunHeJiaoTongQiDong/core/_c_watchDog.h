#ifndef _C_WATCHDOG_H
#define _C_WATCHDOG_H

#include "base/baseInc.h"
#include "base/mmap/mmapWriter.h"
#include "base/mmap/mmapReader.h"

class _c_disasterRecovery;
class _c_deviceSearch;

enum eMmapFileType
{
    eMmapFileTypeAll = 0,
    eMmapFileTypeXiTong = 1,
    eMmapFileTypeSuanFa = 2,
};

#define WATCHDOG_THREAD_INTERVAL   1000//millsec
#define WATCHDOG_RESTARTAPP_INTERVAL    30  //基于 WATCHDOG_THREAD_INTERVAL

#define XITONG_MMAPFILEPATH "/opt/vehicle/program/programPath/mmapHeartBeat"
#define SUANFA_MMAPFILEPATH "/opt/vehicle/program/programPath/chejian_alg_redis.txt"

#define MaxBufSize 128
typedef struct _XITONG_MMAPDATA
{
    int num;
    char version[MaxBufSize];
    char heartBeatTime[MaxBufSize];
}XITONG_MMAPDATA, *PXITONG_MMAPDATA;

typedef struct _SUANFA_MMAPDATA {
    int num;   // 计数
    char redis_version[MaxBufSize];      //redis进程的版本
    char alg_version[MaxBufSize];       //算法版本
    char start_time[MaxBufSize];      // 启动时间
    char gpu_num[MaxBufSize];        //gpu数量
    char gpu_type[MaxBufSize];      //gpu类型  nvidia 和 cambricon
    char heartBeatTime[MaxBufSize];  //心跳(好像没用)
}SUANFA_MMAPDATA, *PSUANFA_MMAPDATA;

typedef struct _XITONG_MONITOR_INFO
{
    MmapReader<XITONG_MMAPDATA>_mmapReader;
    XITONG_MMAPDATA data;
    int _errCount;
    int _lastNum;
    int _lostAppCount;//重启失败多次
    int _mmapStatus;
    bool isNeedRestart;
}XITONG_MONITOR_INFO, *PXITONG_MONITOR_INFO;

typedef struct _SUANFA_MONITOR_INFO
{
    MmapReader<SUANFA_MMAPDATA>_mmapReader;
    SUANFA_MMAPDATA data;
    int _errCount;
    int _lastNum;
    int _mmapStatus;
    bool isNeedRestart;
}SUANFA_MONITOR_INFO, *PSUANFA_MONITOR_INFO;

class _c_watchDog
{
public:
    _c_watchDog(_c_disasterRecovery *pDisasterRecovery, _c_deviceSearch *device);
    ~_c_watchDog(){}
    bool feedDog();

    void watchDogMmapOpen(eMmapFileType type = eMmapFileTypeAll);
    void watchDogMmapClose(eMmapFileType type = eMmapFileTypeAll);

    void watchDogStart();
    void reStartMain();

    void processLostApp();
    bool isCompetitionFinished();

    void setFileUploadStatus(bool status);
    bool isClose(){return false;}

private:
    int _watchDogInterval;

    XITONG_MONITOR_INFO _xiTongMonitorInfo;
    SUANFA_MONITOR_INFO _suanFaMonitorInfo;

    bool _isFileUploading;

    _c_disasterRecovery *_pDisasterRecovery;
    _c_deviceSearch *_deviceSearch;
};

#endif // _C_WATCHDOG_H
