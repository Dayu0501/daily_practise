#include "webserver.h"
#include "alg/_c_algTaskCenter.h"
#include "sessionService/_c_sessionTransCenter.h"
#include "base/dataCenter.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "db/dbquery/dbinterface.h"
#include "base/baseTool.h"
#include "sessionService/chayan/jiNan/_c_chaYanYuan.h"
#include "base/_c_chaYanVehicle.h"
#include "base/_c_vehicle.h"
#include "config/_c_configCenter.h"
#include "config/_c_jsonArrayClass.h"
#include <map>
#include "base/_c_chejian_init.h"
#include "monitorService/mmap/mmapReader.h"
#include "base/http/HttpClient.h"
#include "sessionService/chejian/_c_cheJianSessionService.h"
#include "sessionService/chayan/_c_chaYanSessionService.h"
#include "base/_c_wangLuoJieKouReturn.h"
#include<cmath>
#include "base/soapApi/RecordSoapRequestInDB.h"
#include "base/soapApi/soapApi.h"

#define MAX_PIC_LEN    1024*1024*2
using namespace std;
std::string _version="";
static _c_algTaskCenter *pTaskCenter = NULL;
static _c_sessionTransCenter *pSessionTransCenter = NULL;
static _c_configCenter *pConfigCenter = NULL;

std::vector<slaveInfo> g_slaveInfo;
static std::vector<HTTP_NAME_CB> __name2cb;
#ifndef O_BINARY

#define O_BINARY 0

#endif

std::string getPwd(std::string pwd, int key);
std::string getParam(std::string url,std::string paramName);
void addXrJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot);
void addJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot);
void addVideoJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot);

std::string getPwd(std::string pwd, int key)
{
    char subKey = key%9+1;
    char inpwd[1024] = {0};
    char outPwd[1024] = {0};
    sprintf(inpwd,"%s",pwd.c_str());
    unsigned int pwdLen = strlen(inpwd);

    for (unsigned int i = 0; i < pwdLen; i++) {
        if((
            inpwd[i] + subKey != '!'
            &&inpwd[i] + subKey != '#'
            &&inpwd[i] + subKey != '$'
            &&inpwd[i] + subKey != '%'
            &&inpwd[i] + subKey != '^'
            &&inpwd[i] + subKey != '&'
            &&inpwd[i] + subKey != '*'
        ))
        {
            outPwd[i] = inpwd[i] - subKey;
        }
        else
        {
            outPwd[i] = inpwd[i];
        }
    }
    return outPwd;

}
//CGI事件
void cgiEvent(PHTTP_REQ_HANDLE pHandle)
{
    Json::Value  root;
    evhttp_add_header(pHandle->req->output_headers, "Content-Type", "application/json");
    for (unsigned int i=0; i<__name2cb.size(); i++) {
        //printf("queryName:%s\n",__name2cb[i].queryName.c_str());
        if(pHandle->uri.find(__name2cb[i].queryName) != std::string::npos)
        {
            root["action"]=__name2cb[i].queryName;
            std::string pwd = getParam(pHandle->uri,"pwd");
            std::string randid = getParam(pHandle->uri,"randid");

            if(!pwd.empty()&&!randid.empty())
            {
                int key = stoi(randid);
                if(getPwd(pwd, key) == baseTool::getDBPassWord(DBPWD))
                {
                    __name2cb[i].cb(pHandle,&root);
                    break;
                }
                //printf("pwd:%s\n",getPwd(pwd, key).c_str());
            }

            root["return"] = false;
            root["msg"] = "pwd or randid err";

            break;
        }
    }
    evbuffer_add_printf(pHandle->evbuf, "%s", root.toStyledString().c_str());
    evhttp_send_reply(pHandle->req, HTTP_OK, "OK", pHandle->evbuf);
}

std::string getMethod(evhttp_request *req)
{
    std::string method;

    switch (evhttp_request_get_command(req)) {
        case EVHTTP_REQ_GET:     method = "GET";break;
        case EVHTTP_REQ_POST:    method = "POST"; break;
        case EVHTTP_REQ_HEAD:    method = "HEAD"; break;
        case EVHTTP_REQ_PUT:     method = "PUT"; break;
        case EVHTTP_REQ_DELETE:  method = "DELETE"; break;
        case EVHTTP_REQ_OPTIONS: method = "OPTIONS"; break;
        case EVHTTP_REQ_TRACE:   method = "TRACE"; break;
        case EVHTTP_REQ_CONNECT: method = "CONNECT"; break;
        case EVHTTP_REQ_PATCH:   method = "PATCH"; break;
        default:                 method = "";
    }

    return method;
}

void webCB(evhttp_request *req, void *arg)
{
    UNUSED(arg);
    HTTP_REQ_HANDLE httpHandle;
    struct tm *m;
    time_t timep;

    //memset(&httpHandle,0,sizeof(HTTP_REQ_HANDLE));

    httpHandle.req = req;
    httpHandle.remoteHost = std::string(req->remote_host);

   //printf("----------------------------:%s \n",httpHandle.remoteHost.c_str() ) ;
   // bool isExist = g_whitelist.isInWhite(httpHandle.remoteHost,"httpPermit") ;
    if (false){

        bool isExist = pTaskCenter->checkHttpBaiMingDan(httpHandle.remoteHost) ;
        if( !isExist)
        {
            return ;
        }
    }
    httpHandle.uri = std::string(evhttp_uridecode(evhttp_request_get_uri(req), 0, NULL));
    httpHandle.method = getMethod(req);

   time(&timep);
    m = localtime(&timep);
    sprintf(httpHandle.requesttime, "%4d-%02d-%02d %02d:%02d:%02d", (1900 + m->tm_year), (1 + m->tm_mon), m->tm_mday, m->tm_hour, m->tm_min, m->tm_sec);
    requestEvent(&httpHandle);
}


void setWebNameCb(std::string name,web_func cb)
{
    HTTP_NAME_CB namecb;
    namecb.queryName = name;
    namecb.cb = cb;
    __name2cb.push_back(namecb);
}

void setAlgTaskCenter(void *pHandle)
{
    if(pTaskCenter == NULL)
    {
        pTaskCenter = (_c_algTaskCenter *)pHandle;
    }
}

void setSessionTransCenter(void *pHandle)
{
    if(pSessionTransCenter == NULL)
    {
        pSessionTransCenter = (_c_sessionTransCenter *)pHandle;
    }
}

void setConfigCenter(void *pHandle)
{
    if(pConfigCenter == NULL)
    {
        pConfigCenter = (_c_configCenter *)pHandle;
    }
}

void setMasterInfo(std::string ip)
{
    g_slaveInfo.clear();
    slaveInfo slaveinfo;
    slaveinfo.ip = ip;
    slaveinfo.port = "10080";
    slaveinfo.user = "em";

    g_slaveInfo.push_back(slaveinfo);
}

void setSlaveInfo(std::string ip)
{
    slaveInfo slaveinfo;
    slaveinfo.ip = ip;
    slaveinfo.port = "10080";
    slaveinfo.user = "em";

    g_slaveInfo.push_back(slaveinfo);
}

void setVersion(std::string version)
{
    _version = version;
}

int fileRead(const char *pathName, char *readBuf,int manSize)
{
    int readNum = 0;
    FILE *fp;

    fp = fopen(pathName, "rb+");
    if(NULL == fp)
    {
        printf("Open %s file failed\n", pathName);
        return -1;
    }
    readNum = fread(readBuf,1,manSize,fp);
    fclose(fp);
    //printf("pathName:%s readNum=%d\n",pathName,readNum);
    return readNum;
}

void requestError(PHTTP_REQ_HANDLE pHandle)
{
    if (errno == ENOENT)
    {
        evhttp_send_error(pHandle->req, 404, "HTTP/1.1 404 Not Found");
        sprintf(pHandle->bodybuff, "HTTP/1.1 404 Not Found\t%s\t%s\n", pHandle->uri.c_str(), pHandle->requesttime);
    }
    else if (access(pHandle->filepath, R_OK) < 0)
    {
        evhttp_send_error(pHandle->req, 403, "HTTP/1.1 403 Forbidden");
        sprintf(pHandle->bodybuff, "HTTP/1.1 403 Forbidden\t%s\t%s\n", pHandle->uri.c_str(), pHandle->requesttime);
    }
    else
    {
        evhttp_send_error(pHandle->req, 500, "HTTP/1.1 500 Server Error");
        sprintf(pHandle->bodybuff, "HTTP/1.1 500 Server Error\t%s\t%s\n", pHandle->uri.c_str(), pHandle->requesttime);
    }
    evhttp_add_header(pHandle->req->output_headers, "Content-Type", "text/html; charset=UTF-8");
}

const char *getContentType(char *name){
    const char *dot, *buf;

    dot = strrchr(name, '.');

    /* Text */
    if ( strcmp(dot, ".txt") == 0 ){
        buf = "text/plain";
    } else if ( strcmp( dot, ".css" ) == 0 ){
        buf = "text/css";
    } else if ( strcmp( dot, ".js" ) == 0 ){
        buf = "text/javascript";
    } else if ( strcmp(dot, ".xml") == 0 || strcmp(dot, ".xsl") == 0 ){
        buf = "text/xml";
    } else if ( strcmp(dot, ".xhtm") == 0 || strcmp(dot, ".xhtml") == 0 || strcmp(dot, ".xht") == 0 ){
        buf = "application/xhtml+xml";
    } else if ( strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0 || strcmp(dot, ".shtml") == 0 || strcmp(dot, ".hts") == 0 ){
        buf = "text/html";

    /* Images */
    } else if ( strcmp( dot, ".gif" ) == 0 ){
        buf = "image/gif";
    } else if ( strcmp( dot, ".png" ) == 0 ){
        buf = "image/png";
    } else if ( strcmp( dot, ".bmp" ) == 0 ){
        buf = "application/x-MS-bmp";
    } else if ( strcmp( dot, ".jpg" ) == 0 || strcmp( dot, ".jpeg" ) == 0 || strcmp( dot, ".jpe" ) == 0 || strcmp( dot, ".jpz" ) == 0 ){
        buf = "image/jpeg";

    /* Audio & Video */
    } else if ( strcmp( dot, ".wav" ) == 0 ){
        buf = "audio/wav";
    } else if ( strcmp( dot, ".wma" ) == 0 ){
        buf = "audio/x-ms-wma";
    } else if ( strcmp( dot, ".wmv" ) == 0 ){
        buf = "audio/x-ms-wmv";
    } else if ( strcmp( dot, ".au" ) == 0 || strcmp( dot, ".snd" ) == 0 ){
        buf = "audio/basic";
    } else if ( strcmp( dot, ".midi" ) == 0 || strcmp( dot, ".mid" ) == 0 ){
        buf = "audio/midi";
    } else if ( strcmp( dot, ".mp3" ) == 0 || strcmp( dot, ".mp2" ) == 0 ){
        buf = "audio/x-mpeg";
    } else if ( strcmp( dot, ".rm" ) == 0  || strcmp( dot, ".rmvb" ) == 0 || strcmp( dot, ".rmm" ) == 0 ){
        buf = "audio/x-pn-realaudio";
    } else if ( strcmp( dot, ".avi" ) == 0 ){
        buf = "video/x-msvideo";
    } else if ( strcmp( dot, ".3gp" ) == 0 ){
        buf = "video/3gpp";
    } else if ( strcmp( dot, ".mov" ) == 0 ){
        buf = "video/quicktime";
    } else if ( strcmp( dot, ".wmx" ) == 0 ){
        buf = "video/x-ms-wmx";
    } else if ( strcmp( dot, ".asf" ) == 0  || strcmp( dot, ".asx" ) == 0 ){
        buf = "video/x-ms-asf";
    } else if ( strcmp( dot, ".mp4" ) == 0 || strcmp( dot, ".mpg4" ) == 0 ){
        buf = "video/mp4";
    } else if ( strcmp( dot, ".mpe" ) == 0  || strcmp( dot, ".mpeg" ) == 0 || strcmp( dot, ".mpg" ) == 0 || strcmp( dot, ".mpga" ) == 0 ){
        buf = "video/mpeg";

    /* Documents */
    } else if ( strcmp( dot, ".pdf" ) == 0 ){
        buf = "application/pdf";
    } else if ( strcmp( dot, ".rtf" ) == 0 ){
        buf = "application/rtf";
    } else if ( strcmp( dot, ".doc" ) == 0  || strcmp( dot, ".docx" ) == 0  || strcmp( dot, ".dot" ) == 0 ){
        buf = "application/msword";
    } else if ( strcmp( dot, ".xls" ) == 0  || strcmp( dot, ".xla" ) == 0 ){
        buf = "application/msexcel";
    } else if ( strcmp( dot, ".hlp" ) == 0  || strcmp( dot, ".chm" ) == 0 ){
        buf = "application/mshelp";
    } else if ( strcmp( dot, ".swf" ) == 0  || strcmp( dot, ".swfl" ) == 0 || strcmp( dot, ".cab" ) == 0 ){
        buf = "application/x-shockwave-flash";
    } else if ( strcmp( dot, ".ppt" ) == 0  || strcmp( dot, ".ppz" ) == 0 || strcmp( dot, ".pps" ) == 0 || strcmp( dot, ".pot" ) == 0 ){
        buf = "application/mspowerpoint";

    /* Binary & Packages */
    } else if ( strcmp( dot, ".zip" ) == 0 ){
        buf = "application/zip";
    } else if ( strcmp( dot, ".rar" ) == 0 ){
        buf = "application/x-rar-compressed";
    } else if ( strcmp( dot, ".gz" ) == 0 ){
        buf = "application/x-gzip";
    } else if ( strcmp( dot, ".jar" ) == 0 ){
        buf = "application/java-archive";
    } else if ( strcmp( dot, ".tgz" ) == 0  || strcmp( dot, ".tar" ) == 0 ){
        buf = "application/x-tar";
    } else {
        buf = "application/octet-stream";
    }
    return buf;
}

std::string getParam(std::string url,std::string paramName)
{
    std::string paramValue;
    char value[256]={0};
    paramName+="=";
    if(url.find(paramName) != std::string::npos)
    {
        const char *pStart = url.c_str();
        const char *pName = paramName.c_str();
        const char *pEnd=NULL;;
        pStart = strstr(pStart,pName);
        if(pStart != NULL)
        {
            pEnd = strstr(pStart,"&");

            if(pEnd != NULL)
            {
                pStart +=(paramName.size());
                if(pEnd > pStart)
                {
                    memcpy(value,pStart,(pEnd-pStart));
                    value[pEnd-pStart]='\0';
                    paramValue = value;
                }
            }
            else
            {
                paramValue = pStart+paramName.size();
            }
        }
    }
    return paramValue;
}

//文件加载功能
void webFileLoad(PHTTP_REQ_HANDLE pHandle)
{
//    int fd = -1;
//    struct stat st;
    evhttp_add_header(pHandle->req->output_headers, "Content-Type", getContentType(pHandle->filepath));
//    if (!((fd = open(pHandle->filepath, O_RDONLY|O_BINARY)) < 0)) {
//        if (!(fstat(fd, &st)<0)) {
//            evbuffer_add_file(pHandle->evbuf, fd, 0, st.st_size);
//        }
//    }

//    if (fd>=0)
//    {
//        close(fd);
//    }
    {   //用于自定义模式回复如cgi回复文本信息
        fileRead(pHandle->filepath, pHandle->bodybuff,BODYBUFF_MAX_LEN);
        evbuffer_add_printf(pHandle->evbuf, "%s", pHandle->bodybuff);
    }

    evhttp_send_reply(pHandle->req, HTTP_OK, "OK", pHandle->evbuf);
}

void redirect(PHTTP_REQ_HANDLE pHandle,const char *pUrl)
{
    evhttp_add_header(pHandle->req->output_headers, "Location", pUrl);
    evhttp_send_reply(pHandle->req, 301, "Moved Permanently", pHandle->evbuf);
}

void webRequestNoPermission(PHTTP_REQ_HANDLE pHandle)
{
    UNUSED(pHandle);
//    pHandle->evbuf = evbuffer_new();
//    // 返回给浏览器的信息
//    evhttp_add_header(pHandle->req->output_headers, "Server", "fasthttp");
//    evhttp_add_header(pHandle->req->output_headers, "Connection", "close");
//    redirect(pHandle,"noPermission.html");
//    evbuffer_free(pHandle->evbuf);
}
/*
void cgiEvent(PHTTP_REQ_HANDLE pHandle)
{
    Json::Value  root;
    evhttp_add_header(pHandle->req->output_headers, "Content-Type", "application/json");
    for (unsigned int i=0; i<__name2cb.size(); i++) {
        //printf("queryName:%s\n",__name2cb[i].queryName.c_str());
        if(pHandle->uri.find(__name2cb[i].queryName) != std::string::npos)
        {
            root["action"]=__name2cb[i].queryName;
            std::string pwd = getParam(pHandle->uri,"pwd");
            std::string randid = getParam(pHandle->uri,"randid");

            if(!pwd.empty()&&!randid.empty())
            {
                int key = stoi(randid);
                if(getPwd(pwd, key) == getDBPassWord(DBPWD))
                {
                    __name2cb[i].cb(pHandle,&root);
                    break;
                }
                printf("pwd:%s\n",getPwd(pwd, key).c_str());
            }

            root["return"] = false;
            root["msg"] = "pwd or randid err";

            break;
        }
    }
    evbuffer_add_printf(pHandle->evbuf, "%s", root.toStyledString().c_str());
    evhttp_send_reply(pHandle->req, HTTP_OK, "OK", pHandle->evbuf);
}
*/
void requestEvent(PHTTP_REQ_HANDLE pHandle)
{
    pHandle->evbuf = evbuffer_new();
    // 返回给浏览器的信息
    evhttp_add_header(pHandle->req->output_headers, "Server", "fasthttp");
    evhttp_add_header(pHandle->req->output_headers, "Connection", "close");
    std::string filedesc="";
    // 获取请求的服务器文件路径
    if(pHandle->uri=="/")
    {
        redirect(pHandle,"index.html");
    }else {
        sprintf(pHandle->filepath, "%s%s", DOCUMENT_ROOT, evhttp_uridecode(pHandle->uri.c_str(), 0, NULL));
        printf("pHandle->filepath:%s\n", pHandle->filepath);
        int ret = stat(pHandle->filepath, &pHandle->fileinfo);
        if (ret!=-1 && S_ISREG(pHandle->fileinfo.st_mode))
        {
            webFileLoad(pHandle);
        }else if(strstr(pHandle->filepath,"/cgi/")){
#ifdef PIC_ENCRYPT
            if(strstr(pHandle->filepath,"path=/opt/vehicle/vehicle_photo"))
            {
                string filepro=pHandle->filepath;
                int firloc=filepro.find("/opt/");
                std::string filepathcode= filepro.substr(firloc, filepro.size()) ;
                filedesc=filepathcode;
                filedesc.append(PIC_EPT);
                if((access(filedesc.c_str(),F_OK))==-1)
                    {
                        FILE *v_file = fopen(filedesc.c_str(), "w");
                        if (v_file == nullptr) {
                            return ;
                        }
                        fflush(v_file);
                        fclose(v_file);
                    }

                if(AesDecryptFile(filepathcode,filedesc))
                {

                    strcat(pHandle->filepath,"PWD");
                    pHandle->uri.append("PWD");
                }
            }
#endif
            if(pTaskCenter != NULL)
            {
                cgiEvent(pHandle);
            }
        }else{
            requestError(pHandle);
        }
    }

    evbuffer_free(pHandle->evbuf);
    if((!filedesc.empty()) || (""!=filedesc))
    {

        int flag = remove(filedesc.c_str());  /*remove()函数返回值为0或EPF(-1)*/

        if(0!=flag )
        {
            //DATA_PRINT(LEVEL_INFO, "文件不存在或删除失败 %s\n",filedesc.c_str());

        }

    }
    return ;
}

void getOpenAlgList(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = true;
    (*pRoot)["value"] = pTaskCenter->getOpenAlg();
    UNUSED(pHandle);
}

void getSessionWorkState(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = true;
    Json::Value retRoot = getWorkSessionStateJson();

	std::string beginDate, endDate, result;
	bool isOk = baseTool::checkLicense(result, beginDate, endDate);

    if(!isOk)
    {
	    Json::Value root;
	    Json::Value subroot;
	    std::string outStr = result + ", 有效期开始时间：" + beginDate + ", 有效期结束时间：" + endDate;
	    subroot["deviceState"] = "<p><font size='5' face='arial' color='red'>" + outStr + "</font></p>";
	    subroot["deviceTime"] = baseTool::getCurTime();
	    root.append(subroot);
	    (*pRoot)["mode"] = 2;
	    (*pRoot)["value"] = root;
    } else if(retRoot.size() > 0)
    {
        (*pRoot)["mode"] = 1;
        (*pRoot)["value"] = retRoot;
    }
    else
    {
        Json::Value root;
        Json::Value subroot;
        subroot["deviceState"] = getDeviceState();
        subroot["deviceTime"] = baseTool::getCurTime();
        root.append(subroot);
        (*pRoot)["mode"] = 2;
        (*pRoot)["value"] = root;
    }

    UNUSED(pHandle);
}

void getSlaveDeviceState(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{

    (*pRoot)["return"] = true;
    Json::Value retRoot = getDeviceHeartBeatJson();
    if(retRoot.size()>0)
    {
        (*pRoot)["mode"] = 1;
        (*pRoot)["value"] = retRoot;
    }
    else
    {
        Json::Value root;
        Json::Value subroot;
        subroot["slaveDeviceState"] = "无从机信息";
        subroot["slaveDeviceTime"] = baseTool::getCurTime();
        root.append(subroot);
        (*pRoot)["mode"] = 2;
        (*pRoot)["value"] = root;
    }

    UNUSED(pHandle);
}

void getAlgVector(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{

    (*pRoot)["return"] = true;
    (*pRoot)["value"] = pTaskCenter->getAlgVectorJson();

    UNUSED(pHandle);
}

void getAlgCheckConflict(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = true;
    (*pRoot)["value"] = pTaskCenter->getAlgCheckConflictJson();
    UNUSED(pHandle);
}
void getSoapRequestCount(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = true;
    (*pRoot)["value"] = queryRecordSoapTimes(5) ;//pTaskCenter->getAlgCheckConflictJson();

    UNUSED(pHandle);
}
void getLicenseDate(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
	printf("88888 i am getlicensedate !\n");

	std::string beginDate, endDate, result;
	bool isOk = baseTool::checkLicense(result, beginDate, endDate);

	(*pRoot)["return"] = true;
	(*pRoot)["isOk"] = isOk;
	(*pRoot)["result"] = result;
	(*pRoot)["beginDate"] = beginDate;
	(*pRoot)["endDate"] = endDate;
}

void getAlgClass(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string picType = getParam(pHandle->uri,"PicType");
    if(!picType.empty())
    {
        _c_algBaseClass *pAlgParam = pTaskCenter->loadAlgBaseClassByPicType((PicType)atoi(picType.c_str()));
        (*pRoot)["value"] = pAlgParam->getResultMemberListJson();
        delete pAlgParam;
        if((*pRoot)["value"].size()>0)
            (*pRoot)["return"] = true;
    }
    UNUSED(pHandle);
}

void clearSessionTransCenterData(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;

    if(pSessionTransCenter!=NULL)
    {
        std::string isOpen = getParam(pHandle->uri,"isOpen");
        if(!isOpen.empty())
        {
            if(isOpen == "true")
            {
                pSessionTransCenter->clearDataOpen();
            }else {
                pSessionTransCenter->clearDataClose();
            }
            (*pRoot)["return"] = true;
        }
    }
    UNUSED(pHandle);
}



void setAlgItem(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    std::string picType = getParam(pHandle->uri,"type");

    if(!picType.empty())
    {
        algItem webaAlgItem;

        webaAlgItem.code = getParam(pHandle->uri,"code");
        webaAlgItem.name = getParam(pHandle->uri,"name");
        webaAlgItem.isOpen = (bool)atoi(getParam(pHandle->uri,"isOpen").c_str());
 //       webaAlgItem.subAlgClass = (bool)atoi(getParam(pHandle->uri,"subAlgClass").c_str());
        webaAlgItem.needCheck = (bool)atoi(getParam(pHandle->uri,"needCheck").c_str());
        webaAlgItem.type =(PicType)atoi(picType.c_str());
        webaAlgItem.isTenYears = (bool)atoi(getParam(pHandle->uri,"isTenYears").c_str());
        webaAlgItem.isMust = (bool)atoi(getParam(pHandle->uri,"isMust").c_str());
        webaAlgItem.link = getParam(pHandle->uri,"link");
        pTaskCenter->getSubAlgClass(&webaAlgItem); //修正web上没有传参subAlgClass导致的逻辑错误
        pTaskCenter->changeAlgVectorByType(&webaAlgItem);
        pTaskCenter->saveConfig();
         (*pRoot)["return"] = true;
    }
}


void setAlgClass(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    std::string picType = getParam(pHandle->uri,"PicType");
    if(!picType.empty())
    {
        _c_algBaseClass *pAlgParam = pTaskCenter->loadAlgBaseClassByPicType((PicType)atoi(picType.c_str()));
        memberItem item;
        item.name = getParam(pHandle->uri,"name");

        printf("name:%s\n",item.name.c_str());
        item.desc = getParam(pHandle->uri,"desc");
        item.config.isOpen = (bool)atoi(getParam(pHandle->uri,"isOpen").c_str());
        item.config.descOpen = (bool)atoi(getParam(pHandle->uri,"descOpen").c_str());
        item.config.errLevel = (E_JG)atoi(getParam(pHandle->uri,"errLevel").c_str());
        std::string memberName = getParam(pHandle->uri,"memberName");
        if(!item.name.empty()&&!memberName.empty())
        {

            pAlgParam->setResultMember(memberName, &item);
            pAlgParam->saveResultConfig();
            (*pRoot)["return"] = true;
            delete pAlgParam;
            return;
        }
        delete pAlgParam;
    }
    (*pRoot)["return"] = false;
}

void setCurrencyConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    bool isChange = false;
    unsigned int HDZKS = 0;
    unsigned int fuJianMode = 0;
    unsigned int intSoapMax = 0;
    std::string cityShortName = getParam(pHandle->uri,"cityShortName");
    std::string isOpenCoreDump = getParam(pHandle->uri,"isOpenCoreDump");
    std::string isOpenFilterJianYanJiGou= getParam(pHandle->uri,"isFilterJYJG");
    std::string heDingZaiHeShu = getParam(pHandle->uri,"heDingZaiHeShu");
    std::string chaoShiShiJian = getParam(pHandle->uri,"chaoShiShiJian");
    std::string fuJianCheLiangMode = getParam(pHandle->uri,"fuJianCheLiangMode");
    std::string soapMaxReqTimes = getParam(pHandle->uri,"soapMaxReqTimes");

    if(!heDingZaiHeShu.empty())
    {
        HDZKS = (unsigned int)atoi(heDingZaiHeShu.c_str());
        pTaskCenter->setHeDingZaiKeShuConfig(HDZKS);
        isChange = true;
    }

    if(!fuJianCheLiangMode.empty())
    {
        fuJianMode = (unsigned int)atoi(fuJianCheLiangMode.c_str());
        if(fuJianMode == 0 ||fuJianMode == 1 ||fuJianMode == 2 )
        {
            pTaskCenter->setFuJianCheLiangMode(fuJianMode);
            isChange = true;
        }
    }
    if(!soapMaxReqTimes.empty() ){
        sscanf(soapMaxReqTimes.c_str() ,"%u",&intSoapMax );
        pTaskCenter->setsoapMaxReqTimes(intSoapMax);
        isChange = true ;
    }

    if(!cityShortName.empty())
    {
        pTaskCenter->setCityShortNameConfig(cityShortName);
        isChange = true;
    }
	
	if(!isOpenCoreDump.empty())
    {
        pTaskCenter->setOpenCoredumpConfig(isOpenCoreDump);
        isChange = true;
    }
    if( !isOpenFilterJianYanJiGou.empty())
    {
         pTaskCenter->setOpenFilterJianYanJiGou(isOpenFilterJianYanJiGou);
         isChange = true;
    }
    if(!chaoShiShiJian.empty())
    {
        unsigned int chaoshishijian = (unsigned int)atoi(chaoShiShiJian.c_str());
        pTaskCenter->setChaoShiShiJianConfig(chaoshishijian);
        isChange = true;
    }

    if(isChange)
    {
        pTaskCenter->saveConfig();
    }

    (*pRoot)["return"] = true;
    UNUSED(pHandle);
}

void addHmdConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string chePai = getParam(pHandle->uri,"chePai");
    printf("add hmd uri:%s\n", pHandle->uri.c_str());
    if(!chePai.empty())
    {
        pTaskCenter->addHeiMingDanByChePai(chePai);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}
void addCjhHmdConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string cheJiaHao = getParam(pHandle->uri,"cheJiaHao");
    printf("add cjhHmd uri:%s\n", pHandle->uri.c_str());
    if(!cheJiaHao.empty())
    {
        pTaskCenter->addCjhHeiMingDanByCheJiaHao(cheJiaHao);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }
    UNUSED(pHandle);
}
void addHttpBmdConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string IpAddr = getParam(pHandle->uri,"IpAddr");
    printf("add IpAddr uri:%s\n", pHandle->uri.c_str());
    if(!IpAddr.empty())
    {
        pTaskCenter->addHttpBaiMingDanByipaddr(IpAddr);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}
void setQdcsConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    std::map<std::string, std::string> qdcsMap;
    pConfigCenter->getStartUpParamNameList(qdcsMap);
    std::map<std::string, std::string>::iterator it;
    for (it = qdcsMap.begin(); it != qdcsMap.end(); it++)
    {
        it->second = getParam(pHandle->uri, it->first);
//        printf("name:%s val:%s\n", it->first.c_str(), it->second.c_str());
    }
    std::cout<<"===============########==========startTime:"<< qdcsMap["startTime"]  << "endTime:"<<qdcsMap["endTime"] <<std::endl ;
    qdcsMap["startTime"] = baseTool::formatingTime(qdcsMap["startTime"] ) ;
    qdcsMap["endTime"] = baseTool::formatingTime(qdcsMap["endTime"] );
    std::cout<<"===============########==========startTime:"<< qdcsMap["startTime"]  << "endTime:"<<qdcsMap["endTime"] <<std::endl ;
    pConfigCenter->updateStartUpParamConfig(qdcsMap);

    (*pRoot)["return"] = true;
    UNUSED(pHandle);
}

void setJqxConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    std::map<std::string, std::string> jqxMap;
    pConfigCenter->getJqxParamNameList(jqxMap);
    std::map<std::string, std::string>::iterator it;
    for (it = jqxMap.begin(); it != jqxMap.end(); it++)
    {
        it->second = getParam(pHandle->uri, it->first);
    }

    pConfigCenter->updateJqxParamConfig(jqxMap);

    (*pRoot)["return"] = true;
    UNUSED(pHandle);
}

void setAlgParam(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    if(pTaskCenter == NULL)
    {
        return;
    }

    std::string dataType = getParam(pHandle->uri,"fromType");
    if(!dataType.empty())
    {
        printf("fromType:%s\n",dataType.c_str());
        if(dataType.find("algItem")!= std::string::npos)
        {
            setAlgItem(pHandle, pRoot);
        }
        else if(dataType.find("algClass")!= std::string::npos)
        {
            setAlgClass(pHandle, pRoot);
        }
        else if(dataType.find("Currency")!= std::string::npos)
        {
            setCurrencyConfig(pHandle, pRoot);
        }
        else if(dataType.find("Jyjg")!= std::string::npos)
        {
            addJyjgConfig(pHandle, pRoot);
        }
        else if(dataType.find("Xrjyjg")!= std::string::npos)
        {
            addXrJyjgConfig(pHandle, pRoot);
        }
        else if(dataType.find("CjhHmd")!= std::string::npos)
        {
            addCjhHmdConfig(pHandle, pRoot);
        }
        else if(dataType.find("Hmd")!= std::string::npos)
        {
            addHmdConfig(pHandle, pRoot);
        }
        else if(dataType.find("HttpBmd")!= std::string::npos)
        {
            addHttpBmdConfig(pHandle, pRoot);
        }
        else if(dataType.find("Qdcs")!= std::string::npos)
        {
            setQdcsConfig(pHandle, pRoot);
        }
        else if(dataType.find("Jqx")!= std::string::npos)
        {
            setJqxConfig(pHandle, pRoot);
        }
        else if(dataType.find("VideoCheck")!= std::string::npos)
        {
            addVideoJyjgConfig(pHandle, pRoot);
        }
    }

    UNUSED(pHandle);
}

#define MaxBufSize 128
#define SUANFA_MMAPFILEPATH "/opt/vehicle/program/programPath/chejian_alg_redis.txt"
typedef struct _SUANFA_MMAPDATA {
    int num;   // 计数
    char redis_version[MaxBufSize];      //redis进程的版本
    char alg_version[MaxBufSize];       //算法版本
    char start_time[MaxBufSize];      // 启动时间
    char gpu_num[MaxBufSize];        //gpu数量
    char gpu_type[MaxBufSize];      //gpu类型  nvidia 和 cambricon
    char heartBeatTime[MaxBufSize];  //心跳(好像没用)
}SUANFA_MMAPDATA, *PSUANFA_MMAPDATA;
MmapReader<SUANFA_MMAPDATA> *_pMmapReader = NULL;
SUANFA_MMAPDATA _SUANFA_MMAPDATA;

void getCurrencyConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root;
    root["vesion"] = _version;
    root["heDingZaiHeShu"] = pTaskCenter->getHeDingZaiHeShu();
    root["cityShortName"] = pTaskCenter->getCityShortNmae();
    root["isOpenCoreDump"] = pTaskCenter->getOpenCoredump();
    root["isFilterJYJG"] = pTaskCenter->getOpenFilterJianYanJiGou();
    root["cityType"] = pTaskCenter->getCityType();
    root["chaoShiShiJian"] = pTaskCenter->getChaoShiShiJian();
    root["fuJianCheLiangMode"] = pTaskCenter->getFuJianCheLiangMode();
    root["soapMaxReqTimes"] = pTaskCenter->getsoapMaxReqTimes();

    if(_pMmapReader == NULL)
    {
        _pMmapReader = new MmapReader<SUANFA_MMAPDATA>();
        _pMmapReader->mmapOpen(SUANFA_MMAPFILEPATH);
        _SUANFA_MMAPDATA = _pMmapReader->getAll();
    }

    root["alg_redisVersion"] = _SUANFA_MMAPDATA.redis_version;
    root["alg_version"] = _SUANFA_MMAPDATA.alg_version;
    root["alg_gpuType"] = _SUANFA_MMAPDATA.gpu_type;
    root["alg_heartBeatTime"] = _SUANFA_MMAPDATA.heartBeatTime;
    root["alg_startTime"] = _SUANFA_MMAPDATA.start_time;




    (*pRoot)["value"] = root;
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void getSyxzConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root;
    (*pRoot)["value"] = pTaskCenter->getSYXZVectorJson();
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void deleteSyxzConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string syxz = getParam(pHandle->uri,"syxz");
    if(!syxz.empty())
    {
        pTaskCenter->deleteCheckShiYongXingZhiByKey(syxz);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void addSyzxConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string syxz = getParam(pHandle->uri,"syxz");
    if(!syxz.empty())
    {
        pTaskCenter->addCheckShiYongXingZhiByKey(syxz);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void getCllxConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root;
    (*pRoot)["value"] = pTaskCenter->getCLZLVectorJson();
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void deleteCllxConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string cllx = getParam(pHandle->uri,"cllx");
    if(!cllx.empty())
    {
        pTaskCenter->deleteCheckCheLiangZhongLeiByKey(cllx);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void addCllxConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string cllx = getParam(pHandle->uri,"cllx");
    if(!cllx.empty())
    {
        pTaskCenter->addCheckCheLiangZhongLeiByKey(cllx);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void getXiaoCheConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root;
    (*pRoot)["value"] = pTaskCenter->getSmallVehicleVectorJson();
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void deleteXiaoCheConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string cllx = getParam(pHandle->uri,"cllx");
    if(!cllx.empty())
    {
        pTaskCenter->deleteCheckSmallVehicleVectorByKey(cllx);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void addXiaoCheConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string cllx = getParam(pHandle->uri,"cllx");
    if(!cllx.empty())
    {
        pTaskCenter->addCheckSmallVehicleVectorByKey(cllx);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void getJylbConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root;
    (*pRoot)["value"] = pTaskCenter->getJYLBVectorJson();
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void deleteJylbConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string jylb = getParam(pHandle->uri,"jylb");
    if(!jylb.empty())
    {
        pTaskCenter->deleteCheckJianYanLeiBieByKey(jylb);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void addJylbConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string jylb = getParam(pHandle->uri,"jylb");
    if(!jylb.empty())
    {
        pTaskCenter->addCheckJianYanLeiBieByKey(jylb);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void getJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root;
    (*pRoot)["value"] = pTaskCenter->getJYJGVectorJson();
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void getVideoJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root;
    (*pRoot)["value"] = pConfigCenter->getVideoJyjgbhVectorJson();
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void deleteJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string bh = getParam(pHandle->uri,"bh");
    if(!bh.empty())
    {
        pTaskCenter->deleteCheckJianYanJiGouByKey(bh);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void deleteVideoJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string jyjgbh = getParam(pHandle->uri,"jyjgbh");
    printf("%s\n %s\n", __func__, jyjgbh.c_str());
    if(!jyjgbh.empty())
    {
        _c_jsonArrayBaseItem item("jyjgbh", jyjgbh);
        pConfigCenter->deleteVideoJyjgbhVectorByBaseItem(&item);
        pConfigCenter->videoJyjgbhSaveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void addJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string bh = getParam(pHandle->uri,"bh");
    std::string ip = getParam(pHandle->uri,"ip");
    if(!bh.empty()&&!ip.empty())
    {
        pTaskCenter->addCheckJianYanJiGouByKey(bh,ip);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void addVideoJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string jyjgbh = getParam(pHandle->uri,"jyjgbh");
    std::string portIp = getParam(pHandle->uri,"portIp");
    std::string tongXunFangShi = getParam(pHandle->uri,"tongXunFangShi");
    std::string xieYiLeiXing = getParam(pHandle->uri,"xieYiLeiXing");

    if(!jyjgbh.empty() && !portIp.empty() && !tongXunFangShi.empty() && !xieYiLeiXing.empty())
    {
        printf("%s %s %s %s %s\n", __func__, jyjgbh.c_str(), portIp.c_str(), tongXunFangShi.c_str(), xieYiLeiXing.c_str());
        _c_jsonArrayBaseItem *pJyjgbh = new _c_jsonArrayBaseItem("jyjgbh", jyjgbh);
        _c_jsonArrayBaseItem *pPortIp = new _c_jsonArrayBaseItem("portIp", portIp);
        _c_jsonArrayBaseItem *pTongXunFangShi = new _c_jsonArrayBaseItem("tongXunFangShi", tongXunFangShi);
        _c_jsonArrayBaseItem *pXieYiLeiXing = new _c_jsonArrayBaseItem("xieYiLeiXing", xieYiLeiXing);

        _c_jsonArrayBaseSet *pSet = new _c_jsonArrayBaseSet;
        pSet->addBaseItem(pJyjgbh);
        pSet->addBaseItem(pPortIp);
        pSet->addBaseItem(pTongXunFangShi);
        pSet->addBaseItem(pXieYiLeiXing);

        pConfigCenter->addVideoJyjgbhArraySet(pSet);
        pConfigCenter->videoJyjgbhSaveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void getXrJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root;
    (*pRoot)["value"] = pTaskCenter->getXinRenJYJGVectorJson();
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void deleteXrJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string bh = getParam(pHandle->uri,"bh");
    if(!bh.empty())
    {
        pTaskCenter->deleteCheckXinRenJianYanJiGouByKey(bh);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void addXrJyjgConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string bh = getParam(pHandle->uri,"bh");
    std::string ip = getParam(pHandle->uri,"ip");
    if(!bh.empty()&&!ip.empty())
    {
        pTaskCenter->addCheckXinRenJianYanJiGouByKey(bh,ip);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void getHmdConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root;
    (*pRoot)["value"] = pTaskCenter->getHMDVectorJson();
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void deleteHmdConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string chePai = getParam(pHandle->uri,"chePai");
    if(!chePai.empty())
    {
        pTaskCenter->deleteHeiMingDanByChePai(chePai);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void getCjhHmdConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root;
    (*pRoot)["value"] = pTaskCenter->getCjhHMDVectorJson();
    (*pRoot)["return"] = true;
    UNUSED(pHandle);
}
void deleteCjhHmdConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string cheJiaHao = getParam(pHandle->uri,"cheJiaHao");
    if(!cheJiaHao.empty())
    {
        pTaskCenter->deleteCjhHeiMingDanByCheJiaHao(cheJiaHao);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }
    UNUSED(pHandle);
}
void getHttpBmdConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    std::cout<<"getHttpBmdConfig"<<std::endl;
    Json::Value root;
    (*pRoot)["value"] = pTaskCenter->getHttpBMDVectorJson();
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void deleteHttpBmdConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = false;
    std::string IpAddr = getParam(pHandle->uri,"IpAddr");
    std::cout<<"httpBmdDelete"<<pHandle->uri<<std::endl;
    if(!IpAddr.empty())
    {
        pTaskCenter->deleteHttpBaiMingDanByIpAddr(IpAddr);
        pTaskCenter->saveConfig();
        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}

void getVehicleInfo(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    if(pSessionTransCenter != NULL)
    {
        std::string chePai = getParam(pHandle->uri,"chePai");
        std::string startTime = getParam(pHandle->uri,"startTime");
        std::string endTime = getParam(pHandle->uri,"endTime");
        (*pRoot)["order"] = getVehicleInfoOrderJson();
        (*pRoot)["value"] = getVehicleInfoVectorJson(pSessionTransCenter->getBaseTableName(),chePai,startTime,endTime);
        (*pRoot)["return"] = true;
    }else {
        (*pRoot)["return"] = false;
    }

    UNUSED(pHandle);
}

void getPhotoInfo(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    std::string vehicleId = getParam(pHandle->uri,"vehicleId");
    (*pRoot)["order"] = getPhotoInfoOrderJson();
    (*pRoot)["value"] = getPhotoInfoVectorJson(vehicleId);
    (*pRoot)["return"] = true;
    UNUSED(pHandle);
}

void queryDeviceState(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    //(*pRoot)["value"] = pTaskCenter->queryState();
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}


void startSlaveUpdate(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = true;

    std::string rootPath  = "/opt/vehicle/program/";
    std::string fileName = getParam(pHandle->uri,"fileName");
    std::string scpFile = rootPath+fileName;

    for (unsigned int i=0; i < g_slaveInfo.size(); i++) {
        std::string systemStr = "scp -p "+ g_slaveInfo[i].port +" "+scpFile+" "+g_slaveInfo[i].user+"@"+g_slaveInfo[i].ip+":/opt/vehicle/program";
        system(systemStr.c_str());
    }

    UNUSED(pHandle);
}

void selectUpdateTarGz(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = true;
    Json::Value root;

    std::string rootPath= "/opt/vehicle/program";
    struct dirent* ent = NULL;
    DIR *pDir;
    pDir=opendir(rootPath.c_str());
    while (NULL != (ent=readdir(pDir)))
    {
        if( ent->d_name[0]!='.')
        {
            std::string fileName = ent->d_name;
            if(fileName.find(".tar.gz")!= string::npos)
            {
                Json::Value subRoot;
                subRoot["name"] = fileName;
                root.append(subRoot);
            }
        }
    }
    closedir(pDir);

    (*pRoot)["value"] = root;

    UNUSED(pHandle);
}

void selectBackUp(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = true;
    Json::Value root;

    std::string rootPath= "/opt/vehicle/program";
    struct dirent* ent = NULL;
    DIR *pDir;
    pDir=opendir(rootPath.c_str());
    while (NULL != (ent=readdir(pDir)))
    {
        if( ent->d_name[0]!='.')
        {
            std::string fileName = ent->d_name;
            if(fileName.find("BackUp_")!= string::npos && fileName.find(".json")!= string::npos)
            {
                Json::Value subRoot;
                subRoot["name"] = fileName;
                root.append(subRoot);
            }
        }
    }
    closedir(pDir);

    (*pRoot)["value"] = root;

    UNUSED(pHandle);
}

void getSlaveInfo(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    (*pRoot)["return"] = true;
    Json::Value root;

    for (unsigned int i=0; i < g_slaveInfo.size(); i++) {
        Json::Value subRoot;
        subRoot["ip"] = g_slaveInfo[i].ip;
        subRoot["user"] = g_slaveInfo[i].user;
        subRoot["port"] = g_slaveInfo[i].port;
        root.append(subRoot);
    }

    (*pRoot)["value"] = root;

    UNUSED(pHandle);
}

void keepAlive(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    std::string alg_version = "alg_version";
    //LargeVehicleApi::algorithm_version(alg_version);

    (*pRoot)["return"] = true;
    (*pRoot)["version"] = _version;
    (*pRoot)["algVersion"] = alg_version;
    UNUSED(pHandle);
}

static inline void print_request_head_info(struct evkeyvalq *header)
{
    struct evkeyval *first_node = header->tqh_first;
    while (first_node) {
        printf("key:%s  value:%s \n", first_node->key, first_node->value);
        first_node = first_node->next.tqe_next;
    }
}

int getFileName(char *pInBuf,char *pOutBuf)
{
    int formHeadLen = 0;
    char *pStart = strstr(pInBuf,"filename=\"");
    char *pEnd;
    if(pStart != NULL)
    {
        pEnd = strstr(pStart+strlen("filename=\""),"\"");
        if(pEnd > pStart)
        {
            memcpy(pOutBuf,pStart+strlen("filename=\""),pEnd-pStart-strlen("filename=\""));
            pOutBuf[pEnd-pStart-strlen("filename=\"")] = '\0';
        }
    }

    char *pData = strstr(pInBuf,"\r\n\r\n");
    if(pData != NULL)
    {
        char head[1024]={0};
        formHeadLen =pData -pInBuf;
        memcpy(head,pInBuf,formHeadLen);
        head[formHeadLen] = '\0';
        printf("head:%s\n",head);
    }
    printf("formHeadLen:%d pOutBuf:[%s] \n",formHeadLen,pOutBuf);

    return formHeadLen+4;
}

void uploadRelaseFile(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    printf("uploadRelaseFile !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    (*pRoot)["return"] = false;

    const char *pEnd = "\r\n------WebKitFormBoundaryDoiavxAF30KP7MyZ--\r\n";

    struct evbuffer* buf = evhttp_request_get_input_buffer(pHandle->req);
    print_request_head_info(pHandle->req->output_headers);
    size_t post_size = evbuffer_get_length(buf);
    char webKitFormHead[2048]={0};
    char pathName[256]= {0};
    int formLen = 0;
    if(post_size > sizeof(webKitFormHead))
    {
        memcpy(webKitFormHead, evbuffer_pullup(buf, sizeof(webKitFormHead)), sizeof(webKitFormHead));
        formLen = getFileName(webKitFormHead,pathName);
    }

    if (post_size <= 0)
    {
        return;
    }
    else if(formLen > 0)
    {

        std::string filePath = "/opt/vehicle/program/";
        filePath += pathName;

        FILE *fp;
        if((fp=fopen(filePath.c_str(),"wb+")) == NULL)
        {
            printf("无法打开此文件:%s!\n",filePath.c_str());
            return;
        }

        fwrite(evbuffer_pullup(buf, -1) + formLen, post_size - formLen - strlen(pEnd), 1, fp);

        fclose(fp);



        (*pRoot)["return"] = true;
    }

    UNUSED(pHandle);
}


std::string getTarGzFileName(std::string TarGzFileName)
{
    std::string retFileName = "";
    char fileName[1024] = {0};
    const char *pTarGzFileName = TarGzFileName.c_str();
    const char *pEnd = strstr(pTarGzFileName,".tar.gz");
    if(pEnd != NULL&&(pEnd-pTarGzFileName)>0)
    {
        memcpy(fileName,pTarGzFileName,(pEnd-pTarGzFileName));
        fileName[pEnd-pTarGzFileName]='\0';
        retFileName = fileName;
    }
    return retFileName;
}

void backUp()
{
    std::string backUpConfigName = "/opt/vehicle/program/BackUp_"+_version+"_"+baseTool::getDangTianShiJian()+".json";
    std::string backUpConfigFolder = "/opt/vehicle/program/CheJianConfig_"+_version+"_"+baseTool::getDangTianShiJian();

    Json::Value  root;

    root["backUpConfigFolder"] = backUpConfigFolder;
    root["version"] = _version;

    baseTool::saveConfigByJson(backUpConfigName,root);

    baseTool::CheckDir(backUpConfigFolder);
    baseTool::copyFolder("/opt/vehicle/program/CheJianConfig",backUpConfigFolder);

}

void decodeTarGz(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    printf("decodeTarGz\n");
    (*pRoot)["return"] = false;
    std::string TarGzFileName = getParam(pHandle->uri,"fileName");
    if(!TarGzFileName.empty())
    {
        backUp();
        std::string fileName = getTarGzFileName(TarGzFileName);
        printf("fileName:%s\n",fileName.c_str());
        std::string systemStr = "tar -zxvf /opt/vehicle/program/"+TarGzFileName+" -C /opt/vehicle/program/";
        system(systemStr.c_str());

        systemStr = "rm /opt/vehicle/program/programPath -rf";
        system(systemStr.c_str());

        systemStr = "ln -s /opt/vehicle/program/"+fileName+" /opt/vehicle/program/programPath";
        system(systemStr.c_str());

        (*pRoot)["return"] = true;

        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        exit(1);
    }


    UNUSED(pHandle);
}


void getPassListInfo(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    std::vector<std::string> zplxVector={};

    std::string startTime = getParam(pHandle->uri,"startTime");
    std::string endTime = getParam(pHandle->uri,"endTime");

    pTaskCenter->getAlgVectorCategory(&zplxVector);
    (*pRoot)["order"] = getPassListInfoOrderJson();
    (*pRoot)["value"] = getPassListInfoVectorJson(zplxVector,startTime,endTime);
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void getPassInfo(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{

    std::string zplx = getParam(pHandle->uri,"zplx");
    std::string startTime = getParam(pHandle->uri,"startTime");
    std::string endTime = getParam(pHandle->uri,"endTime");
    (*pRoot)["order"] = getPassInfoOrderJson();
    (*pRoot)["value"] = getPassInfoVectorJson(zplx,startTime,endTime);
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}


std::string Encode(const unsigned char *Data, unsigned int DataByte)
{
    //编码表
    const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    //返回值
    string strEncode;
    unsigned char Tmp[4] = { 0 };
//    int LineLength = 0;
    for (int i = 0; i<(int)(DataByte / 3); i++) {
        Tmp[1] = *Data++;
        Tmp[2] = *Data++;
        Tmp[3] = *Data++;
        strEncode += EncodeTable[Tmp[1] >> 2];
        strEncode += EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
        strEncode += EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
        strEncode += EncodeTable[Tmp[3] & 0x3F];
//        if (LineLength += 4, LineLength == 76)
//        {
//            strEncode += "\r\n";
//            LineLength = 0;
//        }
    }
    //对剩余数据进行编码
    int Mod = DataByte % 3;
    if (Mod == 1) {
        Tmp[1] = *Data++;
        strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
        strEncode += EncodeTable[((Tmp[1] & 0x03) << 4)];
        strEncode += "==";
    } else if (Mod == 2) {
        Tmp[1] = *Data++;
        Tmp[2] = *Data++;
        strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
        strEncode += EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
        strEncode += EncodeTable[((Tmp[2] & 0x0F) << 2)];
        strEncode += "=";
    }

    return strEncode;
}

int readFileByFileName(const char *pFileName,char *pBuf,int maxBufLen)
{
    FILE *fp = std::fopen(pFileName, "rb");
    if (!fp) {
        printf("fopen failure! %s\n",pFileName);
        return -1;
    }

    std::fseek(fp, 0, SEEK_END);
    long length = std::ftell(fp);
    std::fseek(fp, 0, SEEK_SET);

    if(length > maxBufLen)
    {
        return -1;
    }

    long ret = std::fread(pBuf, 1, maxBufLen, fp);
    if (ret != length) {
        printf("fread() failed! \n");
        std::fclose(fp);
        return -1;
    }
    std::fclose(fp);
    return length;
}


std::string getBase64PicByFileName(const char *pFileName)
{

    std::string photoData;
    unsigned char *Data = (unsigned char *)malloc(MAX_PIC_LEN);

    int length = readFileByFileName(pFileName,(char *)Data,MAX_PIC_LEN);
    if(length >0)
    {
       photoData = Encode(Data, length);
       free(Data);
       return photoData;
    }

    free(Data);
    return "0";
}



std::string loadBase64Image(std::string path)
{
    std::string base64Image="data:image/jpeg;base64,"+getBase64PicByFileName(path.c_str());
    return base64Image;
}

void getPhotoImage(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{

    std::string path = getParam(pHandle->uri,"path");
    (*pRoot)["value"] = loadBase64Image(path);
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void getPassInfoDetails(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    std::string zplx = getParam(pHandle->uri,"zplx");
    std::string reason = getParam(pHandle->uri,"reason");
    std::string startTime = getParam(pHandle->uri,"startTime");
    std::string endTime = getParam(pHandle->uri,"endTime");

    (*pRoot)["order"] = getPhotoInfoOrderJson();
    (*pRoot)["value"] = getPhotoInfoVectorJsonByReason(zplx,reason,startTime,endTime);
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void login(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    std::string pwd = getParam(pHandle->uri,"pwd");
    std::string randid = getParam(pHandle->uri,"randid");
    if(!pwd.empty()&&!randid.empty())
    {
        int key = stoi(randid);
        //if(getPwd(pwd, key) == getDBPassWord(DBPWD))
        {
             (*pRoot)["return"] = true;
             return;
        }
         printf("pwd:%s\n",getPwd(pwd, key).c_str());
    }

    (*pRoot)["return"] = false;
    (*pRoot)["msg"] = "pwd or randid err";

    UNUSED(pHandle);

    UNUSED(pHandle);
}

void chaYanYuanRegister(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    _c_chaYanYuan *pChaYanYuan = new _c_chaYanYuan();
    pChaYanYuan->sheBeiId = getParam(pHandle->uri,"sheBeiId");
    pChaYanYuan->chanYanQuXuHao = getParam(pHandle->uri,"chanYanQuXuHao");
    pChaYanYuan->xingMing = getParam(pHandle->uri,"xingMing");
    pChaYanYuan->shenFenZheng = getParam(pHandle->uri,"shenFenZheng");

    if(!pChaYanYuan->sheBeiId.empty()&&!pChaYanYuan->chanYanQuXuHao.empty()&&!pChaYanYuan->xingMing.empty()&&!pChaYanYuan->shenFenZheng.empty())
    {
        pChaYanYuan->dbWork();
        (*pRoot)["return"] = true;
    }else {
        delete pChaYanYuan;
        (*pRoot)["return"] = false;
    }

    UNUSED(pHandle);
}

void queryTouPingMsgBySheBeiId(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    std::string sheBeiId = getParam(pHandle->uri,"sheBeiId");

    (*pRoot)["value"] = queryJiNanTouPingMsgBySheBeiId(sheBeiId);
    //(*pRoot)["algVector"] = pTaskCenter->getAlgVectorJson();

    if((*pRoot)["value"].size() > 0)
    {
        (*pRoot)["return"] = true;
    }
    else
    {
         (*pRoot)["return"] = false;
    }


    UNUSED(pHandle);
}

void processPhotodes(Json::Value &root, _c_session *pVehicle)
{
    if (!root["photodes"].empty())
    {
        for(unsigned int i=0;i < root["photodes"].size();i++)
        {
            _c_photo *pPhoto = new _c_photo();
            Json::Value subRoot = root["photodes"][i];

            if (!subRoot["zpzl"].empty())
            {
                std::string str = subRoot["zpzl"].asString();
                if (str.length() > 0)
                    pPhoto->algCode = str;
                else
                    pPhoto->algCode = "无数据";
            }

            if (!subRoot["zpurl"].empty())
            {
                std::string str = subRoot["zpurl"].asString();
                if (str.length() > 0)
                {
                    pPhoto->photoUrl = str;
                }
                else
                {
                    pPhoto->photoUrl = "无数据";
                }
            }
//            printf("%s code:%s url:%s\n", __func__, pPhoto->algCode.c_str(), pPhoto->photoUrl.c_str());

            if (root["type"].asString() == "chejian")
            {
                _c_vehicle *pChejianV = dynamic_cast<_c_vehicle *>(pVehicle);
                pChejianV->zhaoPianClassVector.push_back(pPhoto);
            }
            else if (root["type"].asString() == "chayan")
            {
                _c_chaYanVehicle *pChanYanV = dynamic_cast<_c_chaYanVehicle *>(pVehicle);
                pChanYanV->zhaoPianClassVector.push_back(pPhoto);
            }
        }
    }
}

void processJQXInfo(Json::Value &root, _c_session *pVehicle)
{
    _c_jiaoQiangXianJkReturnInfo *pJqxInfo = new _c_jiaoQiangXianJkReturnInfo();

    if (!root["jiaoQiangXian_info"].empty())
    {
        Json::Value subRoot = root["jiaoQiangXian_info"];
        pJqxInfo->loadJQXJson(subRoot, pVehicle);
    }
    else
    {
        objectMember *pObject = baseTool::getObjectItemByName(&pJqxInfo->memberVector, "isGetData");
        *pObject->value = "false";
    }

    if (root["type"].asString() == "chejian")
    {
        _c_vehicle *pChejianV = dynamic_cast<_c_vehicle *>(pVehicle);
        pJqxInfo->cheLiangUid = pVehicle->uuid;
        pChejianV->wangLuoJieKouReturnVector.push_back(pJqxInfo);
    }
}

void processTestCase(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    char bodybuff[BODYBUFF_MAX_LEN];
    struct evbuffer* evbuf = evhttp_request_get_input_buffer(pHandle->req);
    size_t len = evbuffer_get_length(evbuf);

    if (len <= 0)
    {
//        printf("%s no body!\n", __func__);
        (*pRoot)["msg"] = "no body";
        (*pRoot)["return"] = false;
        return;
    }
    else
    {
        size_t copy_len = len > BODYBUFF_MAX_LEN ? BODYBUFF_MAX_LEN : len;
        if(evbuffer_copyout(evbuf, bodybuff, copy_len) != -1)
        {
            bodybuff[len] = '\0';
        }
    }

    Json::Value  root;
    Json::Reader reader;
    _c_session *pVehicle = NULL;
    if (reader.parse(bodybuff, root, false))
    {
        if (!root["type"].empty())
        {
            if (root["type"].asString() == "chejian")
            {
                _c_cheJianSessionService *cheJianCenter = static_cast<_c_cheJianSessionService *>(pSessionTransCenter);
//                pVehicle = new _c_vehicle();
                pVehicle = cheJianCenter->loadVehicle();
            }
            else if (root["type"].asString() == "chayan")
            {
                _c_chaYanSessionService *chaYanCenter = static_cast<_c_chaYanSessionService *>(pSessionTransCenter);
//                pVehicle = new _c_chaYanVehicle();
                pVehicle = chaYanCenter->loadChaYanVehicle();
            }
            pVehicle->analyseJson(root);
            if(0){
                std::cout<< "####################不要删除此处用做桩测试########webserver####"<<std::endl;
                if( !test_soapReqRecord_isOK() ){
                    return  ;
                }
            }
            pVehicle->loadUuid();
        }
        else
        {
//            printf("%s %d type is empty!\n", __func__, __LINE__);
            (*pRoot)["msg"] = "type is empty";
            (*pRoot)["return"] = false;
            return;
        }
    }
    else
    {
//        printf("%s %d json error!\n", __func__, __LINE__);
        (*pRoot)["msg"] = "json error";
        (*pRoot)["return"] = false;
        return;
    }

    processPhotodes(root, pVehicle);

    if (!root["isTestWangLuoJQX"].empty())
    {
        if (root["isTestWangLuoJQX"].asInt() == 1)
            processJQXInfo(root, pVehicle);
    }

    if (pVehicle != NULL)
        pSessionTransCenter->pushQueue(pVehicle);

    (*pRoot)["return"] = true;
}

void GetQdcsConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root = pConfigCenter->getStartUpParamJson();

    (*pRoot)["value"] = root;
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void restartApp(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    printf("%s %d\n", __func__, __LINE__);
    (*pRoot)["return"] = true;

    exit(1);
    UNUSED(pHandle);
}

void GetJqxConfig(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    Json::Value root = pConfigCenter->getJqxParamJson();

    (*pRoot)["value"] = root;
    (*pRoot)["return"] = true;

    UNUSED(pHandle);
}

void videoJyjgLocalSync(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    printf("%s %d\n", __func__, __LINE__);
    std::string portIp = "127.0.0.1:10001";

    std::string uri = "";
    uri += "http://";
    uri += portIp;
    uri += "/videoJyjgLocalSync";

    HttpClient clientGet;
    clientGet.set_retries_timeout(1, 5);

    if (!clientGet.init_data(uri.c_str(), REQUEST_GET_FLAG, NULL, NULL))
    {
        printf("videoJyjgLocalSync uri init error %s.\n",uri.c_str());
    }
    clientGet.startHttpClient();

    if (clientGet.d_success_flag)
        (*pRoot)["return"] = true;
    else
        (*pRoot)["return"] = false;

    UNUSED(pHandle);
}
void GetTimeOfDay(PHTTP_REQ_HANDLE pHandle, Json::Value *pRoot)
{
    timeval tval;
    gettimeofday( &tval , NULL );
    printf("sec:%d ,usec:%d \n",tval.tv_sec ,tval.tv_usec );
    Json::Value ti;
    ti["sec"] = (unsigned int )tval.tv_sec ;
    ti["usec"] =(unsigned int )tval.tv_usec ;
    (*pRoot)["value"]= ti ;
    (*pRoot)["return"] =true ;
}

void initWebName2cb()
{
	setWebNameCb("Login",&login);

	setWebNameCb("GetLicenseCheckResult",&getLicenseDate);
    setWebNameCb("GetSoapRequestCount",&getSoapRequestCount);
    setWebNameCb("GetAlgCheckConflict",&getAlgCheckConflict);
    setWebNameCb("GetAlgVector",&getAlgVector);
    setWebNameCb("GetAlgClass",&getAlgClass);
    setWebNameCb("SetAlgParam",&setAlgParam);
    setWebNameCb("GetOpenAlgList",&getOpenAlgList);
    setWebNameCb("GetSessionWorkState",&getSessionWorkState);
    setWebNameCb("GetSlaveDeviceState",&getSlaveDeviceState);
    setWebNameCb("ClearSoapData",&clearSessionTransCenterData);

    setWebNameCb("GetCurrencyConfig",&getCurrencyConfig);
    setWebNameCb("SetCurrencyConfig",&setCurrencyConfig);

    setWebNameCb("GetSyxzConfig",&getSyxzConfig);
    setWebNameCb("DeleteSyxzConfig",&deleteSyxzConfig);
    setWebNameCb("AddSyxzConfig",&addSyzxConfig);

    setWebNameCb("GetCllxConfig",&getCllxConfig);
    setWebNameCb("DeleteCllxConfig",&deleteCllxConfig);
    setWebNameCb("AddCllxConfig",&addCllxConfig);

    setWebNameCb("GetXiaoCheConfig",&getXiaoCheConfig);
    setWebNameCb("DeleteXiaoCheConfig",&deleteXiaoCheConfig);
    setWebNameCb("AddXiaoCheConfig",&addXiaoCheConfig);

    setWebNameCb("GetJylbConfig",&getJylbConfig);
    setWebNameCb("DeleteJylbConfig",&deleteJylbConfig);
    setWebNameCb("AddJylbConfig",&addJylbConfig);

    setWebNameCb("GetJyjgConfig",&getJyjgConfig);
    setWebNameCb("DeleteJyjgConfig",&deleteJyjgConfig);
    setWebNameCb("AddJyjgConfig",&addJyjgConfig);

    setWebNameCb("GetXrJyjgConfig",&getXrJyjgConfig);
    setWebNameCb("DeleteXrJyjgConfig",&deleteXrJyjgConfig);
    setWebNameCb("AddXrJyjgConfig",&addXrJyjgConfig);

    setWebNameCb("GetHmdConfig",&getHmdConfig);
    setWebNameCb("DeleteHmdConfig",&deleteHmdConfig);
    setWebNameCb("AddHmdConfig",&addHmdConfig);

    setWebNameCb("GetCjhHmdConfig",&getCjhHmdConfig);
    setWebNameCb("DeleteCjhHmdConfig",&deleteCjhHmdConfig);
    setWebNameCb("AddCjhHmdConfig",&addCjhHmdConfig);
    setWebNameCb("GetHttpBmdConfig",&getHttpBmdConfig);
    setWebNameCb("httpBmdDelete",&deleteHttpBmdConfig);
    setWebNameCb("AddHttpBmdConfig",&addHttpBmdConfig);

    setWebNameCb("GetVehicleInfo",&getVehicleInfo);
    setWebNameCb("GetPhotoInfo",&getPhotoInfo);

    setWebNameCb("GetPassListInfo",&getPassListInfo);
    setWebNameCb("GetPassInfo",&getPassInfo);
    setWebNameCb("GetPhotoImage",&getPhotoImage);
    setWebNameCb("GetPassErrDetails",&getPassInfoDetails);


    setWebNameCb("SelectUpdateTarGz",&selectUpdateTarGz);
    setWebNameCb("SelectBackUp",&selectBackUp);
    setWebNameCb("GetSlaveInfo",&getSlaveInfo);
    setWebNameCb("KeepAlive",&keepAlive);
    setWebNameCb("UploadRelaseFile",&uploadRelaseFile);
    setWebNameCb("DecodeTarGz",&decodeTarGz);


    setWebNameCb("ChaYanYuanRegister",&chaYanYuanRegister);
    setWebNameCb("QueryTouPingMsgBySheBeiId",&queryTouPingMsgBySheBeiId);

    setWebNameCb("processTestCase",&processTestCase);

    setWebNameCb("GetQdcsConfig",&GetQdcsConfig);
    setWebNameCb("SetQdcsConfig",&setQdcsConfig);

    setWebNameCb("restartApp",&restartApp);

    setWebNameCb("GetJqxConfig",&GetJqxConfig);
    setWebNameCb("SetJqxConfig",&setJqxConfig);

    setWebNameCb("GetVideoJyjgConfig",&getVideoJyjgConfig);
    setWebNameCb("DeleteVideoJyjgConfig",&deleteVideoJyjgConfig);
    setWebNameCb("AddVideoJyjgConfig",&addVideoJyjgConfig);

    setWebNameCb("videoJyjgLocalSync",&videoJyjgLocalSync);

    setWebNameCb("GetTimeOfDay",&GetTimeOfDay);

	/*
    setWebNameCb("QueryDeviceState",&queryDeviceState);

    setWebNameCb("StartSlaveUpdate",&startSlaveUpdate);
	*/
}

int syncSystemTime(std::string portIp )
{
    int ret = -1 ;
    std::string uri ="http://" +portIp+"/cgi/GetTimeOfDay";
    uri += "randid=140&pwd=ks3jgzg3?;8=";
    HttpClient clientGet;
    clientGet.m_request_flag = REQUEST_GET_FLAG ;
    clientGet.m_request_text_type = RESPONSE_JSON ;
    if (!clientGet.init_data(uri.c_str(), REQUEST_GET_FLAG, NULL, NULL))
    {
        printf("/cgi/GetTimeOfDay uri init error %s.\n",uri.c_str());
    }
    clientGet.startHttpClient();
    if (clientGet.d_success_flag)
    {
        std::cout << clientGet.ResponseStringData <<  std::endl;
        Json::Value tidata;
        Json::Reader rd;
        rd.parse(clientGet.ResponseStringData ,tidata) ;
       if ( tidata["return"].asBool() ){
           timeval tival;
           tival.tv_sec = (long)( tidata["value"]["sec"].asUInt() );
           tival.tv_usec = (long)( tidata["value"]["usec"].asUInt() );
           timeval tivallocal;
           gettimeofday(&tivallocal ,NULL);

           //差了3ms (内网时间延迟在 1ms 左右)以上就去同步,避免自己和自己同步导致本地时间精度越来越差
           //abs(tival.tv_sec - tivallocal.tv_sec) > 2
           double m =  tival.tv_sec + tival.tv_usec*0.000001;
           double n =  tivallocal.tv_sec + tivallocal.tv_usec*0.000001;

           //if(  (tival.tv_sec！= tivallocal.tv_sec) ||( tivallocal.tv_usec - 3000> tival.tv_usec) )
           printf("时间比对: m:%lf n:%lf ,fabs(n-m):%lf  \n", m ,n, fabs(n-m) );
           if( fabs(n-m) > 0.03)
           {
               if(tival.tv_sec > 1597202318 )//2020.8.12 11:25
               {
                  ret = settimeofday(&tival ,NULL);
                  printf("-------------同步成功------------\n") ;
               }else{
                   ret = -3 ;
               }
           }else{
               ret = 1 ;
           }
       }
    }else{
        ret = -2 ;
    }
    return ret ;
}
void loopSyncSystemTimeFromMaster(std::string ipPort)
{
    int internal = 30 ;
    std::cout<<  "-sync time from "<< ipPort << "  internal is: "<< internal<<" seconds------------------" <<std::endl;
    while( true ){
        syncSystemTime(ipPort ) ;
        //std::this_thread::sleep_for(std::chrono::minutes(5));
        std::this_thread::sleep_for(std::chrono::seconds(internal));
    }
}
void startSyncTime(std::string ip, unsigned int port)
{
    std::string ipPort = ip ;
    char number[20] = {0} ;
    sprintf( number, "%u", port) ;
    ipPort.append(":");
    ipPort.append(number);
    std::thread  *_psynctime = new std::thread(loopSyncSystemTimeFromMaster,ipPort)    ;
}
