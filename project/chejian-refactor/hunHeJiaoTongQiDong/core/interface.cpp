#include "interface.h"
#include "base/json/json.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <ctime>

std::string getLocalIp()
{
    int                 sockfd;
    struct sockaddr_in  sin;
    struct ifreq        ifr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket error");
        return "0.0.0.0";
    }
    strncpy(ifr.ifr_name, "enp3s0", IFNAMSIZ);      //Interface name

    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == 0) {    //SIOCGIFADDR 获取interface address
        memcpy(&sin, &ifr.ifr_addr, sizeof(ifr.ifr_addr));
        return inet_ntoa(sin.sin_addr);
    }
    return "0.0.0.0";
}

std::string getLocalMac()
{
    char mac[32]={0};
   struct ifreq ifreq;    //ifreq结构体常用来配置和获取ip地址
   int sock;

   if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0)
   {
       perror ("socket");
       return "00:00:00:00:00:00";
   }
   strcpy (ifreq.ifr_name, "enp3s0");    //Currently, only get eth0

   if (ioctl (sock, SIOCGIFHWADDR, &ifreq) < 0)
   {
       perror ("ioctl");
       return "00:00:00:00:00:00";
   }

   sprintf (mac, "%02X:%02X:%02X:%02X:%02X:%02X", (unsigned char) ifreq.ifr_hwaddr.sa_data[0], (unsigned char) ifreq.ifr_hwaddr.sa_data[1], (unsigned char) ifreq.ifr_hwaddr.sa_data[2], (unsigned char) ifreq.ifr_hwaddr.sa_data[3], (unsigned char) ifreq.ifr_hwaddr.sa_data[4], (unsigned char) ifreq.ifr_hwaddr.sa_data[5]);

   return mac;
}

std::string getDeviceReturnJson(_c_deviceSearch *pDeviceSearch)
{
    Json::Value root;
    root["sheBeiLeiXing"] = pDeviceSearch->getSheBeiLeiXing();
    root["macDiZhi"] = pDeviceSearch->getMacDiZhi();
    root["ipDiZhi"] = pDeviceSearch->getIpDiZhi();

    root["banBenHao"] = pDeviceSearch->getXiTongBanBenHao();
    root["qiDongShiJian"] = pDeviceSearch->getXiTongQiDongShiJian();
    root["zhuCongJi"] = pDeviceSearch->getXiTongZhuCongJi();
    root["zhuangTai"] = pDeviceSearch->getXiTongZhuangTai();

    root["suanFaRedisVersion"] = pDeviceSearch->getSuanFaRedisVersion();
    root["suanFaBanBenHao"] = pDeviceSearch->getSuanFaBanBenHao();
    root["suanFaQiDongShiJian"] = pDeviceSearch->getSuanFaQiDongShiJian();
    root["suanFaGpuNum"] = pDeviceSearch->getSuanFaGpuNum();
    root["suanFaGpuType"] = pDeviceSearch->getSuanFaGpuType();
    root["suanFaZhuangTai"] = pDeviceSearch->getSuanFaZhuangTai();
    root["watchDogBanBenHao"] = pDeviceSearch->getWatchDogBanBenHao();
    return root.toStyledString();
}

int str2Int(std::string str)
{
    if(str.empty())
    {
        return 0;
    }

    unsigned int strSize = str.size();
    const char *pStr = str.c_str();
    for(unsigned int i = 0; i < strSize; i++)
    {
        if(pStr[i] < 48 && pStr[i] > 57)
        {
            if(pStr[i] != '-')
            {
                return 0;
            }
        }
    }

    return stoi(str);
}

void setDeviceConfigItem(std::string &str, const char* name)
{
    bool ret = false;
    std::ifstream fin;
    std::string algconfigpath = "/opt/vehicle/program/CheJianConfig/deviceConfig.json";

    std::string cityCode;
    int deviceType = 0;

    Json::Value  rRoot;
    Json::Reader reader;

    fin.open(algconfigpath);
    if (fin.is_open()) {

        if (reader.parse(fin, rRoot, false))
        {
            ret = true;
        }
    }
    fin.close();

    if (ret)
    {
        rRoot[name] = str;
        std::ofstream ofs;
        ofs.open(algconfigpath);
        ofs << rRoot.toStyledString();
        ofs.close();
    }
}

bool setDeviceConfig(char *pMac,PDEVICE_CONFIG pDeviceConfig)
{
    char *configPath = "/opt/vehicle/program/CheJianConfig/deviceConfig.json";

    if(strstr(pDeviceConfig->macList, pMac) != NULL)
    {
        Json::Value root;
        root["cityCode"] = pDeviceConfig->cityCode;
        root["deviceType"] = pDeviceConfig->deviceType;
        root["soapQuanXian"] = pDeviceConfig->soapQuanXian;

        if((access(configPath, F_OK)) < 0)
        {
            root["redisIp"] = "";
        }
        else
        {
            DEVICE_BOOT_CONFIG config;
            loadDeviceBootConfig(&config);
            root["redisIp"] = config.redisIp;
        }

        std::ofstream ofs;
        ofs.open("/opt/vehicle/program/CheJianConfig/deviceConfig.json");
        ofs << root.toStyledString();
        ofs.close();

        return  true;
    }
    return false;
}

bool loadDeviceBootConfig(PDEVICE_BOOT_CONFIG pBootConfig)
{
    bool ret = false;
    std::ifstream fin;
    std::string algconfigpath = "/opt/vehicle/program/CheJianConfig/deviceConfig.json";

    fin.open(algconfigpath);
    if (fin.is_open()) {
        Json::Value  root;
        Json::Reader reader;
        if (reader.parse(fin, root, false))
        {
            if (!root["cityCode"].empty()) {
                pBootConfig->cityType = (CityType)atoi(root["cityCode"].asString().c_str());
            } else {
                pBootConfig->cityType = eUNKONW;
            }

            if (!root["deviceType"].empty()) {
                pBootConfig->deviceType = (DeviceType)root["deviceType"].asInt();
            } else {
                pBootConfig->deviceType = eCeShi;
            }

            if (!root["deviceType"].empty()) {
                pBootConfig->soapQuanXian = (SoapQuanXian)root["soapQuanXian"].asInt();
            } else {
                pBootConfig->soapQuanXian = eSoapQuanXianMeiYou;
            }

            if (!root["redisIp"].empty()) {
                pBootConfig->redisIp = root["redisIp"].asString().c_str();
            } else {
                pBootConfig->redisIp = "";
            }

            ret = true;
        }
    }
    fin.close();

    return ret;
}

static unsigned short const wCRC16Table[256] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 };

void Crc16(const uint8_t* pDataIn, int iLenIn, uint16_t* pCRCOut)
{
    uint16_t wResult = 0;
    uint16_t wTableNo = 0;
    int i = 0;
    for (i = 0; i < iLenIn; i++)
    {
        wTableNo = ((wResult & 0xff) ^ (pDataIn[i] & 0xff));
        wResult = ((wResult >> 8) & 0xff) ^ wCRC16Table[wTableNo];
    }

    *pCRCOut = wResult;
}

bool startHunHeJiaoTong(WorkMode mode)
{
    if((access("/opt/vehicle/program/programPath/start.sh", F_OK)) < 0)
    {
        printf("not find /opt/vehicle/program/programPath/start.sh\n");
        return false;
    }

    if(chdir("/opt/vehicle/program/programPath") < 0)
    {
        perror("chdir");
    }

    system("chmod 0777 start.sh");

    std::string startCmd = "./start.sh";
    if (mode == eHostMode)
    {
        startCmd += " &";
    }
    else if (mode == eClientMode)
    {
        startCmd += " -client &";
    }
    else {
        return false;
    }
    printf("%s\n", startCmd.c_str());

//    system("./start.sh &");
    system(startCmd.c_str());

    //后续添加看进程是否正常启动
    return true;
}

bool restartAlg()
{
    //暂时默认算法自己的狗起着
    if((access("/opt/vehicle/algserver/scripts/kill_chejian_alg.sh", F_OK)) < 0)
    {
        printf("not find /opt/vehicle/algserver/scripts/kill_chejian_alg.sh \n");
        return false;
    }

    if(chdir("/opt/vehicle/algserver/scripts") < 0)
    {
        perror("chdir");
    }

    system("chmod 0777 kill_chejian_alg.sh");

    system("./kill_chejian_alg.sh");

    printf("./kill_chejian_alg.sh");
    return true;
}

int checkAppIsStarted(const char* psProcessName)
{
    int state = -1;

    FILE *fstream=NULL;
    char buff[1024] = {0};

    //用空格，是去掉类似dah_main的噪声
    sprintf(buff, "ps -A | grep \" %s\"", psProcessName);
    if (NULL==(fstream=popen(buff, "r")))
    {
        return -1;
    }

    while (NULL != fgets(buff, sizeof(buff), fstream))
    {
        if (strlen(buff) <= 0)
        {
            break;
        }

        char* psHead = strstr(buff, psProcessName);
        if (psHead == NULL)
        {
            continue;
        }

        int pos = strlen(psHead)-1;
        if (psHead[pos] == '\n')
        {
            psHead[pos] = 0;
        }

        printf("pid name:%s\n", psHead);
        //GH_LOG_INFO("|||%s|||", psHead);
        if (!strcmp(psHead, psProcessName))
        {
            state = 0;
            break;
        }
    }

    pclose(fstream);

    return state;
}

std::string getCurTime()
{
    std::string nowTime;
    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);
    char tmpArray[64] = { 0 };
    sprintf(tmpArray, "%04d-%02d-%02d %02d:%02d:%02d", st->tm_year+1900,st->tm_mon + 1, st->tm_mday, st->tm_hour, st->tm_min, st->tm_sec);

    nowTime = tmpArray;

    return nowTime;
}

void syncSystemTime(const char *time)
{
    //同步成主机时间
    system("timedatectl set-ntp false");
    char syncTimeCmd[128] = {0};
    sprintf(syncTimeCmd, "date -s '%s'", time);
    system(syncTimeCmd);
    printf("syncTimeCmd : %s\n", syncTimeCmd);
}
