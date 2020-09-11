#ifndef _C_REDISCONFIG_H
#define _C_REDISCONFIG_H
#include "base/_c_dbTask.h"
#include "base/baseTool.h"
#include "alg/redis.h"

class _c_redisConfig:public _c_dbTask{
public:
    std::string redisIp = "127.0.0.1";
    std::string redisPort = "6379";
    std::string redisPassword = "123";
    std::string redisDbNumber = "0";
    std::string redisTimeout = "2000";
    std::string redisrequstChan = "alg_request_queue";
    std::string redisreponseChan = "alg_response_queue";
    std::string redisGreenChan = "alg_request_pro_queue";
    std::string redisLeastChan = "alg_request_least_queue";

    REDIS_PARAM redisParam;

    _c_redisConfig(){
        tableName = "redis_config";
        memberVector.push_back({"redisIp", "redisIp", &redisIp, "RedisIp地址", DBOPTION_DEFAULT});
        memberVector.push_back({"redisPort", "redisPort", &redisPort, "Redis端口", DBOPTION_DEFAULT});
        memberVector.push_back({"redisPassword", "redisPassword", &redisPassword, "Redis登录密码", DBOPTION_DEFAULT});
        memberVector.push_back({"redisDbNumber", "redisDbNumber", &redisDbNumber, "Redis指定索引数", DBOPTION_DEFAULT});
        memberVector.push_back({"redisTimeout", "redisTimeout", &redisTimeout, "Redis超时时间", DBOPTION_DEFAULT});
        memberVector.push_back({"redisrequstChan", "redisrequstChan", &redisrequstChan, "Redis发送通道", DBOPTION_DEFAULT});
        memberVector.push_back({"redisreponseChan", "redisreponseChan", &redisreponseChan, "Redis接收通道", DBOPTION_DEFAULT});
        memberVector.push_back({"redisGreenChan", "redisGreenChan", &redisGreenChan, "Redis发送快速通道", DBOPTION_DEFAULT});
        memberVector.push_back({"redisLeastChan", "redisLeastChan", &redisLeastChan, "Redis发送最低优先级通道", DBOPTION_DEFAULT});
    }

    Json::Value getOrderJson()
    {
        Json::Value  root;
        for (unsigned int i = 0; i < memberVector.size(); i++) {
                Json::Value  subRoot;
                subRoot["name"] = memberVector[i].desc;
                root.append(subRoot);
        }
        return root;
    }

    Json::Value getConfigJson()
    {
        Json::Value  root;
        for (unsigned int i = 0; i < memberVector.size(); i++) {
                root[memberVector[i].desc] = *(memberVector[i].value);
        }
        return root;
    }

    bool setConfigJson(Json::Value *pRoot)
    {
        for (unsigned int i = 0; i < memberVector.size(); i++) {
            for (unsigned int j = 0; j < pRoot->size(); j++) {
                    //if()
            }
        }
        return true;
    }

    PREDIS_PARAM getStructRedisParam() {
        redisParam.strIp = redisIp;
        redisParam.port = baseTool::str2Int(redisPort);
        redisParam.strPassword = redisPassword;
        redisParam.db_number = baseTool::str2Int(redisDbNumber);
        redisParam.timeout = baseTool::str2Int(redisTimeout);
        redisParam.requstChan = redisrequstChan;
        redisParam.reponseChan = redisreponseChan;
        redisParam.greenChan = redisGreenChan;
        redisParam.leastChan = redisLeastChan;

        return &redisParam;
    }

    bool needFree(){return false;}
};
#endif // _C_REDISCONFIG_H
