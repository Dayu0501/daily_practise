#ifndef _C_CHAYANSESSIONSERVICE_JINAN_H
#define _C_CHAYANSESSIONSERVICE_JINAN_H
#include "sessionService/chayan/_c_chaYanSessionService.h"

class _c_chaYanSessionService_jiNan: public _c_chaYanSessionService {
public:
    _c_chaYanSessionService_jiNan(PSTARTUPPRARAM param);
    virtual bool extraWorkBeforReponse(_c_session *pSession);
    virtual bool checkGreenChannel(_c_session *pSession);
	virtual void subClearCache();
private:
    Json::Value loadTouPingMsg(_c_chaYanVehicle *_pVehicle);
    std::vector<std::string> greenChannelShenFenZhengVector;

private:

};
#endif // _C_CHAYANSESSIONSERVICE_JINAN_H
