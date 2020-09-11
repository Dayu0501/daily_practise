#include "_c_deviceSearch.h"
#include "interface.h"

#include "_c_disasterRecovery.h"
#include "_c_watchDog.h"

_c_deviceSearch::_c_deviceSearch()
{
    memset(_sheBeiLeiXing, 0, sizeof(_sheBeiLeiXing));
    memset(&_xiTongInfo, 0, sizeof(_xiTongInfo));
    memset(&_suanFaInfo, 0, sizeof(_suanFaInfo));

    setMacDiZhi(getLocalMac().c_str());
    setIpDiZhi(getLocalIp().c_str());
}

void _c_deviceSearch::setSheBeiLeiXingStatus(SheBeiLeiXingStatus status)
{
    _sheBeiLeiXingStatus = status;
}

char* _c_deviceSearch::getSheBeiLeiXing()
{
    memset(_sheBeiLeiXing, 0, sizeof(_sheBeiLeiXing));
    switch (_sheBeiLeiXingStatus)
    {
        case eSheBeiLeiXingFileMiss:
            sprintf(_sheBeiLeiXing, "%s", "找不到配置文件");
        break;
        case eSheBeiLeiXingTypeErr:
            sprintf(_sheBeiLeiXing, "%s", "配置文件设备类型异常");
        break;
        case eSheBeiLeiXingTypeChaYan:
            sprintf(_sheBeiLeiXing, "%s", "查验");
        break;
        case eSheBeiLeiXingTypeCheJian:
            sprintf(_sheBeiLeiXing, "%s", "车检");
        break;
        default:
            sprintf(_sheBeiLeiXing, "%s", "未知类型");
        break;
    }

    return _sheBeiLeiXing;
}

void _c_deviceSearch::setMacDiZhi(const char *mac)
{
    memset(_macDiZhi, 0, sizeof(_macDiZhi));
    sprintf(_macDiZhi, "%s", mac);
}

void _c_deviceSearch::setIpDiZhi(const char *ip)
{
    memset(_ipDiZhi, 0, sizeof(_ipDiZhi));
    sprintf(_ipDiZhi, "%s", ip);
}

char *_c_deviceSearch::getMacDiZhi()
{
    return _macDiZhi;
}

char *_c_deviceSearch::getIpDiZhi()
{
    return _ipDiZhi;
}

void _c_deviceSearch::setXiTongBanBenHao(char *version)
{
    memset(_xiTongInfo.banBenHao, 0, sizeof(_xiTongInfo.banBenHao));
    sprintf(_xiTongInfo.banBenHao, "%s", version);
}

char *_c_deviceSearch::getXiTongBanBenHao()
{
    return _xiTongInfo.banBenHao;
}

void  _c_deviceSearch::setXiTongQiDongShiJian(char *time)
{
    memset(_xiTongInfo.qiDongShiJian, 0, sizeof(_xiTongInfo.qiDongShiJian));
    sprintf(_xiTongInfo.qiDongShiJian, "%s", time);
}

char * _c_deviceSearch::getXiTongQiDongShiJian()
{
    return _xiTongInfo.qiDongShiJian;
}

void _c_deviceSearch::setXiTongZhuCongJi(WorkMode mode)
{
    _xiTongInfo.mode = mode;
}

char *_c_deviceSearch::getXiTongZhuCongJi()
{
    memset(_xiTongInfo.zhuCongJi, 0, sizeof(_xiTongInfo.zhuCongJi));
    switch (_xiTongInfo.mode)
    {
        case eHostMode:
            sprintf(_xiTongInfo.zhuCongJi, "%s", "主机模式");
        break;
        case eClientMode:
            sprintf(_xiTongInfo.zhuCongJi, "%s", "从机模式");
        break;
        default:
            sprintf(_xiTongInfo.zhuCongJi, "%s", "初始化未完成");
        break;
    }

    return _xiTongInfo.zhuCongJi;
}

void _c_deviceSearch::setXiTongZhuangTai(YunXingZhuangTai status)
{
    _xiTongInfo.yunXingStatus = status;
}

void _c_deviceSearch::getZhuangTai(char *zhuangTai, size_t size, YunXingZhuangTai status)
{
    memset(zhuangTai, 0, size);
    switch (status)
    {
        case eYunXingZhuangTaiInit:
            sprintf(zhuangTai, "%s", "应用程序未启动 请稍等");
        break;
        case eYunXingZhuangTaiZhengChang:
            sprintf(zhuangTai, "%s", "正常");
        break;
        case eYunXingZhuangTaiKaSiOrTuiChu:
            sprintf(zhuangTai, "%s", "应用程序异常");
        break;
        case eYunXingZhuangTaiWuFaQiDong:
            sprintf(zhuangTai, "%s", "无法启动应用程序");
        break;
        case eYunXingZhuangTaiUploading:
            sprintf(zhuangTai, "%s", "正在升级程序");
        break;
        case eYunXingZhuangTaiMmapYiChang:
            sprintf(zhuangTai, "%s", "Mmap文件异常");
        break;
        case eYunXingZhuangTaiDengDaiZhuJi:
            sprintf(zhuangTai, "%s", "没有soap权限等待主机");
        break;
        default:
            sprintf(zhuangTai, "%s", "未知状态!");
        break;
    }
}

char *_c_deviceSearch::getXiTongZhuangTai()
{
    getZhuangTai(_xiTongInfo.zhuangTai, sizeof(_xiTongInfo.zhuangTai), _xiTongInfo.yunXingStatus);
    return _xiTongInfo.zhuangTai;
}

void _c_deviceSearch::setFileUploadStatus(bool status)
{
    _isFileUploading = status;
    if (_isFileUploading == true)
    {
        setXiTongZhuangTai(eYunXingZhuangTaiUploading);
    }

    if (_pDisasterRecovery != NULL)
        _pDisasterRecovery->setFileUploadStatus(status);

    if (_pWatchDog != NULL)
        _pWatchDog->setFileUploadStatus(status);
}

bool _c_deviceSearch::getFileUploadStatus()
{
    return _isFileUploading;
}

void _c_deviceSearch::setSuanFaBanBenHao(char *version)
{
    memset(_suanFaInfo.banBenHao, 0, sizeof(_suanFaInfo.banBenHao));
    sprintf(_suanFaInfo.banBenHao, "%s", version);
}

char *_c_deviceSearch::getSuanFaBanBenHao()
{
    return _suanFaInfo.banBenHao;
}

void _c_deviceSearch::setSuanFaRedisVersion(char *rVersion)
{
    memset(_suanFaInfo.redisVersion, 0, sizeof(_suanFaInfo.redisVersion));
    sprintf(_suanFaInfo.redisVersion, "%s", rVersion);
}

char *_c_deviceSearch::getSuanFaRedisVersion()
{
    return _suanFaInfo.redisVersion;
}

void _c_deviceSearch::setSuanFaQiDongShiJian(char *time)
{
    memset(_suanFaInfo.qiDongShiJian, 0, sizeof(_suanFaInfo.qiDongShiJian));
    sprintf(_suanFaInfo.qiDongShiJian, "%s", time);
}

char *_c_deviceSearch::getSuanFaQiDongShiJian()
{
    return _suanFaInfo.qiDongShiJian;
}

void _c_deviceSearch::setSuanFaZhuangTai(YunXingZhuangTai status)
{
    _suanFaInfo.yunXingStatus = status;
}

char *_c_deviceSearch::getSuanFaZhuangTai()
{
    getZhuangTai(_suanFaInfo.zhuangTai, sizeof(_suanFaInfo.zhuangTai), _suanFaInfo.yunXingStatus);
    return _suanFaInfo.zhuangTai;
}

void _c_deviceSearch::setSuanFaGpuNum(char *gpuNum)
{
    memset(_suanFaInfo.gpu_num, 0, sizeof(_suanFaInfo.gpu_num));
    sprintf(_suanFaInfo.gpu_num, "%s", gpuNum);
}

char *_c_deviceSearch::getSuanFaGpuNum()
{
    return _suanFaInfo.gpu_num;
}

void _c_deviceSearch::setSuanFaGpuType(char *gpuType)
{
    memset(_suanFaInfo.gpu_type, 0, sizeof(_suanFaInfo.gpu_type));
    sprintf(_suanFaInfo.gpu_type, "%s", gpuType);
}

char *_c_deviceSearch::getSuanFaGpuType()
{
    return _suanFaInfo.gpu_type;
}

void _c_deviceSearch::setWatchDogBanBenHao(const char *version)
{
    memset(_watchDogBanBenHao, 0, sizeof(_watchDogBanBenHao));
    sprintf(_watchDogBanBenHao, "%s", version);
}

char *_c_deviceSearch::getWatchDogBanBenHao()
{
    return _watchDogBanBenHao;
}

void _c_deviceSearch::updateAppConfigAndStatus()
{
    if (_pDisasterRecovery != NULL)
        _pDisasterRecovery->updateAppConfigAndStatus();
}
