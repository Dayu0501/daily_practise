#ifndef DBINTERFACE_H
#define DBINTERFACE_H
#include "../base/baseInc.h"

Json::Value getPhotoInfoOrderJson();
Json::Value getPhotoInfoVectorJson(std::string vehicleId);

Json::Value getVehicleInfoOrderJson();
Json::Value getVehicleInfoVectorJson(std::string tableName, std::string chePai,std::string startTime,std::string endTime);

Json::Value getPassListInfoOrderJson();
Json::Value getPassListInfoVectorJson(std::vector<std::string> zplxVector,std::string startTime,std::string endTime);

Json::Value getPassInfoOrderJson();
Json::Value getPassInfoVectorJson(std::string zplx,std::string startTime,std::string endTime);
Json::Value getPhotoInfoVectorJsonByReason(std::string category,std::string reason,std::string startTime,std::string endTime);
Json::Value queryJiNanTouPingMsgBySheBeiId(std::string sheBeiId);
bool checkGreenChannelByShenFenZheng(std::string shenFenZheng);
Json::Value queryRecordSoapTimes(int lastestCount = 1);

#endif // DBINTERFACE_H
