#include "_c_udpService.h"
#include "base/dataCenter.h"
#include <errno.h>
#include <cstring>

bool packetIsValid(char *buf)
{
    if (buf[0] == PROTOCOL_CODE_0 && buf[1] == PROTOCOL_CODE_1 && buf[2] == PROTOCOL_CODE_2 && buf[3] == PROTOCOL_CODE_3) {
        return true;
    }
    else {
        return false;
    }
}

char getPacketType(char *buf)
{
    return buf[PACKETTYPE_OFFSET];
}

void udpServiceSendThread(_c_udpService *pService)
{
    while (pService->getUdpSendThreadStatus())
    {
        unsigned int queueSize = getUdpSendQueueSize();
        if (queueSize > 0)
        {
            PPACKET pSendPacket = getUdpSendMsgFromQueue();
            struct sockaddr_in *multiAddr_ = pService->getMultiAddr();
            //组播发送
            int ret = sendto(pService->getSocket(), (char *)pSendPacket, sizeof(PACKETHEAD) + pSendPacket->head.nLen, 0, (struct sockaddr*)multiAddr_, sizeof(sockaddr_in));
            if (ret == -1)
            {
                perror("udp send error!\n");
            }
            delete pSendPacket;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

void udpServiceRecvThread(_c_udpService *pService, recvCallBack callBack)
{
    struct sockaddr_in fromAddr;
    int fromAddrSize = sizeof(fromAddr);
    while (pService->getUdpRecvThreadStatus())
    {
        char buf[MAXBUFFSIZE] = { 0 };
        int len = recvfrom(pService->getSocket(), buf, sizeof(buf), 0, (struct sockaddr *)&fromAddr, (socklen_t*)&fromAddrSize);
        if (len == -1)
        {
            perror("recvfrom error");
            //            break;
        }
        else
        {
            char packetType;
            printf("client == recv buf: %x %x %x %x from %s\n", buf[0], buf[1], buf[2], buf[3], inet_ntoa(fromAddr.sin_addr));
            if (packetIsValid(buf))
            {
                callBack((char *)&buf);
            }
        }
    }
}

_c_udpService::_c_udpService()
{
    isGetHostIp = false;
    memset(&remoteHostIp, 0, sizeof(remoteHostIp));
    initStatus = initUdpService(true, true);
}

_c_udpService::~_c_udpService()
{
#ifdef _WIN32
    closesocket(clientSocket);
#else
    shutdown(clientSocket, SHUT_RDWR);
    close(clientSocket);
#endif
}

void _c_udpService::setHostIpStatus(bool status)
{
    isGetHostIp = status;
}

void _c_udpService::setRemoteHostIp(struct sockaddr_in *addr)
{
    memcpy(&remoteHostIp, addr, sizeof(struct sockaddr_in));
}

#ifdef _WIN32
WSADATA wsa;
int wsaInit = 0;
int Sock_Init()
{

    if (!wsaInit)
    {
        WSAStartup(MAKEWORD(2, 2), &wsa); // initial Ws2_32.dll by a process
        wsaInit = 1;
    }
    return wsaInit;
}
#endif


int _c_udpService::initUdpService(bool needMulticast, bool needReusePort)
{
    printf("initUdpService \n");
    int ret = 0;
#ifdef _WIN32
    Sock_Init();
#endif

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1)
    {
        perror("create sock error!\n");
        ret = -1;
    }

    // 绑定client的iP和端口
    struct sockaddr_in clientAddr;
    //    socklen_t ser_len = sizeof(clientAddr);
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    clientAddr.sin_port = htons(MULTICAST_PORT);

    ret = bind(clientSocket, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
    if (ret == -1)
    {
        perror("udp bind error! \n");
        return ret;
    }

    if (needReusePort)
    {
        int reuse = 1;
        /* 设置地址复用许可, 根据具体情况判断是否增加此功能 */
        ret = setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse));
        if (ret < 0)
        {
            perror("setsockopt SO_REUSEADDR failed!\n");
            return ret;
        }
    }

    if (needMulticast)
    {
        /*加入多播组*/
        struct ip_mreq mreq;
        inet_pton(AF_INET, MULTICAST_IP, &mreq.imr_multiaddr.s_addr);
        mreq.imr_interface.s_addr = htonl(INADDR_ANY);
        ret = setsockopt(clientSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&mreq, sizeof(mreq));
        if (ret < 0)
        {
            perror("setsockopt IP_ADD_MEMBERSHIP failed!\n");
            return ret;
        }

        /*禁止组播回播*/
        unsigned char loop = 0;
        ret = setsockopt(clientSocket, IPPROTO_IP, IP_MULTICAST_LOOP, (const char *)&loop, sizeof(loop));
        if (ret < 0)
        {
            perror("setsockopt IP_MULTICAST_LOOP error!\n");
            return ret;
        }

        /*组播发送信息相关*/
        memset(&multiAddr, 0, sizeof(multiAddr));
        multiAddr.sin_family = AF_INET;
        multiAddr.sin_port = htons(MULTICAST_PORT);
        //大端字节序转化成网络字节序
        inet_pton(AF_INET, MULTICAST_IP, &multiAddr.sin_addr.s_addr);
    }

    return ret;
}

bool _c_udpService::startUdpService(recvCallBack callBack)
{
    bool ret = false;
    ret = startUdpSendThread();
    ret = startUdpRecvThread(callBack);

    return ret;
}

bool _c_udpService::startUdpSendThread()
{
    if (initStatus >= 0) {
        sendStauts = true;
        _pUdpSendThread = new std::thread(udpServiceSendThread, this);
        return true;
    }
    else {
        return false;
    }
}

bool _c_udpService::startUdpRecvThread(recvCallBack callBack)
{
    if (initStatus >= 0) {
        recvStauts = true;
        _pUdpRecvThread = new std::thread(udpServiceRecvThread, this, callBack);
        return true;
    }
    else {
        return false;
    }
}
