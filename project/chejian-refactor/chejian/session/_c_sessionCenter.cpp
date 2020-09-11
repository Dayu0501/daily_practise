#include "_c_sessionCenter.h"
#include "base/dataCenter.h"

_c_sessionCenter::_c_sessionCenter(_c_algTaskCenter *pAlgTaskCenter)
{
    _pAlgTaskCenter = pAlgTaskCenter;
}

void SessionCenter_QueryDataThread(_c_sessionCenter *pCenter)
{
    LOG(SESSION,INFO,"SessionCenter_QueryDataThread start ...\n");
    do{
        threadInfo *pInfo = pCenter->getSessionCenterThread();
        pInfo->updateCurCnt();
        pCenter->queryData();
    }while(!pCenter->isClose());
    LOG(SESSION,INFO,"SessionCenter_CheckSessionThread end ...\n");
}

void SessionCenter_CheckSessionThread(_c_sessionCenter *pCenter)
{
    LOG(SESSION,INFO,"SessionCenter_CheckSessionThread start ...\n");
    do{
        threadInfo *pInfo = pCenter->getSessionCheckThread();
        pInfo->updateCurCnt();
        pCenter->checkSession();
    }while(!pCenter->isClose());
    LOG(SESSION,INFO,"SessionCenter_CheckSessionThread end ...\n");
}

bool _c_sessionCenter::isClose()
{
    return false;
}

bool _c_sessionCenter::checkLicense() {
	std::string tmpDate = baseTool::getDangTianRiQi();
	printf("current date is %s \n", tmpDate.c_str());

	if (tmpDate != _curWorkDate) {
		_curWorkDate = tmpDate;

		std::string beginDate, endDate, licenseResult;
		_licenseOk = baseTool::checkLicense(licenseResult, beginDate, endDate);
		printf("check_licence isFlag : %d, message : %s\n", _licenseOk, licenseResult.c_str());
		LOG(COMMON, INFO, "check_licence isFlag : %d, message : %s\n", _licenseOk, licenseResult.c_str());
	}

	return _licenseOk;
}

void _c_sessionCenter::handleLicenseOutOfDate(_c_session *pSession) {
	pSession->setSessionResult(std::to_string(SOFT_NOTPROCESS), OUTOFLICENCE);

	for (auto item : pSession->algTaskVector) {
		item->result = std::to_string(NOT_PASS);
		item->reason = OUTOFLICENCE;
	}
}

bool _c_sessionCenter::stratSessionCenter()
{
    //启动数据查询线程
//    _pSessionCenterThread = new std::thread(SessionCenter_QueryDataThread, this);
    SessionCenterThread.threadName = "SessionCenterThread";
    SessionCenterThread._pthread = new std::thread(SessionCenter_QueryDataThread, this);
    //启动session回收线程
//    _pSessionCheckThread = new std::thread(SessionCenter_CheckSessionThread, this);
    SessionCheckThread.threadName = "SessionCheckThread";
    SessionCheckThread._pthread = new std::thread(SessionCenter_CheckSessionThread, this);
    return true;
}


bool _c_sessionCenter::queryData()
{
    //查询object队列中object个数
    unsigned int queueSize = getSessionQueueSize();
    if(queueSize > 0)
    {

        //从队列中获取一个待处理的object
        _c_session *pSession = getSessionFromQueue();
        LOG(COMMON,INFO,"get new pSession uuid[%s]\n",pSession->uuid.c_str());
        if(pSession != NULL)
        {
			std::string sessionReason;
            //处理所有网络接口相关
            pSession->processWangLuoJieKou();
            //加载session中object所有携带参数
            pSession->loadAllParam();
            //加载sesssion中object算法任务列表，也就是每张照片的列表
            pSession->loadAlgTask();
            //加载派生类私有的计算任务
            pSession->subLoadAlgTask();

            if (!checkLicense()) {
            	handleLicenseOutOfDate(pSession);
	            pushReponseQueue(pSession);

            	return true;
            }

            //算法检测前置信息检测,如果前置判断不通过直接回复，判断内部自己填充算法结果
            if(_pAlgTaskCenter != NULL && _pAlgTaskCenter->beforAlgCheck(pSession,sessionReason))
            {
                LOG(COMMON,INFO,"push into AlgQueue and SessionVector\n");
                //将session增加到sesion管理vector中
                pushSessionIntoSessionVector(pSession);
                //将session增加到队列中
                pushSessionAlgQueue(pSession);


            }else {
                LOG(COMMON,INFO,"beforAlgCheck is false push into ReponseQueue\n");
                pSession->setSessionResult(std::to_string(SOFT_NOTPROCESS),sessionReason);
               
                //如果前项判定不通过的话，可以自定义不通过的原因。
                _pAlgTaskCenter->beforeSetResult(pSession, sessionReason);
                 //将session中object插入到待回复队列
                pushReponseQueue(pSession);
            }

        }else {
            LOG(COMMON,INFO,"get pSession is NULL\n");
        }
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return true;
}

bool _c_sessionCenter::checkSession()
{
    //获取一个结束的session
    _c_session *pSession = getWorkEndSession();
    if(pSession != NULL)
    {
        LOG(COMMON,INFO,"get end work session uuid[%s]\n",pSession->uuid.c_str());
        std::string sessionResult = std::to_string(SOFT_NOTPASS);
        std::string sessionReason;

        if(_pAlgTaskCenter != NULL)
            sessionResult = std::to_string(_pAlgTaskCenter->afterAlgCheck(pSession,sessionReason));
        else
            sessionReason = "初始化错误";

        pSession->setSessionResult(sessionResult,sessionReason);
        //将session中object插入到待回复队列
        pushReponseQueue(pSession);
    }else {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return true;
}
