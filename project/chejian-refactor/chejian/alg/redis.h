#ifndef _REDIS_H__
#define _REDIS_H__

#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <memory>
#include <mutex>
#include <queue>
#include <sys/time.h> 
#include <map>
#include <set>
#include "hiredis/hiredis.h"

enum RedisChannelType
{
    redisRequstChan = 0,
    redisGreenChan = 1,
    redisLeastChan = 2
};

typedef struct _REDIS_PARAM
{
	std::string strIp;	 //redis ip
	int port; 			//redis 端口
	std::string strPassword; //redis密码
	int db_number; 			//redis指定数据库索引,默认一个数据库，为0
    int timeout; //redis超时设置
    std::string requstChan;
    std::string reponseChan;
    std::string greenChan;
    std::string leastChan;
}REDIS_PARAM, *PREDIS_PARAM;


class KGRedisClient
{
public:
 //   bool ExecuteCmd_spop(const char *cmd, size_t len, std::string &response);
 	bool ExecuteCmd(std::string &response, const char* format, ...);
	bool ExecuteCmdEx(std::string& response, const char* const pszCmd, const char* const pszkey, const char* pszValue);
	bool ExecuteCmd_GetAll(std::set<std::string>& strSet, std::string& response, const char* format, ...);
 	bool ExecuteCmd_GetAll(std::map<std::string, std::string>& strMap, std::string& response, const char* format, ...);
 // redisReply* ExecuteCmd_spop(const char *cmd, size_t len);
    redisReply* ExecuteCmd(const char* format, ...);

	//static void InitializeRedis(const std::string& ip, int port, const std::string& password, int db_number = 0, int timeout = 2000);
        static void InitializeRedis(PREDIS_PARAM redisParam);
 	static KGRedisClient& get_instance();
private:
	KGRedisClient() {};
	virtual ~KGRedisClient();
    static int _timeout;
    static int _serverPort;
    static std::string _setverIp;
	static std::string _password;
	static int	_db_number;
 //   CCriticalSection m_lock;
 	std::mutex _mutex;
    std::queue<redisContext *> m_clients;
    time_t m_beginInvalidTime;
    static const int m_maxReconnectInterval = 3;
	redisContext* CreateContext();
    void ReleaseContext(redisContext *ctx, bool active);
    bool CheckStatus(redisContext *ctx);
};


#endif

