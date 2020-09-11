#include "_c_chaYanSessionService.h"
#include "base/soapApi/soapApi.h"
#include "base/xml/Markup.h"
#include "base/baseTool.h"
#include <ctime>

std::string _c_chaYanSessionService::getLshRequestXml(std::string num, std::string model)
{
#ifdef TESTANDROID
    std::string queryxml = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><QueryCondition><lsh></lsh><zplb>1</zplb><fhzdjls>";
    queryxml += num;
    queryxml += "</fhzdjls><cxzt>1</cxzt></QueryCondition></root>";

#else
    std::string queryxml = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><QueryCondition><lsh></lsh><zplb>";
    queryxml += model;
    queryxml += "</zplb><qsrq>";
    queryxml += baseTool::getDangTianRiQi(_chaYanStartUpParam.qsrqOffset);
    queryxml += "</qsrq><zzrq>";
    queryxml += baseTool::getDangTianRiQi(_chaYanStartUpParam.zzrqOffset);
    queryxml += "</zzrq><fhzdjls>";
    queryxml += num;
    queryxml += "</fhzdjls><cxzt>1</cxzt></QueryCondition></root>";
#endif
    return queryxml;
}

int _c_chaYanSessionService::queryWaiGuanLiuShuiHao(void *pSoap, std::vector<std::string> *pVector)
{
//    printf("queryWaiGuanLiuShuiHao \n");
//    std::string LshRequestXml = getLshRequestXml("10","1");
    std::string LshRequestXml = getLshRequestXml(_chaYanStartUpParam.soapNum, "1");

    return queryLiuShuiHao(pSoap, LshRequestXml, pVector);
}

int _c_chaYanSessionService::queryZhengJianLiuShuiHao(void *pSoap, std::vector<std::string> *pVector)
{
//    printf("queryZhengJianLiuShuiHao \n");
//    std::string LshRequestXml = getLshRequestXml("10","2");
    std::string LshRequestXml = getLshRequestXml(_chaYanStartUpParam.soapNum, "2");

    return queryLiuShuiHao(pSoap, LshRequestXml, pVector);
}

int _c_chaYanSessionService::queryLiuShuiHao(void *pSoap, std::string &LshRequestXml, std::vector<std::string> *pVector)
{
    //清空vector（防止分配已使用内存）
    pVector->clear();
    char *queryReturn = soapApi_requestData(pSoap, (char *)"18", _chaYanStartUpParam.soapXlh, (char *)"18CK3", LshRequestXml
                                            , _chaYanStartUpParam.soapIp.c_str(), _chaYanStartUpParam.soapPort, _chaYanStartUpParam.soapUrl
                                            , _chaYanStartUpParam.g_zdbs, _chaYanStartUpParam.g_cjbh, _chaYanStartUpParam.g_dwjgdm);

    if(queryReturn == NULL)
    {
        printf("SOAP server no response! \n");
    }
    else
    {
//        printf("queryLiuShuiHao : %s\n", queryReturn);
        return AnalyseLshReturn(queryReturn, pVector);
    }

    return 0;
}

//解析返回的lsh信息
int _c_chaYanSessionService::AnalyseLshReturn(char *pLshReturn, std::vector<std::string> *pVector)
{
    CMarkup xml;
    int rownum = 0;
    xml.SetDoc(pLshReturn);
    xml.ResetMainPos();
    if (!xml.FindElem()) {
        LOG(SOAP,ERR,"AnalyseLshReturn: Can not find XML element! \n");
        LOG(SOAP,ERR,"AnalyseLshReturn: data:\n%s\n", pLshReturn);
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
//                        printf("soap lsh:%s\n",lsh.c_str());
                        if(lsh.length()>0)
                            pVector->push_back(lsh);
                }
                vehicle_id++;
            }
        }
    }

    return pVector->size();
}

void _c_chaYanSessionService::deRepeatLiuShuiHao(std::vector<std::string> *pVector, std::vector<std::string> *pNewVector, bool mode)
{
    //此处去重需要先判断流水号是否重复，如果重复判断根据上次进入系统时间是否超过 _timeOutMilliseconds 设置的时间，超过则更新时间(updateInSystemTime())进入后续逻辑，否则丢弃
    pNewVector->clear();

    std::vector<lshVectorMember> *plshVector;
    if (mode){
        plshVector = &_waiGuanLshVector;
    } else {
        plshVector = &_zhengJianlshVector;
    }

    //遍历查询到的流水号
    for (unsigned int i = 0; i < pVector->size(); i++) {
        //是否重复的标记位
        bool isRepeat = false;
        //遍历已审核过的流水号
        for (unsigned int j = 0; j < plshVector->size(); j++) {
            //检测流水号是否相同
            if((*plshVector)[j].check((*pVector)[i]))
            {
                //将是否重复标记位设置位true
                isRepeat = true;
                LOG(COMMON,INFO,"repeat lsh:%s\n",(*pVector)[i].c_str());
                //判断进入系统时间是否超时
                if((*plshVector)[j].getInSystemTime() > _timeOutMilliseconds)
                {
                    LOG(COMMON,INFO,"timeOut lsh:%s\n",(*pVector)[i].c_str());
                    //已超时则更新进入系统时间
                    (*plshVector)[j].updateInSystemTime();
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
            plshVector->push_back(lsh_new);
            pNewVector->push_back((*pVector)[i]);
        }
    }
}


bool _c_chaYanSessionService::AnalyseVehicleReturn(char *pVehicleReturn, _c_chaYanVehicle *pVehicle, std::string model, std::string remoteServerIp, std::string remoteServerPort, std::string photoUri)
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
                        if (str.length() > 0)
                            *pVehicle->memberVector[i].value = str;
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
//                              printf("photoUrl %s\n", pPhoto->photoUrl.c_str());
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

std::string _c_chaYanSessionService::getVehicleInfoRequestXml(std::string lsh,string model)
{
#ifdef TESTANDROID
    std::string queryxml = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><QueryCondition><lsh>";
    queryxml += lsh;
    queryxml += "</lsh><zplb>1</zplb><fhzdjls>1</fhzdjls><cxzt>2</cxzt></QueryCondition></root>";
#else
    std::string queryxml = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><QueryCondition><lsh>";
    queryxml += lsh;
    queryxml += "</lsh><zplb>";
    queryxml += model;
    queryxml += "</zplb><qsrq>";
    queryxml += baseTool::getDangTianRiQi(_chaYanStartUpParam.qsrqOffset);
    queryxml += "</qsrq><zzrq>";
    queryxml += baseTool::getDangTianRiQi(_chaYanStartUpParam.zzrqOffset);
    queryxml += "</zzrq><fhzdjls>1</fhzdjls><cxzt>2</cxzt></QueryCondition></root>";
#endif
    return queryxml;
}

_c_chaYanVehicle * _c_chaYanSessionService::queryVehicleInfo(void *pSoap, std::string liuShuiHao, std::string mode)
{
//    printf("queryVehicleInfo lsh:%s \n", liuShuiHao.c_str());
    _c_chaYanVehicle *pVehicle = NULL;
    std::string VehicleRequestXml = getVehicleInfoRequestXml(liuShuiHao , mode);
    char *queryReturn = soapApi_requestData(pSoap, (char *)"18", _chaYanStartUpParam.soapXlh, (char *)"18CK3", VehicleRequestXml
                                            , _chaYanStartUpParam.soapIp.c_str(), _chaYanStartUpParam.soapPort
                                            , _chaYanStartUpParam.soapUrl, _chaYanStartUpParam.g_zdbs, _chaYanStartUpParam.g_cjbh, _chaYanStartUpParam.g_dwjgdm);

    if(queryReturn != NULL)
    {
//        printf("vechile return_msg :%s－－－－－－－ \n", queryReturn);
        pVehicle = new _c_chaYanVehicle();
        if(pVehicle != NULL)
        {
            if(!AnalyseVehicleReturn(queryReturn,pVehicle, mode
                                     , _chaYanStartUpParam.remoteIp.c_str()
                                     , _chaYanStartUpParam.remotePort
                                     , _chaYanStartUpParam.soapPhotoUri))
            {
                printf("AnalyseVehicleReturn lsh:%s failed \n", liuShuiHao.c_str());
                LOG(COMMON,ERR,"AnalyseVehicleReturn lsh:%s failed \n", liuShuiHao.c_str());
                delete pVehicle;
                pVehicle = NULL;
            }
        }
    }

    return pVehicle;
}

bool _c_chaYanSessionService::deRepeatVehicleInfo(_c_chaYanVehicleInfo &_VehicleInfo)
{
    uint16_t _oCrc16 = 0;
    uint16_t _nCrc16 = _VehicleInfo.getCheckKey();

    for (unsigned int i = 0; i < _vehicleInfoVector.size(); i++)
    {
        _oCrc16 = _vehicleInfoVector[i].getCheckKey();
        if (_nCrc16 == _oCrc16)
            return false;
    }

    //没有重复就返回true
    return true;
}

bool _c_chaYanSessionService::vehicleSetDisposeEnd(_c_object *pObject)
{
    bool ret = false;
    //通过guid找到对应的_c_vehicleInfo,保存对应车辆的照片结果信息
    for (unsigned int i = 0; i < _vehicleInfoVector.size(); i++)
    {
        if (_vehicleInfoVector[i].getGuid() == pObject->uuid)
        {
            LOG(COMMON,INFO,"locate vehicle with uuid: %s\n", _vehicleInfoVector[i].getGuid().c_str());
            _vehicleInfoVector[i].setDisposeEnd((_c_chaYanVehicle *)pObject);
            ret = true;
            break;
        }
    }

    if (!ret){
        _c_chaYanVehicle *_pVehicle = (_c_chaYanVehicle *)pObject;
        LOG(COMMON,ERR,"vehicle %s[%s] __guid dismatch, set dispose failed\n", _pVehicle->liuShuiHao.c_str(), _pVehicle->uuid.c_str());
    }

    return ret;
}

bool _c_chaYanSessionService::repeatVehicleDisponse(_c_object *pObject)
{
    //根据_checkKey获取车辆相关PHOTO信息，写回pVehicle
    bool ret = false;
    _c_chaYanVehicle *_pVehicle = (_c_chaYanVehicle *)pObject;
    _c_chaYanVehicleInfo _VehicleInfo(_pVehicle);
    for (unsigned int i = 0; i < _vehicleInfoVector.size(); i++)
    {
        if (_vehicleInfoVector[i].getCheckKey() == _VehicleInfo.getCheckKey())
        {
            LOG(COMMON,INFO,"get vehicle %s[%s] with keycode: 0x%x\n", _pVehicle->liuShuiHao.c_str(), _pVehicle->uuid.c_str(),_vehicleInfoVector[i].getCheckKey());
            ret = _vehicleInfoVector[i].getVehiclePhotoInfo(_pVehicle);
            return ret;
        }
    }

    LOG(COMMON,ERR,"error :repetitive vehicle %s[%s] _checkKey dismatch! \n", _pVehicle->liuShuiHao.c_str(), _pVehicle->uuid.c_str());

    return ret;
}

void _c_chaYanSessionService::freeUnusefulRepeatedVehicleInfo(_c_object *pObject)
{
     _c_chaYanVehicle *pVehicle = (_c_chaYanVehicle *)pObject;
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

void _c_chaYanSessionService::clearCache()
{
    _waiGuanLshVector.clear();
    _zhengJianlshVector.clear();
    _vehicleInfoVector.clear();
	subClearCache();
    clearData();
}

std::string _c_chaYanSessionService::getVehicleGroupPhotoResponseXml(const _c_chaYanVehicle *p_vehicle)
{
    std::string xmlstring;

    CMarkup xml;
    xml.SetDoc("<?xml version=\"1.0\" encoding=\"GBK\"?>\r\n");
    xml.AddElem("root");
    xml.IntoElem();
    xml.AddElem("vehcrpara");
    xml.IntoElem();
    xml.AddElem("lsh");
    xml.SetData(p_vehicle->liuShuiHao);
    xml.AddElem("zplb");
    xml.SetData(p_vehicle->waiGuanBiaoDanBiaoZhi);
    xml.AddElem("zpshjgs");
    xml.IntoElem();

    /* 照片列表为空时*/
    if (p_vehicle->zhaoPianClassVector.size() == 0)
    {
        xml.AddElem("zpshjg");
        xml.AddChildElem("zpzl");
        xml.SetChildData("no picture");
        xml.AddChildElem("jg");
        xml.SetChildData("5");
        xml.AddChildElem("sm");
        std::string smstr = "无照片信息";
        smstr = URLEncode(smstr);
        xml.SetChildData(smstr);
    }
    else
    {
        for (unsigned int i = 0; i < p_vehicle->zhaoPianClassVector.size(); i++)
        {
            if ((p_vehicle->zhaoPianClassVector[i]->algCode.substr(0,1) >= "0" && p_vehicle->zhaoPianClassVector[i]->algCode.substr(0,1) <= "9")
             || (p_vehicle->zhaoPianClassVector[i]->algCode.substr(0,1) == "A" && p_vehicle->zhaoPianClassVector[i]->algCode.size() > 1))
            {
                xml.AddElem("zpshjg");
                xml.AddChildElem("zpzl");
                xml.SetChildData(p_vehicle->zhaoPianClassVector[i]->algCode);
                xml.AddChildElem("jg");
                if(p_vehicle->zhaoPianClassVector[i]->result == "4"){
                    p_vehicle->zhaoPianClassVector[i]->result = "0";
                }
                xml.SetChildData(p_vehicle->zhaoPianClassVector[i]->result);
                xml.AddChildElem("sm");
                std::string smstr = p_vehicle->zhaoPianClassVector[i]->reason;
                smstr = URLEncode(smstr);
                xml.SetChildData(smstr);
            }
        }
    }

    xml.OutOfElem();
    xml.OutOfElem();
    xml.OutOfElem();
//        std::string xmlstring = "";
    xmlstring = xml.GetDoc();
    //fix me添加回复soap接口
    //xmlstring = URLEncode(xmlstring);

    return xmlstring;
}

void _c_chaYanSessionService::photoResultReply(void *p, const _c_chaYanVehicle *p_vehicle, const std::string &_confJkxlh, const char *_remoteServerIp_Char
                                   , const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                                   , const std::string &_zdbs, const std::string &_dwjgdm)
{
    UNUSED(p);
    std::string xmldata;
    int send_count = 2;

    xmldata = getVehicleGroupPhotoResponseXml(p_vehicle);

//    printf("photoResultReply xml:%s \n", xmldata.c_str());
    while (send_count != 0) {
        std::string writeReturn  ;

        LOG(SOAP,INFO,"Send photo group result to SOAP server...... %s\n",xmldata.c_str());
        writeReturn = soapApi_replyData(_chaYanStartUpParam.soapTimeOut, (char *)"18", xmldata, _confJkxlh, (char *)"18CL1", _remoteServerIp_Char, _SOAP_ServerPort, _requestUri, _cjbh, _zdbs, _dwjgdm);
        if (writeReturn.size() > 0 ){
//            printf("Send photo group result %s \n" ,writeReturn);
            return;
        }
        else
        {
            printf("The result of sending photo group is NULL\n");
            LOG(COMMON, WARN, "The result of sending photo group is NULL\n");
        }
        send_count--;
    }
}

bool _c_chaYanSessionService::checkWorkTime()
{
    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);

    if (st->tm_hour >= _chaYanStartUpParam.startTime && st->tm_hour <= _chaYanStartUpParam.endTime)
    {
        return true;
    }
    else
    {
        return false;
    }
}
