#ifndef _C_FILEUPLOADRECV_H
#define _C_FILEUPLOADRECV_H
#include "fileUpload.h"

class _c_deviceSearch;

class _c_fileUploadRecv
{
public:
	bool uploadOver = false;
	UPDATE_FILE_HEAD fileHead;
    std::string filePath;
	std::vector<FILE_PACKET_STATE> filePacketState;

    _c_fileUploadRecv(char *pDeviceMac,PUPDATE_FILE_HEAD pFileHead, void *pDevice);
	~_c_fileUploadRecv() {}
	bool checkEventKey(int eventKey);
	int saveUploadFilePacket(PUPDATE_FILE_PACKET pFilePacket);
	bool checkFileUploadOver();
	bool checkEventOver();


	bool checkPacketAndRepeat();

	bool checkEvent();
	bool isClose() { return uploadOver; }

private:
	FILE * fd = NULL;
	std::thread *_pCheckThread;
	time_t lastPacketTime;
	int timeErrorCount;
    time_t eventStartTime;
    char deviceMac[32];

    _c_deviceSearch *_pDeviceSearch;
};


#endif // _C_FILEUPLOADRECV_H
