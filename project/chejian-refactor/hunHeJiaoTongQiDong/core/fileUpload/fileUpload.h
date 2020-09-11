#ifndef _FILEUPLOAD_H
#define _FILEUPLOAD_H
#include <stdio.h>
#include <string.h>
#include "base/baseInc.h"
#include "base/dataCenter.h"
#include "base/md5/md5.h"
#include "core/interface.h"

#define MAX_FILE_NAME_LEN 128
#define MAX_PACKET_BUF_LEN 4000
#define MAX_MAC_BUF_LEN MAX_PACKET_BUF_LEN-256

typedef struct _UPDATE_FILE_HEAD
{
	int eventKey;
	char fileKey[64];
	int filePacketMaxNum;
	int fileLen;
	char fileName[MAX_FILE_NAME_LEN];
    char macList[MAX_MAC_BUF_LEN];
}UPDATE_FILE_HEAD, *PUPDATE_FILE_HEAD;

typedef struct _UPDATE_FILE_PACKET
{
	int eventKey;
	int packetNum;
	int packetKey;
	int packetLen;
	char packetBuf[MAX_PACKET_BUF_LEN];
}UPDATE_FILE_PACKET, *PUPDATE_FILE_PACKET;

typedef struct _FILE_PACKET_STATE
{
	int eventKey;
	int packetNum;
	int packetState;
}FILE_PACKET_STATE, *PFILE_PACKET_STATE;

typedef struct _FILE_UPLOAD_STATE
{
    char deviceMac[32];
	int eventKey;
	int eventState;
}FILE_UPLOAD_STATE, *PFILE_UPLOAD_STATE;

int upload_deviceUpdate(char *deviceMacList, char *pFilePath);
int upload_packetRepeat(PFILE_PACKET_STATE pPacketState);
int upload_deviceUpdateEnd(PFILE_UPLOAD_STATE pEvent);

int upload_startRecvEvent(char *pDeviceMac, PUPDATE_FILE_HEAD pFileHead, void *pDevice);
int upload_saveRecvPacket(PUPDATE_FILE_PACKET pFilePacket);

bool checkMac(char *pMacList);

#endif // _C_FILEUPLOADSEND_H
