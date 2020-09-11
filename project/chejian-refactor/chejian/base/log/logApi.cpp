#include "logApi.h"
#include <stdarg.h>

//格式化输出log内容：D时间 P等级 F文件 L行号 t线程号 p进程号 f函数名 m日志输出内容
#define LOG_FORMAT "[%D][%P][%t](%F:%L %f) %m "

//按时间生成log日志 Y年份 m月份 d日 H时：例 ".%Y-%m-%d:%H",默认传空按天生成日志
#define LOG_TIME_DAY ".%Y-%m-%d"
#define LOG_TIME_HOUR ".%Y-%m-%d:%H"

LogApi*  LogApi::m_pInstance = NULL;
std::mutex  LogApi::m_oMutex;
string LogApi::m_path = "/opt/vehicle/program/log";

string strCommonLog = "/common/";
string strSoapLog = "/soap/";
string strSessionLog = "/session/";
string strAlgLog = "/alg/";
string strDbLog = "/db/";

string strInfoName = "infolog";
string strWarnName = "warnlog";
string strErrName = "errlog";
string strDebugName = "debuglog";

shared_ptr<DateFileLogger> LogApi::CreateLogger(string subPath,string name,LogPriority priority,string time)
{
	//cout<<m_path + subPath + name<<endl;
	DateFileLogger *runLog = new DateFileLogger(m_path + subPath + name,LOG_FORMAT,time);
	AC_SET_LOGGER(priority,runLog);
	shared_ptr<DateFileLogger> pLoger(runLog);
	return pLoger;
}

bool LogApi::CreatPath(string path)
{
	if(access(path.c_str(),F_OK)!=0)
    {
        if(mkdir(path.c_str(),S_IRWXU|S_IRWXG|S_IRWXO))
        {
			cout<<"mkdir error:"<<path<<endl;
            return false;
        }
    }
	//cout<<path<<endl;
	return true;
}

void LogApi::LoadPath(string path)
{
	m_path = path;
	if(CreatPath(m_path))
	{
		CreatPath(m_path + strCommonLog);
		CreatPath(m_path + strSoapLog);
		CreatPath(m_path + strSessionLog);
		CreatPath(m_path + strAlgLog);
		CreatPath(m_path + strDbLog);
	}
}

LogApi::LogApi()
{
	shared_ptr<OStreamLogger> stdoutlog(new OStreamLogger(std::cout));
	AC_SET_DEFAULT_LOGGER(stdoutlog.get());
	
	m_pInfoCommonLoger = CreateLogger(strCommonLog,strInfoName,INFO);
	m_pWarnCommonLoger = CreateLogger(strCommonLog,strWarnName,WARN);
	m_pErrCommonLoger = CreateLogger(strCommonLog,strErrName,ERR);
	m_pDebugCommonLoger = CreateLogger(strCommonLog,strDebugName,DEBUG);
	
	m_pInfoSoapLoger = CreateLogger(strSoapLog,strInfoName,INFO);
	m_pWarnSoapLoger = CreateLogger(strSoapLog,strWarnName,WARN);
	m_pErrSoapLoger = CreateLogger(strSoapLog,strErrName,ERR);
	m_pDebugSoapLoger = CreateLogger(strSoapLog,strDebugName,DEBUG);
	
	m_pInfoSessionLoger = CreateLogger(strSessionLog,strInfoName,INFO);
	m_pWarnSessionLoger = CreateLogger(strSessionLog,strWarnName,WARN);
	m_pErrSessionLoger = CreateLogger(strSessionLog,strErrName,ERR);
	m_pDebugSessionLoger = CreateLogger(strSessionLog,strDebugName,DEBUG);
	
	m_pInfoAlgLoger = CreateLogger(strAlgLog,strInfoName,INFO,LOG_TIME_HOUR);
	m_pWarnAlgLoger = CreateLogger(strAlgLog,strWarnName,WARN,LOG_TIME_HOUR);
	m_pErrAlgLoger = CreateLogger(strAlgLog,strErrName,ERR,LOG_TIME_HOUR);
	m_pDebugAlgLoger = CreateLogger(strAlgLog,strDebugName,DEBUG,LOG_TIME_HOUR);
	
	m_pInfoDbLoger = CreateLogger(strDbLog,strInfoName,INFO);
	m_pWarnDbLoger = CreateLogger(strDbLog,strWarnName,WARN);
	m_pErrDbLoger = CreateLogger(strDbLog,strErrName,ERR);
	m_pDebugDbLoger = CreateLogger(strDbLog,strDebugName,DEBUG);
	
}

shared_ptr<DateFileLogger> LogApi::GetLogger(LOGMODLE model,LogPriority type)
{
	if(COMMON == model)
	{
		if(INFO == type)
		{
			return m_pInfoCommonLoger;
		}
		else if(WARN == type)
		{
			return m_pWarnCommonLoger;
		}
		else if(ERR == type)
		{
			return m_pErrCommonLoger;
		}
		else if(DEBUG == type)
		{
			return m_pDebugCommonLoger;
		}
	}
	else if(SOAP == model)
	{
		if(INFO == type)
		{
			return m_pInfoSoapLoger;
		}
		else if(WARN == type)
		{
			return m_pWarnSoapLoger;
		}
		else if(ERR == type)
		{
			return m_pErrSoapLoger;
		}
		else if(DEBUG == type)
		{
			return m_pDebugSoapLoger;
		}
	}
	else if(SESSION == model)
	{
		if(INFO == type)
		{
			return m_pInfoSessionLoger;
		}
		else if(WARN == type)
		{
			return m_pWarnSessionLoger;
		}
		else if(ERR == type)
		{
			return m_pErrSessionLoger;
		}
		else if(DEBUG == type)
		{
			return m_pDebugSessionLoger;
		}
	}
	else if(ALG == model)
	{
		if(INFO == type)
		{
			return m_pInfoAlgLoger;
		}
		else if(WARN == type)
		{
			return m_pWarnAlgLoger;
		}
		else if(ERR == type)
		{
			return m_pErrAlgLoger;
		}
		else if(DEBUG == type)
		{
			return m_pDebugAlgLoger;
		}
	}
	else if(DB == model)
	{
		if(INFO == type)
		{
			return m_pInfoDbLoger;
		}
		else if(WARN == type)
		{
			return m_pWarnDbLoger;
		}
		else if(ERR == type)
		{
			return m_pErrDbLoger;
		}
		else if(DEBUG == type)
		{
			return m_pDebugDbLoger;
		}
	}
	return nullptr;
}
