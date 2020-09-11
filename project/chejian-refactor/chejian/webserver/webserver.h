#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

#include <stdio.h>
#include <vector>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <event.h>
#include <evhttp.h>
#include "base/json/json.h"

#define PACKED
#define BODYBUFF_MAX_LEN 1024*200
#define FILEPATH_MAX_LEN 1024*10

class slaveInfo {
public:
    std::string user;
    std::string ip;
    std::string port;
};

typedef struct _HTTP_REQ_HANDLE
{
    evhttp_request *req{};
    std::string remoteHost;
    std::string uri;
    std::string method;
    char requesttime[32]{0};
    char bodybuff[BODYBUFF_MAX_LEN]{0};
    struct evbuffer *evbuf{nullptr};
    char filepath[FILEPATH_MAX_LEN]{0};
    struct stat fileinfo{};
}PACKED HTTP_REQ_HANDLE, *PHTTP_REQ_HANDLE;

typedef void (*web_func)(PHTTP_REQ_HANDLE pHandle,Json::Value *pRoot);

typedef struct _HTTP_NAME_CB
{
    std::string queryName;
    web_func cb;
}PACKED HTTP_NAME_CB, *PHTTP_NAME_CB;

//#define DOCUMENT_ROOT "../web"
#define DOCUMENT_ROOT "/opt/vehicle/program/programPath/web"

//libevent消息回调
void webCB(evhttp_request *req, void *arg);
//初始化key和函数指针
void initWebName2cb();
//设置版本信息
void setVersion(std::string version);
//设置算法任务管理模块句柄
void setAlgTaskCenter(void *pHandle);
//设置通信模块句柄
void setSessionTransCenter(void *pHandle);
//设置主机信息
void setMasterInfo(std::string ip);
//设置从机信息
void setSlaveInfo(std::string ip);
//请求事件接口
void requestEvent(PHTTP_REQ_HANDLE pHandle);
//请求无权访问接口
void webRequestNoPermission(PHTTP_REQ_HANDLE pHandle);
//设置配置模块句柄
void setConfigCenter(void *pHandle);
void startSyncTime(std::string ip, unsigned int port);
#endif // WEBSERVER_H
