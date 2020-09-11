#include "_c_cheJianSessionService_fuZhou.h"
#include "alg/city/fuzhou/_c_vehicle_fuZhou.h"
#include "base/soapApi/soapApi.h"
#include "base/soapApi/soapTmriOutAccessSoapBindingProxy.h"
#include "base/dataCenter.h"
#include "base/_c_systemInfo.h"

_c_cheJianSessionService_fuZhou::_c_cheJianSessionService_fuZhou(SESSIONSERVICE_PARAM *pSessionServiceParam)
    : _c_cheJianSessionService(pSessionServiceParam) {

}

_c_vehicle *_c_cheJianSessionService_fuZhou::loadVehicle() {
    return new _c_vehicle_fuZhou();
}

void _c_cheJianSessionService_fuZhou::subClearCache() {
	printf("delete file source !\n");
	
	baseTool::keepRecentSomeDaysDir(THRID_PARTY_PIC_PATH, 1, 10) ;
}