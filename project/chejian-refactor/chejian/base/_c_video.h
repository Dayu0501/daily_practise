#ifndef _C_VIDEO_H
#define _C_VIDEO_H

#include "base/_c_dbTask.h"

class _c_video: public _c_dbTask {
public:
    int videoAlgType;
    std::string cheLiangUid;
    std::string videoCode;
    std::string videoUrl;
    std::string localPath;
    std::string result;
    std::string reason;
    std::string videoDownTime;
    std::string algProcTime;
    std::string algRunTime;
    std::string runTime;
    std::string sendRedisDate;
    std::string readRedisDate;

    virtual ~_c_video(){} //用于释放内存（必须）
    _c_video()
    {
        tableName = "video_info";
        memberVector.push_back({"uuid", "UUID", &uuid, "UUID", DBOPTION_DEFAULT});
        memberVector.push_back({"cheLiangUid", "cheLiangUid", &cheLiangUid, "车辆UID", DBOPTION_DEFAULT});
        memberVector.push_back({"zpzl", "shiPinLeiXing", &videoCode, "视频类型", DBOPTION_DEFAULT});
        memberVector.push_back({"zpurl", "zhaoPianXiaZaiDiZhi", &videoUrl, "视频下载地址", DBOPTION_LONGLONGLONG});
        memberVector.push_back({"localPath", "localPath", &localPath, "视频本地地址", DBOPTION_LONGLONGLONG});
        memberVector.push_back({"jieGuo", "jieGuo", &result, "结果", DBOPTION_DEFAULT});
        memberVector.push_back({"shuoMing", "shuoMing", &reason, "说明", DBOPTION_LONGLONG});
        memberVector.push_back({"zhaoPianXiaZaiShiJian", "zhaoPianXiaZaiShiJian", &videoDownTime, "照片下载时间", DBOPTION_DEFAULT});
        memberVector.push_back({"suanFaFenXiShiJian", "suanFaFenXiShiJian", &algProcTime, "算法分析时间", DBOPTION_DEFAULT});
        memberVector.push_back({"suanfaYunXingShiJian", "suanfaYunXingShiJian", &algRunTime, "算法运行时间", DBOPTION_DEFAULT});
        memberVector.push_back({"jiSuanShiJian", "jiSuanShiJian", &runTime, "算法执行总时长时间", DBOPTION_DEFAULT});
    }
};
#endif // _C_SESSION_H
