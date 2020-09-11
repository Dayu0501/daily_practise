#ifndef _C_CHEJIANSESSIONSERVICE_DONGGUAN_H
#define _C_CHEJIANSESSIONSERVICE_DONGGUAN_H
#include "../_c_cheJianSessionService.h"

class _c_cheJianSessionService_dongGuan: public _c_cheJianSessionService {
public:
    _c_cheJianSessionService_dongGuan(SESSIONSERVICE_PARAM *pSessionServiceParam);
    virtual _c_vehicle *loadVehicle();
};
#endif // _C_CHEJIANSESSIONSERVICE_DONGGUAN_H
