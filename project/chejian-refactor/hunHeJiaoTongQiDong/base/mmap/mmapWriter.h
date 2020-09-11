#ifndef MMAPWRITER_H
#define MMAPWRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define MaxBufSize 128

typedef struct _MMAPDATA
{
    int num;
//    int MutexInit;
//    sem_t Mutex;
    char version[MaxBufSize];
    char heartBeatTime[MaxBufSize];
}MMAPDATA, *PMMAPDATA;


//typedef struct _MMAPDATA {
//int num;   // 计数
// //    int MutexInit;
////    sem_t Mutex;
//char redis_version[MaxBufSize];      //redis进程的版本
//char alg_version[MaxBufSize];       //算法版本
//char start_time[MaxBufSize];      // 启动时间
// char gpu_num[MaxBufSize];        //gpu数量
//char gpu_type[MaxBufSize];      //gpu类型  nvidia 和 cambricon
//char heartBeatTime[MaxBufSize];  //心跳(好像没用)
// }MMAPDATA, *PMMAPDATA;

class MmapWriter
{
public:
    MmapWriter();
    ~MmapWriter();

    int mmapOpen(const char *pPath);
    void writeNum (int num);
    int writeVersion(const char *pBuf, int Offset, unsigned int Len);
    int writeHeartBeatTime(const char *pBuf, int Offset, unsigned int Len);
    int readNum();
    int readVersion(char *pBuf, int Offset, int Len);
    int readHeartBeatTime(char *pBuf, int Offset, int Len);

    int free();

private:
    int _FileFd;
    PMMAPDATA _pMmapData;

};
#endif // MMAPWRITER_H
