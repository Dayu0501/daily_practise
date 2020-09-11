#ifndef HTTPSERVERM_H
#define HTTPSERVERM_H
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>
#include <memory>
#include <thread>

#define ROUTE_FUNCTION_TYPE std::function<void (Worker::HTTP_METHOD method,std::map<std::string,std::string>& nameVals,std::string& ostr,std::string& ofile)>

class HttpServerM;
class Worker
{
public:
    enum HTTP_METHOD
    {
        EV_GET,EV_POST,EV_HEAD,
        EV_PUT,EV_DELETE,EV_OPTIONS,
        EV_TRACE,EV_CONNECT,EV_PATCH,EV_UNKNOWN
    };
    Worker();
    virtual ~Worker();
    bool Init(HttpServerM* serv,int fd);
    void Run();
    void Stop();
    friend void HttpServerHandler(struct evhttp_request* req, void* arg);
    friend void HttpExitHandler(evutil_socket_t fd, short events, void* arg);
private:
    HttpServerM* serv_;
    event_base* base_;
    evhttp* evHttpServ_;
    event *exitEv_;
    evutil_socket_t exitSocks_[2];
protected:
    void Exit();
};

class HttpServerM
{
public:
    HttpServerM();
    virtual ~HttpServerM();
public:
    bool Run(int port,int workerNum);
    void Stop();
    void AddRouter(std::string path, ROUTE_FUNCTION_TYPE cb);
    friend void HttpServerHandler(struct evhttp_request* req, void* arg);
private:
    int fd_;
    int port_;
    int32_t workers_n_;
    Worker workers_[100];
    std::vector<std::shared_ptr<std::thread>> worker_threads_;
    std::map<std::string,ROUTE_FUNCTION_TYPE> router_;
};

#endif
