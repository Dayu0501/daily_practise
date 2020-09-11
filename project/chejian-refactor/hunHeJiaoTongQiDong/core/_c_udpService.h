#ifndef _C_UDPSERVICE_H
#define _C_UDPSERVICE_H

#include "base/baseInc.h"
#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <thread>

#ifdef _WIN32
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <windows.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

#define MAXBUFFSIZE 5120

#define  MULTICAST_IP  "239.0.0.66"
#define  MULTICAST_PORT  8888
#define  MULTICAST_LOCAL_PORT 8888

bool packetIsValid(char *buf);

typedef int (*recvCallBack)(char *pBuf);


class _c_udpService
{
public:
    _c_udpService();
    ~_c_udpService();
    int initUdpService(bool needMulticast, bool needReusePort);
    bool startUdpService(recvCallBack callBack);
    bool startUdpSendThread();
    bool startUdpRecvThread(recvCallBack callBack);

    bool getUdpSendThreadStatus() {return sendStauts;}
    bool getUdpRecvThreadStatus() {return recvStauts;}
    int getSocket() {return clientSocket;}
    bool isFindHost() {return isGetHostIp;}
    struct sockaddr_in *getRemoteHostIp() {return &remoteHostIp;}
    struct sockaddr_in *getMultiAddr() {return &multiAddr;}
    void setRemoteHostIp(struct sockaddr_in *addr);
    void setHostIpStatus(bool status);

private:
    int initStatus;
    int clientSocket;
    bool isGetHostIp;
    struct sockaddr_in remoteHostIp;//主机地址
    struct sockaddr_in multiAddr;//组播地址

    bool sendStauts;
    bool recvStauts;
    std::thread *_pUdpSendThread;
    std::thread *_pUdpRecvThread;
};

#endif // _C_UDPSERVICE_H
