#ifndef _C_YINGXIANGSESSIONSERVICE_H
#define _C_YINGXIANGSESSIONSERVICE_H
#include "sessionService/_c_sessionTransCenter.h"
#include "_c_yingXiangSessionServiceExtra.h"
#include "_c_yingXiangVehicle.h"
#include "_c_yingXiangLshQuChong.h"
#include "_c_yingXiangVehicleQuChong.h"

typedef struct _QUERYPRARAM
{
    std::string accountID;
    std::string targetDB;
}QUERYPRARAM, *PQUERYPRARAM;


class _c_yingXiangSessionService: public _c_sessionTransCenter {

public:
    _c_yingXiangSessionService(PSTARTUPPRARAM param);
    ~_c_yingXiangSessionService();
    bool queryData();
    bool reponseData(_c_session *pSession);
    std::string getBaseTableName();
    bool extraWorkBeforReponse(_c_session *pSession){UNUSED(pSession);return true;}
    bool checkGreenChannel(_c_session *pSession){UNUSED(pSession);return false;}

private:
    //查询待审核流水号列表
    int queryLiuShuiHao(std::vector<std::string> *pVector);

    //解析返回的流水号信息
    int AnalyseLshReturn(char *pLshReturn,std::vector<std::string>& pVector);
    //流水号列表去重
    void deRepeatLiuShuiHao(std::vector<std::string> *pVector, std::vector<std::string> *pNewVector);
    //查询车辆信息
    _c_yingXiangVehicle *queryVehicleInfo(std::string liuShuiHao);
    //解析返回的车辆信息
    bool AnalyseVehicleReturn(char *pVehicleReturn, _c_yingXiangVehicle *pVehicle);
    //车辆信息严格去重
    bool deRepeatVehicleInfo(_c_yingXiangLshInfo &_VehicleInfo);
    //清除缓存信息
    void clearCache();
    //设置完成检验的车辆信息
    bool vehicleSetDisposeEnd(_c_object *pObject);
    //重复车辆信息提取
    bool repeatVehicleDisponse(_c_object *pObject);
    //无用车辆信息释放
    void freeUnusefulRepeatedVehicleInfo(_c_object *pObject);
    //一次回复所有检测项
    void photoResultReply(const _c_yingXiangVehicle *p_vehicle);

    void getDirs(std::string path, std::vector<std::string>& files);
    bool isSevenDays(std::string cuCiDengJiRiQi);
    int remove_dir(const char *dir);
    void delDirs();
    std::string getDangTianRiQi();
    bool CreatPath(string path);
    int getOraclePhoto(_c_yingXiangVehicle *pVehicle);

private:
    int _curDay;
    std::vector<lshVectorMember> _lshVector;
    std::vector<_c_yingXiangLshInfo> _yxLshInfoVector;
    void *pSoapApiHandle = NULL;
    STARTUPPRARAM _yingXiangStartUpParam;
    QUERYPRARAM _queryParam;
    string httpPath = "/home/java/new_chejian/web/yingxiang/";
};
#endif // _C_YINGXIANGSESSIONSERVICE_H
