#include "fileUpload.h"
#include "_c_fileUploadSend.h"
#include "_c_fileUploadRecv.h"


std::vector<_c_fileUploadSend *> fileSendEventVector;
std::vector<_c_fileUploadRecv *> fileRecvEventVector;

int upload_deviceUpdate(char *deviceMacList, char *pFilePath)
{
    _c_fileUploadSend *pEvent = new _c_fileUploadSend(deviceMacList,pFilePath);
	if (pEvent->eventFileIsOk)
	{
		fileSendEventVector.push_back(pEvent);
		pEvent->fileUploadSendThreadStart();
	}
	return  1;
}

int upload_packetRepeat(PFILE_PACKET_STATE pPacketState)
{
	for (size_t i = 0; i < fileSendEventVector.size(); i++)
	{
		if (fileSendEventVector[i]->checkEventKey(pPacketState->eventKey))
		{
			fileSendEventVector[i]->filePacketRepeat(pPacketState->packetNum);
		}
	}

	return  1;
}

int upload_deviceUpdateEnd(PFILE_UPLOAD_STATE pEvent)
{
	for (size_t i = 0; i < fileSendEventVector.size(); i++)
	{
		if (fileSendEventVector[i]->checkEventKey(pEvent->eventKey))
		{
            fileSendEventVector[i]->fileUploadEnd(pEvent->deviceMac);
		}
	}
	return 1;
}

int upload_startRecvEvent(char *pDeviceMac, PUPDATE_FILE_HEAD pFileHead, void *pDevice)
{
    if(strstr(pFileHead->macList,pDeviceMac)!=NULL)
    {
        _c_fileUploadRecv *pEvent = new _c_fileUploadRecv(pDeviceMac,pFileHead, pDevice);
        fileRecvEventVector.push_back(pEvent);
    }
	return 1;
}

int upload_saveRecvPacket(PUPDATE_FILE_PACKET pFilePacket)
{
	for (unsigned int i = 0; i < fileRecvEventVector.size(); i++) {
		if (fileRecvEventVector[i]->checkEventKey(pFilePacket->eventKey))
		{
			if (!fileRecvEventVector[i]->uploadOver)
				fileRecvEventVector[i]->saveUploadFilePacket(pFilePacket);
		}
	}
	return 1;
}
