TEMPLATE = app
QT = 
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
#CONFIG += OCCI_MODULE
#DEFINES += OCCI_MODULE

INCLUDEPATH += ./include
INCLUDEPATH += ./base/mysql
INCLUDEPATH += ./base/uuid
INCLUDEPATH += ./base/log
INCLUDEPATH += ./base/http/libevent
INCLUDEPATH += ./base/http/libevent/event2

LIBS += -L../chejian/lib
LIBS += -L../chejian/lib/nvidia_1070
LIBS += -L../chejian/lib/mysql
LIBS += -L../chejian/lib/uuid
LIBS += -L../chejian/lib/redis

OCCI_MODULE {
    INCLUDEPATH += ./base/occi
    INCLUDEPATH += ./base/occi/include
    LIBS += -L../chejian/lib/occi
}

QMAKE_CXXFLAGS += -pthread 
#QMAKE_CXXFLAGS += -fno-var-tracking-assignments
QMAKE_LFLAGS += -pthread

LIBS += -levent
LIBS += -lmysqlclient
LIBS += -lcheckLic
LIBS += -llicence
LIBS += -luuid
LIBS += -lhiredis
LIBS += -lsvrutil
LIBS += -lpthread

OCCI_MODULE {
    LIBS += -locci_db_wrapper
    LIBS += -locci
    LIBS += -lclntshcore
    LIBS += -lnnz19
    LIBS += -lclntsh
}

SOURCES += \
    alg/_c_algTaskCenter.cpp \
    alg/_c_algTaskCenterInterFace.cpp \
    alg/algClass/_c_algClass_0159.cpp \
    alg/algClass/_c_algclass_0324.cpp \
    alg/city/xian/_c_algTaskCenter_XiAn.cpp \
    alg/city/xuancheng/_c_algTaskCenter_XuanCheng.cpp \
    alg/city/xuancheng/_c_algClass_0321_XuanCheng.cpp \
    alg/city/xuancheng/_c_algClass_0158_XuanCheng.cpp \
    alg/city/xuancheng/_c_algClass_0159_XuanCheng.cpp \
    alg/city/fuyang/_c_algTaskCenter_FuYang.cpp \
    alg/city/fuyang/_c_algClass_0212_FuYang.cpp \
    alg/city/qujing/_c_algTaskCenter_QuJing.cpp\
    alg/city/shenzhen/_c_algTaskCenter_ShenZhen.cpp\
    alg/city/zhuhai/_c_algTaskCenter_ZhuHai.cpp \
    alg/city/zhuhai/_c_algClass_0202_ZhuHai.cpp \
    alg/city/nanping/_c_algTaskCenter_NanPing.cpp\
    alg/city/xuzhou/_c_algTaskCenter_XuZhou.cpp\
    alg/city/xuzhou/_c_algClass_0203_XuZhou.cpp\
    alg/city/xuzhou/_c_algClass_0202_XuZhou.cpp\
    alg/city/nanchong/_c_algClass_0199_NanChong.cpp\
    alg/city/nanchong/_c_algClass_0186_NanChong.cpp\
    alg/city/nanchong/_c_algTaskCenter_NanChong.cpp\
    alg/city/zaozhuang/_c_algTaskCenter_ZaoZhuang.cpp   \
    alg/city/dali/_c_algTaskCenter_DaLi.cpp     \
    alg/city/tianjin/_c_algTaskCenter_TianJin.cpp   \
    alg/city/tianjin/_c_algClass_0206_TianJin.cpp   \
    alg/city/baoshan/_c_algTaskCenter_BaoShan.cpp   \
    alg/city/baoshan/_c_algClass_0206_BaoShan.cpp   \
    alg/city/nanchang/_c_algTaskCenter_NanChang.cpp   \
    alg/city/nanchang/_c_algClass_0158_NanChang.cpp   \
    alg/city/nanchang/_c_algClass_0136_NanChang.cpp   \
    alg/city/nanchang/_c_algClass_0154_NanChang.cpp    \
    alg/city/maoming/_c_algTaskCenter_MaoMing.cpp   \
    alg/city/maoming/_c_algClass_0208_MaoMing.cpp   \
    alg/city/lanzhou/_c_algTaskCenter_LanZhou.cpp \
    alg/city/lanzhou/_c_algClass_0158_LanZhou.cpp \
    alg/city/wuzhou/_c_algTaskCenter_WuZhou.cpp   \
    alg/city/wuzhou/_c_algClass_0111_WuZhou.cpp   \
    alg/city/wuzhou/_c_algClass_0112_WuZhou.cpp   \
    alg/city/wuzhou/_c_algClass_0140_WuZhou.cpp   \
    alg/city/wuzhou/_c_algClass_0157_WuZhou.cpp   \
    alg/city/wuzhou/_c_algClass_0205_WuZhou.cpp   \
    alg/city/qiandongnan/_c_algTaskCenter_QianDongNan.cpp \
    alg/city/qiandongnan/_c_algClass_0213_QianDongNan.cpp \
    alg/city/ningbo/_c_algTaskCenter_NingBo.cpp   \
    alg/city/ningbo/_c_algClass_0234_NingBo.cpp   \
    alg/_c_algTaskRequest.cpp \
    alg/_c_algTaskResponse.cpp \
    alg/algClass/_c_algBaseClass.cpp \
    alg/algClass/_c_algClass_0111.cpp \
    alg/algClass/_c_algClass_0112.cpp \
    alg/algClass/_c_algClass_0113.cpp \
    alg/algClass/_c_algClass_0115.cpp \
    alg/algClass/_c_algClass_0119.cpp \
    alg/algClass/_c_algClass_0120.cpp \
    alg/algClass/_c_algClass_0121.cpp \
    alg/algClass/_c_algClass_0122.cpp \
    alg/algClass/_c_algClass_0123.cpp \
    alg/algClass/_c_algClass_0136.cpp \
    alg/algClass/_c_algClass_0155.cpp \
    alg/algClass/_c_algClass_0144.cpp \
    alg/algClass/_c_algClass_0156.cpp \
    alg/algClass/_c_algClass_0160.cpp \
    alg/algClass/_c_algClass_0157.cpp \
    alg/algClass/_c_algClass_0158.cpp \
    alg/algClass/_c_algClass_0166.cpp \
    alg/algClass/_c_algClass_0167.cpp \
    alg/algClass/_c_algClass_0168.cpp \
    alg/algClass/_c_algClass_0175.cpp \
    alg/algClass/_c_algClass_0177.cpp \
    alg/algClass/_c_algClass_0186.cpp \
    alg/algClass/_c_algClass_0201.cpp \
    alg/algClass/_c_algClass_0202.cpp \
    alg/algClass/_c_algClass_0203.cpp \
    alg/algClass/_c_algClass_0204.cpp \
    alg/algClass/_c_algClass_0205.cpp \
    alg/algClass/_c_algClass_0206.cpp \
    alg/algClass/_c_algClass_0208.cpp \
    alg/algClass/_c_algClass_0209.cpp \
    alg/algClass/_c_algClass_0211.cpp \
    alg/algClass/_c_algClass_0212.cpp \
    alg/algClass/_c_algClass_0213.cpp \
    alg/algClass/_c_algClass_0214.cpp \
    alg/algClass/_c_algClass_0215.cpp \
    alg/algClass/_c_algClass_0216.cpp \
    alg/algClass/_c_algClass_0217.cpp \
    alg/algClass/_c_algClass_0218.cpp \
    alg/algClass/_c_algClass_0219.cpp \
    alg/algClass/_c_algClass_0220.cpp \
    alg/algClass/_c_algClass_0221.cpp \
    alg/algClass/_c_algClass_0222.cpp \
    alg/algClass/_c_algClass_0223.cpp \
    alg/algClass/_c_algClass_0224.cpp \
    alg/algClass/_c_algClass_0225.cpp \
    alg/algClass/_c_algClass_0226.cpp \
    alg/algClass/_c_algClass_0227.cpp \
    alg/algClass/_c_algClass_0228.cpp \
    alg/algClass/_c_algClass_0234.cpp \
    alg/algClass/_c_algClass_0287.cpp \
    alg/algClass/_c_algClass_0288.cpp \
    alg/algClass/_c_algClass_0292.cpp \
    alg/algClass/_c_algClass_0297.cpp \
    alg/algClass/_c_algClass_0321.cpp \
    alg/algClass/_c_algClass_0322.cpp \
    alg/algClass/_c_algClass_0323.cpp \
    alg/algClass/_c_algClass_0342.cpp \
    alg/algClass/_c_algClass_0344.cpp \
    alg/algClass/_c_algClass_0348.cpp \
    alg/algClass/_c_algClass_0351.cpp \
    alg/algClass/_c_algClass_0352.cpp \
    alg/algClass/_c_algClass_0354.cpp \
    alg/algClass/_c_algClass_0296.cpp \
    alg/algTaskBase.cpp \
    base/_c_algTask.cpp \
    base/_c_carLogo.cpp \
    base/_c_chejian_init.cpp \
    base/_c_chaYanVehicle.cpp \
    base/_c_dbTask.cpp \
    base/_c_object.cpp \
    base/_c_photo.cpp \
    base/_c_runTime.cpp \
    base/_c_session.cpp \
    base/_c_systemInfo.cpp \
    base/_c_vehicle.cpp \
    base/_c_video.cpp \
    base/baseTool.cpp \
    base/dataCenter.cpp \
    base/_c_upgradeTools.cpp \
    base/md5/md5.cpp \
    base/http/HttpClient.cpp \
    base/http/HttpServer.cpp \
    base/json/json_reader.cpp \
    base/json/json_value.cpp \
    base/json/json_writer.cpp \
    base/log/logApi.cpp \
    base/soapApi/soapApi.cpp \
    base/soapApi/RecordSoapRequestInDB.cpp \
    base/soapApi/soapC.cpp \
    base/soapApi/soapTmriOutAccessSoapBindingProxy.cpp \
    base/soapApi/stdsoap2.cpp \
    base/xml/Markup.cpp \
    base/helper/DateTime.cpp \
    base/helper/HelperFile.cpp \
    base/helper/HelperString.cpp \
    base/helper/HttpServerM.cpp \
    base/helper/TextTable.cpp \
    config/_c_configBaseClass.cpp \
    config/_c_configCenter.cpp \
    config/_c_jsonArrayClass.cpp \
    config/startUpParamConfig/_c_startUpParamConfig.cpp \
    config/videoCheckConfig/_c_videoCheckJyjgbhConfig.cpp \
    config/wangLuoJieKouConfig/_c_wangLuoJieKouConfig.cpp \
    db/_c_dbTaskCenter.cpp \
    db/_c_dbTask_sqlOper.cpp \
    db/dbquery/db_passper.cpp \
    db/dbquery/dbbaseclass.cpp \
    db/dbquery/dbinterface.cpp \
    db/mysql/MySQL_DB.cpp \
    main.cpp \
    monitorService/_c_monitorCenter.cpp \
    monitorService/mmap/mmapWriter.cpp \
    session/_c_sessionCenter.cpp \
    sessionService/_c_sessionTransCenter.cpp \
    sessionService/ceshi/_c_ceShiSessionService.cpp \
    sessionService/chayan/_c_chaYanLshQuChong.cpp \
    sessionService/chayan/_c_chaYanSessionService.cpp \
    sessionService/chayan/_c_chaYanSessionServiceInterface.cpp \
    sessionService/chayan/_c_chaYanVehicleQuChong.cpp \
    sessionService/chayan/jiNan/_c_chaYanSessionService_jiNan.cpp \
    sessionService/chayan/jiNan/_c_chaYanYuan.cpp \
    sessionService/chayan/jiNan/_c_touPing.cpp \
    sessionService/chejian/_c_cheJianLshQuChong.cpp \
    sessionService/chejian/_c_cheJianSessionService.cpp \
    sessionService/chejian/_c_cheJianSessionServiceInterface.cpp \
    sessionService/chejian/_c_cheJianVehicleQuChong.cpp \
    sessionService/chejian/dongGuan/_c_cheJianSessionService_dongGuan.cpp \
    sessionService/chejian/fuZhou/_c_cheJianSessionService_fuZhou.cpp \
    sessionService/chejian/tianJin/_c_cheJianSessionService_tianJin.cpp \
    sessionService/chejian/tianJin/_c_fuJian.cpp    \
    sessionService/chejian/suZhou/_c_cheJianSessionService_suZhou.cpp \
    sessionService/chejian/suZhou/analysis_3rd_ro_sql.cpp \
#    sessionService/yingxianghua/_c_yingXiangLshQuChong.cpp \
#    sessionService/yingxianghua/_c_yingXiangSessionService.cpp \
#    sessionService/yingxianghua/_c_yingXiangSessionServiceInterface.cpp \
#    sessionService/yingxianghua/_c_yingXiangVehicleQuChong.cpp \
#    sessionService/yingxianghua/_c_yingXiangVehicle.cpp \
    webserver/webserver.cpp \
    alg/redis.cpp \
    alg/algClass/_c_algClass_0260.cpp \
    alg/algClass/_c_algClass_0286.cpp \
    alg/algClass/_c_algClass_0341.cpp \
    alg/algClass/_c_algClass_0343.cpp \
    alg/algClass/_c_algClass_0135.cpp \
    alg/city/hengshui/_c_algClass_0354_HengShui.cpp \
    alg/city/hengshui/_c_algTaskCenter_HengShui.cpp \
    alg/algClass/_c_algClass_0151.cpp \
    alg/city/dongguan/_c_algClass_0111_DongGuan.cpp \
    alg/city/dongguan/_c_algClass_0112_DongGuan.cpp \
    alg/city/dongguan/_c_algClass_0113_DongGuan.cpp \
    alg/city/dongguan/_c_algTaskCenter_DongGuan.cpp \
    alg/city/dongguan/_c_vehicle_DongGuan.cpp \
    alg/algClass/_c_algClass_0114.cpp \
    alg/algClass/_c_algClass_0361.cpp \
    alg/algClass/_c_algClass_0360.cpp \
    alg/city/jiaxing/_c_algTaskCenter_JiaXing.cpp \
    alg/city/jiaxing/_c_algclass_0321_jiaxing.cpp \
    alg/city/jiaxing/_c_algclass_0352_jiaxing.cpp \
    alg/city/xiangtan/_c_algclass_0321_xiangtan.cpp \
    alg/city/xiangtan/_c_algclass_0352_xiangtan.cpp \
    alg/city/xiangtan/_c_algTaskCenter_XiangTan.cpp \  
    alg/city/liangjiang/_c_algClass_0206_LiangJiang.cpp \
    alg/city/liangjiang/_c_algTaskCenter_LiangJiang.cpp \
    alg/city/fuzhou/_c_algTaskCenter_FuZhou.cpp \
    alg/city/fuzhou/_c_algClass_0348_FuZhou.cpp \
    alg/city/fuzhou/_c_algClass_0322_FuZhou.cpp \
    alg/city/fuzhou/_c_algClass_0167_FuZhou.cpp \
    alg/city/fuzhou/_c_algClass_0202_FuZhou.cpp \
    alg/city/fuzhou/_c_algClass_0320_FuZhou.cpp \
    alg/city/fuzhou/_c_algClass_0110_FuZhou.cpp \
    alg/city/fuzhou/_c_algClass_0325_FuZhou.cpp \
    alg/city/fuzhou/_c_algClass_0123_FuZhou.cpp \
    alg/city/fuzhou/_c_algClass_0124_FuZhou.cpp \
    alg/city/fuzhou/_c_algClass_0113_FuZhou.cpp \
    alg/city/eerduosi/_c_algTaskCenter_EErDuoSi.cpp \
    alg/city/eerduosi/_c_algClass_0205_EErDuoSi.cpp \
    alg/city/fuzhou/_c_vehicle_fuZhou.cpp \
    alg/city/zhanjiang/_c_algTaskCenter_ZhanJiang.cpp \
    alg/city/zhanjiang/_c_algclass_0288_zhanjiang.cpp \
    alg/city/suzhou/_c_algClass_0144_SuZhou.cpp \
    alg/city/suzhou/_c_algClass_0135_SuZhou.cpp \
    alg/city/suzhou/_c_algClass_0136_SuZhou.cpp \
    alg/city/suzhou/_c_algTaskCenter_SuZhou.cpp \
    alg/city/suzhou/_c_vehicle_SuZhou.cpp \
    alg/city/huaibei/_c_algTaskCenter_HuaiBei.cpp \ 
    alg/city/huaibei/_c_algClass_0203_HuaiBei.cpp \ 
    alg/city/huaibei/_c_algClass_0158_HuaiBei.cpp \ 
    alg/city/huaibei/_c_algClass_0159_HuaiBei.cpp \ 
    alg/city/huaibei/_c_algClass_0164_HuaiBei.cpp \ 
    alg/city/huaibei/_c_algClass_0213_1_HuaiBei.cpp \ 
    alg/city/huaibei/_c_algClass_0258_HuaiBei.cpp \ 
    alg/city/bengbu/_c_algTaskCenter_BengBu.cpp

HEADERS += \ \ \
    alg/_c_algTaskCenter.h \
    alg/algClass/_c_algClass_0159.h \
    alg/algClass/_c_algclass_0324.h \
    alg/city/xian/_c_algTaskCenter_XiAn.h \
    alg/city/xuancheng/_c_algTaskCenter_XuanCheng.h \
    alg/city/xuancheng/_c_algClass_0321_XuanCheng.h \
    alg/city/xuancheng/_c_algClass_0158_XuanCheng.h \
    alg/city/xuancheng/_c_algClass_0159_XuanCheng.h \
    alg/city/fuyang/_c_algTaskCenter_FuYang.h  \
    alg/city/fuyang/_c_algClass_0212_FuYang.h  \
    alg/city/qujing/_c_algTaskCenter_QuJing.h  \
    alg/city/shenzhen/_c_algTaskCenter_ShenZhen.h  \
    alg/city/zhuhai/_c_algTaskCenter_ZhuHai.h  \
    alg/city/zhuhai/_c_algClass_0202_ZhuHai.h  \
    alg/city/nanping/_c_algTaskCenter_NanPing.h  \
    alg/city/xuzhou/_c_algTaskCenter_XuZhou.h\
    alg/city/xuzhou/_c_algClass_0203_XuZhou.h\
    alg/city/xuzhou/_c_algClass_0202_XuZhou.h\
    alg/city/nanchong/_c_algClass_0199_NanChong.h\
    alg/city/nanchong/_c_algClass_0186_NanChong.h\
    alg/city/nanchong/_c_algTaskCenter_NanChong.h\
    alg/city/zaozhuang/_c_algTaskCenter_ZaoZhuang.h   \
    alg/city/dali/_c_algTaskCenter_DaLi.h   \
    alg/city/tianjin/_c_algTaskCenter_TianJin.h \
    alg/city/tianjin/_c_algClass_0206_TianJin.h \
    alg/city/baoshan/_c_algTaskCenter_BaoShan.h \
    alg/city/baoshan/_c_algClass_0206_BaoShan.h \
    alg/city/nanchang/_c_algTaskCenter_NanChang.h   \
    alg/city/nanchang/_c_algClass_0158_NanChang.h   \
    alg/city/nanchang/_c_algClass_0136_NanChang.h   \
    alg/city/nanchang/_c_algClass_0154_NanChang.h    \
    alg/city/maoming/_c_algTaskCenter_MaoMing.h   \
    alg/city/maoming/_c_algClass_0208_MaoMing.h   \
    alg/city/lanzhou/_c_algTaskCenter_LanZhou.h \
    alg/city/lanzhou/_c_algClass_0158_LanZhou.h \
    alg/city/wuzhou/_c_algTaskCenter_WuZhou.h   \
    alg/city/wuzhou/_c_algClass_0111_WuZhou.h   \
    alg/city/wuzhou/_c_algClass_0112_WuZhou.h   \
    alg/city/wuzhou/_c_algClass_0140_WuZhou.h   \
    alg/city/wuzhou/_c_algClass_0157_WuZhou.h   \
    alg/city/wuzhou/_c_algClass_0205_WuZhou.h   \
    alg/city/qiandongnan/_c_algTaskCenter_QianDongNan.h \
    alg/city/qiandongnan/_c_algClass_0213_QianDongNan.h \
    alg/city/ningbo/_c_algTaskCenter_NingBo.h   \
    alg/city/ningbo/_c_algClass_0234_NingBo.h   \
    alg/_c_algTaskRequest.h \
    alg/_c_algTaskResponse.h \
    alg/algClass/_c_algBaseClass.h \
    alg/algClass/_c_algClass_0111.h \
    alg/algClass/_c_algClass_0112.h \
    alg/algClass/_c_algClass_0113.h \
    alg/algClass/_c_algClass_0115.h \
    alg/algClass/_c_algClass_0119.h \
    alg/algClass/_c_algClass_0120.h \
    alg/algClass/_c_algClass_0121.h \
    alg/algClass/_c_algClass_0122.h \
    alg/algClass/_c_algClass_0123.h \
    alg/algClass/_c_algClass_0136.h \
    alg/algClass/_c_algClass_0155.h \
    alg/algClass/_c_algClass_0144.h \
    alg/algClass/_c_algClass_0156.h \
    alg/algClass/_c_algClass_0160.h \
    alg/algClass/_c_algClass_0157.h \
    alg/algClass/_c_algClass_0158.h \
    alg/algClass/_c_algClass_0166.h \
    alg/algClass/_c_algClass_0167.h \
    alg/algClass/_c_algClass_0168.h \
    alg/algClass/_c_algClass_0175.h \
    alg/algClass/_c_algClass_0177.h \
    alg/algClass/_c_algClass_0186.h \
    alg/algClass/_c_algClass_0201.h \
    alg/algClass/_c_algClass_0202.h \
    alg/algClass/_c_algClass_0203.h \
    alg/algClass/_c_algClass_0204.h \
    alg/algClass/_c_algClass_0205.h \
    alg/algClass/_c_algClass_0206.h \
    alg/algClass/_c_algClass_0208.h \
    alg/algClass/_c_algClass_0209.h \
    alg/algClass/_c_algClass_0211.h \
    alg/algClass/_c_algClass_0212.h \
    alg/algClass/_c_algClass_0213.h \
    alg/algClass/_c_algClass_0214.h \
    alg/algClass/_c_algClass_0215.h \
    alg/algClass/_c_algClass_0216.h \
    alg/algClass/_c_algClass_0217.h \
    alg/algClass/_c_algClass_0218.h \
    alg/algClass/_c_algClass_0219.h \
    alg/algClass/_c_algClass_0220.h \
    alg/algClass/_c_algClass_0221.h \
    alg/algClass/_c_algClass_0222.h \
    alg/algClass/_c_algClass_0223.h \
    alg/algClass/_c_algClass_0224.h \
    alg/algClass/_c_algClass_0225.h \
    alg/algClass/_c_algClass_0226.h \
    alg/algClass/_c_algClass_0227.h \
    alg/algClass/_c_algClass_0228.h \
    alg/algClass/_c_algClass_0287.h \
    alg/algClass/_c_algClass_0288.h \
    alg/algClass/_c_algClass_0234.h \
    alg/algClass/_c_algClass_0292.h \
    alg/algClass/_c_algClass_0297.h \
    alg/algClass/_c_algClass_0321.h \
    alg/algClass/_c_algClass_0322.h \
    alg/algClass/_c_algClass_0323.h \
    alg/algClass/_c_algClass_0342.h \
    alg/algClass/_c_algClass_0344.h \
    alg/algClass/_c_algClass_0348.h \
    alg/algClass/_c_algClass_0351.h \
    alg/algClass/_c_algClass_0352.h \
    alg/algClass/_c_algClass_0354.h \
    alg/algClass/_c_algClass_0296.h \
    alg/algTaskBase.h \
    base/BlockQueue.h \
    base/NoBlockSessionVector.h \
    base/_c_algTask.h \
    base/_c_carLogo.h \
    base/_c_chejian_init.h \
    base/_c_chaYanVehicle.h \
    base/_c_dbTask.h \
    base/_c_device.h \
    base/_c_object.h \
    base/_c_photo.h \
    base/_c_runTime.h \
    base/_c_session.h \
    base/_c_systemInfo.h \
    base/_c_udpService.h \
    base/_c_vehicle.h \
    base/_c_video.h \
    base/_c_wangLuoJieKouReturn.h \
    base/baseInc.h \
    base/baseTool.h \
    base/dataCenter.h \
    base/_c_upgradeTools.h \
    base/md5/md5.h  \
    base/http/HttpClient.h \
    base/http/HttpServer.h \
    base/json/autolink.h \
    base/json/config.h \
    base/json/features.h \
    base/json/forwards.h \
    base/json/json.h \
    base/json/json_batchallocator.h \
    base/json/reader.h \
    base/json/value.h \
    base/json/writer.h \
    base/log/logApi.h \
    base/soapApi/TmriOutAccessSoapBinding.nsmap \
    base/soapApi/RecordSoapRequestInDB.h \
    base/soapApi/soapApi.h \
    base/soapApi/soapH.h \
    base/soapApi/soapStub.h \
    base/soapApi/soapTmriOutAccessSoapBindingProxy.h \
    base/soapApi/stdsoap2.h \
    base/uuid/all-io.h \
    base/uuid/c.h \
    base/uuid/randutils.h \
    base/uuid/uuid.h \
    base/uuid/uuidP.h \
    base/uuid/uuidd.h \
    base/xml/Markup.h \
    config/_c_configBaseClass.h \
    config/_c_configCenter.h \
    config/_c_jsonArrayClass.h \
    config/startUpParamConfig/_c_dbConfig.h \
    config/startUpParamConfig/_c_redisConfig.h \
    config/startUpParamConfig/_c_soapConfig.h \
    config/startUpParamConfig/_c_startUpParamConfig.h \
    config/videoCheckConfig/_c_videoCheckJyjgbhConfig.h \
    config/wangLuoJieKouConfig/_c_jiaoQiangXianConfig.h \
    config/wangLuoJieKouConfig/_c_wangLuoJieKouConfig.h \
    db/_c_dbTaskCenter.h \
    db/_c_dbTask_sqlOper.h \
    db/dbquery/db_passper.h \
    db/dbquery/db_photoinfo.h \
    db/dbquery/db_vehicleinfo.h \
    db/dbquery/dbbaseclass.h \
    db/dbquery/dbinterface.h \
    db/mysql/MySQL_DB.h \
    monitorService/_c_monitorCenter.h \
    monitorService/mmap/mmapReader.h \
    monitorService/mmap/mmapWriter.h \
    monitorThreads/_c_monitorThreads.h \
    session/_c_sessionCenter.h \
    sessionService/_c_sessionTransCenter.h \
    sessionService/ceshi/_c_ceShiSessionService.h \
    sessionService/chayan/_c_chaYanLshQuChong.h \
    sessionService/chayan/_c_chaYanSessionService.h \
    sessionService/chayan/_c_chaYanSessionServiceExtra.h \
    sessionService/chayan/_c_chaYanVehicleQuChong.h \
    sessionService/chayan/jiNan/_c_chaYanSessionService_jiNan.h \
    sessionService/chayan/jiNan/_c_chaYanYuan.h \
    sessionService/chayan/jiNan/_c_touPing.h \
    sessionService/chejian/_c_cheJianLshQuChong.h \
    sessionService/chejian/_c_cheJianSessionService.h \
    sessionService/chejian/_c_cheJianSessionServiceExtra.h \
    sessionService/chejian/_c_cheJianVehicleQuChong.h \
    sessionService/chejian/dongGuan/_c_cheJianSessionService_dongGuan.h \
    sessionService/chejian/suZhou/_c_cheJianSessionService_suZhou.h \
    sessionService/chejian/fuZhou/_c_cheJianSessionService_fuZhou.h \
    sessionService/chejian/tianJin/_c_cheJianSessionService_tianJin.h   \
    sessionService/chejian/tianJin/_c_fuJian.h  \
    sessionService/common/_c_commonExtra.h \
    sessionService/common/_c_commonLshQuChong.h \
#    sessionService/yingxianghua/_c_yingXiangLshQuChong.h \
#    sessionService/yingxianghua/_c_yingXiangSessionService.h \
#    sessionService/yingxianghua/_c_yingXiangSessionServiceExtra.h \
#    sessionService/yingxianghua/_c_yingXiangVehicleQuChong.h \
#    sessionService/yingxianghua/_c_yingXiangVehicle.h \
#    base/occi/occi_db_wrapper.h \
    webserver/webserver.h \
    alg/hiredis/adapters/ae.h \
    alg/hiredis/adapters/glib.h \
    alg/hiredis/adapters/ivykis.h \
    alg/hiredis/adapters/libev.h \
    alg/hiredis/adapters/libevent.h \
    alg/hiredis/adapters/libuv.h \
    alg/hiredis/adapters/macosx.h \
    alg/hiredis/adapters/qt.h \
    alg/hiredis/async.h \
    alg/hiredis/hiredis.h \
    alg/hiredis/read.h \
    alg/hiredis/sds.h \
    alg/redis.h \
    base/mysql/big_endian.h \
    base/mysql/binary_log_types.h \
    base/mysql/byte_order_generic.h \
    base/mysql/byte_order_generic_x86.h \
    base/mysql/decimal.h \
    base/mysql/errmsg.h \
    base/mysql/keycache.h \
    base/mysql/little_endian.h \
    base/mysql/m_ctype.h \
    base/mysql/m_string.h \
    base/mysql/my_alloc.h \
    base/mysql/my_byteorder.h \
    base/mysql/my_command.h \
    base/mysql/my_compiler.h \
    base/mysql/my_config.h \
    base/mysql/my_dbug.h \
    base/mysql/my_dir.h \
    base/mysql/my_getopt.h \
    base/mysql/my_global.h \
    base/mysql/my_list.h \
    base/mysql/mysql.h \
    base/mysql/mysql_com.h \
    base/mysql/mysql_com_server.h \
    base/mysql/mysqld_ername.h \
    base/mysql/mysqld_error.h \
    base/mysql/mysql_embed.h \
    base/mysql/mysql_time.h \
    base/mysql/mysql_version.h \
    base/mysql/mysqlx_ername.h \
    base/mysql/mysqlx_error.h \
    base/mysql/mysqlx_version.h \
    base/mysql/my_sys.h \
    base/mysql/my_thread.h \
    base/mysql/my_thread_local.h \
    base/mysql/my_xml.h \
    base/mysql/plugin.h \
    base/mysql/plugin_audit.h \
    base/mysql/plugin_auth_common.h \
    base/mysql/plugin_ftparser.h \
    base/mysql/plugin_group_replication.h \
    base/mysql/plugin_keyring.h \
    base/mysql/plugin_validate_password.h \
    base/mysql/sql_common.h \
    base/mysql/sql_state.h \
    base/mysql/sslopt-case.h \
    base/mysql/sslopt-longopts.h \
    base/mysql/sslopt-vars.h \
    base/mysql/thr_cond.h \
    base/mysql/thr_mutex.h \
    base/mysql/thr_rwlock.h \
    base/mysql/typelib.h \
    base/mysql/mysql/psi/mysql_file.h \
    base/mysql/mysql/psi/mysql_idle.h \
    base/mysql/mysql/psi/mysql_mdl.h \
    base/mysql/mysql/psi/mysql_memory.h \
    base/mysql/mysql/psi/mysql_ps.h \
    base/mysql/mysql/psi/mysql_socket.h \
    base/mysql/mysql/psi/mysql_sp.h \
    base/mysql/mysql/psi/mysql_stage.h \
    base/mysql/mysql/psi/mysql_statement.h \
    base/mysql/mysql/psi/mysql_table.h \
    base/mysql/mysql/psi/mysql_thread.h \
    base/mysql/mysql/psi/mysql_transaction.h \
    base/mysql/mysql/psi/psi.h \
    base/mysql/mysql/psi/psi_base.h \
    base/mysql/mysql/psi/psi_memory.h \
    base/mysql/psi/psi_base.h \
    base/mysql/psi/psi_memory.h \
    alg/algClass/_c_algClass_0260.h \
    alg/algClass/_c_algClass_0286.h \
    alg/algClass/_c_algClass_0343.h \
    alg/algClass/_c_algClass_0341.h \
    alg/algClass/_c_algClass_0135.h \
    alg/city/hengshui/_c_algClass_0354_HengShui.h \
    alg/city/hengshui/_c_algTaskCenter_HengShui.h \
    alg/algClass/_c_algClass_0151.h \
    alg/city/dongguan/_c_algClass_0111_DongGuan.h \
    alg/city/dongguan/_c_algClass_0112_DongGuan.h \
    alg/city/dongguan/_c_algClass_0113_DongGuan.h \
    alg/city/dongguan/_c_algTaskCenter_DongGuan.h \
    alg/city/dongguan/_c_vehicle_DongGuan.h \
    alg/algClass/_c_algClass_0114.h \
    alg/algClass/_c_algClass_0360.h \
    alg/algClass/_c_algClass_0361.h \
    alg/city/jiaxing/_c_algTaskCenter_JiaXing.h \
    alg/city/jiaxing/_c_algclass_0321_jiaxing.h \
    alg/city/jiaxing/_c_algclass_0352_jiaxing.h \
    alg/city/xiangtan/_c_algclass_0321_xiangtan.h \
    alg/city/xiangtan/_c_algclass_0352_xiangtan.h \
    alg/city/xiangtan/_c_algTaskCenter_XiangTan.h  \
    alg/city/liangjiang/_c_algClass_0206_LiangJiang.h \
    alg/city/liangjiang/_c_algTaskCenter_LiangJiang.h \
    alg/city/fuzhou/_c_algTaskCenter_FuZhou.h \
    alg/city/fuzhou/_c_algClass_0348_FuZhou.h \
    alg/city/fuzhou/_c_algClass_0322_FuZhou.h \
    alg/city/fuzhou/_c_algClass_0167_FuZhou.h \
    alg/city/fuzhou/_c_algClass_0202_FuZhou.h \
    alg/city/fuzhou/_c_algClass_0320_FuZhou.h \
    alg/city/fuzhou/_c_algClass_0110_FuZhou.h \
    alg/city/fuzhou/_c_algClass_0325_FuZhou.h \
    alg/city/fuzhou/_c_algClass_0123_FuZhou.h \
    alg/city/fuzhou/_c_algClass_0124_FuZhou.h \
    alg/city/fuzhou/_c_algClass_0113_FuZhou.h \
    alg/city/fuzhou/_c_vehicle_fuZhou.h \
    alg/city/eerduosi/_c_algTaskCenter_EErDuoSi.h \
    alg/city/eerduosi/_c_algClass_0205_EErDuoSi.h \
    alg/city/zhanjiang/_c_algTaskCenter_ZhanJiang.h \
    alg/city/zhanjiang/_c_algclass_0288_zhanjiang.h \
    alg/city/suzhou/_c_algClass_0144_SuZhou.h \
    alg/city/suzhou/_c_algClass_0135_SuZhou.h \
    alg/city/suzhou/_c_algClass_0136_SuZhou.h \
    alg/city/suzhou/_c_algTaskCenter_SuZhou.h \
    alg/city/suzhou/_c_vehicle_SuZhou.h \
    alg/city/huaibei/_c_algTaskCenter_HuaiBei.h \
    alg/city/huaibei/_c_algClass_0203_HuaiBei.h \
    alg/city/huaibei/_c_algClass_0158_HuaiBei.h \
    alg/city/huaibei/_c_algClass_0159_HuaiBei.h \
    alg/city/huaibei/_c_algClass_0164_HuaiBei.h \ 
    alg/city/huaibei/_c_algClass_0213_1_HuaiBei.h \ 
    alg/city/huaibei/_c_algClass_0258_HuaiBei.h \
    alg/city/bengbu/_c_algTaskCenter_BengBu.h
