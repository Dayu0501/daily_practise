#include "sessionService/chejian/_c_cheJianSessionService.h"
#include "sessionService/chejian/dongGuan/_c_cheJianSessionService_dongGuan.h"
#include "sessionService/chejian/fuZhou//_c_cheJianSessionService_fuZhou.h"
#include "sessionService/chejian/tianJin/_c_cheJianSessionService_tianJin.h"
#include "sessionService/chayan/_c_chaYanSessionService.h"
#include "sessionService/chayan/jiNan/_c_chaYanSessionService_jiNan.h"
#include "sessionService/yingxianghua/_c_yingXiangSessionService.h"
#include "session/_c_sessionCenter.h"
#include "alg/_c_algTaskCenter.h"
#include "db/_c_dbTaskCenter.h"
#include "base/http/HttpServer.h"
#include "webserver/webserver.h"
#include "base/dataCenter.h"
#include "checkLic.h"
#include "base/baseTool.h"
#include "monitorService/_c_monitorCenter.h"
#include "alg/city/xuancheng/_c_algTaskCenter_XuanCheng.h"
#include "alg/city/fuyang/_c_algTaskCenter_FuYang.h"
#include "alg/city/hengshui/_c_algTaskCenter_HengShui.h"
#include "alg/city/jiaxing/_c_algTaskCenter_JiaXing.h"
#include "alg/city/qujing/_c_algTaskCenter_QuJing.h"
#include "alg/city/shenzhen/_c_algTaskCenter_ShenZhen.h"
#include "alg/city/dongguan/_c_algTaskCenter_DongGuan.h"
#include "alg/city/nanping/_c_algTaskCenter_NanPing.h"
#include "alg/city/xian/_c_algTaskCenter_XiAn.h"
#include "alg/city/zaozhuang/_c_algTaskCenter_ZaoZhuang.h"
#include "alg/city/xiangtan/_c_algTaskCenter_XiangTan.h"
#include "alg/city/zhuhai/_c_algTaskCenter_ZhuHai.h"
#include "alg/city/fuzhou/_c_algTaskCenter_FuZhou.h"
#include "alg/city/eerduosi//_c_algTaskCenter_EErDuoSi.h"
#include "alg/city/xuzhou/_c_algTaskCenter_XuZhou.h"
#include "alg/city/nanchong/_c_algTaskCenter_NanChong.h"
#include "alg/city/dali/_c_algTaskCenter_DaLi.h"
#include "alg/city/liangjiang/_c_algTaskCenter_LiangJiang.h"
#include "base/_c_carLogo.h"
#include "alg/city/tianjin/_c_algTaskCenter_TianJin.h"
#include "alg/city/zhanjiang/_c_algTaskCenter_ZhanJiang.h"
#include "alg/city/baoshan/_c_algTaskCenter_BaoShan.h"
#include "alg/city/nanchang/_c_algTaskCenter_NanChang.h"
#include "base/_c_chejian_init.h"
#include "alg/city/suzhou/_c_algTaskCenter_SuZhou.h"
#include "alg/city/maoming/_c_algTaskCenter_MaoMing.h"
#include "alg/city/lanzhou/_c_algTaskCenter_LanZhou.h"
#include "alg/city/wuzhou/_c_algTaskCenter_WuZhou.h"
#include "alg/city/qiandongnan/_c_algTaskCenter_QianDongNan.h"
#include "alg/city/ningbo/_c_algTaskCenter_NingBo.h"
#include "sessionService/chejian/suZhou/_c_cheJianSessionService_suZhou.h"
#include "alg/city/huaibei/_c_algTaskCenter_HuaiBei.h"
#include "alg/city/bengbu/_c_algTaskCenter_BengBu.h"
#include "base/soapApi/soapApi.h"
const std::string VERSION = "5.1.8";
const std::string VERSION_MSG = "标准版本";

void printfVersion()
{
    LOG(SESSION,INFO,"VERSION:[%s]",VERSION.c_str());
    LOG(SESSION,INFO,"VERSION_MSG[%s]",VERSION_MSG.c_str());

    printf("VERSION:[%s]\n",VERSION.c_str());
    printf("VERSION_MSG[%s]\n",VERSION_MSG.c_str());
}

class cpFile {
public:
    std::string src;
    std::string dest;
    std::string desc;
};

std::vector<cpFile> fileVector = {
    {"./hunHeJiaoTong", "/bin", "主程序"},
    {"../chejian/lib", "lib", "连接库文件"},
    {"../web/", "web", "网页文件"},
    {"../chejian/start.sh", "", "启动程序"},
    {"../chejian/processCoredump.sh", "", "启动程序"},
};

std::string getFileName(std::string filePath)
{
    std::string name;
    char path[1024] = {0};

    sprintf(path,"%s",filePath.c_str());
    char *pEnd = path;
    char *pOver = pEnd + strlen(path);
    while(1)
    {
        char *p =strstr(pEnd,"/");
        if(p != NULL && p < pOver)
        {
            pEnd = p+1;
        }else {
            break;
        }
    }
    name = pEnd;

    return name;
}

void makeUpdateReleaseTar(std::string rootPath,std::string version)
{
    std::string rootDir = rootPath+"/Release_"+version;
    baseTool::CheckDir(rootDir);

    for (unsigned int i = 0; i < fileVector.size(); i++) {

         if(baseTool::isFolder(fileVector[i].src))
         {
            printf("copyFolder item[%d] %s\n",i,fileVector[i].src.c_str());
            baseTool::CheckDir(rootDir+"/"+fileVector[i].dest);
            baseTool::copyFolder(fileVector[i].src,rootDir+"/"+fileVector[i].dest);
         }
         else
         {
            printf("copyFile item[%d] %s\n",i,fileVector[i].src.c_str());
            baseTool::CheckDir(rootDir+"/"+fileVector[i].dest);
            baseTool::copyFile(fileVector[i].src,rootDir+"/"+fileVector[i].dest+"/"+getFileName(fileVector[i].src));
         }

    }

    std::string tarStr = "tar zcvf "+rootDir+".tar.gz "+rootDir;
    printf("tarStr:%s\n",tarStr.c_str());
    system(tarStr.c_str());
}


int main(int argc, char *argv[])
{
    // 车牌logo初始化
    initLogoList();
    LogApi::LoadPath("log");

    if((argc == 2) && (std::string(argv[1])== "-v"))
    {
        printfVersion();
        return 1;
    }

    if ((argc > 1) && (std::string(argv[1]) == "-mv"))
    {
        std::string rootPath = "..";
        if(argc > 2)
             rootPath = argv[2];
        makeUpdateReleaseTar(rootPath,VERSION);
        return EXIT_SUCCESS;
    }

	std::string beginDate, endDate, licenseResult;
    bool isLicenseOK = baseTool::checkLicense(licenseResult, beginDate, endDate);
    LOG(COMMON, INFO, "check_licence isFlag : %d, message : %s\n", isLicenseOK, licenseResult.c_str());

    if(!isLicenseOK)
    {
        return -1;
    }

    //不带参数默认host模式
    WorkMode appWorkMode = eHostMode;
    if ((argc > 1) && (std::string(argv[1]) == "-client"))
    {
        appWorkMode = eClientMode;
    }
    else if ((argc > 1) && (std::string(argv[1]) == "-t"))
    {
        appWorkMode = eTestCaseMode;
    }
    LOG(COMMON,INFO,"appWorkMode: %d\n", appWorkMode);
    printf("appWorkMode: %d\n", appWorkMode);

    DEVICE_BOOT_CONFIG bootConfig;
    _c_configCenter::loadDeviceBootConfig(&bootConfig);

    std::cout<< "bootConfig.masterAddress:"<<bootConfig.masterAddress<<std::endl;
    if( appWorkMode == eClientMode ){
        startSyncTime(bootConfig.masterAddress ,10080);
    }
    initConfigCenter(bootConfig.cityType);
    _c_configCenter *pConfig = loadSystemConfig();
    _c_monitorCenter threadMonitor;


     //_c_algTaskCenter  algTaskCenter(bootConfig.cityType,pConfig->getStructRedisParam());
    // algTaskCenter.setWorkMode(appWorkMode);

    _c_algTaskCenter* palgTaskcenter;
    palgTaskcenter = _c_algTaskCenter::creatCenter(bootConfig.cityType,pConfig->getStructRedisParam());

    palgTaskcenter->setWorkMode(appWorkMode);

    _c_sessionTransCenter *pSessionTransCenter;
    pSessionTransCenter = _c_sessionTransCenter::createdCenter(&bootConfig,pConfig);
    pSessionTransCenter->setWorkMode(appWorkMode);
    pSessionTransCenter->setIsOpenFilterJianYanJiGou(palgTaskcenter->getIsOpenFilterJianYanJiGou() );
    pSessionTransCenter->setJianYanJiGou(palgTaskcenter->getJyjg());

    _c_sessionCenter sessionCenter(palgTaskcenter);
    _c_dbTaskCenter dbTaskCenter(pConfig->getStructDbParam());

    threadMonitor.registerForMonitor(palgTaskcenter->getAlgTaskCenterQueryThread());
    threadMonitor.registerForMonitor(palgTaskcenter->getAlgRedisResponseThread());
    threadMonitor.registerForMonitor(palgTaskcenter->getAlgTaskReponseThread());
//    threadMonitor.registerForMonitor(algTaskCenter.getAlgTaskRequestThread());
//    threadMonitor.registerForMonitor(sessionTransCenter.getSessionTransQueryThread());
//    threadMonitor.registerForMonitor(sessionTransCenter.getSessionTransReponseThread());
    threadMonitor.registerForMonitor(sessionCenter.getSessionCenterThread());
    threadMonitor.registerForMonitor(sessionCenter.getSessionCheckThread());
    threadMonitor.registerForMonitor(dbTaskCenter.getDbTaskCenterQueryThread());

    palgTaskcenter->stratAlgTaskCenter();
    soapInit_checkRequestCount(palgTaskcenter->getPointSoapMaxReqTimes() );

    coreDumpFileInit(palgTaskcenter->getOpenCoredump() == "true");

    sessionCenter.stratSessionCenter();
    pSessionTransCenter->startSessionTransCenter();
    dbTaskCenter.stratDbTaskCenter();
    threadMonitor.startMonitor();

    HttpServer Https;
    initWebName2cb();
    setVersion(VERSION);
    setAlgTaskCenter((void *)palgTaskcenter);
    setSessionTransCenter((void *)pSessionTransCenter);
    setConfigCenter((void *)pConfig);
    Https.startHttpServer("0.0.0.0", 10080,webCB,NULL);
    LOG(COMMON,INFO,"program start failed !\n");

    return 0;
}

_c_algTaskCenter *_c_algTaskCenter::creatCenter(CityType cityType,PREDIS_PARAM redisParam)
{
    switch (cityType) {
        case eXuanCheng:
            return new _c_algTaskCenter_XuanCheng(cityType,redisParam);
        case eFuYang:
            return new _c_algTaskCenter_FuYang(cityType,redisParam);
        case eHengShui:
            return new _c_algTaskCenter_HengShui(cityType,redisParam);
        case eQuJing:
            return new _c_algTaskCenter_QuJing(cityType,redisParam);
        case eShenZhen:
            return new _c_algTaskCenter_ShenZhen(cityType,redisParam);
        case eDongGuan:
            return new _c_algTaskCenter_DongGuan(cityType,redisParam);
        case eNanPing:
            return new _c_algTaskCenter_NanPing(cityType, redisParam);
        case eZaoZhunag:
            return new _c_algTaskCenter_ZaoZhuang(cityType,redisParam);
        case eJiaXing:
            return new _c_algTaskCenter_JiaXing(cityType,redisParam);
        case eXiangTan:
            return new _c_algTaskCenter_XiangTan(cityType,redisParam);
        case eXiAn:
            return new _c_algTaskCenter_XiAn(cityType,redisParam);
        case eDaLi:
            return new _c_algTaskCenter_DaLi(cityType,redisParam);
        case eZhuHai:
            return new _c_algTaskCenter_ZhuHai(cityType,redisParam);
        case eFuZhou:
            return new _c_algTaskCenter_FuZhou(cityType, redisParam);
        case eLiangJiang:
            return new _c_algTaskCenter_LiangJiang(cityType,redisParam);
        case eTianJin:
            return new _c_algTaskCenter_TianJin(cityType,redisParam);
        case eZhanJiang:
            return new _c_algTaskCenter_ZhanJiang(cityType,redisParam);
	    case eBaoShan:
            return new _c_algTaskCenter_BaoShan(cityType,redisParam);
        case eNanChang:
            return new _c_algTaskCenter_NanChang(cityType,redisParam);
	    case eSuZhou:
            return new _c_algTaskCenter_SuZhou(cityType,redisParam);
        case eXuZhou:
            return new _c_algTaskCenter_XuZhou(cityType, redisParam);
        case eEErDuoSi:
            return new _c_algTaskCenter_EErDuoSi(cityType, redisParam);
        case eNanChong:
            return new _c_algTaskCenter_NanChong( cityType,redisParam);
        case eMaoMing:
        	return new _c_algTaskCenter_MaoMing( cityType,redisParam );
    	case eLanZhou:
        	return new _c_algTaskCenter_LanZhou( cityType,redisParam );
    	case eHuaiBei:
        	return new _c_algTaskCenter_HuaiBei( cityType,redisParam );
    	case eWuZhou:
        	return new _c_algTaskCenter_WuZhou( cityType,redisParam );
        case eQianDongNan:
            return new _c_algTaskCenter_QianDongNan( cityType,redisParam );
        case eNingBo:
            return new _c_algTaskCenter_NingBo( cityType,redisParam ); 
        case eBengBu:
            return new _c_algTaskCenter_BengBu( cityType,redisParam );
    	default:
            return new _c_algTaskCenter(cityType,redisParam);
    }
}

_c_sessionTransCenter *_c_sessionTransCenter::createdCenter(PDEVICE_BOOT_CONFIG bootConfig,_c_configCenter *pConfig)
{
    if(bootConfig->deviceType == eCeShi)
    {
        printf("bootConfig ERR exit\n");
        LOG(COMMON,ERR,"bootConfig ERR exit\n");
        exit(0);
    }
    else if(bootConfig->deviceType == eChaYan)
    {
        switch (bootConfig->cityType) {
            case eJiNan:
                return new _c_chaYanSessionService_jiNan(pConfig->getSoapParam());
            default:
                return new _c_chaYanSessionService(pConfig->getSoapParam());
        }

    }
    else if(bootConfig->deviceType == eYingXiang)
    {
        //return new _c_yingXiangSessionService(pConfig->getSoapParam());
    }
    else
    {
        switch (bootConfig->cityType) {
            case eDongGuan:
                return new _c_cheJianSessionService_dongGuan(pConfig->getSessionServiceParam());
            case eTianJin:
                return new _c_cheJianSessionService_tianJin(pConfig->getSessionServiceParam());
            case eFuZhou:
                return new _c_cheJianSessionService_fuZhou(pConfig->getSessionServiceParam());
            case eSuZhou:
                printf("启动第三方接收线程\n");
                start_receive_data_suzhou();
                return new _c_cheJianSessionService_suZhou(pConfig->getSessionServiceParam());
            default:
                return new _c_cheJianSessionService(pConfig->getSessionServiceParam());
        }
    }

    return NULL;
}

