#ifndef _C_ALGTASKCENTER_H
#define _C_ALGTASKCENTER_H
#include "base/baseInc.h"
#include "algTaskBase.h"
#include "base/dataCenter.h"
#include "base/_c_algTask.h"
#include "algClass/_c_algBaseClass.h"
#include "_c_algTaskResponse.h"
#include "redis.h"

class _c_algTaskCenter{
public:
    static _c_algTaskCenter *creatCenter(CityType cityType,PREDIS_PARAM redisParam);
    //构造函数，加载参数初始化成员变量
    _c_algTaskCenter(CityType cityType,PREDIS_PARAM redisParam);
    virtual ~_c_algTaskCenter(){}
    //算法任务管理模块启动
    bool stratAlgTaskCenter();
    //查询待算法任务出据的数据
    bool queryData();
    //查询算法任务回复输出
    bool queryTaskReponse();
    //查询算法任务请求
    bool queryTaskRequest();
    //查询redis算法回复
    bool queryRedisResponse();  //查询redis回复算法结果
    //模块是否结束
    bool isClose();
    //加载算法业务实体
    _c_algBaseClass *loadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type, bool subParamClass);
    Json::Value getAlgCheckConflictJson();
    //获取算法接口容器并转换为json字串
    Json::Value getAlgVectorJson();
    //根据算法任务id创建算法业务类实体
    _c_algBaseClass *loadAlgBaseClassByPicType(PicType type);
    //获取算法接口容器并转换为json
    Json::Value getAlgVectorJson(std::vector<algItem> *pAlgVector);
    //根据算法业务id修改算法配置
    bool changeAlgVectorByType(algItem *pAlgItem);
    bool addAlgVectorByItem(algItem item);

    //保存参数
    void saveConfig();
    //获取开启的算法业务列表
    Json::Value getOpenAlg();
    //会话后置检测
    E_ZZJG afterAlgCheck(_c_session *pSession, std::string& sessionReason);
    //算法前置检测
    bool beforAlgCheck(_c_session *pSession, std::string& sessionReason);
    //使用性质参数设置获取修改接口
    Json::Value getSYXZVectorJson();
    void setSYXZVectorConfig(Json::Value root,std::vector<std::string> *pVector);
    void deleteCheckShiYongXingZhiByKey(std::string key);
    void addCheckShiYongXingZhiByKey(std::string key);
    //小车参数设置获取修改接口
    Json::Value getSmallVehicleVectorJson();
    void setSmallVehicleVectorConfig(Json::Value root,std::vector<std::string> *pVector);
    void deleteCheckSmallVehicleVectorByKey(std::string key);
    void addCheckSmallVehicleVectorByKey(std::string key);
    //车辆种类设置获取修改接口
    Json::Value getCLZLVectorJson();
    void setCLZLVectorConfig(Json::Value root,std::vector<std::string> *pVector);
    void deleteCheckCheLiangZhongLeiByKey(std::string key);
    void addCheckCheLiangZhongLeiByKey(std::string key);
    //检验类别设置获取修改接口
    Json::Value getJYLBVectorJson();
    void setJYLBVectorConfig(Json::Value root,std::vector<std::string> *pVector);
    void deleteCheckJianYanLeiBieByKey(std::string key);
    void addCheckJianYanLeiBieByKey(std::string key);
    //检验机构设置获取修改接口
    Json::Value getJYJGVectorJson();
    void deleteCheckJianYanJiGouByKey(std::string bh);
    void addCheckJianYanJiGouByKey(std::string bh,std::string ip);
    void setJYJGVectorConfig(Json::Value root,std::vector<JYJG> *pVector);


    //信任检验机构设置获取修改接口
    Json::Value getXinRenJYJGVectorJson();
    void deleteCheckXinRenJianYanJiGouByKey(std::string bh);
    void addCheckXinRenJianYanJiGouByKey(std::string bh,std::string ip);
    void setXinRenJYJGVectorConfig(Json::Value root,std::vector<JYJG> *pVector);

    //黑名单设置获取修改接口
    Json::Value getHMDVectorJson();
    void setHMDVectorConfig(Json::Value root,std::vector<std::string> *pVector);
    void deleteHeiMingDanByChePai(std::string chePai);
    void addHeiMingDanByChePai(std::string chePai);

    Json::Value getCjhHMDVectorJson();
    void setCjhHMDVectorConfig(Json::Value root,std::vector<std::string> *pVector);
    void deleteCjhHeiMingDanByCheJiaHao(std::string cheJiaHao);
    void addCjhHeiMingDanByCheJiaHao(std::string cheJiaHao);
    //http白名单设置获取修改接口
    Json::Value getHttpBMDVectorJson();
    void setHttpMDVectorConfig(Json::Value root,std::vector<std::string> *pVector);
    void deleteHttpBaiMingDanByIpAddr(std::string ipaddr);
    void addHttpBaiMingDanByipaddr(std::string ipaddr);

    //城市代号获取修改接口
    std::string getCityShortNmae();
    void setCityShortNameConfig(std::string shortName);

    //设置coredump开关
    std::string getOpenCoredump();
    void setOpenCoredumpConfig(std::string isopen);
    std::string getOpenFilterJianYanJiGou();
    void setOpenFilterJianYanJiGou(std::string isopen);
    //核定载客获取修改接口
    void setHeDingZaiKeShuConfig(unsigned int hdzks);
    unsigned int getHeDingZaiHeShu();

    //复检车辆处理模式
    void setFuJianCheLiangMode(unsigned int fuJianCheLiangMode);
    unsigned int getFuJianCheLiangMode();

    void setsoapMaxReqTimes(unsigned int maxSoap);
    unsigned int getsoapMaxReqTimes();
    bool checkFuJianCheLiang(std::string mode, std::string isRepeat, std::vector<_c_algTask *> *algTaskVector);

    //超时时间
    void setChaoShiShiJianConfig(unsigned int timeOut);
    unsigned int getChaoShiShiJian();



    void getAlgVectorCategory(std::vector<std::string> *pCategoryVector);
    //获取城市编号
    std::string getCityType();

    threadInfo *getAlgTaskCenterQueryThread() {return &AlgTaskCenterQueryThread;}
    threadInfo *getAlgTaskReponseThread() {return &AlgTaskReponseThread;}
    threadInfo *getAlgTaskRequestThread() {return &AlgTaskRequestThread;}
    threadInfo *getAlgRedisResponseThread() {return &AlgRedisResponseThread;}

    void setWorkMode(WorkMode mode);

    std::vector<algItem> *getAlgVector() {return &__algVector;}
    std::vector<JYJG>* getJyjg(){
        return &__JYJG ;
    }
    std::string* getIsOpenFilterJianYanJiGou(){
        return &__isOpenFilterJianYanJiGou ;
    }
    unsigned int* getPointSoapMaxReqTimes(){
        return &__soapMaxReqTimes ;
    }

    std::string getAlgCodeByType(PicType type);
    void getSubAlgClass(algItem *pAlgItem);
    bool checkHttpBaiMingDan(std::string IpAddr );
    //在前项判定不过的时候，设置整车结果
    virtual bool beforeSetResult(_c_session *pSession, std::string& sessionReason) {UNUSED(pSession); UNUSED(sessionReason); return true;}
protected:
    //用于子类加载各个城市algVector的变化情况, 如果该类派生类不再本接口改变__algVector的内容，则不受参数文件影响，否责将被参数文件中内容覆盖
    virtual void changeAlgVector(){}
    //数据前置校验
    virtual bool subBeforAlgCheck(_c_session *pSession, std::string& sessionReason){UNUSED(pSession);UNUSED(sessionReason);return true;}
    //数据算法后校验
    virtual E_ZZJG subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason){ UNUSED(baseResult);UNUSED(pSession);UNUSED(sessionReason);return baseResult;}
    //最终结果输出编辑
    virtual E_ZZJG finalCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason){ UNUSED(baseResult);UNUSED(pSession);UNUSED(sessionReason);return baseResult;}
    //算法algVector检测
    virtual bool subAlgVectorCheck(_c_session *pSession,_c_algTask *pTask,algItem *pAlgItem){UNUSED(pSession);UNUSED(pTask);UNUSED(pAlgItem);return true;}
    //创建算法基础参数类
    virtual _c_algBaseClass *subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type);
   // std::string getAlgCodeByType(PicType type);

private:
    WorkMode workMode;
    CityType __cityType = eDEMO;
    PREDIS_PARAM __pRedisParam;
    unsigned int __timeOutMilliSeconds = 100;
    unsigned int __picProcessTime = 4;
    std::string __configRoot = "/opt/vehicle/program/CheJianConfig";

//    std::thread *_pAlgTaskCenterQueryThread;
//    std::thread *_pAlgRedisResponseThread;  //从redis取算法回复线程
//    std::thread *_pAlgTaskReponseThread;
//    std::thread *_pAlgTaskRequestThread;

    threadInfo AlgTaskCenterQueryThread;
    threadInfo AlgRedisResponseThread;
    threadInfo AlgTaskReponseThread;
    threadInfo AlgTaskRequestThread;

    std::vector<std::string> __HttpMD;
    std::vector<std::string> __HMD;
    std::vector<std::string> __CjhHMD;
    std::vector<std::string> __JYLB;
    std::vector<std::string> __SYXZ = {"A"};    //使用性质
    std::vector<std::string> __CLZL =  {"K31", "K32", "K33", "K34", "K35", "K36", "K37", "K38", "K41", "K42", "K43", "K44", "K45", "K46", "K47", "K48", "K49"};    //车辆种类
    std::vector<JYJG> __JYJG;   //检验机构
    std::vector<JYJG> __XRJYJG;   //信任检验机构
    unsigned int __HDZKS = 7;   //核定载客数
    std::string __cityShortName = "沪";
    std::string __IsOpenCoreDump = "false";
    std::string __isOpenFilterJianYanJiGou = "false";
    unsigned int __soapMaxReqTimes = 0;
    std::vector<std::string> __smallVehicle = {"K31", "K32", "K33", "K34", "K35", "K36", "K37", "K38", "K41", "K42", "K43", "K44", "K45", "K46", "K47", "K48"};
    unsigned int __fuJianCheLiangMode = 0;   //复审车辆判定模式

    std::vector<_c_algTask *> _TaskMap; //存放所有的发给算法的task
    std::vector<algItem> __algVector = {
        {"0111", true, "车辆左前方斜视45度照片", e0111, true, false, false, false, "无", NOPICEXAMPLE},
        {"0112", true, "车辆右后方斜视45度照片", e0112, true, false, false, false, "无", NOPICEXAMPLE},
        {"0113", true, "车辆识别代号照片", e0113, true, false, false, false, "无", NOPICEXAMPLE},
        //{"0114", false, "驾驶员可视区玻璃照片", e0114, false, false, false, false, "无", NOPICEXAMPLE},
        {"0115", false, "车厢内部照片", e0115, false, false, false, false, "无", NOPICEXAMPLE},
        {"0119", false, "发动机号或柔性标签", e0119, false, false, false, false, "无", NOPICEXAMPLE},
        {"0132", false, "发动机舱自动灭火装置", e0120, false, false, false, false, "无", NOPICEXAMPLE},
        {"0117", false, "应急锤照片", e0121, false, false, false, false, "无", NOPICEXAMPLE},
        {"0118", false, "行驶记录装置照片", e0122, false, false, false, false, "无", NOPICEXAMPLE},
        {"0123", false, "外廓尺寸自动测量前面侧面-照片", e0123, false, false, false, false, "无", NOPICEXAMPLE},
        {"0135", false, "轮胎花纹-照片1", e0135, false, false, false, false, "无",NOPICEXAMPLE},
        {"0136", false, "左前轮胎规格型号", e0136, false, false, false, false, "无", NOPICEXAMPLE},
        {"0155", false, "左后轮胎规格型号", e0155, false, false, false, false, "无", NOPICEXAMPLE},
        {"0140", false, "教练车副制动踏板", e0140, false, false, false, false, "无", NOPICEXAMPLE},
        {"0144", false, "后备箱（尾箱）-照片", e0144, false, false, false, false, "无", NOPICEXAMPLE},
        {"0151", false, "轮胎花纹(后轮)-照片2", e0151, false, false, false, false, "无",NOPICEXAMPLE},
        {"0154", false, "右前轮胎规格型号", e0156, false, false, false, false, "无", NOPICEXAMPLE},
        {"0156", false, "右后轮胎规格型号", e0160, false, false, false, false, "无", NOPICEXAMPLE},
        {"0157", false, "驾驶人座椅汽车安全带", e0157, false, false, false, false, "无", NOPICEXAMPLE},
        {"0158", false, "车辆正后方照片", e0158, false, false, false, false, "无", NOPICEXAMPLE},
        {"0159", false, "车辆正前方(车牌特写)-照片", e0159, false, false, false, false, "无", NOPICEXAMPLE},
        {"0166", false, "车厢内部后排-照片", e0166, false, false, false, false, "无", NOPICEXAMPLE},
        {"0167", false, "车辆前方照片-照片", e0167, false, false, false, false, "无", NOPICEXAMPLE},
        {"0168", false, "车辆后方牌照-照片", e0168, false, false, false, false, "无", NOPICEXAMPLE},
        {"0175", false, "左侧方-照片", e0175, false, false, false, false, "无",NOPICEXAMPLE},
        {"0177", false, "核定载客数-照片", e0177, false, false, false, false, "无",NOPICEXAMPLE},
        {"0186", false, "车辆铭牌-照片", e0186, false, false, false, false, "无", NOPICEXAMPLE},
        {"0201", true, "机动车行驶证", e0201, true, false, false, false, "无", NOPICEXAMPLE},
        {"0202", true, "机动车牌证申请表", e0202, true, false, false, false, "无", NOPICEXAMPLE},
        {"0203", true, "机动车交通事故责任强制保险凭证", e0203, true, false, false, false, "无", NOPICEXAMPLE},
        {"0204", true, "机动车安全技术检验报告单", e0204, true, false, false, false, "无", NOPICEXAMPLE},
        {"0205", true, "机动车查验记录表", e0205, true, false, false, false, "无", NOPICEXAMPLE},
        {"0206", false, "车船税纳税或者免税证明", e0206, false, false, false, false, "无", NOPICEXAMPLE},
        {"0208", false, "代理人授权书", e0208, false, false, false, false, "无", NOPICEXAMPLE},
        {"0209", false, "尾气检测报告-照片", e0209, false, false, false, false, "无", NOPICEXAMPLE},
        {"0218", false, "机动车注册转移注销转入申请表-照片", e0211, false, false, false, false, "无", NOPICEXAMPLE},
        {"0212", false, "机动车所有人身份证明复印件-照片", e0212, false, false, false, false, "无", NOPICEXAMPLE},    //算法暂无
        {"0213", false, "居住证明-照片", e0213, false, false, false, false, "无", NOPICEXAMPLE},                 //算法暂无
        {"0207", false, "委托核发检验合格标志通知书", e0214, false, false, false, false, "无", NOPICEXAMPLE},
        {"0215", false, "机动车所有权转移证明-照片", e0215, false, false, false, false, "无", NOPICEXAMPLE},
        {"0216", false, "随车环保清单-照片", e0216, false, false, false, false, "无", NOPICEXAMPLE},
        {"0217", false, "机动车登记证书-照片", e0217, false, false, false, false, "无", NOPICEXAMPLE},
        {"0211", false, "国产机动车整车出厂合格证和底盘合格证", e0218, false, false, false, false, "无", NOPICEXAMPLE},
        {"0219", false, "车辆一致性证书-照片", e0219, false, false, false, false, "无", NOPICEXAMPLE},
        {"0220", false, "机动车变更登记(备案)-照片", e0220, false, false, false, false, "无", NOPICEXAMPLE},      //算法暂无
        {"0221", false, "机动车抵押登记(质押备案)-照片", e0221, false, false, false, false, "无", NOPICEXAMPLE},
        {"0222", false, "机动车灭失证明-照片", e0222, false, false, false, false, "无", NOPICEXAMPLE},
        {"0223", false, "查验员-照片", e0223, false, false, false, false, "无", NOPICEXAMPLE},
        {"0224", false, "外廓服务检验报告-照片", e0224, false, false, false, false, "无", NOPICEXAMPLE},
        {"0257", false, "路试检验记录单", e0225, false, false, false, false, "无", NOPICEXAMPLE},          //算法暂无
        {"0226", false, "购车发票-照片", e0226, false, false, false, false, "无", NOPICEXAMPLE},
        {"0227", false, "进口凭证-照片", e0227, false, false, false, false, "无", NOPICEXAMPLE},
        {"0228", false, "送检人身份证-照片正面", e0228, false, false, false, false, "无",NOPICEXAMPLE},
        {"0260", false, "送检人身份证-照片背面", e0260, false, false, false, false, "无", NOPICEXAMPLE},
        {"0234", false, "定期检验告知书-照片", e0234, false, false, false, false, "无", NOPICEXAMPLE},
        {"0286", false, "仪器检验报告", e0286, false, false, false, false, "无", NOPICEXAMPLE},
        {"0287", false, "行驶证(正面)-照片", e0287, false, false, false, false, "无", NOPICEXAMPLE},
        {"0288", false, "行驶证(背面)-照片", e0288, false, false, false, false, "无", NOPICEXAMPLE},
        {"0292", false, "机动车交强险(车船税)联网查询结果-照片", e0292, false, false, false, false, "无", NOPICEXAMPLE},
        {"0296", false, "罚单-照片", e0296, false, false, false, false, "无",NOPICEXAMPLE},
        {"0297", false, "检验报告(人工)-照片", e0297, false, false, false, false, "无", NOPICEXAMPLE},
        {"0321", true, "左灯光工位照片", e0321, true, false, false, false, "无", NOPICEXAMPLE},
        {"0352", true, "右灯光工位照片", e0352, true, false, false, false, "无", NOPICEXAMPLE},
        {"0322", true, "一轴制动工位照片", e0322, true, true, false, false, "无", NOPICEXAMPLE},
        {"0348", true, "二轴制动工位照片", e0348, true, true, false, false, "无", NOPICEXAMPLE},
        {"0323", true, "底盘检验照片", e0323, true, true, false, false, "无", NOPICEXAMPLE},
        {"0324", false, "底盘间隙测量-照片", e0324, false, true, false, false, "无", NOPICEXAMPLE},
        {"0344", true, "底盘动态检验开始照片", e0344, true, true, false, false, "无", NOPICEXAMPLE},
        {"0342", true, "底盘动态检验结束照片", e0342, true, true, false, false, "无", NOPICEXAMPLE},
        {"0341", false, "路试行车制动开始照片", e0341, false, true, false, false, "无",NOPICEXAMPLE},
        {"0343", false, "路试行车制动结束照片", e0343, false, true, false, false, "无",NOPICEXAMPLE},
        {"0351", true, "驻车制动工位照片", e0351, true, true, false, false, "无", NOPICEXAMPLE},
        {"0353", false, "侧滑工位照片", e0354, false, false, false, false, "无", NOPICEXAMPLE},
        {"0360", false, "外廓尺寸自动测量前面照片", e0360, false, false, false, false, "无", NOPICEXAMPLE},
        {"0361", false, "外廓尺寸自动测量侧面照片", e0361, false, false, false, false, "无", NOPICEXAMPLE},
        {"A", false, "车辆左前方斜视45度-档案照片", eCLZQFXS45DZP_A, false, false , false, false, "无", NOPICEXAMPLE}, //sub
        {"J", false, "车辆识别照片拓印膜-照片", eCLSBDHZP_TYM, false, false, false, false, "无", NOPICEXAMPLE},   //sub
        {"0210", false, "尾气检测报告-照片2", eWQDZP2, false, false, false, false, "无", NOPICEXAMPLE},    //sub
    };

    bool checkHeiMingDan(std::string chePai, std::vector<_c_algTask *> *algTaskVector );
    bool checkCjhHeiMingDan(std::string chePai, std::vector<_c_algTask *> *algTaskVector );
    bool checkJianYanLeiBie(std::string jylb, std::vector<_c_algTask *> *algTaskVector);
    bool checkShiYongXingZhi(std::string syxz, std::vector<_c_algTask *> *algTaskVector);
    bool checkCheLiangZhongLei(std::string clzl, std::vector<_c_algTask *> *algTaskVector);
    bool checkJianYanJiGou(std::string bh, std::string ip, std::vector<_c_algTask *> *algTaskVector);
    bool checkXinRenJianYanJiGou(std::string bh, std::string ip, std::vector<_c_algTask *> *algTaskVector);
//    bool checkFuJianCheLiang(std::string mode, std::string isRepeat, std::vector<_c_algTask *> *algTaskVector);

    bool checkHeDingZaiKeShu(std::string hdzks, std::vector<_c_algTask *> *algTaskVector);

    //左右灯光联合判定
    bool editZuoYouDengGuang(_c_session *pSession);
    //左前右后三脚架联合判定
    bool editQianHouSanJiaoJia( _c_session *pSession);
    //交强险完税证明   车船税联合判定
    bool editJiaoQiangXianWanShuiZhengMing( _c_session *pSession);

    bool checkIsSamllVehicle(std::string clzl, std::vector<_c_algTask *> *algTaskVector);
    virtual bool checkComplete(bool isTenYears, _c_session *pSession, std::string& sessionReason );
    E_ZZJG checkUnqualified(bool isTenYears, std::vector<_c_algTask *> *algTaskVector, std::string& sessionReason);

    bool algTaskAnalyse(_c_session *pSession);
    void checkWangLuoJieKouResult(_c_session *pSession);
    int checkTaskNeedAlgAnalyse(_c_session *pSession, _c_algTask *pTask);
    bool pushAlgTaskInfoRedis(std::string strSendJson, RedisChannelType redisChannel);
    bool AlgTaskRecovery(_c_algTask_Reponse *pRequest);
    bool algVectorCheck(_c_session *pSession,_c_algTask *pTask,algItem *pAlgItem);
    _c_algTask *getAlgTaskByGuid(std::string algTaskGuid);
    bool checkAlgTaskTimeOut();
    void loadConfig();
    void setAlgVectorConfig(Json::Value root,std::vector<algItem> *pAlgVector);
    bool initAlgTask(_c_algTask *pTask, _c_session *pSession, algItem *pAlgItem);

    void processVideoCheckAlg(_c_algTask *pTask);
    Json::Value getVideoAlgJson(_c_algTask *pTask, _c_video *pVideo);
    void pushVideoJsonToRedis(_c_algTask *pTask, _c_video *pVideo);

    void loadPicExamples();
    virtual bool checkIsTenYearCar(_c_session *pSession);
};

#endif // _C_ALGTASKCENTER_H
