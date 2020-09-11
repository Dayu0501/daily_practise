#include "core/interface.h"
#include "core/fileUpload/fileUpload.h"
#include "base/dataCenter.h"
#include "core/_c_disasterRecovery.h"
#include "core/_c_deviceSearch.h"

_c_deviceSearch *_pDeviceSearch = NULL;
int udpRecvCallBack(char *pBuf)
{
    PPACKETHEAD pHead = (PPACKETHEAD)pBuf;

    bool needReturn = false;

    unsigned int len = 0;
    int type = eUnknown;
    char returnSendBuf[PACKETCONTECTMAXLEN] = {0};

    printf("udpRecvCallBack [%d]\n",pHead->type);

    switch (pHead->type)
    {
        case eDeviceSearch:
        {
            printf("eDeviceSearch\n");
            if (_pDeviceSearch != NULL)
            {
                std::string content = getDeviceReturnJson(_pDeviceSearch);
                sprintf(returnSendBuf,"%s\n",content.c_str());
                type = eDeviceSearch + eReturn;
                len = content.size();
                needReturn = true;
            }
        }
        break;
        case eUpdateStart:
        {
            printf("eUpdateStart\n");
            _pDeviceSearch->setFileUploadStatus(true);
            upload_startRecvEvent((char *)getLocalMac().c_str(),(PUPDATE_FILE_HEAD)(pBuf+sizeof(PACKETHEAD)), (void *)_pDeviceSearch);
        }
        break;
        case eUpdatePacket:case eUpdatePacketRepeat:
        {
            printf("eUpdatePacket\n");
            upload_saveRecvPacket((PUPDATE_FILE_PACKET)(pBuf+sizeof(PACKETHEAD)));
        }
        break;
        case eCompetitionInitial:
        case eCompetitionComplete:
        case eCompetitionRestart:
        {
            PPACKET pPacket = new PACKET;
            memcpy(pPacket, pBuf, sizeof(PACKET));
            pushDisasterRecoveryQueue(pPacket);
        }
        break;
		case eConfigSet:
        {
            printf("eUpdatePacket\n");
            setDeviceConfig((char *)getLocalMac().c_str(),(PDEVICE_CONFIG)(pBuf+sizeof(PACKETHEAD)));
            _pDeviceSearch->updateAppConfigAndStatus();
        }
        break;
        default:
            needReturn = false;
        break;
    }

    if(needReturn)
    {
        packagePacket(type, returnSendBuf, len);
    }

    return 1;
}

#define COMPILE_DATE    __DATE__
#define COMPILE_TIME    __TIME__
const std::string VERSION = "0.0.1";

void printfVersion()
{
    printf("COMPILE DATE[%s] ",COMPILE_DATE);
    printf("COMPILE TIME[%s] ",COMPILE_TIME);
    printf("VERSION:[%s]\n",VERSION.c_str());
}

int main()
{
    _c_deviceSearch deviceSearch;
    _pDeviceSearch = &deviceSearch;

    printfVersion();
    deviceSearch.setWatchDogBanBenHao(VERSION.c_str());

    _c_udpService udpService;
    if (!udpService.startUdpService(udpRecvCallBack))
    {
        printf("udp init error! exit\n ");
        exit(1);
    }

    DEVICE_BOOT_CONFIG bootConfig;
    while (true)
    {
        if (loadDeviceBootConfig(&bootConfig))
        {
            if (bootConfig.deviceType == eCheJian)
            {
                deviceSearch.setSheBeiLeiXingStatus(eSheBeiLeiXingTypeCheJian);
                break;
            }
            else if (bootConfig.deviceType == eChaYan)
            {
                deviceSearch.setSheBeiLeiXingStatus(eSheBeiLeiXingTypeChaYan);
                break;
            }
            else
            {
                deviceSearch.setSheBeiLeiXingStatus(eSheBeiLeiXingTypeErr);
                printf("please confirm deviceConfig! deviceType is error!!\n");
            }
        }
        else
        {
            deviceSearch.setSheBeiLeiXingStatus(eSheBeiLeiXingFileMiss);
            printf("not find /opt/vehicle/program/CheJianConfig/deviceConfig.json\n");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }

    printf("deviceType:%d\n", bootConfig.deviceType);
    _c_disasterRecovery disasterRecovery(bootConfig, &deviceSearch);
    deviceSearch.setDisasterRecovery(&disasterRecovery);

    disasterRecovery.startDisasterRecoveryService();

    _c_watchDog watchDog(&disasterRecovery, &deviceSearch);
    deviceSearch.setWatchDog(&watchDog);

    while (!disasterRecovery.isCompetitionFinished())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }

    watchDog.watchDogStart();

    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }

    return 1;
}

