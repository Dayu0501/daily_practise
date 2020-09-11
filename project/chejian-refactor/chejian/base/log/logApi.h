#ifndef _LOGAPI_H_
#define _LOGAPI_H_
#include <mutex>
#include <string>
#include <memory>
#include <unistd.h>
#include <sys/stat.h>
#include "yt/log/ostreamlogger.h"
#include "yt/log/log.h"
#include "yt/log/datefilelogger.h"
using namespace yt; 

using namespace std;
#define UNUSED(x) (void)x
#define INFO LP_INFO
#define WARN LP_WARNING
#define ERR LP_ERROR
#define DEBUG LP_DEBUG

#define MAX_LENGTH 15000
//class LogApi;
//对外提供打印接口
#define LOG(LOGMODLE,LP, ...) \
        (LogApi::GetInstance())->GetLogger(LOGMODLE,LP)->Log(LP, ::yt::FormatLog(::yt::LogDispatcher::Instance()->GetLogger(LP)->GetFormat(), LP, __FILE__, __LINE__, __FUNCTION__,MAX_LENGTH, __VA_ARGS__))

//日志不同模块		
enum LOGMODLE
{
   COMMON = 1,
   SOAP = 2,
   SESSION = 3,
   ALG = 4,
   DB =5
};

class LogApi
{
public:
    static LogApi* GetInstance()
    {
        if(NULL==m_pInstance)
        {
            std::lock_guard<std::mutex> locker(m_oMutex);
            if(NULL==m_pInstance)
            {
                m_pInstance = new LogApi;
            }
        }
        return m_pInstance;
    }
	static void LoadPath(string path); //加载日志路径
	shared_ptr<DateFileLogger> GetLogger(LOGMODLE model,LogPriority type); //获取日志对象写不同日志
private:
    LogApi();
    ~LogApi() {}
    LogApi(const LogApi& other) {UNUSED(other);}
    LogApi& operator = (const LogApi& other) 
	{
		UNUSED(other);
		return *this;
	}
    void Destroy()
    {
        if (m_pInstance != NULL)
        {
            delete m_pInstance;
        }
        m_pInstance = NULL;
    }
	static shared_ptr<DateFileLogger> CreateLogger(string path,string name,LogPriority priority,string time="");
	static bool CreatPath(string path);
private:
    static LogApi*  m_pInstance;
    static std::mutex          m_oMutex;
	
	static string m_path;  //日志总路径
	
	shared_ptr<DateFileLogger> m_pInfoCommonLoger;
	shared_ptr<DateFileLogger> m_pWarnCommonLoger;
	shared_ptr<DateFileLogger> m_pErrCommonLoger;
	shared_ptr<DateFileLogger> m_pDebugCommonLoger;
 
	shared_ptr<DateFileLogger> m_pInfoSoapLoger;
	shared_ptr<DateFileLogger> m_pWarnSoapLoger;
	shared_ptr<DateFileLogger> m_pErrSoapLoger;
	shared_ptr<DateFileLogger> m_pDebugSoapLoger;
 
	shared_ptr<DateFileLogger> m_pInfoSessionLoger;
	shared_ptr<DateFileLogger> m_pWarnSessionLoger;
	shared_ptr<DateFileLogger> m_pErrSessionLoger;
	shared_ptr<DateFileLogger> m_pDebugSessionLoger;

	shared_ptr<DateFileLogger> m_pInfoAlgLoger;
	shared_ptr<DateFileLogger> m_pWarnAlgLoger;
	shared_ptr<DateFileLogger> m_pErrAlgLoger;
	shared_ptr<DateFileLogger> m_pDebugAlgLoger;

	shared_ptr<DateFileLogger> m_pInfoDbLoger;
	shared_ptr<DateFileLogger> m_pWarnDbLoger;
	shared_ptr<DateFileLogger> m_pErrDbLoger;
	shared_ptr<DateFileLogger> m_pDebugDbLoger;
};

#endif // _CONFIG_H_