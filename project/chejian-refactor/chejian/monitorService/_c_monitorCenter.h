#ifndef _C_MONITORCENTER_H
#define _C_MONITORCENTER_H

#include "base/baseInc.h"
#include "mmap/mmapWriter.h"

#define MMAPFILEPATH "/opt/vehicle/program/programPath/"
#define MMAPFILENAME "mmapHeartBeat"

class _c_monitorCenter
{
public:
    _c_monitorCenter();
    //列表注册函数
    void registerForMonitor(threadInfo *p);
    //开启检测线程
    void startMonitor();
    //检测列表
    std::vector<threadInfo *> threadsVector;
    bool getRunningFlag() {return monitorRunning;}
    //获取监测间隔
    unsigned int getMonitorInterval() {return monitorInterval;}
    void updateMmap();

private:
    void initMmap(int num, const char *version, unsigned int vLen, const char *time, unsigned int tLen);

private:
    //监测间隔时间 毫秒
    unsigned int monitorInterval;

    //检测线程
    bool monitorRunning;
    std::thread *_pMonitorThread;

    MmapWriter mmapWriter;
};

#endif // _C_MONITORCENTER_H
