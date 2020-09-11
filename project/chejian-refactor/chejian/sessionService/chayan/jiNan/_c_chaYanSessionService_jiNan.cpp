#include "_c_chaYanSessionService_jiNan.h"
#include "_c_touPing.h"
#include "db/dbquery/dbinterface.h"
#include "base/baseTool.h"

_c_chaYanSessionService_jiNan::_c_chaYanSessionService_jiNan(PSTARTUPPRARAM param):_c_chaYanSessionService(param)
{
}

class JiNanExecutePhoto
{
public:
    std::string queryKey;
    std::string zplx;
};


bool _c_chaYanSessionService_jiNan::checkGreenChannel(_c_session *pSession)
{
    if (baseTool::checkDateChange(curDay))
    {

    }

    _c_chaYanVehicle *_pVehicle = (_c_chaYanVehicle *)pSession;
    if(checkGreenChannelByShenFenZheng(_pVehicle->chaYanYuanShenFenZhengMingHao))
    {
        pSession->redisChannel = redisGreenChan;
        pSession->greenChannel = "true";
    }else {
        pSession->redisChannel = redisRequstChan;
        pSession->greenChannel = "false";
    }

    std::vector<JiNanExecutePhoto> photo_type_uri = {
        {"getLeftFrontPicinfo","H1"},
        {"getRightRearPicinfo","H2"},
        {"getCarNumPicinfo","H3"},
        {"getVehNamePlacePicinfo","H4"} };

    for (unsigned int i = 0; i < photo_type_uri.size(); i++) {
        _c_photo *pPhoto = new _c_photo();
        pPhoto->loadUuid();
        pPhoto->cheLiangUid = _pVehicle->uuid;
        pPhoto->zhaoPianBianHao = std::to_string(_pVehicle->zhaoPianClassVector.size()+1);
        pPhoto->algCode = photo_type_uri[i].zplx;
        pPhoto->photoUrl = "http://10.10.1.43:9210/tPictureinfo/"+photo_type_uri[i].queryKey+"?vin="+_pVehicle->cheLiangShiBieDaiHao;
        pPhoto->localPath = "无数据";
        pPhoto->result = "无数据";
        pPhoto->reason = "无数据";
        pPhoto->photoDownTime = "无数据";
        pPhoto->algProcTime = "无数据";
        pPhoto->algRunTime = "无数据";
        pPhoto->runTime = "无数据";
        _pVehicle->zhaoPianClassVector.push_back(pPhoto);
    }

    return false;
}


bool _c_chaYanSessionService_jiNan::extraWorkBeforReponse(_c_session *pSession)
{
    _c_chaYanVehicle *_pVehicle = (_c_chaYanVehicle *)pSession;
    _c_touPing *pTouPing = new _c_touPing();
    pTouPing->isSend = "0";
    pTouPing->shenFenZheng = _pVehicle->chaYanYuanShenFenZhengMingHao;
    Json::Value root = loadTouPingMsg(_pVehicle);
    if(root["photoRoot"].size() > 0)
    {
        pTouPing->jsonMsg = root.toStyledString();
        pTouPing->dbWork();
        //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! %d _ %d %s\n!!!!!!\n", _pVehicle->zhaoPianClassVector.size(),pTouPing->jsonMsg.length(), pTouPing->jsonMsg.c_str());
    }

    return true;
}

class JiNanTouPhoto
{
public:
    std::string queryKey;
    std::string zplx;
};

class JiNanPhotoList
{
public:
    std::string zplx;
    std::vector<std::string> subUrl;
};

Json::Value getSubPhotoUrl(std::vector<_c_photo *> *pPhotoVector,JiNanPhotoList *pJiNanPhotoListItem)
{
    Json::Value root;
    for (unsigned int i = 0; i < pJiNanPhotoListItem->subUrl.size(); i++) {
        for (unsigned int j = 0; j < pPhotoVector->size(); j++) {
            if(pJiNanPhotoListItem->subUrl[i] == (*pPhotoVector)[j]->algCode)
            {
                Json::Value subRoot;
                subRoot["subUrl"] = (*pPhotoVector)[j]->photoUrl;
                root.append(subRoot);
                break;
            }
        }
    }
    return root;
}

Json::Value _c_chaYanSessionService_jiNan::loadTouPingMsg(_c_chaYanVehicle *_pVehicle)
{
    Json::Value root;
    Json::Value paramRoot;
    Json::Value photoRoot;

    for (unsigned int i = 0; i < _pVehicle->memberVector.size(); i++) {
        Json::Value subParamRoot;

        subParamRoot["codeName"] = _pVehicle->memberVector[i].codeName;
        subParamRoot["value"] = *_pVehicle->memberVector[i].value;
        subParamRoot["desc"] = _pVehicle->memberVector[i].desc;

        paramRoot.append(subParamRoot);
    }

    std::vector<JiNanPhotoList> photoList = {
        {"0198",{"0198","H1","A"}},
        {"0102",{"0102","H2"}},
        {"0103",{"0103","H3"}},
        {"0105",{"0105","H4"}},
        {"0106",{"0106"}},
        {"0104",{"0104"}},
    };

    for (unsigned int k = 0; k < photoList.size(); k++) {
        for (unsigned int j = 0; j < _pVehicle->zhaoPianClassVector.size(); j++) {
            if(photoList[k].zplx == _pVehicle->zhaoPianClassVector[j]->algCode)
            {
                Json::Value subPhotoRoot;

                subPhotoRoot["algCode"] = _pVehicle->zhaoPianClassVector[j]->algCode;
                subPhotoRoot["algName"] = _pVehicle->zhaoPianClassVector[j]->algName;

                subPhotoRoot["photoUrl"] = _pVehicle->zhaoPianClassVector[j]->photoUrl;
                subPhotoRoot["result"] = _pVehicle->zhaoPianClassVector[j]->result;
                subPhotoRoot["reason"] = _pVehicle->zhaoPianClassVector[j]->reason;

                subPhotoRoot["photoDownTime"] = _pVehicle->zhaoPianClassVector[j]->photoDownTime;
                subPhotoRoot["algProcTime"] = _pVehicle->zhaoPianClassVector[j]->algProcTime;
                subPhotoRoot["algRunTime"] = _pVehicle->zhaoPianClassVector[j]->algRunTime;
                subPhotoRoot["runTime"] = _pVehicle->zhaoPianClassVector[j]->runTime;
                subPhotoRoot["subPhoro"] = getSubPhotoUrl(&_pVehicle->zhaoPianClassVector,&photoList[k]);

                photoRoot.append(subPhotoRoot);

            }
        }
    }

    root["paramRoot"] = paramRoot;
    root["photoRoot"] = photoRoot;

    return root;
}


 void _c_chaYanSessionService_jiNan::subClearCache(){
    _c_touPing_clearTable*  tp_clear = new _c_touPing_clearTable();
    tp_clear->dbWork() ;
 }

