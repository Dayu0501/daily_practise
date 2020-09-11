#include "_c_session.h"
#include "base/baseTool.h"

bool _c_session::isEndWork()
{
    bool allEndWork = true;
    for (unsigned int i = 0; i < algTaskVector.size(); i++) {
        if(!algTaskVector[i]->checkIsEndWork())
        {
            allEndWork = false;
            break;
        }
    }
    return allEndWork;
}

bool _c_session::processWangLuoJieKou()
{
    return true;
}

bool _c_session::wangLuoJieKouResultEdit(void *p)
{
    UNUSED(p);
    return true;
}

bool _c_session::loadAllParam()
{
    return true;
}

bool _c_session::loadAlgTask()
{
    return true;
}

bool _c_session::subLoadAlgTask()
{
    return true;
}

bool _c_session::getPhotoByCode(std::string code,std::string *pUrl,std::string *pLoaclPath)
{
    for (unsigned int i = 0; i < algTaskVector.size(); i++) {
        if(algTaskVector[i]->algCode == code)
        {
            *pUrl = algTaskVector[i]->photoUrl;
            *pLoaclPath =  algTaskVector[i]->localPath;
            return true;
        }
    }

    *pUrl = "TBD";
    *pLoaclPath = "TBD";

    return false;
}

Json::Value _c_session::getSessionJson()
{
    Json::Value root;
    root["uuid"] = uuid;
    root["endWork"] = isEndWork();
    if(algTaskVector.size() > 0)
    {
        Json::Value algRoot;
        for (unsigned int j = 0; j < algTaskVector.size(); j++) {
            algRoot.append(algTaskVector[j]->getTaskJson());
        }
        root["algVector"] = algRoot;
    }
    return root;
}

void _c_session::setSessionInSystemTime()
{
    if(pRunTime != NULL)
    {
        pRunTime->inSystemTime = baseTool::getNowDate();
    }
}

void _c_session::setPushSessionQueueTime()
{
    if(pRunTime != NULL)
    {
        pRunTime->pushSessionQueueTime = baseTool::getNowDate();
    }
}

void _c_session::setGetSessionQueueTime()
{
    if(pRunTime != NULL)
    {
        pRunTime->getSessionQueueTime = baseTool::getNowDate();
    }
}

void _c_session::setPushAlgSessionQueueTime()
{
    if(pRunTime != NULL)
    {
        pRunTime->pushAlgSessionQueueTime = baseTool::getNowDate();
    }
}

void _c_session::setGetAlgSessionQueueTime()
{
    if(pRunTime != NULL)
    {
        pRunTime->getAlgSessionQueueTime = baseTool::getNowDate();
    }
}

void _c_session::setPushReponseQueueTime()
{
    if(pRunTime != NULL)
    {
        pRunTime->pushReponseQueueTime = baseTool::getNowDate();
    }
}

void _c_session::setGetReponseQueueTime()
{
    if(pRunTime != NULL)
    {
        pRunTime->getReponseQueueTime = baseTool::getNowDate();
    }
}

void _c_session::setPushDbTaskQueueTime()
{
    if(pRunTime != NULL)
    {
        pRunTime->cheLiangUid = uuid;
        pRunTime->pushDbTaskQueueTime = baseTool::getNowDate();
    }
}


