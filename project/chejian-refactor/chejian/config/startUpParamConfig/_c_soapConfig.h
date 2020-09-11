#ifndef _C_SOAPCONFIG_H
#define _C_SOAPCONFIG_H
#include "base/_c_dbTask.h"
#include "base/baseTool.h"
#include "sessionService/common/_c_commonExtra.h"

class _c_soapConfig: public _c_dbTask{
public:

    std::string soapIp = "192.168.21.8";
    std::string soapPort = "9083";
    std::string remoteIp = "192.168.21.8";
    std::string remotePort = "3001";
    std::string soapNum = "2000";
    std::string soapUrl = "/pnweb/services/TmriOutNewAccess?wsdl";//chayan
    std::string soapXlh = "7F1D0909010217040015E5EA8AFDEA94E3F5FF89FE9080F08D8CDA8CA7DFACDBCDB32DD6C7C4DCC9F3BACBCFB5CDB3";//chayan
//    std::string soapUrl = "/TmriOutAccess.asmx/writeObjectOut";//chejian
//    std::string soapXlh = "7C1E0909030717040015F9E4E6EF8A878CDAEEE084979EABFABFA2C7A49D636E";//chejian
    std::string soapTimeOut = "30";
    std::string qsrqOffset = "0";
    std::string zzrqOffset = "23";
    std::string startTime = "0";
    std::string endTime = "23";
    std::string soapPhotoUri = "/";
    std::string workMode = "1";
    std::string soapGroupResponse = "1";
    std::string soapQueryInterval = "10000";
    std::string queryVideo = "0";

    STARTUPPRARAM soapParam;

    _c_soapConfig() {
        tableName = "soap_config";
        memberVector.push_back({"soapIp", "soapIp", &soapIp, "Soap 服务器地址", DBOPTION_DEFAULT});
        memberVector.push_back({"soapPort", "soapPort", &soapPort, "Soap 服务器端口", DBOPTION_DEFAULT});
        memberVector.push_back({"remoteIp", "remoteIp", &remoteIp, "照片请求 服务器地址", DBOPTION_DEFAULT});
        memberVector.push_back({"remotePort", "remotePort", &remotePort, "照片请求 服务器端口", DBOPTION_DEFAULT});
        memberVector.push_back({"soapNum", "soapNum", &soapNum, "Soap 请求数", DBOPTION_DEFAULT});
        memberVector.push_back({"soapUrl", "soapUrl", &soapUrl, "Soap 请求URL", DBOPTION_LONGLONG});
        memberVector.push_back({"soapTimeOut", "soapTimeOut", &soapTimeOut, "Soap 请求超时时间", DBOPTION_DEFAULT});
        memberVector.push_back({"qsrqOffset", "qsrqOffset", &qsrqOffset, "开始时间", DBOPTION_DEFAULT});
        memberVector.push_back({"zzrqOffset", "zzrqOffset", &zzrqOffset, "结束时间", DBOPTION_DEFAULT});
        memberVector.push_back({"startTime", "startTime", &startTime, "工作开始时间", DBOPTION_DEFAULT});
        memberVector.push_back({"endTime", "endTime", &endTime, "工作结束时间", DBOPTION_DEFAULT});
        memberVector.push_back({"soapXlh", "soapXlh", &soapXlh, "Soap 序列号", DBOPTION_LONGLONG});
        memberVector.push_back({"soapPhotoUri", "soapPhotoUri", &soapPhotoUri, "照片请求目录", DBOPTION_DEFAULT});
        memberVector.push_back({"workMode", "workMode", &workMode, "工作模式", DBOPTION_DEFAULT});
        memberVector.push_back({"soapGroupResponse", "soapGroupResponse", &soapGroupResponse, "Soap 回复形式", DBOPTION_DEFAULT});
        memberVector.push_back({"soapQueryInterval", "soapQueryInterval", &soapQueryInterval, "Soap 请求间隔", DBOPTION_DEFAULT});
        memberVector.push_back({"queryVideo", "queryVideo", &queryVideo, "请求视频信息", DBOPTION_DEFAULT});
    }

    PSTARTUPPRARAM getSoapParam() {
        soapParam.qsrqOffset = baseTool::str2Int(qsrqOffset);
        soapParam.zzrqOffset = baseTool::str2Int(zzrqOffset);
//        soapParam.startTime = baseTool::str2Int(startTime);
//        soapParam.endTime = baseTool::str2Int(endTime);
        soapParam.startTime = baseTool::strTime2Second(startTime);
        soapParam.endTime = baseTool::strTime2Second(endTime);
        soapParam.soapQueryInterval = baseTool::str2Int(soapQueryInterval);
        soapParam.soapIp = soapIp;
        soapParam.soapPort = soapPort;
        soapParam.remoteIp = remoteIp;
        soapParam.remotePort = remotePort;
        soapParam.soapUrl = soapUrl;
        soapParam.soapTimeOut = baseTool::str2Int(soapTimeOut);
        soapParam.soapNum = soapNum;
        soapParam.soapXlh = soapXlh;
        soapParam.soapPhotoUri = soapPhotoUri;
        soapParam.workMode = workMode;
        soapParam.isGroupResponse = (soapGroupResponse.compare("0") == 0)?false:true;
        soapParam.queryVideo = (queryVideo.compare("0") == 0)?false:true;
        return &soapParam;
    }

    bool needFree(){return false;}
};
#endif // _C_SOAPCONFIG_H
