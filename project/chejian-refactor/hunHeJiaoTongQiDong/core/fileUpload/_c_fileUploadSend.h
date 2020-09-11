#ifndef _C_FILEUPLOADSEND_H
#define _C_FILEUPLOADSEND_H
#include "fileUpload.h"

class _c_fileUploadSend
{
public:
	bool eventFileIsOk;
	UPDATE_FILE_HEAD fileHead;
    _c_fileUploadSend(char *deviceMacList, char *pFilePath);
	~_c_fileUploadSend();

	int fileUploadSendThreadStart();
	int fileUploadSend();

	bool checkEventKey(int eventKey);
	int filePacketRepeat(int packetNum);

    int fileUploadEnd(char *pDeviceMac);

private:
	FILE * fd;
    int updateDeviceNum = 0;
	int filePacketSend(PUPDATE_FILE_HEAD pFileHead, int packetNum);
};


#endif // _C_FILEUPLOADSEND_H
