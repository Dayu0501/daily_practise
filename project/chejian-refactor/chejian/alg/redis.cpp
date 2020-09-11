#include "redis.h"


int KGRedisClient::_timeout = 2000;
int KGRedisClient::_serverPort = 0;
std::string KGRedisClient::_setverIp = "";
std::string KGRedisClient::_password = "";
int	KGRedisClient::_db_number = 0;



KGRedisClient::~KGRedisClient()
{
//    CAutoLock autolock(m_lock);
	std::unique_lock <std::mutex> lck(_mutex);
    while(!m_clients.empty())
    {
        redisContext *ctx = m_clients.front();
        redisFree(ctx);
        m_clients.pop();
    }
}

//void KGRedisClient::InitializeRedis(const std::string& ip, int port, const std::string& password, int db_number, int timeout)
void KGRedisClient::InitializeRedis(PREDIS_PARAM redisParam)
{

    KGRedisClient::_timeout = redisParam->timeout;
    KGRedisClient::_serverPort = redisParam->port;
    KGRedisClient::_setverIp = redisParam->strIp;
    KGRedisClient::_password = redisParam->strPassword;
    KGRedisClient::_db_number = redisParam->db_number;


	printf("Initialize Redis param: ip:%s, port:%d , pwd:%s.\n", KGRedisClient::_setverIp.c_str(), KGRedisClient::_serverPort, KGRedisClient::_password.c_str());
}


KGRedisClient& KGRedisClient::get_instance(void)
{
	if (KGRedisClient::_serverPort == 0 || KGRedisClient::_setverIp.empty())
		printf("Initialize Redis failed!");
	static KGRedisClient instance_;
	return instance_;
}



bool KGRedisClient::ExecuteCmd(std::string &response, const char* format, ...)
{

	va_list args;
	va_start(args, format);
	redisReply *reply = ExecuteCmd(format, args);
	va_end(args);

    
 	if(reply == NULL) return false;
    std::shared_ptr<redisReply> autoFree(reply, freeReplyObject);

    if(reply->type == REDIS_REPLY_INTEGER)
    {
        response = std::to_string(reply->integer);
        return true;
    }
    else if(reply->type == REDIS_REPLY_STRING)
    {
        response.assign(reply->str, reply->len);
        return true;
    }
    else if(reply->type == REDIS_REPLY_STATUS)
    {
        response.assign(reply->str, reply->len);
        return true;
    }
    else if(reply->type == REDIS_REPLY_NIL)
    {
        response = "";
        return true;
    }
    else if(reply->type == REDIS_REPLY_ERROR)
    {
        response.assign(reply->str, reply->len);
        return false;
    }
    else if(reply->type == REDIS_REPLY_ARRAY)
    {
        response = "Not Support Array Result!!!";
        return false;
    }
    else
    {
        response = "Undefine Reply Type";
        return false;
    }
}

bool KGRedisClient::ExecuteCmdEx(std::string& response, const char* const pszCmd, const char* const pszkey, const char* pszValue)
{
	redisContext *ctx = CreateContext();
	if (ctx == nullptr) return false;
	redisReply* reply = nullptr;
	if(pszValue == nullptr)
		reply = reinterpret_cast<redisReply *>(redisCommand(ctx, "%s %s", pszCmd, pszkey));
	else
		reply = reinterpret_cast<redisReply *>(redisCommand(ctx, "%s %s %s", pszCmd, pszkey, pszValue));
	ReleaseContext(ctx, reply != nullptr);

	if (reply == nullptr) return false;
	std::shared_ptr<redisReply> autoFree(reply, freeReplyObject);

	if (reply->type == REDIS_REPLY_INTEGER){
		response = std::to_string(reply->integer);
		return true;
	}
	else if (reply->type == REDIS_REPLY_STRING){
		response.assign(reply->str, reply->len);
		return true;
	}
	else if (reply->type == REDIS_REPLY_STATUS){
		response.assign(reply->str, reply->len);
		return true;
	}
	else if (reply->type == REDIS_REPLY_NIL){
		response = "";
		return true;
	}
	else if (reply->type == REDIS_REPLY_ERROR)
	{
		response.assign(reply->str, reply->len);
		return false;
	}
	else if (reply->type == REDIS_REPLY_ARRAY){
		response = "Not Support Array Result!!!";
		return false;
	}
	else{
		response = "Undefine Reply Type";
		return false;
	}
	return true;
}

bool KGRedisClient::ExecuteCmd_GetAll(std::set<std::string>& strSet, std::string& response, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	redisReply *reply = ExecuteCmd(format, args);
	va_end(args);
	if (reply == NULL) return false;
	if (reply->type == REDIS_REPLY_ARRAY)
	{
		for (size_t i = 0; i < reply->elements; ++i)
		{
			strSet.insert(reply->element[i]->str);
		}
		response = "Reply OK";
		return true;
	}
	else
	{
		response = "Error";
		return false;
	}
}

bool KGRedisClient::ExecuteCmd_GetAll(std::map<std::string, std::string>& strMap, std::string& response, const char* format, ...)
{

	va_list args;
	va_start(args, format);
	redisReply *reply = ExecuteCmd(format, args);
	va_end(args);

    
 	if(reply == NULL) return false;
    std::shared_ptr<redisReply> autoFree(reply, freeReplyObject);

    if(reply->type == REDIS_REPLY_ARRAY)
    {
		for(size_t i = 0; i < reply->elements; i+=2)
		{
			int type = reply->element[i+1]->type;
			if(type == REDIS_REPLY_STRING)
			{
				strMap.insert(std::make_pair(reply->element[i]->str, reply->element[i+1]->str));
			}
			else if(type == REDIS_REPLY_INTEGER)
			{
				strMap.insert(std::make_pair(reply->element[i]->str, std::to_string(reply->element[i+1]->integer)));
			}
			else
			{
				//printf("found others..., i:%d\n", i);
				response = "Reply OK";
        		return false;
			}
		}
	
        response = "Reply OK";
        return true;
    }
    else
    {
        response = "Error";
        return false;
    }
}


redisReply* KGRedisClient::ExecuteCmd(const char* format, ...)
{

	va_list args;
	va_start(args, format);

    redisContext *ctx = CreateContext();
    if(ctx == NULL) 
	{
		va_end(args);
		return NULL;
	}
  //  redisReply *reply = (redisReply*)redisCommand(ctx, "spop %b", cmd, len);
 //  	redisReply *reply = (redisReply*)redisCommand(ctx, "%s", cmd);	
 	redisReply* reply = (redisReply*)redisCommand(ctx, format, args);
  	va_end(args);
	
    ReleaseContext(ctx, reply != NULL);
    return reply;
}

redisContext* KGRedisClient::CreateContext()
{
    {
//        CAutoLock autolock(m_lock);
		std::unique_lock <std::mutex> lck(_mutex);

        if(!m_clients.empty())
        {
            redisContext *ctx = m_clients.front();
            m_clients.pop();
            return ctx;
        }
    }
    time_t now = time(NULL);
    if(now < m_beginInvalidTime + m_maxReconnectInterval) return NULL;
    struct timeval tv;
    tv.tv_sec = KGRedisClient::_timeout / 1000;
    tv.tv_usec = (KGRedisClient::_timeout % 1000) * 1000;;
    redisContext *ctx = redisConnectWithTimeout(KGRedisClient::_setverIp.c_str(), KGRedisClient::_serverPort, tv);

    if(ctx == NULL || ctx->err != 0)
    {
        if(ctx != NULL) redisFree(ctx);
        m_beginInvalidTime = time(NULL);
        
        return NULL;
    }

	redisReply *reply;
	std::string strReply = "AUTH ";
	strReply += KGRedisClient::_password;
	reply = (redisReply*)redisCommand(ctx, strReply.c_str());

	std::string strSelectDB = "SELECT ";
	strSelectDB += std::to_string(KGRedisClient::_db_number);
	printf("Redis database %s \n", strSelectDB.c_str());

	reply = (redisReply*)redisCommand(ctx, strSelectDB.c_str());

	freeReplyObject(reply);
	reply = NULL;

	printf("connect OK\n");
    return ctx;
}
void KGRedisClient::ReleaseContext(redisContext *ctx, bool active)
{
    if(ctx == NULL) return;
    if(!active) {redisFree(ctx); return;}
//    CAutoLock autolock(m_lock);
	std::unique_lock <std::mutex> lck(_mutex);

    m_clients.push(ctx);
}
bool KGRedisClient::CheckStatus(redisContext *ctx)
{
    redisReply *reply = (redisReply*)redisCommand(ctx, "ping");
    if(reply == NULL) return false;
    std::shared_ptr<redisReply> autoFree(reply, freeReplyObject);
    if(reply->type != REDIS_REPLY_STATUS) return false;
    if(strcasecmp(reply->str,"PONG") != 0) return false;
    return true;
}

