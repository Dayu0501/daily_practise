#include "_c_watchDog.h"
#include "interface.h"
#include "base/dataCenter.h"

#include "_c_disasterRecovery.h"
#include "_c_deviceSearch.h"

_c_watchDog::_c_watchDog(_c_disasterRecovery *pDisasterRecovery, _c_deviceSearch *device)
{
    _deviceSearch = device;
    _pDisasterRecovery = pDisasterRecovery;

    _xiTongMonitorInfo._mmapStatus = 0;
    _xiTongMonitorInfo._lastNum = 0;
    _xiTongMonitorInfo._errCount = 0;
    _xiTongMonitorInfo._lostAppCount = 0;
    _xiTongMonitorInfo.isNeedRestart = false;

    _suanFaMonitorInfo._mmapStatus = 0;
    _suanFaMonitorInfo._lastNum = 0;
    _suanFaMonitorInfo._errCount = 0;
    _suanFaMonitorInfo.isNeedRestart = false;

    _watchDogInterval = WATCHDOG_THREAD_INTERVAL;
    _isFileUploading = false;
}

void watchDog_Thread(_c_watchDog *pWatchDog)
{
    do{
       //判断重新竞争是否完成,完成才会启动狗
       if (pWatchDog->isCompetitionFinished())
       {
           if(!pWatchDog->feedDog())
           {
                pWatchDog->reStartMain();
           }
       }
    }while(!pWatchDog->isClose());
}

void _c_watchDog::watchDogMmapOpen(eMmapFileType type)
{
    if (type == eMmapFileTypeAll)
    {
        _xiTongMonitorInfo._mmapStatus = _xiTongMonitorInfo._mmapReader.mmapOpen(XITONG_MMAPFILEPATH);
        _suanFaMonitorInfo._mmapStatus = _suanFaMonitorInfo._mmapReader.mmapOpen(SUANFA_MMAPFILEPATH);
    }
    else if (type == eMmapFileTypeXiTong)
    {
        _xiTongMonitorInfo._mmapStatus = _xiTongMonitorInfo._mmapReader.mmapOpen(XITONG_MMAPFILEPATH);
    }
    else if (type == eMmapFileTypeSuanFa)
    {
        _suanFaMonitorInfo._mmapStatus = _suanFaMonitorInfo._mmapReader.mmapOpen(SUANFA_MMAPFILEPATH);
    }
    else
    {
        printf("Mmap type error!\n");
    }
}

void _c_watchDog::watchDogMmapClose(eMmapFileType type)
{
    if (type == eMmapFileTypeAll)
    {
        _xiTongMonitorInfo._mmapStatus = 0;
        _xiTongMonitorInfo._mmapReader.mmapClose();

        _suanFaMonitorInfo._mmapStatus = 0;
        _suanFaMonitorInfo._mmapReader.mmapClose();
    }
    else if (type == eMmapFileTypeXiTong)
    {
        _xiTongMonitorInfo._mmapStatus = 0;
        _xiTongMonitorInfo._mmapReader.mmapClose();
    }
    else if (type == eMmapFileTypeSuanFa)
    {
        _suanFaMonitorInfo._mmapStatus = 0;
        _suanFaMonitorInfo._mmapReader.mmapClose();
    }
}

bool _c_watchDog::feedDog()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(_watchDogInterval));

    //应用升级的时候狗暂停监测
    if (!_isFileUploading)
    {
        //系统相关
        if (_xiTongMonitorInfo._mmapStatus > 0)
        {
            _xiTongMonitorInfo.data = _xiTongMonitorInfo._mmapReader.getAll();
            int num = _xiTongMonitorInfo.data.num;
            if(_xiTongMonitorInfo._lastNum != num)
            {
               _xiTongMonitorInfo._lastNum = num;
               _xiTongMonitorInfo._errCount = 0;
               _deviceSearch->setXiTongZhuangTai(eYunXingZhuangTaiZhengChang);
            }
            else
            {
                if(_xiTongMonitorInfo._errCount++ > WATCHDOG_RESTARTAPP_INTERVAL)
                {
                    _xiTongMonitorInfo._errCount = 0;
                    _xiTongMonitorInfo._lostAppCount++;
                    _deviceSearch->setXiTongZhuangTai(eYunXingZhuangTaiKaSiOrTuiChu);

                    if (_xiTongMonitorInfo._lostAppCount > 3)//表示已经重启3次
                    {
                        //若是主机 重新竞争 主动放弃主机模式
                        if (_pDisasterRecovery->getHunHeJiaoTongModel() == eHostMode)
                        {
                            processLostApp();
                        }

                        _deviceSearch->setXiTongZhuangTai(eYunXingZhuangTaiWuFaQiDong);
                        _xiTongMonitorInfo._lostAppCount = 0;
                    }

                    _xiTongMonitorInfo.isNeedRestart = true;
                    return false;
                }
                printf("xitong _errCount:%d\n",_xiTongMonitorInfo._errCount);
            }

            _deviceSearch->setXiTongBanBenHao(_xiTongMonitorInfo.data.version);
            _deviceSearch->setXiTongQiDongShiJian(_xiTongMonitorInfo.data.heartBeatTime);

            printf("xitong info:\n");
            printf("n:%d\n",num);
//            printf("v:%s\n",_deviceSearch->getXiTongBanBenHao());
//            printf("t:%s\n",_deviceSearch->getXiTongQiDongShiJian());
        }
        else
        {
            watchDogMmapOpen(eMmapFileTypeXiTong);
            _deviceSearch->setXiTongZhuangTai(eYunXingZhuangTaiMmapYiChang);
        }

        //算法相关
        if (_suanFaMonitorInfo._mmapStatus > 0)
        {
            _suanFaMonitorInfo.data = _suanFaMonitorInfo._mmapReader.getAll();
            int num = _suanFaMonitorInfo.data.num;
            if(_suanFaMonitorInfo._lastNum != num)
            {
               _suanFaMonitorInfo._lastNum = num;
               _suanFaMonitorInfo._errCount = 0;
               _deviceSearch->setSuanFaZhuangTai(eYunXingZhuangTaiZhengChang);
            }
            else
            {
                if(_suanFaMonitorInfo._errCount++ > WATCHDOG_RESTARTAPP_INTERVAL)
                {
                    _suanFaMonitorInfo._errCount = 0;
                    _deviceSearch->setSuanFaZhuangTai(eYunXingZhuangTaiKaSiOrTuiChu);
                    _suanFaMonitorInfo.isNeedRestart = true;
                    return false;
                }
                printf("suanfa _errCount:%d\n",_suanFaMonitorInfo._errCount);
            }

            _deviceSearch->setSuanFaRedisVersion(_suanFaMonitorInfo.data.redis_version);
            _deviceSearch->setSuanFaBanBenHao(_suanFaMonitorInfo.data.alg_version);
            _deviceSearch->setSuanFaQiDongShiJian(_suanFaMonitorInfo.data.start_time);
            _deviceSearch->setSuanFaGpuNum(_suanFaMonitorInfo.data.gpu_num);
            _deviceSearch->setSuanFaGpuType(_suanFaMonitorInfo.data.gpu_type);

            printf("suanfa info:\n");
            printf("n:%d\n",num);
//            printf("v1:%s\n",_deviceSearch->getSuanFaRedisVersion());
//            printf("v2:%s\n",_deviceSearch->getSuanFaBanBenHao());
//            printf("t:%s\n",_deviceSearch->getSuanFaQiDongShiJian());
//            printf("gn:%s\n",_deviceSearch->getSuanFaGpuNum());
//            printf("gt:%s\n",_deviceSearch->getSuanFaGpuType());
        }
        else
        {
            watchDogMmapOpen(eMmapFileTypeSuanFa);
            _deviceSearch->setSuanFaZhuangTai(eYunXingZhuangTaiMmapYiChang);
        }
    }

    return true;
}

void _c_watchDog::watchDogStart()
{
    watchDogMmapOpen();
    new std::thread(watchDog_Thread, this);
}

void _c_watchDog::reStartMain()
{
    printf("reStartMain~~~~~~~~~~~~~~~~~~~~~~!!! 111\n");
    if (_xiTongMonitorInfo.isNeedRestart)
    {
        _xiTongMonitorInfo.isNeedRestart = false;
        startHunHeJiaoTong(_pDisasterRecovery->getHunHeJiaoTongModel());
    }

    if (_suanFaMonitorInfo.isNeedRestart)
    {
        _suanFaMonitorInfo.isNeedRestart = false;
        restartAlg();
    }
    printf("reStartMain~~~~~~~~~~~~~~~~~~~~~~!!! 222\n");
}

void _c_watchDog::processLostApp()
{
    _pDisasterRecovery->processLostApp();
}

//重新竞争阶段,狗暂停监测
bool _c_watchDog::isCompetitionFinished()
{
    return _pDisasterRecovery->isCompetitionFinished();
}

void _c_watchDog::setFileUploadStatus(bool status)
{
    _isFileUploading = status;

    //升级时统一关闭mmap文件,升级完毕后重新打开
    if (status == true)
    {
        _xiTongMonitorInfo._mmapStatus = 0;
        _xiTongMonitorInfo._mmapReader.mmapClose();

        _suanFaMonitorInfo._mmapStatus = 0;
        _suanFaMonitorInfo._mmapReader.mmapClose();
    }
}
