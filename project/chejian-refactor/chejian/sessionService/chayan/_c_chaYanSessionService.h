#ifndef _C_CHAYANSESSIONSERVICE_H
#define _C_CHAYANSESSIONSERVICE_H
#include "sessionService/_c_sessionTransCenter.h"
#include "_c_chaYanSessionServiceExtra.h"
#include "base/_c_chaYanVehicle.h"
#include "_c_chaYanLshQuChong.h"
#include "_c_chaYanVehicleQuChong.h"

//#define TESTANDROID//自测时需要定义

class _c_chaYanSessionService: public _c_sessionTransCenter {

public:
    _c_chaYanSessionService(PSTARTUPPRARAM param);
    virtual ~_c_chaYanSessionService();
    virtual bool queryData();
    virtual bool reponseData(_c_session *pSession);
    virtual std::string getBaseTableName();
    virtual bool extraWorkBeforReponse(_c_session *pSession){UNUSED(pSession);return true;}
    virtual bool checkGreenChannel(_c_session *pSession){UNUSED(pSession);return false;}
    virtual _c_chaYanVehicle *loadChaYanVehicle(){return new _c_chaYanVehicle();}

private:
    //生成请求流水号Xml
    std::string getLshRequestXml(std::string num, std::string model);
    //查询待审核流水号列表
    int queryLiuShuiHao(void *pSoap, std::string &LshRequestXml, std::vector<std::string> *pVector);
    int queryWaiGuanLiuShuiHao(void *pSoap, std::vector<std::string> *pVector);
    int queryZhengJianLiuShuiHao(void *pSoap, std::vector<std::string> *pVector);

    //解析返回的流水号信息
    int AnalyseLshReturn(char *pLshReturn, std::vector<std::string> *pVector);
    //流水号列表去重
    void deRepeatLiuShuiHao(std::vector<std::string> *pVector, std::vector<std::string> *pNewVector, bool mode);
    //生成请求车辆信息Xml
    std::string getVehicleInfoRequestXml(std::string lsh,string model);
    //查询车辆信息
    _c_chaYanVehicle *queryVehicleInfo(void *p, std::string liuShuiHao, std::string mode);
    //解析返回的车辆信息
    bool AnalyseVehicleReturn(char *pVehicleReturn, _c_chaYanVehicle *pVehicle, std::string model, std::string remoteServerIp, std::string remoteServerPort, std::string photoUri);
    //车辆信息严格去重
    bool deRepeatVehicleInfo(_c_chaYanVehicleInfo &_VehicleInfo);
    //清除缓存信息
    void clearCache();
	virtual void subClearCache(){}
    //设置完成检验的车辆信息
    bool vehicleSetDisposeEnd(_c_object *pObject);
    //重复车辆信息提取
    bool repeatVehicleDisponse(_c_object *pObject);
    //无用车辆信息释放
    void freeUnusefulRepeatedVehicleInfo(_c_object *pObject);
    //获取所有检测项的Xml，准备返回
    std::string getVehicleGroupPhotoResponseXml(const _c_chaYanVehicle *pVehicle);
    //一次回复所有检测项
    void photoResultReply(void *p, const _c_chaYanVehicle *p_vehicle, const std::string &_confJkxlh,
                          const char *_remoteServerIp_Char, const std::string &_SOAP_ServerPort, const std::string &_requestUri,
                          const std::string &_cjbh, const std::string &_zdbs, const std::string &_dwjgdm);

    //判断是否在工作时间 若不在则不发起请求
    bool checkWorkTime();
protected:
    int curDay;

private:

    std::vector<lshVectorMember> _waiGuanLshVector;
    std::vector<lshVectorMember> _zhengJianlshVector;
    std::vector<_c_chaYanVehicleInfo> _vehicleInfoVector;
    void *pSoapApiHandle = NULL;
    STARTUPPRARAM _chaYanStartUpParam;
};
#endif // _C_CHAYANSESSIONSERVICE_H
