//#include "afx.h"

#include <queue>
#include "libevent/event2/event.h"
#include "libevent/event2/buffer.h"
#include "libevent/event2/http.h"
#include "libevent/event2/http_struct.h"
#include "libevent/event2/keyvalq_struct.h"
#include "HttpServer.h"
#include "stdlib.h"
#include <locale.h> 
#include <fstream>


HttpServer::HttpServer()
{
    s_ip = "0.0.0.0";
    s_port = 0;
	base = event_base_new();          
}

HttpServer::~HttpServer()
{
	event_base_free(base);
}

bool HttpServer::startHttpServer(const char* ip, int port, void(*cb)(struct evhttp_request *, void *), void *arg)
{     
	//创建event_base和evhttp     
	http_server = evhttp_new(base);
	if (!http_server) 
    {
        //DATA_PRINT(LEVEL_ERROR, "HTTP server evhttp_new() failed! IP:%s, Port:%d \n", ip, port);
		return false;    
    }
	//绑定到指定地址上     
	int ret = evhttp_bind_socket(http_server, ip, port & 0xFFFF);     
	if (ret != 0) 
    {
        //DATA_PRINT(LEVEL_ERROR, "HTTP server evhttp_bind_socket() failed! IP:%s, Port:%d \n", ip, port);
		return false;     
	}     
	//设置事件处理函数     
    evhttp_set_gencb(http_server, cb, arg);
	//启动事件循环，当有http请求的时候会调用指定的回调     
    //DATA_PRINT(LEVEL_INFO, "HTTP server listening(%s:%d)...... \n", ip, port);
    event_base_dispatch(base);
	/*
	HANDLE m_hThread;
	DWORD dwThread;

	// 创建响应线程，启动线程函数
	m_hThread = ::CreateThread(NULL, 0, httpserverthread, (LPVOID)this, 0, &dwThread);
	if (NULL == m_hThread)
		return FALSE;*/

    evhttp_free(http_server);
	return true; 
} 


int HttpServer::run()
{     
	//Windows 平台套接字库的初始化 
#ifdef WIN32     
	WSADATA wsaData;    
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif     


#ifdef WIN32     
	WSACleanup(); 
#endif     
	return 0;
}


void HttpServer::stop()
{
	event_base_loopexit(base,0);
}


