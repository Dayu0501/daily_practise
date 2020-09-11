#ifndef _C_PHOTO_H
#define _C_PHOTO_H
#include "_c_algTask.h"

class _c_photo:public _c_algTask{
public:
    std::string cheLiangUid;
    std::string zhaoPianBianHao;

    virtual ~_c_photo(){} //用于释放内存（必须）
    _c_photo(){
        tableName = "photo_info";
        memberVector.push_back({"uuid", "UUID", &uuid, "UUID", DBOPTION_DEFAULT});
        memberVector.push_back({"cheLiangUid", "cheLiangUid", &cheLiangUid, "车辆UID", DBOPTION_DEFAULT});
        memberVector.push_back({"photodes", "zhaoPianBianHao", &zhaoPianBianHao, "照片编号", DBOPTION_DEFAULT});
        memberVector.push_back({"zpzl", "zhaoPianLeiXing", &algCode, "照片类型", DBOPTION_DEFAULT});
        memberVector.push_back({"zpurl", "zhaoPianXiaZaiDiZhi", &photoUrl, "照片下载地址", DBOPTION_LONGLONGLONG});
        memberVector.push_back({"localPath", "localPath", &localPath, "照片本地地址", DBOPTION_LONGLONGLONG});
        memberVector.push_back({"jieGuo", "jieGuo", &result, "结果", DBOPTION_DEFAULT});
        memberVector.push_back({"shuoMing", "shuoMing", &reason, "说明", DBOPTION_LONGLONG});
        memberVector.push_back({"zhaoPianXiaZaiShiJian", "zhaoPianXiaZaiShiJian", &photoDownTime, "照片下载时间", DBOPTION_DEFAULT});
        memberVector.push_back({"suanFaFenXiShiJian", "suanFaFenXiShiJian", &algProcTime, "算法分析时间", DBOPTION_DEFAULT});
        memberVector.push_back({"suanfaYunXingShiJian", "suanfaYunXingShiJian", &algRunTime, "算法运行时间", DBOPTION_DEFAULT});
        memberVector.push_back({"sheBeiIp", "sheBeiIp", &processDeviceIp, "处理设备ip", DBOPTION_DEFAULT});
        memberVector.push_back({"jiSuanShiJian", "jiSuanShiJian", &runTime, "算法执行总时长时间", DBOPTION_DEFAULT});
    }
};
#endif // _C_SESSION_H