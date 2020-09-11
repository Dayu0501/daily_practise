#ifndef _C_DISASTERRECOVERY_H
#define _C_DISASTERRECOVERY_H
#include "base/baseInc.h"

class _c_deviceSearch;
#define MONITOR_HOST_MSG_INTERVAL_SEC  (3 * 60 * 1000)//监测主机包时间间隔 3分钟
#define HOST_SEND_INTERVAL_SEC    (20 * 1000)//固定20秒发送主机包

#define RANDOM_SEC_RANGE  19 //竞争时间20秒之内
#define RANDOM_MILLSEC_RANGE  9

#define DR_THREAD_SLEEP_INTERVAL_MILLSEC    100

#define APPNAME "hunHeJiaoTong"

enum DisasterRecoveryStatus
{
    eCompetitionUnknown = 0,    //初始状态
    eCompetitionActive = 1,     //主动状态
    eCompetitionPassive = 2,    //被动状态
    eCompetitionHost = 3,       //主机状态
    eCompetitionClient = 4      //从机状态
};

typedef struct _COMPETITION_MSG_CONTENT
{
    std::string ip;
    std::string mac;
    std::string time;
    int sendInterval;
    int deviceType;
    int recvMsgNum;
}COMPETITION_MSG_CONTENT, *PCOMPETITION_MSG_CONTENT;

typedef struct _MONITOR_HOST_MSG
{
    std::string hostIp;
    std::string hostMac;
    std::string time;
    int hostSendInterval;
    int deviceType;
    int monitorHostMsgInterval;
    int monitorHostMsgCountDown;
    bool isMissHost;
}MONITOR_HOST_MSG, *PMONITOR_HOST_MSG;

class _c_disasterRecovery
{
public:
    _c_disasterRecovery(DEVICE_BOOT_CONFIG &bootConfig, _c_deviceSearch *device);
    void startDisasterRecoveryService();
    void startDisasterRecoveryThread();

    //接收分发不同类型的竞争包
    void processDisasterRecoveryMsg();
    void processRecvCompetitionInitial(PPACKET packet);
    void processRecvCompetitionComplete(PPACKET packet);
    void processRecvCompetitionRestart(PPACKET packet);
    //发送竞争包
    void sendCompetitionPacket(int type, bool isImmediate);
    //解析竞争包
    bool getCompetitionPacketContent(PPACKET packet, COMPETITION_MSG_CONTENT &content);

    //设置竞争时间
    void generateSendInterval();

    //重启竞争
    void restartCompetition();

    //启动应用程序
    bool startApp(WorkMode mode);

    //处理应用程序无法启动
    void processLostApp();

    //工具更改配置文件后 做相应的处理 重启应用程序以及算法程序
    void updateAppConfigAndStatus();

    //设置升级状态
    void setFileUploadStatus(bool status);

    //获取主从及状态
    WorkMode getHunHeJiaoTongModel() {return _hunHeJiaoTongModel;}

    //判断竞争是否完成
    bool isCompetitionFinished();

    //记录host相关信息
    void setHostInfo(COMPETITION_MSG_CONTENT &content);

    bool isClose(){return false;}
public:
    //竞争状态
    DisasterRecoveryStatus _disasterRecoveryStatus;

    //本机mac
    std::string _localMac;
    std::string _localIp;

    //线程运行间隔
    int _threadSleepInterval;

    //发包相关的参数
    int _sendInterval;
    int _sendCountDown;
    int _sendMsgNum;

    //如果为false, watchdog模块停止监测,第一次启动或者重新竞争时会设置该值
    bool _appStarted = false;

    //升级应用标记
    bool _isFileUploading = false;

    //主从模式
    WorkMode _hunHeJiaoTongModel = eInitMode;

    //查验或车检
    DeviceType _deviceType;
    //是否有soap权限 没有权限不竞争主机
    SoapQuanXian _soapQuanXian;

    //监测主机信息
    MONITOR_HOST_MSG _monitorHostMsg;

    //竞争时接收的消息
    std::vector<COMPETITION_MSG_CONTENT> _recvCompetitionMsg;

    _c_deviceSearch *_deviceSearch;

private:
    std::thread *_pDisasterRecoveryThread;
};

void processDisasterRecoveryMsg(_c_disasterRecovery *pDisasterRecovery);
void checkDisasterRecoveryStatus(_c_disasterRecovery *pDisasterRecovery);

#endif // _C_DISASTERRECOVERY_H
