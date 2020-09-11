#ifndef _C_CHEJIANSESSIONSERVICE_H
#define _C_CHEJIANSESSIONSERVICE_H
#include "sessionService/_c_sessionTransCenter.h"
#include "_c_cheJianSessionServiceExtra.h"
#include "_c_cheJianLshQuChong.h"
#include "_c_cheJianVehicleQuChong.h"
#include "base/_c_vehicle.h"

#include "base/_c_wangLuoJieKouReturn.h"

class _c_cheJianSessionService: public _c_sessionTransCenter {

public:
    _c_cheJianSessionService(SESSIONSERVICE_PARAM *pSessionServiceParam);
    virtual ~_c_cheJianSessionService();
//    ~_c_cheJianSessionService();
    virtual bool queryData();
    virtual bool reponseData(_c_session *pSession);
    virtual std::string getBaseTableName();
    virtual bool extraWorkBeforReponse(_c_session *pSession){UNUSED(pSession);return true;}

    virtual _c_vehicle *loadVehicle(){return new _c_vehicle();}

protected:
    //流水号列表去重
    void deRepeatLiuShuiHao(std::vector<std::string> *pVector,std::vector<std::string> *pNewVector);
    //车辆信息严格去重
    int deRepeatVehicleInfo(_c_vehicleInfo &_VehicleInfo);
    //设置完成检验的车辆信息
    bool vehicleSetDisposeEnd(_c_object *pObject);
    //判断是否在工作时间 若不在则不发起请求
    bool checkWorkTime();
	
    virtual void subClearCache(){}


private:
    //生成请求流水号Xml
    std::string getLshRequestXml(std::string queryNumber);
    //查询待审核流水号列表
    int queryLiuShuiHao(void *p, std::vector<std::string> *pVector);
    //解析返回的流水号信息
    int AnalyseLshReturn(char *pLshReturn,std::vector<std::string> *pVector);
    //解析 soap reply 获取状态码
    int AnalyseSoapReturn(string& retmsg,string& retcode);
    //生成请求车辆信息Xml
    std::string getVehicleInfoRequestXml(const std::string &_Lsh);
    //查询车辆信息
    _c_vehicle *queryVehicleInfo(void *p, std::string liuShuiHao);
    //解析返回的车辆信息
    bool AnalyseVehicleReturn(char *pVehicleReturn,_c_vehicle *pVehicle, std::string remoteServerIp, std::string remoteServerPort, std::string photoUri);

    //清除缓存信息
    void clearCache();
    //重复车辆信息提取
    bool repeatVehicleDisponse(_c_object *pObject);
    //无用车辆信息释放
    void freeUnusefulRepeatedVehicleInfo(_c_object *pObject);
    //获取所有检测项的Xml，准备返回
    std::string getVehicleGroupPhotoResponseXml(const _c_vehicle *pVehicle);
    //一次回复所有检测项
    void photoResultGroupReply(void *p, const _c_vehicle *p_vehicle, const std::string &_confJkxlh, const char *_remoteServerIp_Char
                                       , const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                                       , const std::string &_zdbs, const std::string &_dwjgdm);
    //逐个回复检测项
    void photoResultSingleReply(void *p, const _c_vehicle *p_vehicle, const std::string &_confJkxlh, const char *_remoteServerIp_Char
                                               , const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                                               , const std::string &_zdbs, const std::string &_dwjgdm);
    //逐个回复检测项发送
    void sendPhotoSingleResult(void *p, const _c_vehicle *p_vehicle, int zplist_index, std::string data, const std::string &_confJkxlh, const char *_remoteServerIp_Char
                                              , const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                                              , const std::string &_zdbs, const std::string &_dwjgdm);

    //执行标识所对应的操作
    void processWangLuoJieKouInfo(void *p, _c_vehicle *pVehicle);

    //处理电子交强险(含车船税)相关
    std::string getJqxRequestXml(_c_vehicle *pVehicle);
    bool queryJiaoQiangXian(void *p, _c_vehicle *pVehicle, std::string shouQuanMa);
    bool AnalyseJqxReturn(char *pJqxReturn, _c_vehicle *pVehicle, _c_jiaoQiangXianJkReturnInfo *pJqxInfo);

    //请求车辆相关的视频信息
    void requestVideoInfo(_c_vehicle *pVehicle);

protected:
    std::vector<_c_vehicleInfo> _vehicleInfoVector;

private:
    int _curDay;
    std::vector<lshVectorMember> _lshVector;
   // std::vector<_c_vehicleInfo> _vehicleInfoVector;
    void *pSoapApiHandle = NULL;
    STARTUPPRARAM _cheJianStartUpParam;
    std::vector<wangLuoJieKouItem> *_wangLuoJieKouInfo;
    std::vector<VIDEOJYJGBH> *_videoCheckJyjgbhConfig;
    std::string _cityCode;
};
#endif // _C_CHEJIANSESSIONSERVICE_H
