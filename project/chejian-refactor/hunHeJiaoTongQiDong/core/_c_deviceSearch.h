#ifndef _C_DEVICESEARCH_H
#define _C_DEVICESEARCH_H
#include "base/baseInc.h"

class _c_disasterRecovery;
class _c_watchDog;

enum SheBeiLeiXingStatus
{
    eSheBeiLeiXingFileMiss = 0,//配置文件丢失
    eSheBeiLeiXingTypeErr = 1,//类型异常
    eSheBeiLeiXingTypeChaYan = 2,//查验
    eSheBeiLeiXingTypeCheJian = 3,//车检
};

enum YunXingZhuangTai
{
    eYunXingZhuangTaiInit = 0,
    eYunXingZhuangTaiZhengChang = 1,
    eYunXingZhuangTaiKaSiOrTuiChu = 2,  //应用程序卡死或异常退出
    eYunXingZhuangTaiWuFaQiDong = 3,    //多次启动无效
    eYunXingZhuangTaiUploading = 4, //升级应用中
    eYunXingZhuangTaiMmapYiChang = 5, //Mmap文件异常
    eYunXingZhuangTaiDengDaiZhuJi = 6, //没有soap权限等待主机
};

typedef struct _XITONG_INFO
{
    char banBenHao[MAXLEN64];
    char qiDongShiJian[MAXLEN64];
    char zhuCongJi[MAXLEN64];
    char zhuangTai[MAXLEN64];
    WorkMode mode;
    YunXingZhuangTai yunXingStatus;
}XITONG_INFO, *PXITONG_INFO;

typedef struct _SUANFA_INFO
{
    char redisVersion[MAXLEN64];//redis进程的版本
    char banBenHao[MAXLEN64];
    char qiDongShiJian[MAXLEN64];
    char gpu_num[MAXLEN64];
    char gpu_type[MAXLEN64];
    char zhuangTai[MAXLEN64];
    YunXingZhuangTai yunXingStatus;
}SUANFA_INFO, *PSUANFA_INFO;

class _c_deviceSearch
{
public:
    _c_deviceSearch();

    void setDisasterRecovery(_c_disasterRecovery *p) {_pDisasterRecovery = p;}
    void setWatchDog(_c_watchDog *p) {_pWatchDog = p;}

    void setSheBeiLeiXingStatus(SheBeiLeiXingStatus status);
    char *getSheBeiLeiXing();

    void setMacDiZhi(const char *mac);
    char *getMacDiZhi();

    void setIpDiZhi(const char *ip);
    char *getIpDiZhi();

    void setXiTongBanBenHao(char *version);
    char *getXiTongBanBenHao();

    void setXiTongQiDongShiJian(char *time);
    char *getXiTongQiDongShiJian();

    void setXiTongZhuCongJi(WorkMode mode);
    char *getXiTongZhuCongJi();

    void getZhuangTai(char *zhuangTai, size_t size, YunXingZhuangTai status);
    void setXiTongZhuangTai(YunXingZhuangTai status);
    char *getXiTongZhuangTai();

    void setFileUploadStatus(bool status);
    bool getFileUploadStatus();

    void setSuanFaBanBenHao(char *version);
    char *getSuanFaBanBenHao();

    void setSuanFaRedisVersion(char *rVersion);
    char *getSuanFaRedisVersion();

    void setSuanFaQiDongShiJian(char *time);
    char *getSuanFaQiDongShiJian();

    void setSuanFaZhuangTai(YunXingZhuangTai status);
    char *getSuanFaZhuangTai();

    void setSuanFaGpuNum(char *gpuNum);
    char *getSuanFaGpuNum();

    void setSuanFaGpuType(char *gpuType);
    char *getSuanFaGpuType();

    void setWatchDogBanBenHao(const char *version);
    char *getWatchDogBanBenHao();

    void updateAppConfigAndStatus();

private:
    char _watchDogBanBenHao[MAXLEN64];
    char _sheBeiLeiXing[MAXLEN64];
    SheBeiLeiXingStatus _sheBeiLeiXingStatus;
    char _macDiZhi[MAXLEN64];
    char _ipDiZhi[MAXLEN64];

    bool _isFileUploading;
    XITONG_INFO _xiTongInfo;
    SUANFA_INFO _suanFaInfo;

    _c_disasterRecovery *_pDisasterRecovery = NULL;
    _c_watchDog *_pWatchDog = NULL;
};

#endif // _C_DEVICESEARCH_H
