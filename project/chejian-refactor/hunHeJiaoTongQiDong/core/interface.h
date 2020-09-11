#ifndef INTERFACE_H
#define INTERFACE_H
#include "base/md5/md5.h"
#include "base/dataCenter.h"
#include "base/baseInc.h"
#include "core/_c_udpService.h"
#include "core/_c_watchDog.h"
#include "core/_c_deviceSearch.h"

std::string getLocalIp();
std::string getLocalMac();
int str2Int(std::string str);
std::string getDeviceReturnJson(_c_deviceSearch *pDeviceSearch);
bool setDeviceConfig(char *pMac, PDEVICE_CONFIG pDeviceConfig);
void Crc16(const uint8_t* pDataIn, int iLenIn, uint16_t* pCRCOut);
bool loadDeviceBootConfig(PDEVICE_BOOT_CONFIG pBootConfig);
bool startHunHeJiaoTong(WorkMode mode);
bool restartAlg();
int checkAppIsStarted(const char* psProcessName);
std::string getCurTime();
void syncSystemTime(const char *time);
void setDeviceConfigItem(std::string &str, const char* name);
#endif // INTERFACE_H
