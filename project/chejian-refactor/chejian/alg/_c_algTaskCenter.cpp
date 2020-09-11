#include "_c_algTaskCenter.h"
#include "base/baseTool.h"
_c_algTaskCenter::_c_algTaskCenter(CityType cityType,PREDIS_PARAM redisParam)
{
    //初始化redis服务器IP端口，及认证密码，超时时间
	KGRedisClient::InitializeRedis(redisParam);
    __pRedisParam = redisParam;
    __cityType = cityType;

    loadPicExamples();
}

void AlgTaskCenter_QueryThread(_c_algTaskCenter *pCenter)
{
    do{
        threadInfo *pInfo = pCenter->getAlgTaskCenterQueryThread();
        pInfo->updateCurCnt();
        pCenter->queryData();
    }while(!pCenter->isClose());
}

void AlgTaskCenter_ReponseThread(_c_algTaskCenter *pCenter)
{
    do{
        threadInfo *pInfo = pCenter->getAlgTaskReponseThread();
        pInfo->updateCurCnt();
        pCenter->queryTaskReponse();
    }while(!pCenter->isClose());
}

void AlgTaskCenter_RequestThread(_c_algTaskCenter *pCenter)
{
    do{
        threadInfo *pInfo = pCenter->getAlgTaskRequestThread();
        pInfo->updateCurCnt();
        pCenter->queryTaskRequest();
    }while(!pCenter->isClose());
}

void AlgRedis_ReponseThread(_c_algTaskCenter *pCenter)
{
    do{
        threadInfo *pInfo = pCenter->getAlgRedisResponseThread();
        pInfo->updateCurCnt();
        pCenter->queryRedisResponse();
    }while(!pCenter->isClose());
}

bool _c_algTaskCenter::isClose()
{
    return false;
}

bool _c_algTaskCenter::stratAlgTaskCenter()
{
    changeAlgVector();
    loadConfig();
    //启动数据查询队列
//    _pAlgTaskCenterQueryThread = new std::thread(AlgTaskCenter_QueryThread, this);
    AlgTaskCenterQueryThread.threadName = "AlgTaskCenterQueryThread";
    AlgTaskCenterQueryThread._pthread = new std::thread(AlgTaskCenter_QueryThread, this);
    //启动redis监听队列，取算法回复结果Redis
//    _pAlgRedisResponseThread = new std::thread(AlgRedis_ReponseThread, this);
    AlgRedisResponseThread.threadName = "AlgRedisResponseThread";
    AlgRedisResponseThread._pthread = new std::thread(AlgRedis_ReponseThread, this);

    //启动结果回收队列
//    _pAlgTaskReponseThread = new std::thread(AlgTaskCenter_ReponseThread, this);
    AlgTaskReponseThread.threadName = "AlgTaskReponseThread";
    AlgTaskReponseThread._pthread = new std::thread(AlgTaskCenter_ReponseThread, this);

    //启动任务请求队列
//    _pAlgTaskRequestThread = new std::thread(AlgTaskCenter_RequestThread, this);
    AlgTaskRequestThread.threadName = "AlgTaskRequestThread";
    AlgTaskRequestThread._pthread = new std::thread(AlgTaskCenter_RequestThread, this);
    return true;
}

bool _c_algTaskCenter::queryTaskRequest()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000*1000));
    return true;
}

bool _c_algTaskCenter::queryTaskReponse()
{
    unsigned int queueSize = getAlgTaskResponseQueueSize();
    if(queueSize > 0)
    {
        _c_algTask_Reponse *pReponse = getAlgTaskResponseFromQueue();
        if(pReponse != NULL)
        {
            AlgTaskRecovery(pReponse);
        }
    }else {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return true;
}

bool _c_algTaskCenter::AlgTaskRecovery(_c_algTask_Reponse *pRequest)
{
    if(pRequest!=NULL)
    {
        _c_algTask *pTask = getAlgTaskByGuid(pRequest->algTaskKeyCode); //拿到任务池中对应的task
        if(pTask!=NULL)
        {
            bool isVideo = false;

            _c_video *pVideo = NULL;

            //记录照片或视频结果
            if (pTask->videoProcessState == videoProcessUnInit)
            {
                pTask->runTime = std::to_string(pTask->getInSystemTime());
                pTask->algProcTime = pRequest->algProcTime;
                pTask->algRunTime = pRequest->algRunTime;
                pTask->photoDownTime = pRequest->photoDownTime;
                pTask->readRedisDate = baseTool::getNowDate();
            }
            else
            {
                pVideo = baseTool::getVideoObject(pTask);
                if (pVideo != NULL)
                {
                    pVideo->runTime = std::to_string(pTask->getInSystemTime());
                    pVideo->algProcTime = pRequest->algProcTime;
                    pVideo->algRunTime = pRequest->algRunTime;
                    pVideo->videoDownTime = pRequest->photoDownTime;
                    pVideo->readRedisDate = baseTool::getNowDate();
                    isVideo = true;
                }
            }
			
            pTask->processDeviceIp = pRequest->processIp;
            pTask->loadAlgTaskResult(pRequest->algReturn, pRequest->getResultList(), isVideo);//加载所有来自算法的结果

            if(!pTask->checkResult())
            {
                pTask->setAlgTaskResult(4,"无处理结果", isVideo);
            }

//            processVideoCheckAlg(pTask);

            delete pRequest;
            pRequest = NULL;
        }
        else
        {
            pRequest->dbWork();
            pRequest = NULL;
        }
    }

   return true;
}

bool _c_algTaskCenter::queryData()
{
    //获取session队列中的session个数（队列非阻塞式应用，用于监视线程是否卡死使用）
    unsigned int queueSize = getSessionAlgQueueSize();
    if(queueSize > 0)
    {
        //从队列中获取一个session
        _c_session *pSession = getSessionAlgFromQueue();
        if(pSession != NULL)
        {
            //算法任务处理
            algTaskAnalyse(pSession);
        }
    }else {
        if(_TaskMap.size() > 0)
        {
            checkAlgTaskTimeOut(); //这个地方会判断所有的task是否都有结果了，如果有结果把task设置为结束
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return true;
}

bool  _c_algTaskCenter::initAlgTask(_c_algTask *pTask, _c_session *pSession, algItem *pAlgItem)
{
    //加载输入参数和输出结果列表（某一类型算法的检测项）
    pTask->pClass = loadAlgBaseClassByPicType(__cityType,pAlgItem->name, pAlgItem->type, pAlgItem->subAlgClass);
    if(pTask->pClass != NULL)
    {
        //使用从车检数据拿来的数据填充的车辆信息，填充到algClass上
        pTask->loadAlgTaskInParam(&pSession->paramVector, &__algVector, &pSession->algTaskVector, pSession->pWangLuoJieKouReturnVector);

        //修改图片存储时的名称
        //if( pTask->localPath.size() > 0 &&  pTask->localPath.at(pTask->localPath.size()-1) == '/' )
        //{
            pTask->localPath = "/"+baseTool::getDangTianRiQi()+"/"+baseTool::formatPhotoFileName(pTask->pClass->getPhotoName(pTask->algCode));
            //printf(" attach_photo_name3:%s\n",pTask->localPath.c_str()  );
            //LOG(COMMON,INFO," attach_photo_name3:%s\n",ptask->localPath.c_str()  );
        //}

        std::string mainPhotoCode = getAlgCodeByType(pTask->pClass->mainPhotoType);
        std::string subPhotoCode = getAlgCodeByType(pTask->pClass->subPhotoType);
        std::string mainUrl,mainPath;
        std::string subUrl,subPath;

        pSession->getPhotoByCode(mainPhotoCode, &mainUrl, &mainPath);
        pSession->getPhotoByCode(subPhotoCode, &subUrl, &subPath);

        pTask->pClass->setPhoto(mainUrl, mainPath, subUrl, subPath); //algClass填充上图片路径 
        return true;
    }
    return false;
}

void test_redis(std::string str)
{
    //printf("test_redis : %s\n",str.c_str());
    _c_algTask_Reponse *reponse = new _c_algTask_Reponse(str);
    std::this_thread::sleep_for(std::chrono::milliseconds(rand()%25000));
    pushAlgTaskResponseQueue(reponse);
}

void test(_c_algTask *pTask)
{
    Json::Value root;
    root["algTaskKeyCode"] = pTask->uuid;
    root["algReturn"] = "1";


    if(pTask->pClass->pResultMemberList->size()>0)
    {
        std::string retBool = "true";
        if((rand()%5) == 0)
        {
            retBool = "false";
        }
        Json::Value memberRoot;
        for (unsigned int i = 0; i < pTask->pClass->pResultMemberList->size(); i++) {
                //printf("_c_algTaskCenter--%s:[%s]\n",(*pTask->pClass->pResultMemberList)[i].name.c_str(),retBool.c_str());
                Json::Value subRoot;
                subRoot["name"] = (*pTask->pClass->pResultMemberList)[i].name;
                subRoot["value"] = retBool;
                memberRoot.append(subRoot);
        }
         root["returnResultMemberList"]=memberRoot;
    }

    std::thread *pThread = new std::thread(test_redis, root.toStyledString());
    pThread->detach();
    delete pThread;

}
bool _c_algTaskCenter::algTaskAnalyse(_c_session *pSession)
{
    //session中是否有需要计算的任务标记
    bool needAlgCheck = false;

    //获取session携带的算法任务vector
    std::vector<_c_algTask *> *pVector = &pSession->algTaskVector; //这里表示的是一辆车的所有图片
    Json::Value root;
    root["sessionId"] = pSession->uuid;
    root["encodeKey"] = baseTool::Crc16String((uint8_t*)pSession->uuid.c_str(), pSession->uuid.size());
    root["inSystemTime"] = baseTool::getNowDate();
    root["timeoutSecond"] = std::to_string(__timeOutMilliSeconds);
    root["picProcessTime"] = std::to_string(__picProcessTime);
    root["reponseChan"] = __pRedisParam->reponseChan;

    Json::Value subRoot;

    for (unsigned int i = 0; i < pVector->size(); i++) {
        //判断算法任务是否需要计算，在web中的算法类别中是否isopen
        int algItemIndex =  checkTaskNeedAlgAnalyse(pSession,(*pVector)[i]);
        if(algItemIndex != -1)
        {
            //将标记置为true，表示session 有需要计算的任务
            //初始化algClass
            needAlgCheck = initAlgTask((*pVector)[i], pSession, &__algVector[(unsigned int)algItemIndex]);

            if(needAlgCheck)
            {
                //编辑算法任务实体的输入参数
                //bool needSendRedis = (*pVector)[i]->pClass->InParamEdit();
	            bool needSendRedis = (*pVector)[i]->pClass->setInParamEdit();
                if(needSendRedis)
                {
                    _TaskMap.push_back((*pVector)[i]); //把每一个算法任务（对应每一张照片）放到任务池中
                    (*pVector)[i]->sendRedisDate = baseTool::getNowDate();
                    Json::Value value = (*pVector)[i]->getParamSendJson(__timeOutMilliSeconds,__pRedisParam->reponseChan);
                    subRoot.append(value);
                    //test((*pVector)[i]);
                }
                else
                {
					std::string reason;
                    (*pVector)[i]->pClass->ResultEdit();
                    E_JG result =(*pVector)[i]->pClass->getResult(&reason);
                    (*pVector)[i]->setAlgTaskResult((int)result, reason);
                    (*pVector)[i]->setEndWork();
                }
                continue;
            }
        }
        //不需要计算的任务直接设置为未知检验类型
        (*pVector)[i]->setAlgTaskResult(4, "未知检验类型");
        (*pVector)[i]->setEndWork();
    }
    root["algTaskList"] = subRoot;
    Json::FastWriter writer;
    std::string strSendJson = writer.write(root);
    printf("++++ strSendJson:%s",strSendJson.c_str());
    if(subRoot.size() > 0)
    {
        //将算法任务丢入计算队列
        pushAlgTaskInfoRedis(strSendJson,pSession->redisChannel); //把一辆车的所有检测的图片信息传送给算法
    }

    return needAlgCheck;
}

bool _c_algTaskCenter::queryRedisResponse()
{
    if (workMode != eClientMode)
    {
        std::string redisResponse;
        bool flag = KGRedisClient::get_instance().ExecuteCmdEx(redisResponse,"LPOP",__pRedisParam->reponseChan.c_str(),nullptr);
        if(flag && !redisResponse.empty())
        {
            printf("---- redis response:%s\n",redisResponse.c_str());
            LOG(ALG,INFO,"queryRedisResponse %s:[%s]",__pRedisParam->reponseChan.c_str(),redisResponse.c_str());

            auto *reponse = new _c_algTask_Reponse(redisResponse);
            pushAlgTaskResponseQueue(reponse);
        }else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::string heartBeatRedisResponse;
        bool heartBeatFlag = KGRedisClient::get_instance().ExecuteCmdEx(heartBeatRedisResponse,"LPOP","heartBeatChan",nullptr);
        if(heartBeatFlag && !heartBeatRedisResponse.empty())
        {
            LOG(ALG,INFO,"heartBeatRedisResponse %s:[%s]","heartBeatChan",heartBeatRedisResponse.c_str());
            _c_device *pDevice = new _c_device(heartBeatRedisResponse);
            setDeviceHeartBeat(pDevice);
        }
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return true;
}

bool _c_algTaskCenter::beforAlgCheck(_c_session *pSession, std::string& sessionReason)
{
    std::string jylb = baseTool::getObjectItemValueByName(&pSession->paramVector, "jianYanLeiBie");
    std::string syxz = baseTool::getObjectItemValueByName(&pSession->paramVector, "shiYongXingZhi");
    std::string cllx = baseTool::getObjectItemValueByName(&pSession->paramVector, "cheLiangLeiXing");
    std::string bh = baseTool::getObjectItemValueByName(&pSession->paramVector, "jianYanJiGouBianHao");
    std::string ip = baseTool::getObjectItemValueByName(&pSession->paramVector, "jianYanJiGouIp");
    std::string chePai = baseTool::getObjectItemValueByName(&pSession->paramVector, "faZhengJiGuan");
    std::string cheJiaHao = baseTool::getObjectItemValueByName(&pSession->paramVector, "cheJiaHao");
    std::string isRepeat = baseTool::getObjectItemValueByName(&pSession->paramVector, "isRepeat");
    if(chePai.size() > 1)
    {
        chePai.pop_back();
    }
    chePai +=baseTool::getObjectItemValueByName(&pSession->paramVector, "chePaiHao");
    printf("chePai:%s\n",chePai.c_str());

    //黑名单过滤
    if(!checkHeiMingDan(chePai, &pSession->algTaskVector))
    {
        sessionReason = "黑名单车辆";
        return false;
    }
    if(!checkCjhHeiMingDan(cheJiaHao, &pSession->algTaskVector))
    {
        sessionReason = "车架号黑名单车辆";
        return false;
    }

    //检验类别检测
    if(!checkJianYanLeiBie(jylb, &pSession->algTaskVector))
    {
        sessionReason = "检验类别不在审核范围内";
        return false;
    }

    //使用性质检测
    if(!checkShiYongXingZhi(syxz, &pSession->algTaskVector))
    {
        sessionReason = "使用性质不在审核范围内";
        return false;
    }

    //车辆种类检测
    if(!checkCheLiangZhongLei(cllx, &pSession->algTaskVector))
    {
        sessionReason = "车辆类型不在审核范围内";
        return false;
    }

    //检验机构检测
    if(!checkJianYanJiGou(bh, ip, &pSession->algTaskVector))
    {
        sessionReason = "检验机构不在审核范围内";
        return false;
    }

    //复检车辆mode 1 不审核回复给车管所为复检车辆
    if(!checkFuJianCheLiang("1",isRepeat, &pSession->algTaskVector))
    {
        sessionReason = "复检车辆";
        return false;
    }

    return subBeforAlgCheck(pSession,sessionReason);
}

bool _c_algTaskCenter::checkIsTenYearCar(_c_session *pSession)
{
    std::string ccdjrq = baseTool::getObjectItemValueByName(&pSession->paramVector,"chuCiDengJiRiQi");
    bool isTenYear = baseTool::isTenYears(ccdjrq);
    //LOG(ALG, INFO, "%s : isTenYesr = [%d]", __PRETTY_FUNCTION__, isTenYear);
    return isTenYear;
}


E_ZZJG _c_algTaskCenter::afterAlgCheck(_c_session *pSession, std::string& sessionReason)
{
   E_ZZJG baseResult = SOFT_PASS;
   std::string heDingZaiKeShu = baseTool::getObjectItemValueByName(&pSession->paramVector, "heDingZaiKeShu");
   std::string cheLiangLeiXing = baseTool::getObjectItemValueByName(&pSession->paramVector, "cheLiangLeiXing");
   std::string ccdjrq = baseTool::getObjectItemValueByName(&pSession->paramVector,"chuCiDengJiRiQi");
   std::string jyjgip = baseTool::getObjectItemValueByName(&pSession->paramVector, "jianYanJiGouIp");
   std::string jyjgbh = baseTool::getObjectItemValueByName(&pSession->paramVector, "jianYanJiGouBianHao");
   std::string isRepeat = baseTool::getObjectItemValueByName(&pSession->paramVector, "isRepeat");

   bool isTenYears =false;

   //如果车辆等级时间 > 10 年
   if(checkIsTenYearCar(pSession))
   {
       isTenYears = true;
   }
   editQianHouSanJiaoJia(pSession);
   editZuoYouDengGuang(pSession);
   editJiaoQiangXianWanShuiZhengMing(pSession);
   checkWangLuoJieKouResult(pSession);

	//将结果传递给派生类中并返回派生类的判断结果，默认直接返回baseResult
    baseResult = subAfterAlgCheck(baseResult, pSession,sessionReason);
    if(baseResult != SOFT_PASS)
    {
        if(sessionReason.empty())
        {
            sessionReason = "城市子类判定不通过";
        }

        return baseResult;
    }
	
   //判定核定载客数是否符合要求如果核定载客数未空则默认设置为7 如果该值大于__HDZKS则判定不通过
   if(!checkHeDingZaiKeShu(heDingZaiKeShu, &pSession->algTaskVector))
   {
       sessionReason = "该车辆的核定载客数大于" + std::to_string(__HDZKS);

       return SOFT_NOTPROCESS;
   }

   //判断是否未小车如果不是判定不通过
   if(!checkIsSamllVehicle(cheLiangLeiXing, &pSession->algTaskVector))
   {
       sessionReason = "车辆类型不在整车判定类型范围内";

       return SOFT_NOTPROCESS;
   }
   //检验需要检测的算法是否都有被检测的数据 
   //ismust的检查
   std::string detailReason;
   if(!checkComplete(isTenYears, pSession, detailReason))
   {
       sessionReason = "图片种类不完整:"+detailReason;
       return SOFT_NOTPASS;
   }

   //检验机构检测
   if(!checkXinRenJianYanJiGou(jyjgbh, jyjgip, &pSession->algTaskVector))
   {
       sessionReason = "检验机构不在信任范围内";
       return SOFT_ERR;
   }

   //复检车辆mode 2 审核但是整车不通过
   if(!checkFuJianCheLiang("2",isRepeat, &pSession->algTaskVector))
   {
       sessionReason = "复检车辆";

       return SOFT_ERR;
   }


    //整车判定检查所有的子项
   baseResult = checkUnqualified(isTenYears, &pSession->algTaskVector,sessionReason);
   if(baseResult != SOFT_PASS)
   {
       if(sessionReason.empty())
       {
            sessionReason = "照片审核项不通过";
       }
       return baseResult;
   }
   baseResult = finalCheck(baseResult,pSession,sessionReason);

   if(baseResult != SOFT_PASS )
   {
       if(sessionReason.empty())
       {
            sessionReason = "算法检测项均已通过,审核不通过原因未知";
       }
       return baseResult;
   }

   sessionReason = "通过";
   //返回各个图片处理结果的汇总情况
   return baseResult;
}

bool _c_algTaskCenter::algVectorCheck(_c_session *pSession,_c_algTask *pTask,algItem *pAlgItem)
{
    //判断算法接口是否启用
    if(!pAlgItem->isOpen)
    {
        return false;
    }
    //判断派生类是否有私有的检测
    return subAlgVectorCheck(pSession,pTask,pAlgItem);
}

int _c_algTaskCenter::checkTaskNeedAlgAnalyse(_c_session *pSession,_c_algTask *pTask)
{
    //遍历算法列表找到算法任务相对应的算法接口
    for (unsigned int i = 0; i < __algVector.size(); i++) {
        if (pTask->algCode ==__algVector[i].code)
        {
            pTask->algName = __algVector[i].name;
            //判断算法接口是否可用，在_c_algTaskCenter中管理着每个算法的配置（可以从网页配置上），在_c_algTaskCenter中找到具体的算法看是否开启
            if(algVectorCheck(pSession,pTask,&__algVector[i])) 
            {
                return (int)i;
            }
            break;
        }
    }
    return  -1;
}

void _c_algTaskCenter::checkWangLuoJieKouResult(_c_session *pSession)
{
    pSession->wangLuoJieKouResultEdit((void *)getAlgVector());
}

bool _c_algTaskCenter::pushAlgTaskInfoRedis(std::string strSendJson, RedisChannelType redisChannel)
{
    //将处理任务增加到redis队列中去
    //algTask 需要有获取参数照片转json字串接口
    //将pTask->getParamSendJson()返回结果发送到redis

    //printf("pushAlgTaskInfoRedis taskCode:[%s] json:[%s]\n",pTask->algCode.c_str(),pTask->getParamSendJson().c_str());
	/*
    Json::Value root;
    root["algTaskKeyCode"] = pTask->uuid;
    root["algReturn"] = "1";


    if(pTask->pClass->pResultMemberList->size()>0)
    {
        std::string retBool = "true";
        if((rand()%5) == 0)
        {
            retBool = "false";
        }
        Json::Value memberRoot;
        for (unsigned int i = 0; i < pTask->pClass->pResultMemberList->size(); i++) {
                //printf("_c_algTaskCenter--%s:[%s]\n",(*pTask->pClass->pResultMemberList)[i].name.c_str(),retBool.c_str());
                Json::Value subRoot;
                subRoot["name"] = (*pTask->pClass->pResultMemberList)[i].name;
                subRoot["value"] = retBool;
                memberRoot.append(subRoot);
        }
         root["returnResultMemberList"]=memberRoot;
    }

    std::thread *pThread = new std::thread(test_redis, root.toStyledString());
    pThread->detach();
    delete pThread;
	return true;
	*/
	//去掉回车换行空格等字符串
    //pTask->sendRedisDate = baseTool::getNowDate();
    //std::string sendJsonStr = pTask->getParamSendJson();
    //LOG(ALG,INFO,"alg sendJsonStr[%s]:[%s]\n",pTask->uuid.c_str(),sendJsonStr.c_str());
     //printf("strSendJson:%s",strSendJson.c_str());
    //发送redis队列
    std::string response;
    switch(redisChannel)
    {
        case redisRequstChan:
            LOG(ALG,INFO,"pushAlgTaskInfoRedis %s:[%s]",__pRedisParam->requstChan.c_str(),strSendJson.c_str());
            return KGRedisClient::get_instance().ExecuteCmdEx(response,"RPUSH",__pRedisParam->requstChan.c_str(),strSendJson.c_str());
        break;

        case redisGreenChan:
            LOG(ALG,INFO,"pushAlgTaskInfoRedis %s:[%s]",__pRedisParam->greenChan.c_str(),strSendJson.c_str());
            return KGRedisClient::get_instance().ExecuteCmdEx(response,"RPUSH",__pRedisParam->greenChan.c_str(),strSendJson.c_str());
        break;

        case redisLeastChan:
            LOG(ALG,INFO,"pushAlgTaskInfoRedis %s:[%s]",__pRedisParam->leastChan.c_str(),strSendJson.c_str());
            return KGRedisClient::get_instance().ExecuteCmdEx(response,"RPUSH",__pRedisParam->leastChan.c_str(),strSendJson.c_str());
        break;
    }
}

_c_algBaseClass *_c_algTaskCenter::subClassLoadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type)
{
    UNUSED(cityType);UNUSED(algName);UNUSED(type);
    return new _c_algBaseClass();
}

bool _c_algTaskCenter::checkAlgTaskTimeOut()
{
    auto pTask = _TaskMap.begin() ;
    while (pTask != _TaskMap.end())
    {
        //肯能出现回复线程修改数据和此处状态设置冲突问题（task在修改过程中超时释放掉了，回复线程还为处理完毕，需考虑）
        _c_algTask *pAlgTask = (*pTask);
//        if(!pAlgTask->checkIsEndWork() && pAlgTask->checkResult() && (pAlgTask->processReponseIsDone &&
//        (pAlgTask->videoProcessState == videoProcessUnInit || pAlgTask->videoProcessState == videoProcessRecvFromRedis)))
        if(!pAlgTask->checkIsEndWork() && pAlgTask->checkResult())
        {
            //在回复线程中处理完毕,并且没有后续的视频处理任务,才能算结束
            pTask = _TaskMap.erase(pTask);
            //pAlgTask->freeAlgBaseClass();
            pAlgTask->setEndWork();
        }
        else if (!pAlgTask->checkIsEndWork()&&pAlgTask->getInSystemTime() > (__timeOutMilliSeconds * 1000))
        {
            pTask = _TaskMap.erase(pTask);

            bool isVideo = false;
//            if (pAlgTask->videoProcessState != videoProcessUnInit)
//                isVideo = true;

            pAlgTask->setAlgTaskResult(4, "服务器繁忙", isVideo);
            //pAlgTask->freeAlgBaseClass();
            pAlgTask->setEndWork();
        }
        else
        {
            pTask++;
        }
    }
    return true;
}

void _c_algTaskCenter::setWorkMode(WorkMode mode)
{
    workMode = mode;
}

void _c_algTaskCenter::loadPicExamples()
{
    std::string upPath = "/opt/vehicle/program/programPath/examplePics/";
    for (unsigned int i = 0; i < __algVector.size(); i++)
    {
        __algVector[i].examplePics.clear();
        std::string dirPath = upPath + to_string(__algVector[i].type);
//        printf("examplePic's folder path %s\n", dirPath.c_str());

        if (access(dirPath.c_str(), 0) == 0)
        {
            baseTool::getFileList(dirPath, __algVector[i].examplePics);
        }
    }
}

void _c_algTaskCenter::processVideoCheckAlg(_c_algTask *pTask)
{
    if (pTask->pVideoCheckInfo != NULL)
    {
        //1.没有视频需求
        if (!pTask->pVideoCheckInfo->isNeedLoadVideoInfo)
        {
            pTask->processReponseIsDone = true;
        }
        else
        {
            //2.有视频需求但没有视频算法项
    //        printf("%s:%d %s result:%s status:%d\n", __func__, __LINE__, pTask->algCode.c_str(), pTask->result.c_str(), pTask->videoProcessState);
            //照片结果不通过 进入视频审核流程
            if (pTask->result == std::to_string(NOT_PASS) && pTask->videoProcessState == videoProcessUnInit)
            {
                //需要先确定该车视频相关是否请求完毕
                while (!pTask->pVideoCheckInfo->shiPinDownloadIsFinished)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //                printf("wait for video request finish!\n");
                }

                pTask->pClass->isVideo = true;
                pTask->pClass->InParamEdit();//0344 等重置ID
                _c_video *pVideo = baseTool::getVideoObject(pTask);
                if (pVideo != NULL)
                {
                    pTask->videoProcessState = videoProcessSendToRedis;
                    pushVideoJsonToRedis(pTask, pVideo);
                }
            }
            //视频审核流程结束
            else if(pTask->videoProcessState == videoProcessSendToRedis)
            {
                pTask->videoProcessState = videoProcessRecvFromRedis;
            }

            pTask->processReponseIsDone = true;
        }
    }
    else
    {
        pTask->processReponseIsDone = true;
    }
}

void _c_algTaskCenter::pushVideoJsonToRedis(_c_algTask *pTask,  _c_video *pVideo)
{
    Json::Value root;
    root["inSystemTime"] = baseTool::getNowDate();
    root["timeoutSecond"] = std::to_string(__timeOutMilliSeconds);
    root["reponseChan"] = __pRedisParam->leastChan;

    Json::Value subRoot;
    Json::Value value = getVideoAlgJson(pTask, pVideo);
    subRoot.append(value);

    //0342 0344 照片时2个合并成一个 但视频是独立的
    _c_algTask *pExtTask = pTask->pClass->loadExtAlgTask();
    if (pExtTask != NULL)
    {
        _c_video *pExtVideo = baseTool::getVideoObject(pExtTask);

        if (pExtVideo != NULL)
        {
            value = getVideoAlgJson(pExtTask, pExtVideo);
            subRoot.append(value);
            pExtTask->videoProcessState = videoProcessSendToRedis;
            pExtTask->clearEndWork();
            pExtTask->algTaskVector.push_back(pExtTask);
            _TaskMap.push_back(pExtTask);
        }
    }
    root["algTaskList"] = subRoot;

//    printf("%s\n%s\n", __func__, root.toStyledString().c_str());
    LOG(ALG, INFO, "%s\n%s\n", __func__, root.toStyledString().c_str());
    Json::FastWriter writer;
    std::string strSendJson = writer.write(root);

    //将算法任务丢入计算队列
    pushAlgTaskInfoRedis(strSendJson, redisLeastChan);
}

Json::Value _c_algTaskCenter::getVideoAlgJson(_c_algTask *pTask, _c_video *pVideo)
{
    Json::Value root;
    //设置视频相关路径
    std::string mainUrl = pVideo->videoUrl;
    std::string mainPath = pVideo->localPath;

    //视频暂时没有副项 后续有了再说
    std::string subUrl = "TBD";
    std::string subPath = "TBD";

    pTask->pClass->setPhoto(mainUrl, mainPath, subUrl, subPath);
    pTask->pClass->isVideo = true;
    pTask->pClass->InParamEdit();

    root = pTask->getParamSendJson(__timeOutMilliSeconds, __pRedisParam->leastChan, true);

    return root;
}
