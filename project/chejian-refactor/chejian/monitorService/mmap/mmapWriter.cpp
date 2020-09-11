#include "mmapWriter.h"

MmapWriter::MmapWriter()
{
    _FileFd = -1;
    _pMmapData = NULL;
}

MmapWriter::~MmapWriter()
{

}

int MmapWriter::mmapOpen(const char *pPath)
{
    if (_FileFd == -1)
    {
        _FileFd = open(pPath, O_CREAT | O_RDWR, 00777);
        lseek(_FileFd, sizeof(MMAPDATA) - 1, SEEK_SET);
        write(_FileFd, "", 1);
        _pMmapData = (PMMAPDATA)mmap(NULL, sizeof(MMAPDATA), PROT_READ | PROT_WRITE, MAP_SHARED, _FileFd, 0);
        //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 11111 \n");
        if (_pMmapData == (void *)-1)
        {
            return 0;
        }

        return 1;
    }
    return 0;
}


void MmapWriter::writeNum(int num)
{
    //printf("n:%d\nv:%s\nt:%s\n",_pMmapData->num,_pMmapData->version,_pMmapData->heartBeatTime);

    (*(_pMmapData)).num = num;
}

int MmapWriter::writeVersion(const char *pBuf, int Offset, int Len)
{
    if (Len <= (MaxBufSize - Offset))
    {
        memcpy((*(_pMmapData)).version + Offset, pBuf, Len);
//        int ret = sem_post(&_pMmapData->Mutex);
        return Len;
    }
    return -1;
}

int MmapWriter::writeHeartBeatTime(const char *pBuf, int Offset, int Len)
{
    if (Len <= (MaxBufSize - Offset))
    {
        memcpy((*(_pMmapData)).heartBeatTime + Offset, pBuf, Len);
//        int ret = sem_post(&_pMmapData->Mutex);
        return Len;
    }
    return -1;
}

int MmapWriter::readNum(void)
{
    return (*(_pMmapData)).num;
}


int  MmapWriter::readVersion(char *pBuf,int Offset,int Len)
{
    if (Len <= (MaxBufSize - Offset))
    {
        memcpy(pBuf, (*(_pMmapData)).version + Offset,  Len);
        return Len;
    }
    return -1;
}

int  MmapWriter::readHeartBeatTime(char *pBuf,int Offset,int Len)
{
    if (Len <= (MaxBufSize - Offset))
    {
        memcpy(pBuf, (*(_pMmapData)).heartBeatTime + Offset,  Len);
        return Len;
    }
    return -1;
}

int MmapWriter::free()
{
    if (_FileFd != -1)
    {
        close(_FileFd);
        _FileFd = -1;
        munmap(_pMmapData, sizeof(MMAPDATA));
    }
    return 1;
}
