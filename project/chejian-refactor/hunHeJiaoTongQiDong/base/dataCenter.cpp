#include "dataCenter.h"
#include "base/BlockQueue.h"
#include "../core/_c_udpService.h"
#include <string.h>

BlockingQueue<PPACKET> udpSend_queue;
BlockingQueue<PPACKET> disasterRecovery_queue;

unsigned int getUdpSendQueueSize()
{
    return udpSend_queue.Size();
}

bool pushReponseQueue(PPACKET msg)
{
    udpSend_queue.Put(msg);
    return true;
}

PPACKET getUdpSendMsgFromQueue()
{
    return udpSend_queue.Take();
}

int packagePacket(int codeType, char *pbuf, unsigned int bufLen)
{
    PPACKET pPacket = new PACKET();

    memset(pPacket, 0, sizeof(PACKET));
    pPacket->head.startCode[0] = PROTOCOL_CODE_0;
    pPacket->head.startCode[1] = PROTOCOL_CODE_1;
    pPacket->head.startCode[2] = PROTOCOL_CODE_2;
    pPacket->head.startCode[3] = PROTOCOL_CODE_3;
    pPacket->head.type = codeType;
    pPacket->head.nLen = bufLen;
    memcpy(pPacket->buf,pbuf,bufLen);

    pushReponseQueue(pPacket);
    return 1;
}

unsigned int getDisasterRecoveryQueueSize()
{
    return disasterRecovery_queue.Size();
}

bool pushDisasterRecoveryQueue(PPACKET msg)
{
    disasterRecovery_queue.Put(msg);
    return true;
}

PPACKET getDisasterRecoveryMsgFromQueue()
{
    return disasterRecovery_queue.Take();
}

