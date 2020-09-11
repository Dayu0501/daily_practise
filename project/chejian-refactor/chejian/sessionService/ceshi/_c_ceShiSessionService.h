#ifndef _C_CESHISESSIONSERVICE_H
#define _C_CESHISESSIONSERVICE_H
#include "sessionService/_c_sessionTransCenter.h"
#include "../chejian/_c_cheJianSessionServiceExtra.h"
#include "base/_c_vehicle.h"

class _c_ceShiSessionService: public _c_sessionTransCenter {

public:
    _c_ceShiSessionService(PSTARTUPPRARAM param);
    virtual ~_c_ceShiSessionService();
//    ~_c_cheJianSessionService();
    virtual bool queryData();
    virtual bool reponseData(_c_session *pSession);

private:

private:

};
#endif // _C_CESHISESSIONSERVICE_H
