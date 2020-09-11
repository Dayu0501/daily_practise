#include "_c_fileUploadRecv.h"

bool _c_fileUploadRecv::checkPacketAndRepeat()
{
	for (int i = 0; i < fileHead.filePacketMaxNum; i++) {
		bool packetIsUpload = false;
		for (unsigned int j = 0; j < filePacketState.size(); j++) {
			if (filePacketState[j].packetNum == i)
			{
				packetIsUpload = true;
				break;
			}
		}
		if (!packetIsUpload)
		{
			printf("eUpdatePacketRepeat :%d \n", i);
			FILE_PACKET_STATE filePacketState = { 0 };
			filePacketState.eventKey = fileHead.eventKey;
			filePacketState.packetNum = i;
			filePacketState.packetState = 0;
			packagePacket(eUpdatePacketRepeat + eReturn, (char *)&filePacketState, sizeof(FILE_PACKET_STATE));
		}
	}
	return true;
}

bool _c_fileUploadRecv::checkEvent()
{
	time_t nowTime;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	if (!uploadOver)
	{
		time(&nowTime);
		double dif = difftime(nowTime, lastPacketTime);
		if (dif > 10)
		{
			if (timeErrorCount++ > 10)
			{
				timeErrorCount = 0;
				checkPacketAndRepeat();
			}
			printf("dif:%f\n", dif);
		}
        else if(dif > 120)//工具异常退出的情况
        {
            //退出升级
            uploadOver = true;
            //关闭文件句柄
            fclose(fd);
            fd = NULL;
            //清空状态向量
            filePacketState.clear();
            //设置升级结束状态
            _pDeviceSearch->setFileUploadStatus(false);
        }
	}

	return true;
}


void fileUploadCheck_Thread(_c_fileUploadRecv *pFileUpload)
{
	do {
		pFileUpload->checkEvent();
	} while (!pFileUpload->isClose());
}

_c_fileUploadRecv::_c_fileUploadRecv(char *pDeviceMac,PUPDATE_FILE_HEAD pFileHead, void *pDevice)
{
	memcpy(&fileHead, pFileHead, sizeof(UPDATE_FILE_HEAD));
    sprintf(deviceMac,"%s",pDeviceMac);
    filePath = "/opt/vehicle/program/";
    filePath += pFileHead->fileName;
//    strcpy(pFileHead->fileName, path.c_str());
    fd = fopen(filePath.c_str(), "wb");
	uploadOver = false;
	time(&lastPacketTime);
    time(&eventStartTime);

	timeErrorCount = 0;

	_pCheckThread = new std::thread(fileUploadCheck_Thread, this);
	_pCheckThread->detach();

    _pDeviceSearch = static_cast<_c_deviceSearch *>(pDevice);

    printf("eventKey ~~ :%d\n", pFileHead->eventKey);
    printf("fileKey:%s\n", pFileHead->fileKey);
	printf("filePacketMaxNum:%d\n", pFileHead->filePacketMaxNum);
	printf("fileLen:%d\n", pFileHead->fileLen);
    printf("fileName:%s\n", filePath.c_str());
    printf("macList:%s\n", pFileHead->macList);
}

bool _c_fileUploadRecv::checkEventKey(int eventKey)
{

	if (eventKey == fileHead.eventKey)
	{
		return true;
	}

	return false;
}

bool _c_fileUploadRecv::checkFileUploadOver()
{
	if (filePacketState.size() >= fileHead.filePacketMaxNum)
	{
		bool packetUploadOver = true;

		for (int i = 0; i < fileHead.filePacketMaxNum; i++) {
			bool packetIsUpload = false;
			for (unsigned int j = 0; j < filePacketState.size(); j++) {
				if (filePacketState[j].packetNum == i)
				{
					packetIsUpload = true;
					break;
				}
			}
			if (!packetIsUpload)
			{
				packetUploadOver = false;
				break;
			}
		}
		return packetUploadOver;
    }
    else
    {
        if(filePacketState.size() % (fileHead.filePacketMaxNum / 100) == 0)
        {
            FILE_UPLOAD_STATE fileUploadState = { 0 };
            fileUploadState.eventKey = fileHead.eventKey;
            fileUploadState.eventState = filePacketState.size()*100/fileHead.filePacketMaxNum;
            sprintf(fileUploadState.deviceMac,"%s",deviceMac);
            packagePacket(eUpdateState + eReturn, (char *)&fileUploadState, sizeof(FILE_UPLOAD_STATE));
        }
    }
	return false;
}

bool _c_fileUploadRecv::checkEventOver()
{
	MD5 md5;
	std::string md5Code;
    if (!uploadOver)
	{
		md5Code = md5.FileDigest(fileHead.fileName);
		if (strcmp(md5Code.c_str(), fileHead.fileKey) == 0)
		{
			uploadOver = true;
            time_t nowTime;
            time(&nowTime);
            double dif = difftime(nowTime, eventStartTime);
            printf("1111111111111111111111111  %f \n",dif);
		}
		FILE_UPLOAD_STATE fileUploadState = { 0 };
		fileUploadState.eventKey = fileHead.eventKey;
		fileUploadState.eventState = uploadOver;
        sprintf(fileUploadState.deviceMac,"%s",deviceMac);
		packagePacket(eUpdateEnd + eReturn, (char *)&fileUploadState, sizeof(FILE_UPLOAD_STATE));

        //执行解压
        char unzipCmd[500];
        sprintf(unzipCmd, "tar zxvf %s -C /opt/vehicle/program/", filePath.c_str());
        printf("1111111111111111111111111  start unzip ,cmd is %s\n",unzipCmd);
        system(unzipCmd);
        printf("2222222222222222222222222  end unzip \n");
        std::string zipFileName = fileHead.fileName;
        std::string fileName = "/opt/vehicle/program/";
        fileName += zipFileName.substr(8, 14);
        std::this_thread::sleep_for(std::chrono::microseconds(5000));

        char lnsCmd[500];
        sprintf(lnsCmd, "ln -s %s /opt/vehicle/program/programPath", fileName.c_str());
        printf("333333333333333333333333333  creat ln ,lnscmd is %s\n",lnsCmd);
        system("rm /opt/vehicle/program/programPath");
        system(lnsCmd);

        //调用解压后的脚本
        system("bash /opt/vehicle/program/programPath/update.sh &");
        //调用算法相关脚本
        restartAlg();
        //设置升级结束状态
        _pDeviceSearch->setFileUploadStatus(false);
	}
	return  uploadOver;
}

int _c_fileUploadRecv::saveUploadFilePacket(PUPDATE_FILE_PACKET pFilePacket)
{

	if (fd != NULL)
	{
		int packetKey = 0;

		time(&lastPacketTime);
		Crc16((const uint8_t *)pFilePacket->packetBuf, pFilePacket->packetLen, (uint16_t *)&packetKey);

        printf("packetKey %d [%d] [%d] len:%d\n",pFilePacket->packetNum ,pFilePacket->packetKey, packetKey ,pFilePacket->packetLen);
		if (packetKey == pFilePacket->packetKey)
		{
			int offset = pFilePacket->packetNum * MAX_PACKET_BUF_LEN;
			fseek(fd, offset, SEEK_SET);
			fwrite(pFilePacket->packetBuf, 1, pFilePacket->packetLen, fd);
            filePacketState.push_back({ pFilePacket->eventKey,pFilePacket->packetNum,1 });
		}
		else {
			FILE_PACKET_STATE filePacketState = { 0 };
			filePacketState.eventKey = fileHead.eventKey;
			filePacketState.packetNum = pFilePacket->packetNum;
			filePacketState.packetState = 0;
			packagePacket(eUpdatePacketRepeat + eReturn, (char *)&filePacketState, sizeof(FILE_PACKET_STATE));
		}

		if (checkFileUploadOver())
		{
			if (fd != NULL)
			{
				fclose(fd);
				fd = NULL;
			}
			checkEventOver();
		}
	}

	return 1;
}
