#ifndef _BASEINC_H
#define _BASEINC_H
#include <stdio.h>
#include <vector>
#include <thread>
#include <string>
#include <string.h>

#define UNUSED(x) (void)x
#define MAXLEN64 64
#define MAXLEN128 128

#ifdef _WIN32
#ifdef __cplusplus
#define EXTERN_C    extern "C"
#else
#define EXTERN_C    extern
#endif
#define API _declspec(dllexport)
#else
#define API
#endif

#ifdef _WIN32
typedef void(__stdcall *MsgCallBack)(int type, char *pBuf);
typedef void(__stdcall *DeviceInfoCallBack)(char *sheBeiLeiXing, char *macDiZhi, char *ipDiZhi, char *banBenHao, char *qiDongShiJian, char *zhuCongJi, char *zhuangTai);
#else
typedef void(*MsgCallBack)(int type, char *pBuf);
typedef void(*DeviceInfoCallBack)(char *sheBeiLeiXing, char *macDiZhi, char *ipDiZhi, char *banBenHao, char *qiDongShiJian, char *zhuCongJi, char *zhuangTai);
#endif

enum DeviceType
{
    eCeShi = 0,
    eCheJian = 1,
    eChaYan = 2,
};

enum CityType
{
    eUNKONW =0,
    eDEMO = 1,               //演示子类
    eJiaXing        = 3304,  //嘉兴
    eYingTan        = 3606,  //鹰潭
    eFangChengGang  = 4506,  //防城港
    eJiangMen       = 4407,  //江门
    eDongGuan       = 4419,  //东莞
    eYuLin          = 4509,  //玉林
    eDongYing       = 4551,  //东营
    eQuJing         = 5303,  //曲靖
};

enum WorkMode
{
    eInitMode = 0,
    eHostMode = 1,
    eClientMode = 2,
};

enum SoapQuanXian
{
    eSoapQuanXianMeiYou = 0,
    eSoapQuanXianYou = 1,
};

#pragma pack(push, 1) //采用1字节对齐方式

#define PACKETTYPE_OFFSET       4
#define PACKETLENGTH_OFFSET     8
#define PACKETCONTENT_OFFSET    sizeof(PACKETHEAD)
#define PACKETCONTECTMAXLEN     4096

#define PROTOCOL_CODE_0 0x12
#define PROTOCOL_CODE_1 0x34
#define PROTOCOL_CODE_2 0x56
#define PROTOCOL_CODE_3 0x78

enum UdpPacketType
{
    eUnknown = 0,
    eHostInitiate = 1,
    eDeviceSearch = 2,
    eUpdateStart =3,
    eUpdatePacket =4,
    eUpdatePacketRepeat = 5,
    eUpdateEnd = 6,
	eUpdateState = 7,
    eConfigSet = 8,
    eCompetitionInitial = 9,
    eCompetitionComplete = 10,
    eCompetitionRestart = 11,


    eReturn = 128
};

//包头
typedef struct _PACKETHEAD
{
    char startCode[4];
    int type;  //包返回类型
    unsigned int nLen;  //包内容长度
}PACKETHEAD, *PPACKETHEAD;

typedef struct _PACKET
{
    PACKETHEAD head;
    char buf[PACKETCONTECTMAXLEN];
}PACKET, *PPACKET;

typedef struct _DEVICE_CONFIG
{
    char cityCode[16];
    int deviceType;
    int soapQuanXian;
    char res[1024];
    char macList[2048];
}DEVICE_CONFIG, *PDEVICE_CONFIG;

#pragma pack(pop)

typedef struct _DEVICE_BOOT_CONFIG {
    DeviceType deviceType;
    CityType cityType;
    std::string redisIp;
    SoapQuanXian soapQuanXian;
}DEVICE_BOOT_CONFIG, *PDEVICE_BOOT_CONFIG;

#endif // _BASEINC_H
