#include "HttpClient.h"
#include <ctime>
#include <string.h>
#include <stdlib.h>

static std::string g_localServerPort = "9080";

void http_requset_post_cb(struct evhttp_request *req, void *arg);
void http_requset_get_cb(struct evhttp_request *req, void *arg);

std::string UTF8toANSI(char *strUTF8)
{
    std::string ansistr = strUTF8;
    return ansistr;
}

std::string ANSItoUTF8(char* strAnsi)
{
    std::string ansistr = strAnsi;
    return ansistr;
}

// 写文件
std::string fun_write_new_file(std::string, std::string, std::string);
// B64 decode
//std::string b64Decode(const char* Data, int DataByte);
HttpClient::HttpClient()
{
	base = event_base_new();
	m_request_text_type = 0;
	m_uri = NULL;
	m_post_data = NULL;
	m_connection = NULL;
	m_request_flag = REQUEST_GET_FLAG;
    m_content_type = NULL;
    m_retries = 5;
    m_timeout = 15;
    ResponseStringData.clear();
}

bool HttpClient::init_data(const char *uri, int request_flag, char* content_type, const char *data)
{
    m_uri = evhttp_uri_parse(uri);
    if (!m_uri) {
        printf("URI has unsafe code!\n");
        return false;
    }

    m_request_flag = request_flag;
    if (m_request_flag == REQUEST_POST_FLAG)
    {
        if (content_type == NULL)
        {
            m_content_type = strdup(HTTP_CONTENT_TYPE_URL_ENCODED);
        }
        else
        {
            m_content_type = strdup(content_type);
        }

        if (data == NULL)
        {
            m_post_data = NULL;
        }
        else
        {
            m_post_data = strdup(data);
        }
    }

    return true;
}

HttpClient::~HttpClient()
{
	if (m_request_flag == REQUEST_POST_FLAG) {
		if (m_content_type) {
			free(m_content_type);
			m_content_type = NULL;
		}
		if (m_post_data) {
			free(m_post_data);
			m_post_data = NULL;
		}
	}
    if (m_request_flag == REQUEST_GET_FLAG)
    {
        if (m_content_type) {
            free(m_content_type);
            m_content_type = NULL;
        }

    }
	event_base_free(base);
}
void HttpClient::freenem()
{
    if (m_request_flag == REQUEST_POST_FLAG) {
        if (m_content_type) {
            free(m_content_type);
            m_content_type = NULL;
        }
        if (m_post_data) {
            free(m_post_data);
            m_post_data = NULL;
        }
    }
    if (m_request_flag == REQUEST_GET_FLAG)
    {
        if (m_content_type) {
            free(m_content_type);
            m_content_type = NULL;
        }

    }
    event_base_free(base);
}


/************************** Request Function ******************************/
void http_requset_post_cb(struct evhttp_request *req, void *arg)
{
    printf("<-----http_requset_post_cb is in  - \n");
	HttpClient *httpclientpost = (HttpClient *)arg;
	if (req == NULL)
	{
        printf("HTTP client[POST]: no response! \n");
        printf("URL: %s:%d%s \n",
                   evhttp_uri_get_host(httpclientpost->m_uri),
                   evhttp_uri_get_port(httpclientpost->m_uri),
                   evhttp_uri_get_path(httpclientpost->m_uri));

		httpclientpost->d_success_flag = false;
		event_base_loopexit(httpclientpost->base, 0);
		return;
	}

	httpclientpost->d_success_flag = true;
	struct evbuffer* buf = evhttp_request_get_input_buffer(req);
    unsigned int len = (unsigned int)evbuffer_get_length(buf);
	if (len > 0)
	{
		char *data = (char*)malloc(len + 1);
        if(evbuffer_copyout(buf, data, len) != -1)
        {
            *(data + len) = 0;
        }
        else
            printf("event_copyout = -1 !!!!");
        //..................................
        if (strstr(evhttp_request_get_uri(req), "InsurService.asmx") != NULL)
        {
//            g_jqxbd_result.assign(data); 如果需要的话就保存
        }
		free(data);
	}

	switch (req->response_code)
	{
    case HTTP_OK:
    {
        if (len > 0) {
            char *data = (char *)malloc(len + 1);
            evbuffer_copyout(buf, data, len);
            *(data + len) = 0;
            httpclientpost->ResponseStringData = data;
            free(data);
        }

        event_base_loopexit(httpclientpost->base, 0);
        break;
    }
    case HTTP_MOVEPERM:
        printf("<-----Client:");
        printf("%s\n", "the uri moved permanently");
        break;

    case HTTP_MOVETEMP:
    {
        const char *new_location = evhttp_find_header(req->input_headers, "Location");
        struct evhttp_uri *new_uri = evhttp_uri_parse(new_location);
        evhttp_uri_free(httpclientpost->m_uri);
        httpclientpost->m_uri = new_uri;
        httpclientpost->start_url_request();
        return;
    }

    default:
        printf("HTTP client[POST]: abnormal response! \n");
        printf("HTTP code: %d, Message:%s \n", req->response_code, req->response_code_line);
        printf("URL: %s:%d%s \n",
                   evhttp_uri_get_host(httpclientpost->m_uri),
                   evhttp_uri_get_port(httpclientpost->m_uri),
                   evhttp_uri_get_path(httpclientpost->m_uri));

        event_base_loopexit(httpclientpost->base, 0);
        return;
	}
}


void http_requset_get_cb(struct evhttp_request *req, void *arg)
{
	HttpClient *httpclientget = (HttpClient *)arg;

    if (req == NULL) {
        printf("HTTP client[GET]: no response! \n");
        printf("URL: %s:%d%s \n",
                   evhttp_uri_get_host(httpclientget->m_uri),
                   evhttp_uri_get_port(httpclientget->m_uri),
                   evhttp_uri_get_path(httpclientget->m_uri));
        printf("#################################### \n");

        httpclientget->d_success_flag = false;
		event_base_loopexit(httpclientget->base, 0);
		return;
	}

    httpclientget->d_success_flag = true;

	switch (req->response_code)
	{
	case HTTP_OK:
	{
        if (httpclientget->m_request_text_type != 0)
        {
            struct evbuffer* buf = evhttp_request_get_input_buffer(req);
            unsigned int len = (unsigned int)evbuffer_get_length(buf);

            char *data = (char *)malloc(len + 1);
            evbuffer_copyout(buf, data, len);
            *(data + len) = 0;

            if (httpclientget->m_request_text_type == RESPONSE_JSON)
            {
                httpclientget->ResponseStringData = data;
            }

            free(data);
        }
        event_base_loopexit(httpclientget->base, 0);
		break;
	}
	case HTTP_MOVEPERM:
        printf("<-----Client:");
        printf("%s\n", "the uri moved permanently");
		event_base_loopexit(httpclientget->base, 0);
		break;
	case HTTP_MOVETEMP:
	{
		const char *new_location = evhttp_find_header(req->input_headers, "Location");
		struct evhttp_uri *new_uri = evhttp_uri_parse(new_location);
		evhttp_uri_free(httpclientget->m_uri);
		httpclientget->m_uri = new_uri;
		httpclientget->start_url_request();
		return;
	}
	default:
        printf("HTTP client[GET]: abnormal response! \n");
        printf("HTTP code: %d, Message:%s \n", req->response_code, req->response_code_line);
        printf("URL: %s:%d%s \n",
                   evhttp_uri_get_host(httpclientget->m_uri),
                   evhttp_uri_get_port(httpclientget->m_uri),
                   evhttp_uri_get_path(httpclientget->m_uri));

        httpclientget->d_success_flag = false;
		event_base_loopexit(httpclientget->base, 0);
		return;
	}
}

/************************** Start POST/GET Function ******************************/
/**
* @param content_type: refer HTTP_CONTENT_TYPE_*
*/

int HttpClient::start_url_request()
{
	struct evkeyvalq params;
//    printf("start_url_request ! \n");

	if (m_connection)
		evhttp_connection_free(m_connection);

	int port = evhttp_uri_get_port(m_uri);
    if (port == -1) port = atoi(g_localServerPort.c_str()) + 1;

    m_connection = evhttp_connection_base_new(base, NULL, evhttp_uri_get_host(m_uri), port);
    evhttp_connection_set_retries(m_connection, m_retries);
    evhttp_connection_set_timeout(m_connection, m_timeout);

	/**
	* Request will be released by evhttp connection
	* See info of evhttp_make_request()
	*/
	if (m_request_flag == REQUEST_POST_FLAG) {
		m_httpreq = evhttp_request_new(http_requset_post_cb, this);
	}
    else if (m_request_flag == REQUEST_GET_FLAG) {
		m_httpreq = evhttp_request_new(http_requset_get_cb, this);
	}

	/** Set the header properties */
    evhttp_add_header(m_httpreq->output_headers, "Host", evhttp_uri_get_host(m_uri));
	if (m_request_flag == REQUEST_POST_FLAG) {

		const char* query = evhttp_uri_get_query(m_uri);
		const char* path = evhttp_uri_get_path(m_uri);
		string path_query;
		if (path)
			path_query = path;
		if (query)
		{
			path_query += "?"; 
			path_query += query;
		}

		/** Set the post data */
		if (m_post_data)
			evbuffer_add(m_httpreq->output_buffer, ANSItoUTF8(m_post_data).c_str(), strlen(ANSItoUTF8(m_post_data).c_str()));
		evhttp_add_header(m_httpreq->output_headers, "Content-Type", m_content_type);

		char num[10];
        itoa((int)strlen(ANSItoUTF8(m_post_data).c_str()), num, 10);

        evhttp_add_header(m_httpreq->output_headers, "Length", num);

		evhttp_make_request(m_connection, m_httpreq, EVHTTP_REQ_POST,
            (path_query.length()>1) ? path_query.data() : "/");
	}
	else if (m_request_flag == REQUEST_GET_FLAG) {
		const char* query = evhttp_uri_get_query(m_uri);
		const char* path = evhttp_uri_get_path(m_uri);
		string path_query;
		if (path)
			path_query = path;
		if (query)
		{
			path_query += "?";
			path_query += query;
		}
		evhttp_make_request(m_connection, m_httpreq, EVHTTP_REQ_GET,
            (path_query.length()>1) ? path_query.data() : "/");
	}

	return 0;
}

void  HttpClient::http_request_free()
{
	evhttp_connection_free(m_connection);
	m_connection = NULL;
	evhttp_uri_free(m_uri);
	m_uri = NULL;
}

bool HttpClient::startHttpClient(std::string filename)
{
    ResponseStringData.clear();
    if("TBD"==filename)
    {
//        printf("startHttpClient TBD if! \n");
        start_url_request();
    }

//    printf("HTTP client has sent request(host:%s, port:%d, path:%s)......\n",
//               evhttp_uri_get_host(m_uri), evhttp_uri_get_port(m_uri), evhttp_uri_get_path(m_uri));

	event_base_dispatch(base);
	http_request_free();
	
    return true;
}

void HttpClient::set_retries_timeout(int retries, int timeout)
{
    m_retries = retries, m_timeout = timeout;
}
