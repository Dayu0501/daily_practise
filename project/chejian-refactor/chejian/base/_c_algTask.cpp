#include "_c_algTask.h"
#include "base/baseTool.h"
bool _c_algTask::algTaskInit()
{
    loadUuid();
    __endWork = false;
    pClass = NULL;
    //algCode = "";
    //photoUrl = "";
    result = "";
    reason = "";
    runTime = "0";
    photoDownTime = "0";
    algProcTime = "0";
    algRunTime = "0";
    __inTime = std::chrono::system_clock::now();

    pVideoCheckInfo = NULL;
    processReponseIsDone = false;
    videoProcessState = videoProcessUnInit;
    return true;
}

bool _c_algTask::setEndWork()
{
    __endWork = true;
    return __endWork;
}

bool _c_algTask::clearEndWork()
{
    __endWork = false;
    return __endWork;
}

bool _c_algTask::checkIsEndWork()
{
    return __endWork;
}

bool _c_algTask::checkResult()
{
    return (!result.empty());
}

bool _c_algTask::freeAlgBaseClass()
{
    if(pClass!=NULL)
    {
        delete pClass;
        pClass = NULL;
    }
    return true;
}

unsigned int _c_algTask::getInSystemTime()
{
    std::chrono::time_point<std::chrono::system_clock> nowTime = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> milliseconds = nowTime - __inTime;
    return (unsigned int)milliseconds.count();
}

bool _c_algTask::setAlgTaskResult(int result, std::string reason, bool isVideo)
{
    if (!isVideo)
    {
        //填充照片项结果
        this->result = std::to_string(result);
        this->reason = reason;
    }
    else
    {
        //这里是已经处理过照片的情况下,再额外添加视频的结果.
        //如果照片结果没过,视频结果过了,那么算过
        //printf("*********** setAlgTaskResult %s,\n", algCode.c_str());
        if (this->result != std::to_string(PASS) && result == PASS)
            this->result = std::to_string(result);
        this->reason += "{视频:" + reason + "}";

        //填充视频项
        _c_video *pVideo = baseTool::getVideoObject(this);
        if (pVideo != NULL)
        {
            pVideo->result = std::to_string(result);
            pVideo->reason = reason;
        }
    }

    return true;
}


Json::Value _c_algTask::getParamSendJson(unsigned int timeOut, std::string reponseChan, bool isVideo)
{
    Json::Value root;
    if(pClass!=NULL)
    {
        return pClass->getInParamJson(uuid, timeOut, isVideo, reponseChan);
    }
    return root;
}

/*
pVector:一个算法的所有参数值（从车管所过来的所有输入参数值）
pItemVector:当前支持的算法类型
pAlgTaskVector:一辆车的所有算法任务
*/
bool _c_algTask::loadAlgTaskInParam(std::vector<objectMember *> *pVector, std::vector<algItem> *pItemVector, std::vector<_c_algTask *> *pAlgTaskVector, std::vector<_c_object *> *pWangluoJieKouVector)
{
    bool isfound = false;

    pClass->pAllParamVector = pVector;
    pClass->pAllAlgItemVector = pItemVector;
    pClass->pAlgTaskVector = pAlgTaskVector;
    pClass->pWangLuoJieKouReturnVector = pWangluoJieKouVector;

    for (unsigned int i = 0; i < pClass->inListVector.size(); i++) {
        for (unsigned int j = 0; j < pClass->inListVector[i].pVector->size(); j++) {
            isfound = false;
            for (unsigned int k = 0; k < pVector->size(); k++) {
                if((*pVector)[k]->codeName == (*pClass->inListVector[i].pVector)[j].name) //找到_c_algClass中对应的输入参数
                {
                    (*pClass->inListVector[i].pVector)[j].value->inData = (*pVector)[k]->value->c_str(); //把从车管所库拿到的解析后的数据添加输入参数中去。

					
                    //printf("name:[%s],value:[%s]\n",(*pVector)[k]->codeName.c_str(),(*__pClass->inListVector[i].pVector)[j].value->inData.c_str());
                    isfound = true;
                    break;
                }
            }

            if (!isfound)
            {
//                printf("can't find [%s]! please check whether inList param is right!\n", (*pClass->inListVector[i].pVector)[j].name.c_str());
                LOG(ALG, WARN,"can't find [%s]! please check whether inList param is right!\n", (*pClass->inListVector[i].pVector)[j].name.c_str());
            }
        }
    }

    return true;
}

/*
pVector:来自算法的结果list
*/
bool _c_algTask::loadAlgTaskResult(std::string redisRet, std::vector<objectMember> *pVector, bool isVideo)
{

    if(pClass != NULL)
    {
        if (!isVideo)
        {
	        algTaskVector.push_back(this);
	        pClass->loadExtAlgClass(&algTaskVector); //多个算法任务联合判定的，比如0322和0348
        }
        for (unsigned int i = 0; i < algTaskVector.size(); i++) {
            _c_algBaseClass *pBaseClass = algTaskVector[i]->pClass ;
            if(!pBaseClass)
            {
                continue;   
            }

            pBaseClass->beforLoadResult();
            if(redisRet == "1")
            {
                pBaseClass->LoadResult(redisRet, pVector); //把算法返回来的结果填到对应的algtask上去
				
				//前置编辑判定[ 1. 单据类型  ]
                bool beforeRetValue = pBaseClass->beforeResultEdit();
                bool RetValue = beforeRetValue && pBaseClass->ResultEdit() ;// ResultEdit是对返回来的结果，做总结判定的。
                if(!beforeRetValue || RetValue )
                {
                    if(pBaseClass->afterResultEdit())
                    {
                        std::string reason = "";
                        if(algTaskVector[i]->sendRedisDate.empty())
                        {
                            algTaskVector[i]->sendRedisDate = baseTool::getCurTime();
                        }
                        E_JG result =pBaseClass->getResult(&reason);
                        algTaskVector[i]->setAlgTaskResult((int)result, reason, isVideo);
                    }
                }
            }else if (redisRet == "2") {
                 algTaskVector[i]->setAlgTaskResult(4,"算法处理超时", isVideo);
            }else if (redisRet == "3") {
                algTaskVector[i]->setAlgTaskResult(4,"未知算法ID", isVideo);
            }else if (redisRet == "4") {
                algTaskVector[i]->setAlgTaskResult(4,"加密错误", isVideo);
            }else if (redisRet == "5") {
                algTaskVector[i]->setAlgTaskResult(4,"下载失败", isVideo);
            }else{
                printf("algCode：%s  redisRet:%s\n",algTaskVector[i]->algCode.c_str(),redisRet.c_str());
            }

            //有多张照片的时候 视频结果会累加写
            if (isVideo)
            {
                break;
            }
        }
        return true;
    }
    return false;
}

Json::Value _c_algTask::getTaskJson()
{
    Json::Value algRoot;
    algRoot["algCode"] = algCode;
    algRoot["result"] = result;
    algRoot["reason"] = reason;
    algRoot["photoDownTime"] = photoDownTime;
    algRoot["algProcTime"] = algProcTime;
    algRoot["algRunTime"] = algRunTime;
    algRoot["sendRedisDate"] = sendRedisDate;
    algRoot["readRedisDate"] = readRedisDate;
    algRoot["runTime"] = runTime;
    algRoot["photoUrl"] = photoUrl;
    algRoot["inSystemTime"] = getInSystemTime();

    return algRoot;
}



