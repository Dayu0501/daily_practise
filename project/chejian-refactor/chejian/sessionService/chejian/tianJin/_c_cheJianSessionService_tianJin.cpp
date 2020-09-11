#include "_c_cheJianSessionService_tianJin.h"
#include "_c_fuJian.h"

_c_cheJianSessionService_tianJin::_c_cheJianSessionService_tianJin(SESSIONSERVICE_PARAM *pSessionServiceParam):_c_cheJianSessionService(pSessionServiceParam)
{

}

bool _c_cheJianSessionService_tianJin::extraWorkBeforReponse(_c_session *pSession)
{
    _c_vehicle* _pVehicle = (_c_vehicle *)pSession;
    _c_fuJian* pFuJian = new _c_fuJian();
    if(pFuJian && _pVehicle->isRepeat == "0") // "2"复检 "1"重复 均不入库
    {
        pFuJian->cheJiaHao = _pVehicle->cheLiangShiBieDaiHao;
        pFuJian->dbWork();
    }

    return true;
}

 void _c_cheJianSessionService_tianJin::subClearCache(){
    _c_fuJian_clearTable*  tp_clear = new _c_fuJian_clearTable();
    tp_clear->dbWork() ;
    LOG(SESSION,INFO,"start tianjin subClearCache ...");
 }
