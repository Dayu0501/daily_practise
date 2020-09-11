#include "_c_cheJianSessionService_dongGuan.h"
#include "alg/city/dongguan/_c_vehicle_DongGuan.h"

_c_cheJianSessionService_dongGuan::_c_cheJianSessionService_dongGuan(SESSIONSERVICE_PARAM *pSessionServiceParam):_c_cheJianSessionService(pSessionServiceParam)
{

}

_c_vehicle *_c_cheJianSessionService_dongGuan::loadVehicle(){
    return new _c_vehicle();
}
