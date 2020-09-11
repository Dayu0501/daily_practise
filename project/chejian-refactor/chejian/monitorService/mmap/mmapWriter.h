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

class MmapWriter
{
public:
    MmapWriter();
    ~MmapWriter();

    int mmapOpen(const char *pPath);
    void writeNum (int num);
    int writeVersion(const char *pBuf, int Offset, int Len);
    int writeHeartBeatTime(const char *pBuf, int Offset, int Len);
    int readNum();
    int readVersion(char *pBuf, int Offset, int Len);
    int readHeartBeatTime(char *pBuf, int Offset, int Len);

    int free();

private:
    int _FileFd;
    PMMAPDATA _pMmapData;
};

#endif // MMAPWRITER_H
