#ifndef _C_CHEJIANSESSIONSERVICE_FUZHOU_H
#define _C_CHEJIANSESSIONSERVICE_FUZHOU_H

#include "../_c_cheJianSessionService.h"

#define THRID_PARTY_PIC_PATH "/home/fuzhou/localpicweb/"

class _c_cheJianSessionService_fuZhou: public _c_cheJianSessionService {
public:
    _c_cheJianSessionService_fuZhou(SESSIONSERVICE_PARAM *pSessionServiceParam);

    _c_vehicle *loadVehicle() override;

protected:
	void subClearCache() override;
};

#endif 
