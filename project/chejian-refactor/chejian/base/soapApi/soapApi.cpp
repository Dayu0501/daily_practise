#include "soapApi.h"
#include <vector>
#include <string>
#include "soapTmriOutAccessSoapBindingProxy.h"
#include "RecordSoapRequestInDB.h"
#include "base/_c_vehicle.h"
#include "base/xml/Markup.h"

bool newSoapInterface = false;
std::string  ns1_queryObjectOut ="ns1:queryObjectOut";
std::string  ns1_queryObjectOutResponse="ns1:queryObjectOutResponse";
std::string  queryObjectOutResponse="queryObjectOutResponse";
std::string  queryObjectOut="queryObjectOut";
std::string  ns1_writeObjectOut="ns1:writeObjectOut";
std::string  ns1_writeObjectOutResponse="ns1:writeObjectOutResponse";
std::string  writeObjectOutResponse="writeObjectOutResponse";
std::string  writeObjectOut="writeObjectOut"; /* soap接口字符串 用于控制新旧接口*/
static RecordSoapRequestTimes  soapReqRecord;
bool test_soapReqRecord_isOK(){
    return soapReqRecord.isOk() ;
}
void recordData(){
    while( true ) {
        soapReqRecord.generateRecordSoapRequestInDB()->dbWork() ;

        std::this_thread::sleep_for(std::chrono::seconds(20) )  ;
    }
}
void disableSoapFlag(){
    soapReqRecord.disableToday();
}
void resetSoapFlag()
{
    soapReqRecord.clear();
}
void soapInit_checkRequestCount(unsigned int* maxSoapRequest){

    unsigned int usedTimes  = 0 ,permits = 0 ;
    Json::Value val = queryRecordSoapTimes();

    if(val.size() == 1){
        unsigned int index = 0 ;
        std::string todayTimeS = val[index]["todayRequestTimes"].asString() ;
        std::string permitTimeS = val[index]["todayPermitTimes"].asString() ;

        ns_baseTool::str2number<unsigned int>(todayTimeS.c_str(),&usedTimes, "%u") ;
        ns_baseTool::str2number<unsigned int>(permitTimeS.c_str(),&permits, "%u") ;

        std::string today = val[index]["today"].asString();
        if( today == baseTool::getDangTianRiQi() ){
             soapReqRecord.currentDayRequestTimes = usedTimes ;
             soapReqRecord.permitTimes =permits ;
        }
    }
    soapReqRecord.init(  maxSoapRequest);
    std::thread * th = new std::thread(recordData);
}

void *soapApi_creatSoapApiHandle(void)
{
    TmriOutAccessSoapBindingProxy *soapclient = new TmriOutAccessSoapBindingProxy();
    soapclient->accept_timeout = 30;
    soapclient->connect_timeout = 30;
    soapclient->recv_timeout = 30;
    soapclient->send_timeout = 30;
    return (void *)soapclient;
}

void soapApi_closeSoapApiHandle(void *pHandele)
{
    UNUSED(pHandele);
}

char *soapApi_requestData(void *p, char *_xtlb, const std::string &_confJkxlh, char *_jkid, const std::string &_queryString, const char *_remoteServerIp_Char
                          , const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                          , const std::string &_zdbs, const std::string &_dwjgdm)
{
    if(!soapReqRecord.isOk()){
        return NULL ;
    }
    char *queryReturn = NULL;
    TmriOutAccessSoapBindingProxy *soapclient = static_cast<TmriOutAccessSoapBindingProxy *>(p);
    soapclient->queryObjectOut(_xtlb, (char *)_confJkxlh.c_str(), _jkid, (char *)_queryString.c_str(), queryReturn
                               , _remoteServerIp_Char, _SOAP_ServerPort, _requestUri, _cjbh, _zdbs, _dwjgdm);
    return queryReturn;
}

std::string soapApi_replyData(int timeout, char *_xtlb, std::string data, const std::string &_confJkxlh, char *_jkid, const char *_remoteServerIp_Char
                        , const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                        , const std::string &_zdbs, const std::string &_dwjgdm)
{
    TmriOutAccessSoapBindingProxy soapclient;
    soapclient.accept_timeout = timeout;
    soapclient.connect_timeout = timeout;
    soapclient.recv_timeout = timeout;
    soapclient.send_timeout = timeout;
    char *queryReturn = NULL;

    int val=soapclient.writeObjectOut(_xtlb, (char *)_confJkxlh.c_str(), _jkid, (char *)data.c_str(), queryReturn
                               , _remoteServerIp_Char, _SOAP_ServerPort, _requestUri, _cjbh, _zdbs, _dwjgdm);
    std::string retcode ;
    std::string soapRet ;
    if(val == SOAP_OK){
        soapRet.assign(queryReturn,strlen(queryReturn) );
        AnalyseSoapReturn(soapRet,  retcode) ;
    }
    LOG(SOAP,INFO,"soap_error:%d ,%s,size:%d\n",val,soapRet.c_str() ,soapRet.size()) ;
    return retcode ;
}
int AnalyseSoapReturn(std::string& retmsg,std::string& retcode)
{
    //printf("%s \n",retmsg.c_str() );
    CMarkup xml;
    xml.SetDoc(retmsg.c_str() );
    xml.ResetMainPos();
    if (!xml.FindElem()) {
        printf("find error") ;
        return -1;
    }

    xml.IntoElem();
    if (xml.FindElem("head"))
    {
        xml.IntoElem();
        if (xml.FindElem("code"))
        {
           // if (atoi(xml.GetData().c_str()) == 1)
           //printf("getcode:%s \n", xml.GetData().c_str() );
           retcode = xml.GetData().c_str() ;
           if( retcode == "12" ){
               disableSoapFlag() ;
           }
           //TODO retcode == 12 disable request
        }
        xml.OutOfElem();
    }
    return 0;
}
