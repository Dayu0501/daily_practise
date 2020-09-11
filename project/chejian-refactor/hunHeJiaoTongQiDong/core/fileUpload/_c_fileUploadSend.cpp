#include "_c_fileUploadSend.h"

_c_fileUploadSend::_c_fileUploadSend(char *deviceMacList, char *pFilePath)
{
	MD5 md5;
	eventFileIsOk = false;
	if ((fd = fopen(pFilePath, "rb")) == NULL)
	{
		printf("_c_fileUploadSend :: Can not open output file :%s \n", pFilePath);
		return;
	}
	eventFileIsOk = true;

	fseek(fd, 0, SEEK_END);
	fileHead.fileLen = ftell(fd);
	fileHead.filePacketMaxNum = (fileHead.fileLen / MAX_PACKET_BUF_LEN) + 1;
	sprintf(fileHead.fileKey, "%s", md5.FileDigest(pFilePath).c_str());
	fileHead.eventKey = rand() % 100000 + 100000;
	sprintf(fileHead.fileName, "sun_%d_%s", fileHead.eventKey, "upload.jpg");
    sprintf(fileHead.macList, "%s", deviceMacList);
    updateDeviceNum = strlen(deviceMacList);

	printf("fileLen:%d\n", fileHead.fileLen);
	printf("filePacketMaxNum:%d\n", fileHead.filePacketMaxNum);
	printf("fileKey:%s\n", fileHead.fileKey);
	printf("eventKey:%d\n", fileHead.eventKey);
    printf("macList:%s\n", fileHead.macList);


}

_c_fileUploadSend::~_c_fileUploadSend()
{

}

void fileUploadSend_Thread(_c_fileUploadSend *pFileUpload)
{
	pFileUpload->fileUploadSend();
}

int _c_fileUploadSend::fileUploadSend()
{
	if (fd != NULL)
	{
		packagePacket(eUpdateStart, (char *)&fileHead, sizeof(UPDATE_FILE_HEAD));
		for (int packetNum = 0; packetNum < fileHead.filePacketMaxNum; packetNum++)
		{
			filePacketSend(&fileHead, packetNum);
		}
	}

	return 1;
}

int _c_fileUploadSend::fileUploadSendThreadStart()
{
	std::thread *pCheckThread = new std::thread(fileUploadSend_Thread, this);
	pCheckThread->detach();

	return 1;
}

int _c_fileUploadSend::filePacketSend(PUPDATE_FILE_HEAD pFileHead, int packetNum)
{
	PPACKET pPacket = new PACKET();
	PUPDATE_FILE_PACKET pFilePacket = (PUPDATE_FILE_PACKET)pPacket->buf;

	memset(pPacket, 0, sizeof(PACKET));

	pFilePacket->eventKey = pFileHead->eventKey;
	pFilePacket->packetNum = packetNum;
	int offset = packetNum * MAX_PACKET_BUF_LEN;
	printf("packetNum:%d\n", packetNum);
	if (offset <= pFileHead->fileLen && fd != NULL)
	{
		fseek(fd, offset, SEEK_SET);
		if (offset + MAX_PACKET_BUF_LEN <= pFileHead->fileLen)
		{
			pFilePacket->packetLen = MAX_PACKET_BUF_LEN;
		}
		else
		{
			pFilePacket->packetLen = pFileHead->fileLen - offset;
		}

		fread(pFilePacket->packetBuf, 1, pFilePacket->packetLen, fd);
		Crc16((const uint8_t *)pFilePacket->packetBuf, pFilePacket->packetLen, (uint16_t *)&pFilePacket->packetKey);

		pPacket->head.startCode[0] = PROTOCOL_CODE_0;
		pPacket->head.startCode[1] = PROTOCOL_CODE_1;
		pPacket->head.startCode[2] = PROTOCOL_CODE_2;
		pPacket->head.startCode[3] = PROTOCOL_CODE_3;
		pPacket->head.type = eUpdatePacket;
		pPacket->head.nLen = pFilePacket->packetLen + 16;
		pushReponseQueue(pPacket);
	}
	return 1;
}

int _c_fileUploadSend::filePacketRepeat(int packetNum)
{
	filePacketSend(&fileHead, packetNum);
	return 1;
}

bool _c_fileUploadSend::checkEventKey(int eventKey)
{
	if (fileHead.eventKey == eventKey)
	{
		return true;
	}
	return false;
}

int _c_fileUploadSend::fileUploadEnd(char *pDeviceMac)
{
    if (fd != NULL)
        {
            updateDeviceNum -= (strlen(pDeviceMac) + 1);
            if (updateDeviceNum <= 0)
            {
                fclose(fd);
                fd = NULL;
            }
        }
	return 1;
}

