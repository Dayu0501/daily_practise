#ifndef _DATACENTER_H
#define _DATACENTER_H
#include "base/baseInc.h"

unsigned int getUdpSendQueueSize();
bool pushReponseQueue(PPACKET msg);
PPACKET getUdpSendMsgFromQueue();
int packagePacket(int codeType, char *pbuf, unsigned int bufLen);

unsigned int getDisasterRecoveryQueueSize();
bool pushDisasterRecoveryQueue(PPACKET msg);
PPACKET getDisasterRecoveryMsgFromQueue();

#endif // _DATACENTER_H
