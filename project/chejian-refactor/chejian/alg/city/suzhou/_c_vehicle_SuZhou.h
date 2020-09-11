#ifndef _C_VEHICLE_SUZHOU_H
#define _C_VEHICLE_SUZHOU_H

#include "base/_c_vehicle.h"

//第三方图片文件保存路径
#define DIR_PATH            "/home/java/new_chejian/web/third_photo/"

class _c_vehicle_SuZhou:public _c_vehicle {
public:
//    string third_address ; // 第三方结果写入数据库地址
//    _c_vehicle_SuZhou(){
//         memberVector.push_back({"third_address", "third_address", &third_address, "第三方存放图片的数据库", DBOPTION_DEFAULT});
//    }
    virtual bool loadAlgTask();
    virtual _e_session_type getSessionType(){ return SESS_3TH ;}
};

#endif
