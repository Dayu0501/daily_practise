#include "_c_cheJianSessionService.h"
#include "base/soapApi/soapApi.h"
#include "base/xml/Markup.h"
#include "base/baseTool.h"
#include <ctime>
#include "base/_c_wangLuoJieKouReturn.h"
#include "base/dataCenter.h"
#include "base/http/HttpClient.h"
//std::string _c_cheJianSessionService::getLshRequestXml(int timeLimit,std::string queryNumber)
//{
//    std::string queryString;
//    if (timeLimit > 0)
//    {
//        std::time_t t = std::time(NULL);
//        t += 86400;
//        std::tm *st = std::localtime(&t);
//        char tmpArray[128] = { 0 };
//        sprintf(tmpArray, "%d-%02d-%02d", st->tm_year + 1900, st->tm_mon + 1, st->tm_mday);
//        t -= (timeLimit * 86400);
//        st = std::localtime(&t);
//        char tmpArray2[128] = { 0 };
//        sprintf(tmpArray2, "%d-%02d-%02d", st->tm_year + 1900, st->tm_mon + 1, st->tm_mday);
//        queryString = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><QueryCondition><lsh></lsh>";
//        queryString += "<qsrq>";
//        queryString += tmpArray2;
//        queryString += "</qsrq><zzrq>";
//        queryString += tmpArray;
//        queryString += "</zzrq><fhzdjls>";
//        queryString += queryNumber;
//        queryString += "</fhzdjls><cxzt>1</cxzt></QueryCondition></root>";
//    }
//    else
//    {
//        queryString = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><QueryCondition><lsh></lsh><fhzdjls>";
//        queryString += queryNumber;
//        queryString += "</fhzdjls><cxzt>1</cxzt></QueryCondition></root>";
//    }
//    return queryString;
//}

std::string _c_cheJianSessionService::getLshRequestXml(std::string queryNumber)
{
    std::string queryString;
    if (_cheJianStartUpParam.qsrqOffset == 0 && _cheJianStartUpParam.zzrqOffset == 0)
    {
        queryString = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><QueryCondition><lsh></lsh><fhzdjls>";
        queryString += queryNumber;
        queryString += "</fhzdjls><cxzt>1</cxzt></QueryCondition></root>";
    }
    else
    {
        queryString = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><QueryCondition><lsh></lsh>";
        queryString += "<qsrq>";
        queryString += baseTool::getDangTianRiQi(_cheJianStartUpParam.qsrqOffset);
        queryString += "</qsrq><zzrq>";
        queryString += baseTool::getDangTianRiQi(_cheJianStartUpParam.zzrqOffset);
        queryString += "</zzrq><fhzdjls>";
        queryString += queryNumber;
        queryString += "</fhzdjls><cxzt>1</cxzt></QueryCondition></root>";
    }
    return queryString;
}

//解析返回的lsh信息
int _c_cheJianSessionService::AnalyseLshReturn(char *pLshReturn,std::vector<std::string> *pVector)
{
    CMarkup xml;
    int rownum = 0;
    xml.SetDoc(pLshReturn);
    xml.ResetMainPos();
    if (!xml.FindElem()) {
        LOG(SOAP,ERR,"Analyse_QueryReturn_Data: Can not find XML element! \n");
        LOG(SOAP,ERR,"Analyse_QueryReturn_Data: data:\n%s\n", pLshReturn);
        setDeviceState(URLDecode(pLshReturn));
        return -1;
    }

    xml.IntoElem();
    if (xml.FindElem("head"))
    {
        xml.IntoElem();
        setlocale(LC_ALL, "chs");
        if (xml.FindElem("code"))
        {
            if (atoi(xml.GetData().c_str()) == 1)
            {
                xml.ResetMainPos();
                if (xml.FindElem("rownum"))
                {
                    rownum = atoi(xml.GetData().c_str());
                    if (rownum > 0)
                    {
                         //printf("查询到%d个待检数据\n",rownum);
                    }
                    else if(rownum == 0)
                    {
                        setDeviceState("监管平台无审核数据");
                    }
                }
            }
        }

        xml.OutOfElem();
    }

    if(rownum > 0)
    {
        if (xml.FindElem("body"))
        {
            int vehicle_id = 0;
            xml.IntoElem();
            //printf("[解析body]\n");

            while (xml.FindElem("vehicle"))
            {
                if (atoi(xml.GetAttrib("id").c_str()) == vehicle_id)
                {
                        xml.FindChildElem("lsh");
                        std::string lsh = xml.GetChildData();
                        //printf("soap lsh:%s\n",lsh.c_str());
                        if(lsh.length()>0)
                            pVector->push_back(lsh);
                }
                vehicle_id++;
            }
        }
    }

    return pVector->size();
}

int _c_cheJianSessionService::AnalyseSoapReturn(string& retmsg,string& retcode)
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
        }
        xml.OutOfElem();
    }
    return 0;
}

int _c_cheJianSessionService::queryLiuShuiHao(void *p, std::vector<std::string> *pVector)
{
    //清空vector（防止分配已使用内存）
    pVector->clear();
    std::string LshRequestXml = getLshRequestXml(_cheJianStartUpParam.soapNum);
    char *queryReturn = soapApi_requestData(p,(char *)"18", _cheJianStartUpParam.soapXlh, (char *)"18C22", LshRequestXml
                                      , _cheJianStartUpParam.soapIp.c_str(), _cheJianStartUpParam.soapPort
                                      , _cheJianStartUpParam.soapUrl, _cheJianStartUpParam.g_cjbh, _cheJianStartUpParam.g_zdbs
                                      , _cheJianStartUpParam.g_dwjgdm);

    if(queryReturn != NULL)
    {
        LOG(SOAP,INFO,"queryLiuShuiHao : %s\n", queryReturn);
        return AnalyseLshReturn(queryReturn,pVector);
    }
    setDeviceState("监管平台连接不通");
    return 0;
}

void _c_cheJianSessionService::deRepeatLiuShuiHao(std::vector<std::string> *pVector,std::vector<std::string> *pNewVector)
{
    //此处去重需要先判断流水号是否重复，如果重复判断根据上次进入系统时间是否超过 _timeOutMilliseconds 设置的时间，超过则更新时间(updateInSystemTime())进入后续逻辑，否则丢弃
    pNewVector->clear();
    //遍历查询到的流水号
    for (unsigned int i = 0; i < pVector->size(); i++) {

        //是否重复的标记位
        bool isRepeat = false;
        //遍历已审核过的流水号
        for (unsigned int j = 0; j < _lshVector.size(); j++) {
            //检测流水号是否相同
            if(_lshVector[j].check((*pVector)[i]))
            {
                //将是否重复标记位设置位true
                isRepeat = true;
                LOG(COMMON,INFO,"repeat lsh:%s\n",(*pVector)[i].c_str());
                //判断进入系统时间是否超时
                if(_lshVector[j].getInSystemTime() > _timeOutMilliseconds)
                {
                    LOG(COMMON,INFO,"timeOut lsh:%s\n",(*pVector)[i].c_str());
                    //已超时则更新进入系统时间
                    _lshVector[j].updateInSystemTime();
                    pNewVector->push_back((*pVector)[i]);
                }
                break;
            }
        }

        //如果是新流水号则将流水号插入到已审核的流水号vector
        if(!isRepeat)
        {
            LOG(COMMON,INFO,"new lsh:%s\n",(*pVector)[i].c_str());
            lshVectorMember lsh_new((*pVector)[i]);
            _lshVector.push_back(lsh_new);
            pNewVector->push_back((*pVector)[i]);
        }
    }
}

std::string _c_cheJianSessionService::getVehicleInfoRequestXml(const std::string &_Lsh)
{
    std::string queryString = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><QueryCondition><lsh>";
    queryString += _Lsh;
    queryString += "</lsh><fhzdjls>1</fhzdjls><cxzt>2</cxzt></QueryCondition></root>";

    return queryString;
}

//解析返回的车辆信息
bool _c_cheJianSessionService::AnalyseVehicleReturn(char *pVehicleReturn,_c_vehicle *pVehicle, std::string remoteServerIp, std::string remoteServerPort, std::string photoUri)
{
    CMarkup xml;
    const std::string VehicleXml = pVehicleReturn;
    xml.SetDoc(URLDecode(VehicleXml).c_str());
    xml.ResetMainPos();
    if (!xml.FindElem()) {
        LOG(SOAP,ERR,"Analyse_QueryReturn_Data: Can not find XML element! \n");
        LOG(SOAP,ERR,"Analyse_QueryReturn_Data: data:\n%s\n", pVehicleReturn);
        return false;
    }

    xml.IntoElem();
    if (xml.FindElem("head"))
    {
        xml.IntoElem();
        setlocale(LC_ALL, "chs");

        if (xml.FindElem("code"))
        {
            if (atoi(xml.GetData().c_str()) != 1)
            {
                return false;
            }
        }

        xml.OutOfElem();
    }


    if (xml.FindElem("body"))
    {
        int vehicle_id = 0;
        xml.IntoElem();

        while (xml.FindElem("vehicle"))
        {
            if (atoi(xml.GetAttrib("id").c_str()) == vehicle_id)
            {
                for (unsigned int i = 0; i < pVehicle->memberVector.size(); i++) {
                    if (xml.FindChildElem(pVehicle->memberVector[i].soapName.c_str())){
                        std::string str = xml.GetChildData();

                        //printf("[%s]:%s\n",pVehicle->memberList[i].soapName.c_str(),str.c_str());

                        if (str.length() > 0) {
                        	if ("fdjh" == pVehicle->memberVector[i].soapName) {
		                        *pVehicle->memberVector[i].value = baseTool::deleteMarks(str, ' ');
                        	} else {
		                        *pVehicle->memberVector[i].value = str; //把从车管所拿过来的数据填充到对应的member的value中。
                        	}
                        }
                        else
                            *pVehicle->memberVector[i].value = "无数据";
                    }
                    else {
                        //printf("[%s]:not find data \n",pVehicle->memberList[i].soapName.c_str());
                        *pVehicle->memberVector[i].value = "无数据";
                    }
                    xml.ResetMainPos();
                }
                int photodes_id=0;
                xml.ResetMainPos();
                while (xml.FindElem("photodes"))
                {
                    _c_photo *pPhoto = new _c_photo();
                    pPhoto->zhaoPianBianHao = xml.GetAttrib("id").c_str();
                    if (atoi(xml.GetAttrib("id").c_str()) == photodes_id)
                    {

                        if (xml.FindChildElem("zpzl")){
                            std::string str = xml.GetChildData();
                            if (str.length() > 0)
                                pPhoto->algCode = str;
                            else
                                pPhoto->algCode = "无数据";
                        }

                        if (xml.FindChildElem("zpurl")){
                            std::string str = xml.GetChildData();
                            if (str.length() > 0)
                            {
                                std::string zpurlstr = "http://";
                                zpurlstr += remoteServerIp;
                                zpurlstr += ":";
                                zpurlstr += remoteServerPort;
                                zpurlstr += "/";
                                zpurlstr += photoUri;
                                zpurlstr += "/";
                                zpurlstr += str;
                                pPhoto->photoUrl = zpurlstr;

                            }
                            else
                                pPhoto->photoUrl = "无数据";
                        }

                    }
                    pVehicle->zhaoPianClassVector.push_back(pPhoto);

                    photodes_id++;
                }

                break;
            }
            vehicle_id++;
        }
        return true;
    }

    return false;
}

_c_vehicle *_c_cheJianSessionService::queryVehicleInfo(void *p, std::string liuShuiHao)
{
    _c_vehicle *pVehicle = NULL;
    std::string VehicleRequestXml = getVehicleInfoRequestXml(liuShuiHao);
    char *queryReturn = soapApi_requestData(p, (char *)"18", _cheJianStartUpParam.soapXlh, (char *)"18C22", VehicleRequestXml
                                      , _cheJianStartUpParam.soapIp.c_str(), _cheJianStartUpParam.soapPort
                                      , _cheJianStartUpParam.soapUrl, _cheJianStartUpParam.g_cjbh, _cheJianStartUpParam.g_zdbs
                                      , _cheJianStartUpParam.g_dwjgdm);
    if(queryReturn != NULL)
    {
        LOG(SOAP,INFO,"queryVehicleInfo : %s\n", queryReturn);

        pVehicle = loadVehicle();
        if(pVehicle!=NULL)
        {
            pVehicle->javaFlat = "0";
            if(!AnalyseVehicleReturn(queryReturn,pVehicle
                                             , _cheJianStartUpParam.remoteIp.c_str()
                                             , _cheJianStartUpParam.remotePort
                                             , _cheJianStartUpParam.soapPhotoUri))
            {
                delete pVehicle;
                pVehicle = NULL;
            }
            else
            {
                pVehicle->javaFlat = "0";
            } 
        }
    }

    return pVehicle;
}

int _c_cheJianSessionService::deRepeatVehicleInfo(_c_vehicleInfo &_VehicleInfo)
{
    std::string _oCrc16;
    std::string _nCrc16 = _VehicleInfo.getCheckMd5();

    for (unsigned int i = 0; i < _vehicleInfoVector.size(); i++)
    {
        _oCrc16 = _vehicleInfoVector[i].getCheckMd5();
        if (_nCrc16 == _oCrc16)
            return RET_REPEAT;
    }

    _nCrc16 = _VehicleInfo.getReCheckMd5();
    for (unsigned int i = 0; i < _vehicleInfoVector.size(); i++)
    {
        _oCrc16 = _vehicleInfoVector[i].getReCheckMd5();
        if (_nCrc16 == _oCrc16)
        {
            return RET_RECHECK;
        }
    }

    //没有重复就返回RET_NORMAL
    return RET_NORMAL;
}

bool _c_cheJianSessionService::vehicleSetDisposeEnd(_c_object *pObject)
{
    bool ret = false;
    //通过guid找到对应的_c_vehicleInfo,保存对应车辆的照片结果信息
    for (unsigned int i = 0; i < _vehicleInfoVector.size(); i++)
    {
        if (_vehicleInfoVector[i].getGuid() == pObject->uuid)
        {
            LOG(COMMON,INFO,"locate vehicle with uuid: %s\n", _vehicleInfoVector[i].getGuid().c_str());
            _vehicleInfoVector[i].setDisposeEnd((_c_vehicle *)pObject);
            ret = true;
            break;
        }
    }

    if (!ret){
        _c_vehicle *_pVehicle = (_c_vehicle *)pObject;
        LOG(COMMON,ERR,"vehicle %s[%s] __guid dismatch, set dispose failed\n", _pVehicle->liuShuiHao.c_str(), _pVehicle->uuid.c_str());
    }

    return ret;
}

bool _c_cheJianSessionService::repeatVehicleDisponse(_c_object *pObject)
{
    //根据_checkKey获取车辆相关PHOTO信息，写回pVehicle
    bool ret = false;
     _c_vehicle *_pVehicle = (_c_vehicle *)pObject;
    _c_vehicleInfo _VehicleInfo(_pVehicle);
    for (unsigned int i = 0; i < _vehicleInfoVector.size(); i++)
    {
        if (_vehicleInfoVector[i].getCheckMd5() == _VehicleInfo.getCheckMd5())
        {
            LOG(COMMON,INFO,"get vehicle %s[%s] with keycode: %s\n", _pVehicle->liuShuiHao.c_str(), _pVehicle->uuid.c_str(),_vehicleInfoVector[i].getCheckMd5().c_str());
            ret = _vehicleInfoVector[i].getVehiclePhotoInfo(_pVehicle);
            return ret;
        }
    }

    LOG(COMMON,ERR,"error :repetitive vehicle %s[%s] _checkKey dismatch! \n", _pVehicle->liuShuiHao.c_str(), _pVehicle->uuid.c_str());

    return ret;
}

void _c_cheJianSessionService::freeUnusefulRepeatedVehicleInfo(_c_object *pObject)
{
     _c_vehicle *pVehicle = (_c_vehicle *)pObject;
     _c_photo *pPhoto = NULL;
     //先把原来的照片相关信息释放掉
     for (unsigned int i = 0; i < pVehicle->zhaoPianClassVector.size(); i++)
     {
         pPhoto = pVehicle->zhaoPianClassVector[i];
         if (pPhoto != NULL)
         {
             delete pPhoto;
             pPhoto = NULL;
         }
     }
     pVehicle->zhaoPianClassVector.clear();
}

void _c_cheJianSessionService::clearCache()
{
    _lshVector.clear();
    _vehicleInfoVector.clear();
    clearData();
	subClearCache();
}

std::string _c_cheJianSessionService::getVehicleGroupPhotoResponseXml(const _c_vehicle *p_vehicle)
{
    std::string xmldata;

    CMarkup xml;
    xml.SetDoc("<?xml version=\"1.0\" encoding=\"GBK\"?>\r\n");
    xml.AddElem("root");
    xml.IntoElem();
    setlocale(LC_ALL, "chs");
    xml.AddElem("vehispara");
    xml.IntoElem();
    xml.AddElem("lsh");
    xml.SetData(p_vehicle->liuShuiHao);
    xml.AddElem("zpshjgs");
    xml.IntoElem();
    for (unsigned int i = 0; i < p_vehicle->zhaoPianClassVector.size(); i++)
    {
//        if(p_vehicle->zhaoPianClassVector[i]->algCode.substr(0,1)=="0")
        if (p_vehicle->zhaoPianClassVector[i]->result.empty())
        {
            p_vehicle->zhaoPianClassVector[i]->result =  std::to_string(4);
            p_vehicle->zhaoPianClassVector[i]->reason =  "未知检验类型";
        }
		
                xml.AddElem("zpshjg");
                xml.AddChildElem("zpzl");
                xml.SetChildData(p_vehicle->zhaoPianClassVector[i]->algCode);
                xml.AddChildElem("jg");
                xml.SetChildData(p_vehicle->zhaoPianClassVector[i]->result);
                xml.AddChildElem("sm");
                std::string smstr = p_vehicle->zhaoPianClassVector[i]->reason;
                smstr = URLEncode(smstr.c_str());
                xml.SetChildData(smstr);
    }
    xml.OutOfElem();
    xml.OutOfElem();
    xml.OutOfElem();
    xmldata = xml.GetDoc();

//    LOG(SOAP,DEBUG,"The result XML message has been send: \n %s---------------------\n",xmldata.c_str());
    return xmldata;
}

void _c_cheJianSessionService::photoResultGroupReply(void *p, const _c_vehicle *p_vehicle, const std::string &_confJkxlh, const char *_remoteServerIp_Char
                                   , const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                                   , const std::string &_zdbs, const std::string &_dwjgdm)
{
    UNUSED(p);
    std::string xmldata;
    int send_count = 2;

    xmldata = getVehicleGroupPhotoResponseXml(p_vehicle);

    while (send_count != 0) {
        std::string writeReturn ;
        LOG(SOAP,INFO,"chejian_group_result \n %s \n", xmldata.c_str());
        writeReturn = soapApi_replyData(10, (char *)"18", xmldata, _confJkxlh, (char *)"18C92", _remoteServerIp_Char, _SOAP_ServerPort, _requestUri, _cjbh, _zdbs, _dwjgdm);

//        printf("Send photo group result %s \n" ,writeReturn);

        LOG(SOAP,INFO,"chejian_group_result_return -----%s\n" ,writeReturn.c_str());
        //std::string retcode = "";
        if (writeReturn.size() > 0 ){
            //LOG(SOAP,INFO,"Send photo group_result :[%s] -----\n" ,writeReturn.c_str());
            //AnalyseSoapReturn(writeReturn,retcode) ;
            const_cast<_c_vehicle*>(p_vehicle)->soapReplyCode = writeReturn;
            return;
        }
        else
            LOG(COMMON,WARN,"The result of sending photo group is NULL\n");

        send_count--;
    }
    LOG(SOAP,INFO,"chejian_group_result sendNum:%d -----\n" ,send_count);

}

void _c_cheJianSessionService::sendPhotoSingleResult(void *p, const _c_vehicle *p_vehicle, int zplist_index, std::string data, const std::string &_confJkxlh, const char *_remoteServerIp_Char
                                          , const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                                          , const std::string &_zdbs, const std::string &_dwjgdm)
{
    UNUSED(p_vehicle);UNUSED(p);UNUSED(zplist_index);
    int send_count = 5;

    while (send_count != 0) {
        std::string writeReturn ;
        //printf("Send photo(LSH:%s, ZPZL:%s) result to SOAP server...... \n",
//               p_vehicle->liuShuiHao.data(),
//               zplist_index == -1 ? "zplist is empty" : p_vehicle->zhaoPianVector[zplist_index].zhaoPianLeiXing.data());

        writeReturn = soapApi_replyData(10, (char *)"18", data, _confJkxlh, (char *)"18C92", _remoteServerIp_Char, _SOAP_ServerPort, _requestUri, _cjbh, _zdbs, _dwjgdm);

//        printf("Send photo single result %s \n" ,writeReturn);

        if (writeReturn.size() > 0){
            return;
        }
        else
            LOG(COMMON,WARN,"The result of sending photo single is NULL\n");

        send_count--;
    }
}

void _c_cheJianSessionService::photoResultSingleReply(void *p, const _c_vehicle *p_vehicle, const std::string &_confJkxlh, const char *_remoteServerIp_Char
                                           , const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                                           , const std::string &_zdbs, const std::string &_dwjgdm)
{
    std::string xmldata;

    for (unsigned int i = 0; i < p_vehicle->zhaoPianClassVector.size(); i++) {
        if (p_vehicle->zhaoPianClassVector[i]->result.empty())
        {
            p_vehicle->zhaoPianClassVector[i]->result =  std::to_string(4);
            p_vehicle->zhaoPianClassVector[i]->reason =  "未知检验类型";
        }

        xmldata = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><vehispara><lsh>";
        xmldata += p_vehicle->liuShuiHao;
        xmldata += "</lsh><zpzl>";
        xmldata += p_vehicle->zhaoPianClassVector[i]->algCode;
        xmldata += "</zpzl><jg>";
        xmldata += p_vehicle->zhaoPianClassVector[i]->result;
        xmldata += "</jg><sm>";
        std::string smstr = p_vehicle->zhaoPianClassVector[i]->reason;
        smstr = URLEncode(smstr.c_str());
        xmldata += smstr;
        xmldata += "</sm></vehispara></root>";
		
        LOG(SOAP,INFO,"The result XML message has been send: \n %s---------------------\n",xmldata.c_str());
        sendPhotoSingleResult(p, p_vehicle, i, xmldata, _confJkxlh, _remoteServerIp_Char, _SOAP_ServerPort, _requestUri, _cjbh, _zdbs, _dwjgdm);
    }
}

bool _c_cheJianSessionService::checkWorkTime()
{
    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);
    int nowIntVal= st->tm_hour *60 + st->tm_min ;
  //  if (st->tm_hour >= _cheJianStartUpParam.startTime && st->tm_hour <= _cheJianStartUpParam.endTime)
    if (nowIntVal >= _cheJianStartUpParam.startTime && nowIntVal <= _cheJianStartUpParam.endTime)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string _c_cheJianSessionService::getJqxRequestXml(_c_vehicle *pVehicle)
{
    std::string queryString;

    queryString = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><QueryCondition><lsh></lsh>";
    queryString += "<hpzl>";
    queryString += "</hpzl><hphm>";
    queryString += "</hphm><clsbdh>";
    queryString += pVehicle->cheLiangShiBieDaiHao;
    queryString += "</clsbdh>";
    queryString += "<jyjgbh>";
    queryString += pVehicle->jianYanJiGouBianHao;
    queryString += "</jyjgbh>";
    queryString += "</QueryCondition></root>";

    return queryString;
}

bool _c_cheJianSessionService::AnalyseJqxReturn(char *pJqxReturn, _c_vehicle *pVehicle, _c_jiaoQiangXianJkReturnInfo *pJqxInfo)
{
    CMarkup xml;
    const std::string jqxXml = pJqxReturn;
    xml.SetDoc(URLDecode(jqxXml).c_str());
    xml.ResetMainPos();
    if (!xml.FindElem()) {
        LOG(SOAP,ERR,"AnalyseJqxReturn: Can not find XML element! \n");
        LOG(SOAP,ERR,"AnalyseJqxReturn: data:\n%s\n", pJqxReturn);
        return false;
    }

    xml.IntoElem();
    if (xml.FindElem("head"))
    {
        xml.IntoElem();
        setlocale(LC_ALL, "chs");

        if (xml.FindElem("code"))
        {
            if (atoi(xml.GetData().c_str()) != 1)
            {
                return false;
            }
        }

        xml.OutOfElem();
    }

    if (xml.FindElem("body"))
    {
        xml.IntoElem();

        if (xml.FindElem("vehispara"))
        {
//            printf("%s %d\n", __func__, __LINE__);
            for (unsigned int i = 0; i < pJqxInfo->memberVector.size(); i++)
            {
                if (xml.FindChildElem(pJqxInfo->memberVector[i].soapName.c_str()))
                {
                    std::string str = xml.GetChildData();
                    //printf("[%s]:%s\n",pReturnInfo->memberList[i].soapName.c_str(),str.c_str());
                    if (str.length() > 0)
                        *pJqxInfo->memberVector[i].value = str;
                    else
                        *pJqxInfo->memberVector[i].value = "无数据";
                }
                else
                {
                    //printf("[%s]:not find data \n",pReturnInfo->memberList[i].soapName.c_str());
                    if (pJqxInfo->memberVector[i].soapName != "jieKouBiaoShi")//表示不能被覆盖
                    {
                        *pJqxInfo->memberVector[i].value = "无数据";
                    }

                    if (pJqxInfo->memberVector[i].soapName == "isGetData")
                    {
                        *pJqxInfo->memberVector[i].value = "true";
                    }
                }
                xml.ResetMainPos();
            }

            return true;
        }
    }

    printf("AnalyseJqxReturn failed!\n");
    LOG(SOAP,WARN,"AnalyseJqxReturn failed!\n");

    return false;
}

bool _c_cheJianSessionService::queryJiaoQiangXian(void *p, _c_vehicle *pVehicle, std::string shouQuanMa)
{
    bool ret = false;
    std::string jqxRequestXml = getJqxRequestXml(pVehicle);
    //printf("queryJiaoQiangXian:\n %s\n", jqxRequestXml.c_str());
    char *queryReturn = soapApi_requestData(p, (char *)"18", shouQuanMa, (char *)"18C23", jqxRequestXml
                                      , _cheJianStartUpParam.soapIp.c_str(), _cheJianStartUpParam.soapPort
                                      , _cheJianStartUpParam.soapUrl, _cheJianStartUpParam.g_cjbh, _cheJianStartUpParam.g_zdbs
                                      , _cheJianStartUpParam.g_dwjgdm);

    _c_jiaoQiangXianJkReturnInfo *pJqxInfo = new _c_jiaoQiangXianJkReturnInfo();

    if(queryReturn != NULL)
    {
        LOG(SOAP,INFO,"queryJiaoQiangXian : %s\n", queryReturn);
//        printf("queryJiaoQiangXian : %s\n", queryReturn);
        ret =  AnalyseJqxReturn(queryReturn, pVehicle, pJqxInfo);
    }
    else
    {
//        printf("queryJiaoQiangXian no return\n");
        LOG(SOAP,WARN,"queryJiaoQiangXian no return\n", queryReturn);
    }

    if (!ret)
    {
        //没有获取到有效数据
        objectMember *pObject = baseTool::getObjectItemByName(&pJqxInfo->memberVector, "isGetData");
        *pObject->value = "false";
    }

    pJqxInfo->cheLiangUid = pVehicle->uuid;
    pVehicle->wangLuoJieKouReturnVector.push_back(pJqxInfo);

    return ret;
}

//执行标识所对应的操作
void _c_cheJianSessionService::processWangLuoJieKouInfo(void *p, _c_vehicle *pVehicle)
{
    for (unsigned int i = 0; i < _wangLuoJieKouInfo->size(); i++) {
        if ((*_wangLuoJieKouInfo)[i].biaoShi == "18C23")
        {
            queryJiaoQiangXian(p, pVehicle, (*_wangLuoJieKouInfo)[i].shouQuanMa);
        }
    }
}

void requestVideoInfoThreadHandle(std::string uri)
{
//    printf("%s uri:%s\n", __func__, uri.c_str());
    LOG(SOAP, INFO, "requestVideoInfo: %s\n", uri.c_str());

    HttpClient clientGet;
    clientGet.set_retries_timeout(2, 12);

    if (!clientGet.init_data(uri.c_str(), REQUEST_GET_FLAG, NULL, NULL))
    {
        printf("requestVideoInfo uri init error %s.\n",uri.c_str());
    }
    clientGet.startHttpClient();

    //后续添加如果对方服务器异常的判断,以及记录
}

//uri中需要包含的项
//1. 城市代码 2. 车辆UUID 3. lsh 4. jylsh 5. clsbdh 6. fzjg 7. hphm 8. hpzl 9. jyjgbh
void _c_cheJianSessionService::requestVideoInfo(_c_vehicle *pVehicle)
{
    //先要判断是否是本地部署
    std::string portIp = "127.0.0.1:10001";
    bool isInList = false;

    if (_videoCheckJyjgbhConfig != NULL)
    {
        for (unsigned int i = 0; i < _videoCheckJyjgbhConfig->size(); i++)
        {
            if ((*_videoCheckJyjgbhConfig)[i].jyjgbh == pVehicle->jianYanJiGouBianHao)
            {
                if ((*_videoCheckJyjgbhConfig)[i].tongXunFangShi == "remote")
                {
                    portIp = (*_videoCheckJyjgbhConfig)[i].portIp;
                }
                isInList = true;
                break;
            }
        }
    }

    if (!isInList)
    {
        pVehicle->downloadVideoState = "该检验机构暂未提供视频";
        pVehicle->videoCheckInfo.shiPinDownloadIsFinished = true;
        return;
    }

    std::string uri = "";
    uri += "http://";
    uri += portIp;
    uri += "/requestVideoInfo?";
    uri += "city=" + _cityCode + "&";
    uri += "cheLiangUid=" + pVehicle->uuid + "&";
    uri += "lsh=" + normalizeUriContent(pVehicle->liuShuiHao) + "&";
    uri += "jylsh=" + normalizeUriContent(pVehicle->jianYanLiuShuiHao) + "&";
    uri += "jyjgbh=" + normalizeUriContent(pVehicle->jianYanJiGouBianHao) + "&";
    uri += "clsbdh=" + normalizeUriContent(pVehicle->cheLiangShiBieDaiHao) + "&";
    uri += "fzjg=" + normalizeUriContent(pVehicle->faZhengJiGuan) + "&";
    uri += "hphm=" + normalizeUriContent(pVehicle->haoPaiHaoMa) + "&";
    uri += "hpzl=" + normalizeUriContent(pVehicle->haoPaiZhongLei);

//    printf("%s uri:%s\n", __func__, uri.c_str());
    std::thread *sendThread = new std::thread(requestVideoInfoThreadHandle, uri);
    sendThread->detach();
    delete sendThread;
}
