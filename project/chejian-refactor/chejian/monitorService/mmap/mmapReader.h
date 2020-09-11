#ifndef MMAPREADER_H
#define MMAPREADER_H

#include <sys/mman.h>

template<class T>
class MmapReader
{
public:
    MmapReader();
    ~MmapReader();

    int mmapOpen(const char *pPath);
    T getAll();
    void mmapClose();

private:
    int _FileFd;
    T *_pMmapData;
};

template <class T>
MmapReader<T>::MmapReader()
{
    _FileFd = -1;
    _pMmapData = NULL;
}

template <class T>
MmapReader<T>::~MmapReader()
{
    if (_FileFd != -1)
    {
        close(_FileFd);
        _FileFd = -1;
        munmap(_pMmapData, sizeof(T));
    }
}

template <class T>
T MmapReader<T>::getAll()
{
    return *_pMmapData;
}

template <class T>
void MmapReader<T>::mmapClose()
{
    if (_FileFd != -1)
    {
        close(_FileFd);
        _FileFd = -1;
        munmap(_pMmapData, sizeof(T));
    }
}

template <class T>
int MmapReader<T>::mmapOpen(const char *pPath)
{
//    printf("%u\n", sizeof(T));
    if (_FileFd == -1)
    {
        _FileFd = open(pPath, O_CREAT | O_RDWR, 00777);
        if (_FileFd < 0)
            return 0;

        lseek(_FileFd, sizeof(T) - 1, SEEK_SET);
        write(_FileFd, "", 1);
        _pMmapData = (T *)mmap(NULL, sizeof(T), PROT_READ | PROT_WRITE, MAP_SHARED, _FileFd, 0);
        //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 11111 \n");
        if (_pMmapData == (void *)-1)
        {
            return 0;
        }

        return 1;
    }
    return 0;
}

#endif // MMAPREADER_H
