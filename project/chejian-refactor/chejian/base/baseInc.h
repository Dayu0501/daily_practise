#ifndef _BASEINC_H
#define _BASEINC_H
#include <stdio.h>
#include <vector>
#include <thread>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "json/json.h"
#include "base/BlockQueue.h"
#include "base/log/logApi.h"
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <map>

#define DBPWD "ju3eizd1;57?"

#define UNUSED(x) (void)x

#define DBSCHEMANAME "chejian_refactor"

#define DBOPTION_DEFAULT {true, "VARCHAR(32)"}
#define DBOPTION_LONG {true,"VARCHAR(64)"}
#define DBOPTION_LONGLONG {true,"VARCHAR(128)"}
#define DBOPTION_LONGLONGLONG {true,"VARCHAR(512)"}
#define DBOPTION_NODB {false,"VARCHAR(32)"}
#define DBOPTION_TOOLONG {true,"VARCHAR(1024)"}
#define DBOPTION_TEXT {true,"TEXT"}

#define NOPICEXAMPLE {}

#define INSTALL_PATH "/opt/vehicle/program/programPath/"
enum DeviceType
{
    eCeShi =0,
    eCheJian = 1,
    eChaYan = 2,
    eYingXiang = 3,
};

enum CityType
{
    eUNKONW         =0,
    eDEMO           = 1,     //演示子类
    eTianJin        = 1200,  //天津
	eLangFang       = 1310,  //廊坊
	eHengShui       = 1311,  //衡水

	eXuZhou         = 3203,  //徐州
    eSuZhou         = 3205,  //苏州
    eNingBo         = 3302,  //宁波
    eJiaXing        = 3304,  //嘉兴
	eHuaiBei        = 3406,  //淮北
	eFuYang         = 3412,  //阜阳
	eXuanCheng      = 3418,  //宣城
    eFuZhou         = 3501,  //福州
	eNanChong		= 5113,  //南充
    eEErDuoSi       = 1506,  //鄂尔多斯
    eBengBu         = 3403,  //蚌埠
	eNanPing        = 3507,  //南平
    eNanChang       = 3601,  //南昌
    eYingTan        = 3606,  //鹰潭
    eJiNan          = 3701,  //济南
	eZaoZhunag      = 3704,  //枣庄
    eBinZhou        = 3716,  //滨州
	
    eJingMen        = 4208,  //荆门
    eXiangTan       = 4303,  //湘潭
    eYueYang        = 4306,  //岳阳
	eShenZhen       = 4403,  //深圳
    eZhuHai         = 4404,  //珠海
    eJiangMen       = 4407,  //江门
    eZhanJiang      = 4408,  //湛江
    eMaoMing        = 4409,  //茂名
    eDongGuan       = 4419,  //东莞
    eWuZhou         = 4504,  //梧州
	eFangChengGang  = 4506,  //防城港
	eChongZuo       = 4514,  //崇左 
    eYuLin          = 4509,  //玉林
    eDongYing       = 4551,  //东营
	
	eLiangJiang     = 5000,  //重庆两江
    eQianDongNan    = 5226,  //黔东南
    eQuJing         = 5303,  //曲靖 
	eDaLi           = 5329,  //大理  
    eBaoShan        = 5305,  //云南保山
	
    eXiAn           = 6101,  //西安  
    eLanZhou        = 6201,  //兰州
    
    
    
};

enum WorkMode
{
    eHostMode = 0,
    eClientMode = 1,
    eTestCaseMode = 2,
};

typedef struct _DEVICE_BOOT_CONFIG {
    DeviceType deviceType;
    CityType cityType;
    std::string masterAddress;
}DEVICE_BOOT_CONFIG, *PDEVICE_BOOT_CONFIG;

typedef struct _JYJG {
    std::string bh;
    std::string ip;  /* 检验机构指定IP */
}JYJG, *PJYJG;

typedef struct _DB_OPTION
{
    bool dbLink;        // 是否关联数据库操作
    std::string dbtype; //数据库对应类型生成sql，需要符合数据语法

}DB_OPTION, *PDB_OPTION;

class objectMember{
public:
    std::string soapName;   //对应字段名称
    std::string codeName;
    std::string *value; //值地址
    std::string desc;   // 描述
    DB_OPTION dbOption; //数据库选项
};

typedef struct _DB_PARAM
{
	std::string strDbName;	 //数据库名称
	std::string strHost;	//数据库所在主机ip
	std::string strUserName; //数据库用户名
	std::string strPassword; //数据库密码
    unsigned int port;
}DB_PARAM, *PDB_PARAM;

class threadInfo {
public:
    threadInfo() {
        curCnt = 1;
        preCnt = 0;
    }

    void updateCurCnt() {
        std::lock_guard<std::mutex> lck (mutex);
        curCnt++;
    }

    void setPreCnt() {
        std::lock_guard<std::mutex> lck (mutex);
        preCnt = curCnt;
    }
public:
    std::string threadName;
    std::thread *_pthread;
    std::mutex mutex;
    unsigned long curCnt;
    unsigned long preCnt;
};

class wangLuoJieKouItem
{
public:
    std::string biaoShi;
    std::string shouQuanMa;
};

class wangLuoJieKouMap
{
public:
    std::string biaoShi;
    int biaoShiPicType;
    int xieRuXiangPicType;
};

class _c_video;
typedef struct _VIDEOCHECK_INFO {
    bool isNeedLoadVideoInfo;
    volatile bool shiPinDownloadIsFinished;//下载请求是非阻塞的
    std::vector<_c_video *> shiPinClassVector;
}VIDEOCHECK_INFO, *PVIDEOCHECK_INFO;

typedef struct _VIDEOJYJGBH {
    std::string jyjgbh;
    std::string portIp;
    std::string xieYiLeiXing;
    std::string tongXunFangShi;
}VIDEOJYJGBH, *PVIDEOJYJGBH;

typedef struct _SESSIONSERVICE_PARAM {
    CityType cityType;
    std::map<std::string, void *> params;
}SESSIONSERVICE_PARAM, *PSESSIONSERVICE_PARAM;
#endif // _BASEINC_H
