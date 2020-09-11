#ifndef _HTTPSERVER_H_
#define _HTTPSERVER_H_

#include "libevent/event2/event.h"
#include "libevent/event2/buffer.h"
#include "libevent/event2/http.h"
#include <string>

using namespace std;

class HttpServer
{
public:
	string s_ip;
	int s_port;
	event_base* base;
	evhttp* http_server;
	std::string m_method;
	std::string m_jkxlh;
	std::string m_jkid;
	std::string m_xtlb;

public:
	HttpServer();
	~HttpServer();
	bool startHttpServer(const char* ip, int port, void(*cb)(struct evhttp_request *, void *), void *arg);
	int run();
	void stop();
};
#endif
