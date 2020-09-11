#ifndef _C_CHEJIANSESSIONSERVICE_SUZHOU_H
#define _C_CHEJIANSESSIONSERVICE_SUZHOU_H
#include "../_c_cheJianSessionService.h"
#include "alg/_c_algTaskCenter.h"

class _c_cheJianSessionService_suZhou: public _c_cheJianSessionService {
public:
    _c_cheJianSessionService_suZhou(SESSIONSERVICE_PARAM *pSessionServiceParam);
   // virtual _c_vehicle *loadVehicle();
   // virtual bool queryReponseData();
   // virtual bool pushQueue(_c_session *pSession);
    virtual bool queryData();
    virtual bool reponseData(_c_session *pSession);
    bool extraReponseData(_c_session *pSession);//  第三方接口返回
    bool extraQueryData(); // 第三方查询接口
protected:
    virtual void subClearCache();

};

void* start_receive_data_suzhou() ;
#endif // _C_CHEJIANSESSIONSERVICE_DONGGUAN_H

