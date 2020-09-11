#ifndef _C_CHEJIANSESSIONSERVICE_TIANJIN_H
#define _C_CHEJIANSESSIONSERVICE_TIANJIN_H
#include "../_c_cheJianSessionService.h"

class _c_cheJianSessionService_tianJin: public _c_cheJianSessionService {
public:
    _c_cheJianSessionService_tianJin(SESSIONSERVICE_PARAM *pSessionServiceParam);
//    virtual _c_vehicle *loadVehicle();
    virtual bool extraWorkBeforReponse(_c_session *pSession);
    virtual void subClearCache();
};
#endif // _C_CHEJIANSESSIONSERVICE_DONGGUAN_H
