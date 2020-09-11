#include "_c_disasterRecovery.h"
#include "base/dataCenter.h"
#include "interface.h"
#include "_c_deviceSearch.h"
#include "base/json/json.h"

#include <algorithm>
#include <regex>
#include <stdlib.h>
#include <time.h>

void processDisasterRecoveryMsg(_c_disasterRecovery *pDisasterRecovery)
{
    unsigned int queueSize = getDisasterRecoveryQueueSize();

    if (queueSize > 0)
    {
        PPACKET pPacket = getDisasterRecoveryMsgFromQueue();
        switch (pPacket->head.type)
        {
            case eCompetitionInitial:
            {
                pDisasterRecovery->processRecvCompetitionInitial(pPacket);
            }
            break;

            case eCompetitionComplete:
            {
                pDisasterRecovery->processRecvCompetitionComplete(pPacket);
            }
            break;

            case eCompetitionRestart:
            {
                pDisasterRecovery->processRecvCompetitionRestart(pPacket);
            }
            break;

            default:
            break;
        }

        delete pPacket;
    }
}

void checkDisasterRecoveryStatus(_c_disasterRecovery *pDisasterRecovery)
{
    switch (pDisasterRecovery->_disasterRecoveryStatus)
    {
        case eCompetitionUnknown:
        case eCompetitionActive:
        {
            //判断当前机器是否有soap请求权限
            if (pDisasterRecovery->_soapQuanXian == eSoapQuanXianMeiYou)
            {
                //停止发送
                pDisasterRecovery->_sendInterval = -1;
                //切换状态
                pDisasterRecovery->_disasterRecoveryStatus = eCompetitionPassive;

                if (pDisasterRecovery->_deviceSearch != NULL)
                {
                    pDisasterRecovery->_deviceSearch->setXiTongZhuangTai(eYunXingZhuangTaiDengDaiZhuJi);
                    pDisasterRecovery->_deviceSearch->setSuanFaZhuangTai(eYunXingZhuangTaiDengDaiZhuJi);
                }
                printf("no soap quanxian! wait for host!\n");
            }
            else if(pDisasterRecovery->_soapQuanXian == eSoapQuanXianYou)
            {
                //sendInterval < 0 表示不向外发送竞争消息
                if (pDisasterRecovery->_sendInterval > 0)
                {
                    if (pDisasterRecovery->_sendCountDown == 0)
                    {
                        //能持续发送,则逐步变成eCompetitionHost
                        if (pDisasterRecovery->_sendMsgNum == 2)
                        {
                            if (pDisasterRecovery->_disasterRecoveryStatus == eCompetitionUnknown)
                            {
                                printf("%s %d convert to eCompetitionActive\n", __func__, __LINE__);
                                pDisasterRecovery->_disasterRecoveryStatus = eCompetitionActive;
                                pDisasterRecovery->_sendMsgNum = 0;
                            }
                            else
                            {
                                printf("%s %d convert to eCompetitionHost\n", __func__, __LINE__);
                                pDisasterRecovery->_disasterRecoveryStatus = eCompetitionHost;
                                pDisasterRecovery->_sendMsgNum = 0;
                                //切换成host之后 修改发送间隔
                                pDisasterRecovery->_sendInterval = HOST_SEND_INTERVAL_SEC / pDisasterRecovery->_threadSleepInterval;
                            }
                        }
                        int type;
                        if (pDisasterRecovery->_disasterRecoveryStatus == eCompetitionUnknown || pDisasterRecovery->_disasterRecoveryStatus == eCompetitionActive)
                            type = eCompetitionInitial;
                        else
                            type = eCompetitionComplete;

                        pDisasterRecovery->sendCompetitionPacket(type, false);
                        printf("%s %d sendpacket:%d status:%d\n", __func__, __LINE__, pDisasterRecovery->_sendMsgNum, pDisasterRecovery->_disasterRecoveryStatus);
                    }
                    else
                    {
                        pDisasterRecovery->_sendCountDown--;
                    }
                }
            }
            else
            {
                printf("eSoapQuanXian Err!\n");
            }
        }
        break;

        //变成host之后就持续按这个间隔来发送消息
        case eCompetitionHost:
        {
            if (pDisasterRecovery->_deviceSearch != NULL)
                pDisasterRecovery->_deviceSearch->setXiTongZhuCongJi(eHostMode);
            //如果进入应用升级流程,主机暂停发送主机包
            if (!pDisasterRecovery->_isFileUploading)
            {
                if (pDisasterRecovery->_sendInterval > 0)
                {
                    if (pDisasterRecovery->_sendCountDown == 0)
                    {
                        printf("%s %d im eCompetitionHost deviceType:%d\n", __func__, __LINE__ , pDisasterRecovery->_deviceType);

                        int type = eCompetitionComplete;
                        pDisasterRecovery->sendCompetitionPacket(type, false);
                    }
                    else
                    {
                        pDisasterRecovery->_sendCountDown--;
                    }
                }

                //启动app
                if (!pDisasterRecovery->_appStarted)
                {
                    pDisasterRecovery->_hunHeJiaoTongModel = eHostMode;
                    pDisasterRecovery->_appStarted = pDisasterRecovery->startApp(eHostMode);
                    setDeviceConfigItem(pDisasterRecovery->_localIp, "redisIp");
                    restartAlg();
                    printf("%s %d host start app\n", __func__, __LINE__);
                }
            }
        }
        break;

        //变成client后,就开始监听主机的发送包,如果收到包monitorHostMsgCnt会重置。不然一直递减直到为0，表示丢失主机。
        case eCompetitionClient:
        {
            if (pDisasterRecovery->_deviceSearch != NULL)
                pDisasterRecovery->_deviceSearch->setXiTongZhuCongJi(eClientMode);

            //如果进入应用升级流程,从机暂停监控主机包
            if (!pDisasterRecovery->_isFileUploading)
            {
                //启动app
                if (!pDisasterRecovery->_appStarted)
                {
                    pDisasterRecovery->_hunHeJiaoTongModel = eClientMode;
                    pDisasterRecovery->_appStarted = pDisasterRecovery->startApp(eClientMode);
                    setDeviceConfigItem(pDisasterRecovery->_monitorHostMsg.hostIp, "redisIp");
                    restartAlg();
                    printf("%s %d client start app\n", __func__, __LINE__);
                }

                //监测主机包
                if (!pDisasterRecovery->_monitorHostMsg.isMissHost)
                {
                    if (pDisasterRecovery->_monitorHostMsg.monitorHostMsgCountDown == 0)
                    {
                        printf("%s %d missHost\n", __func__, __LINE__);
                        pDisasterRecovery->_monitorHostMsg.isMissHost = true;
                        pDisasterRecovery->restartCompetition();
                    }
                    else
                    {
                        pDisasterRecovery->_monitorHostMsg.monitorHostMsgCountDown--;
                    }
                }
                else
                {
                    printf("%s %d miss host!\n", __func__, __LINE__);
                }
            }
        }
        break;

        default:
        break;
    }
}

void disasterRecoveryThread(_c_disasterRecovery *pDisasterRecovery)
{
    do{
        processDisasterRecoveryMsg(pDisasterRecovery);
        checkDisasterRecoveryStatus(pDisasterRecovery);
        std::this_thread::sleep_for(std::chrono::milliseconds(pDisasterRecovery->_threadSleepInterval));
    }while(!pDisasterRecovery->isClose());
}

_c_disasterRecovery::_c_disasterRecovery(DEVICE_BOOT_CONFIG &bootConfig, _c_deviceSearch *device)
{
    _disasterRecoveryStatus = eCompetitionUnknown;

    _deviceType = bootConfig.deviceType;
    _soapQuanXian = bootConfig.soapQuanXian;

    _deviceSearch = device;

    //获取本机信息
    _localIp = getLocalIp();
    _localMac = getLocalMac();

    //根据mac生成随机数种子
    uint16_t crc16Key;
    Crc16((const uint8_t *)_localMac.data(), _localMac.size(), (uint16_t *)&crc16Key);
    srand(crc16Key);

    _threadSleepInterval = DR_THREAD_SLEEP_INTERVAL_MILLSEC;

    //竞争相关参数
    generateSendInterval();
    _sendCountDown = _sendInterval;
    _sendMsgNum = 0;

    //监控主机相关参数
    _monitorHostMsg.monitorHostMsgInterval = MONITOR_HOST_MSG_INTERVAL_SEC / _threadSleepInterval;
    _monitorHostMsg.isMissHost = false;
    _monitorHostMsg.monitorHostMsgCountDown = _monitorHostMsg.monitorHostMsgInterval;

    _appStarted = false;
    _isFileUploading = false;
}

void _c_disasterRecovery::startDisasterRecoveryService()
{
    startDisasterRecoveryThread();
}

void _c_disasterRecovery::startDisasterRecoveryThread()
{
    _pDisasterRecoveryThread = new std::thread(disasterRecoveryThread, this);
}

void _c_disasterRecovery::generateSendInterval()
{
    int sec = rand() % RANDOM_SEC_RANGE;
    int millSec = rand() % RANDOM_MILLSEC_RANGE;
    _sendInterval = (sec * 1000 + millSec * 100) / _threadSleepInterval;//以100毫秒为单位
    printf("%s sendInterval:%d\n", __func__, _sendInterval);
}

//只处理接收到的消息,根据消息设置相关状态
void _c_disasterRecovery::processRecvCompetitionInitial(PPACKET packet)
{
    printf("%s %d\n", __func__, __LINE__);
    COMPETITION_MSG_CONTENT content;
    if (!getCompetitionPacketContent(packet, content))
        return;

    //只要消息正确 就保存
    if (content.deviceType == _deviceType)
    {
        bool isNeedPush = true;
        for (unsigned int i = 0; i < _recvCompetitionMsg.size(); i++)
        {
            if (content.mac == _recvCompetitionMsg[i].mac)
            {
                _recvCompetitionMsg[i].recvMsgNum++;//增加添加记录
                isNeedPush = false;
                break;
            }
        }

        if (isNeedPush)
            _recvCompetitionMsg.push_back(content);
    }
    else
    {
        return;
    }

    switch (_disasterRecoveryStatus)
    {
        case eCompetitionUnknown://初始状态时收到,说明自己的interval比较慢,判断一下,并且保存数据,停止发送,切换一下状态
        case eCompetitionActive: //打断的情况,如果比自己慢无视
        {
            if (content.sendInterval < _sendInterval)
            {
                //停止发送
                _sendInterval = -1;
                //切换状态
                _disasterRecoveryStatus = eCompetitionPassive;
                printf("%s %d convert to eCompetitionPassive\n", __func__, __LINE__);
            }
            else if(content.sendInterval == _sendInterval)//如果是相等的情况, 则重置
            {
                printf("%s %d equal\n", __func__, __LINE__);
                generateSendInterval();
                _sendCountDown = _sendInterval;
                _sendMsgNum = 0;
                _disasterRecoveryStatus = eCompetitionUnknown;
            }
            else
            {
                //新竞争者 打断的情况 无视
                printf("%s %d interrupt\n", __func__, __LINE__);
            }
        }
        break;

        case eCompetitionPassive://被动状态 统计第几次收到 某一条累计收到2次 则切为从机状态
        {
            for (unsigned int i = 0; i < _recvCompetitionMsg.size(); i++)
            {
                printf("%s %d mac:%s recvNum:%d\n", __func__, __LINE__,  _recvCompetitionMsg[i].mac.c_str(),  _recvCompetitionMsg[i].recvMsgNum);
                if (content.mac == _recvCompetitionMsg[i].mac)
                {
                    _recvCompetitionMsg[i].recvMsgNum++;//某条消息收到2次,则切为从机模式
                    if (_recvCompetitionMsg[i].recvMsgNum >= 2)
                    {
                        _disasterRecoveryStatus = eCompetitionClient;
                        printf("%s %d convert to eCompetitionClient\n", __func__, __LINE__);
                        setHostInfo(_recvCompetitionMsg[i]);
                    }
                }
            }
        }
        break;

        case eCompetitionHost://主机状态 还收到竞争包 标明是新机器 立马回主机包
        {
            int type = eCompetitionComplete;
            sendCompetitionPacket(type, true);
        }
        break;

        default:
        break;
    }
}

void _c_disasterRecovery::processRecvCompetitionComplete(PPACKET packet)
{
    printf("%s %d\n", __func__, __LINE__);
    COMPETITION_MSG_CONTENT content;
    if (!getCompetitionPacketContent(packet, content))
        return;

    if (content.deviceType != _deviceType)
        return;

    switch (_disasterRecoveryStatus)
    {
        //一旦收到主机包 则无条件切换到从机状态
        case eCompetitionUnknown:
        case eCompetitionPassive:
        case eCompetitionActive:
        {
            //停止发送
            _sendInterval = -1;
            _disasterRecoveryStatus = eCompetitionClient;
            setHostInfo(content);
        }
        break;

        //这个阶段从机就负责监测主机的发包状况即可
        case eCompetitionClient:
        {
            //收到主机的信息则重置倒计时
            if (_monitorHostMsg.hostMac == content.mac)
            {
                _monitorHostMsg.monitorHostMsgCountDown = _monitorHostMsg.monitorHostMsgInterval;
            }
        }
        break;

        default:
        break;
    }
}

void _c_disasterRecovery::processRecvCompetitionRestart(PPACKET packet)
{
    printf("%s %d\n", __func__, __LINE__);
    COMPETITION_MSG_CONTENT content;
    if (!getCompetitionPacketContent(packet, content))
        return;

    if (content.deviceType != _deviceType)
        return;

    switch (_disasterRecoveryStatus)
    {
        //所有状态收到这个包都开始重新竞争
        case eCompetitionUnknown:
        case eCompetitionPassive:
        case eCompetitionActive:
        case eCompetitionClient:
        case eCompetitionHost:
        {
            restartCompetition();
        }
        break;

        default:
        break;
    }
}

void _c_disasterRecovery::restartCompetition()
{
    printf("%s %d\n", __func__, __LINE__);

    _sendMsgNum = 0;

    _monitorHostMsg.hostMac.clear();
    _monitorHostMsg.isMissHost = false;
    _monitorHostMsg.monitorHostMsgCountDown = _monitorHostMsg.monitorHostMsgInterval;

    _appStarted = false;
    _recvCompetitionMsg.clear();

    generateSendInterval();
    _disasterRecoveryStatus = eCompetitionUnknown;

    DEVICE_BOOT_CONFIG bootConfig;
    if (loadDeviceBootConfig(&bootConfig))
    {
        _deviceType = bootConfig.deviceType;
        if (_deviceType != eCheJian && _deviceType != eChaYan)
        {
            if (_deviceSearch != NULL)
                _deviceSearch->setSheBeiLeiXingStatus(eSheBeiLeiXingTypeErr);
        }
        _soapQuanXian = bootConfig.soapQuanXian;
    }
    else
    {
        if (_deviceSearch != NULL)
            _deviceSearch->setSheBeiLeiXingStatus(eSheBeiLeiXingFileMiss);
    }

    if (_deviceSearch != NULL)
        _deviceSearch->setXiTongZhuCongJi(eInitMode);
}

void _c_disasterRecovery::sendCompetitionPacket(int type, bool isImmediate)
{
    char returnSendBuf[PACKETCONTECTMAXLEN] = {0};
    //ip;mac;time;sendInterval;deviceid
    std::string time = getCurTime();
    sprintf(returnSendBuf,"%s;%s;%s;%d;%d", _localIp.c_str(), _localMac.c_str(), time.c_str(), _sendInterval, (int)_deviceType);
    packagePacket(type, returnSendBuf, strlen(returnSendBuf));
    if (!isImmediate)
    {
        _sendCountDown = _sendInterval;//重置发送竞争包的时间
        _sendMsgNum++;
    }
}

bool _c_disasterRecovery::getCompetitionPacketContent(PPACKET packet, COMPETITION_MSG_CONTENT &content)
{
    bool ret = false;

    std::vector<std::string> splitVector;
    std::string packetContent(packet->buf, packet->head.nLen);
    printf("%s %s\n", __func__, packetContent.c_str());

    std::regex reg(";");
    std::sregex_token_iterator begin(packetContent.begin(), packetContent.end(), reg ,-1), end;
    std::copy(begin, end, std::back_inserter(splitVector));

    if (splitVector.size() == 5)
    {
        content.ip = splitVector[0];
        content.mac = splitVector[1];
        content.time = splitVector[2];
        content.sendInterval = str2Int(splitVector[3]);
        content.deviceType = str2Int(splitVector[4]);
        content.recvMsgNum = 0;
        printf("%s ip:%s mac:%s time:%s interval:%d devType:%d\n", __func__, content.ip.c_str(), content.mac.c_str(), content.time.c_str(), content.sendInterval, content.deviceType);
        ret = true;
    }
    else {
        printf("%s msg format error! check watchDog version!\n", __func__);
    }

    return ret;
}

bool _c_disasterRecovery::startApp(WorkMode mode)
{
    return startHunHeJiaoTong(mode);
}

//这种情况一般该机器有某些异常，放弃主动竞争主机
void _c_disasterRecovery::processLostApp()
{
    printf("processLostApp!");
    int type = eCompetitionRestart;
    sendCompetitionPacket(type, true);

    restartCompetition();

    //直接切换到从机状态, 不参与竞争
    _sendInterval = -1;
    _disasterRecoveryStatus = eCompetitionPassive;
}

void _c_disasterRecovery::setFileUploadStatus(bool status)
{
    _isFileUploading = status;
}

bool _c_disasterRecovery::isCompetitionFinished()
{
    return _appStarted;
}

void _c_disasterRecovery::setHostInfo(COMPETITION_MSG_CONTENT &content)
{
    printf("%s %d\n", __func__, __LINE__);
    _monitorHostMsg.hostIp = content.ip;
    _monitorHostMsg.hostMac = content.mac;
    _monitorHostMsg.time = content.time;
    _monitorHostMsg.hostSendInterval = content.sendInterval;
    _monitorHostMsg.deviceType = content.deviceType;

    syncSystemTime(content.time.c_str());
}

void _c_disasterRecovery::updateAppConfigAndStatus()
{
    printf("%s %d %d %d\n", __func__, __LINE__,_appStarted, _hunHeJiaoTongModel);
    //如果竞争已经完成了,那个就只重启各自应用 ,如果竞争没有完成,说明是第一次启动, 继续后续流程即可
    if (_appStarted == true)
    {
        startHunHeJiaoTong(_hunHeJiaoTongModel);
        restartAlg();
    }
}
