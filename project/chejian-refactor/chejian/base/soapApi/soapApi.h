#ifndef _SOAPAPI_H
#define _SOAPAPI_H
#include <string>

void *soapApi_creatSoapApiHandle(void);
void soapApi_closeSoapApiHandle(void *pHandele);

char *soapApi_requestData(void *p, char *_xtlb, const std::string &_confJkxlh, char *_jkid,const std::string &_queryString,
                          const char *_remoteServerIp_Char, const std::string &_SOAP_ServerPort, const std::string &_requestUri,
                          const std::string &_cjbh, const std::string &_zdbs, const std::string &_dwjgdm);

std::string soapApi_replyData(int timeout, char *_xtlb, std::string data, const std::string &_confJkxlh, char *_jkid, const char *_remoteServerIp_Char
                        , const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                        , const std::string &_zdbs, const std::string &_dwjgdm);

int AnalyseSoapReturn(std::string& retmsg,std::string& retcode);

void soapInit_checkRequestCount(unsigned int* maxSoapRequest);
void disableSoapFlag();
void resetSoapFlag();
bool test_soapReqRecord_isOK() ;


































#endif // _SOAPAPI_H


