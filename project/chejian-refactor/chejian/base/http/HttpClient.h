#include <event2/event.h> 
#include <event2/buffer.h> 
#include <event2/http.h>
#include <event2/http_struct.h>
#include <event2/keyvalq_struct.h>

#include <string>
#include <unistd.h>
#include "base/baseInc.h"

using namespace std;
#define REQUEST_POST_FLAG               EVHTTP_REQ_POST
#define REQUEST_GET_FLAG                EVHTTP_REQ_GET

#define RESPONSE_JSON       1
// (default)
#define HTTP_CONTENT_TYPE_URL_ENCODED     "application/x-www-form-urlencoded"
// (use for files: picture, mp3, tar-file etc.)
#define HTTP_CONTENT_TYPE_FORM_DATA       "multipart/form-data"
// (use for plain text)
#define HTTP_CONTENT_TYPE_TEXT_PLAIN      "text/plain"
// (use for plain xml)
#define HTTP_CONTENT_TYPE_TEXT_XML        "text/xml"

/* 由于目前调用itoa的时候，都是10进制，所以radix被省略 */
#define itoa(number, array, radix) sprintf(array, "%d", number)

#pragma once
class HttpClient
{
public:
	struct evhttp_uri *m_uri;
	struct event_base *base;
	int m_request_flag;
	int m_request_text_type;
	struct evhttp_connection *m_connection;
	struct evhttp_request *m_httpreq;
    char *m_content_type ;
	char *m_post_data;
    std::string ResponseStringData;
    bool d_success_flag;

public:
    HttpClient();
    bool init_data(const char *uri, int request_flag, char* content_type, const char *data);
	~HttpClient();
    void freenem();
    bool startHttpClient(std::string filename="TBD");
	void http_request_free();
	int start_url_request();
    void set_retries_timeout(int retries, int timeout);

private:
    int m_retries;
    int m_timeout;
};

