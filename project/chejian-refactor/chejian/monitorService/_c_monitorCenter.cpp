#include "_c_monitorCenter.h"
#include "base/dataCenter.h"
#include "base/baseTool.h"
#include <cstring>

void monitorThread(_c_monitorCenter *pThread)
{
    while (pThread->getRunningFlag())
    {
        bool sendHeart = true;
        for (unsigned int i = 0; i < pThread->threadsVector.size(); i++)
        {
             if (pThread->threadsVector[i]->preCnt == pThread->threadsVector[i]->curCnt)
             {
                 //printf("thread name:%s curCnt:%lu \n", pThread->threadsVector[i]->threadName.c_str(), pThread->threadsVector[i]->curCnt);
                 LOG(COMMON, WARN, "monitor warning! thread name:%s curCnt:%lu \n", pThread->threadsVector[i]->threadName.c_str(), pThread->threadsVector[i]->curCnt);
                 //sendHeart = false;
                 break;
             }
             else
             {
                pThread->threadsVector[i]->setPreCnt();
             }
        }

        if (sendHeart)
        {
            pThread->updateMmap();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(pThread->getMonitorInterval()));
    }
}

_c_monitorCenter::_c_monitorCenter()
{
    monitorInterval = 1 * 1000;

    std::string version = baseTool::getCurVersion();
    std::string startTime = baseTool::getCurTime();
    initMmap(0, version.data(), version.size(), startTime.data(), startTime.size());
}

void _c_monitorCenter::startMonitor()
{
    monitorRunning = true;
    _pMonitorThread = new std::thread(monitorThread, this);
}

void _c_monitorCenter::registerForMonitor(threadInfo *p)
{
    threadsVector.push_back(p);
}

void _c_monitorCenter::initMmap(int num, const char *version, unsigned int vLen, const char *time, unsigned int tLen)
{
    std::string filePath = MMAPFILEPATH;
    filePath += MMAPFILENAME;

    mmapWriter.mmapOpen(filePath.data());
    mmapWriter.writeNum(num);
    mmapWriter.writeVersion(version, 0, vLen);
    mmapWriter.writeHeartBeatTime(time, 0, tLen);
}

void _c_monitorCenter::updateMmap()
{
    int num = mmapWriter.readNum();
    num++;

    mmapWriter.writeNum(num);
}

