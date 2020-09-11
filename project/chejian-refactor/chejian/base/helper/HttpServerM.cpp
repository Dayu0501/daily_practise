#include "HttpServerM.h"
#include <event.h>
#include <evhttp.h>
#include <event2/thread.h>
#include "event2/keyvalq_struct.h"
#include <cstring>
#include "event2/buffer_compat.h"
#include <iostream>
#ifdef __linux
#include <unistd.h>
#endif
#include <memory>
#include <stdlib.h>
#include <fcntl.h>
#include <iostream>
#include "HelperFile.h"
#include "HelperString.h"

std::map<std::string,std::string> gmime = { {".323","text/h323"}, {".aac","audio/aac"}, {".abw","application/abiword"}, {".acx","application/internet-property-stream"}, {".ai","application/illustrator"}, {".aif","audio/aiff"}, {".aifc","audio/aiff"}, {".aiff","audio/aiff"}, {".asf","video/x-ms-asf"}, {".asp","application/x-asp"}, {".asr","video/x-ms-asf"}, {".asx","video/x-ms-asf"}, {".au","audio/basic"}, {".avi","video/avi"}, {".axs","application/olescript"}, {".bas","text/plain"}, {".bin","application/octet-stream"}, {".bmp","image/bmp"}, {".bz2","application/x-bzip2"}, {".c","text/x-csrc"}, {".c++","text/x-c++src"}, {".cab","application/vnd.ms-cab-compressed"}, {".cat","application/vnd.ms-pkiseccat"}, {".cct","application/x-director"}, {".cdf","application/cdf"}, {".cer","application/x-x509-ca-cert"}, {".cfc","application/x-cfm"}, {".cfm","application/x-cfm"}, {".class","application/x-java"}, {".clp","application/x-msclip"}, {".cmx","image/x-cmx"}, {".cod","image/cis-cod"}, {".cp","text/x-c++src"}, {".cpio","application/x-cpio"}, {".cpp","text/x-c++src"}, {".crd","application/x-mscardfile"}, {".crt","application/x-x509-ca-cert"}, {".crl","application/pkix-crl"}, {".crt","application/x-x509-ca-cert"}, {".csh","application/x-csh"}, {".css","text/css"}, {".cst","application/x-director"}, {".csv","text/csv"}, {".cxt","application/x-director"}, {".dcr","application/x-director"}, {".der","application/x-x509-ca-cert"}, {".dib","image/bmp"}, {".diff","text/x-patch"}, {".dir","application/x-director"}, {".dll","application/x-msdownload"}, {".dms","application/octet-stream"}, {".doc","application/vnd.ms-word"}, {".docm","application/vnd.ms-word.document.macroEnabled.12"}, {".docx","application/vnd.openxmlformats-officedocument.wordprocessingml.document"}, {".dot","application/msword"}, {".dotm","application/vnd.ms-word.template.macroEnabled.12"}, {".dotx","application/vnd.openxmlformats-officedocument.wordprocessingml.template"}, {".dta","application/x-stata"}, {".dv","video/x-dv"}, {".dvi","application/x-dvi"}, {".dwg","image/x-dwg"}, {".dxf","application/x-autocad"}, {".dxr","application/x-director"}, {".elc","application/x-elc"}, {".eml","message/rfc822"}, {".enl","application/x-endnote-library"}, {".enz","application/x-endnote-library"}, {".eps","application/postscript"}, {".etx","text/x-setext"}, {".evy","application/envoy"}, {".exe","application/x-msdos-program"}, {".fif","application/fractals"}, {".flr","x-world/x-vrml"}, {".fm","application/vnd.framemaker"}, {".fqd","application/x-director"}, {".gif","image/gif"}, {".gtar","application/tar"}, {".gz","application/gzip"}, {".h","text/x-chdr"}, {".hdf","application/x-hdf"}, {".hlp","application/winhlp"}, {".hqx","application/binhex"}, {".hta","application/hta"}, {".htc","text/x-component"}, {".htm","text/html"}, {".html","text/html"}, {".htt","text/webviewhtml"}, {".ico","image/x-ico"}, {".ics","text/calendar"}, {".ief","image/ief"}, {".iii","application/x-iphone"}, {".indd","application/x-indesign"}, {".ins","application/x-internet-signup"}, {".isp","application/x-internet-signup"}, {".jad","text/vnd.sun.j2me.app-descriptor"}, {".jar","application/java-archive"}, {".java","text/x-java"}, {".jfif","image/jpeg"}, {".jpe","image/jpeg"}, {".jpeg","image/jpeg"}, {".jpg","image/jpeg"}, {".js","text/javascript"}, {".kml","application/vnd.google-earth.kml+xml"}, {".kmz","application/vnd.google-earth.kmz"}, {".latex","application/x-latex"}, {".lha","application/x-lha"}, {".lib","application/x-endnote-library"}, {".llb","application/x-labview"}, {".log","text/x-log"}, {".lsf","video/x-la-asf"}, {".lsx","video/x-la-asf"}, {".lvx","application/x-labview-exec"}, {".lzh","application/x-lha"}, {".m","text/x-objcsrc"}, {".m1v","video/mpeg"}, {".m2v","video/mpeg"}, {".m3u","audio/x-mpegurl"}, {".m4a","audio/m4a"}, {".m4v","video/mp4"}, {".ma","application/mathematica"}, {".mail","message/rfc822"}, {".man","application/x-troff-man"}, {".mcd","application/x-mathcad"}, {".mdb","application/vnd.ms-access"}, {".me","application/x-troff-me"}, {".mfp","application/x-shockwave-flash"}, {".mht","message/rfc822"}, {".mhtml","message/rfc822"}, {".mid","audio/x-midi"}, {".midi","audio/x-midi"}, {".mif","application/vnd.framemaker"}, {".mny","application/x-msmoney"}, {".mov","video/quicktime"}, {".mp2","video/mpeg"}, {".mp3","audio/mpeg"}, {".mpa","video/mpeg"}, {".mpe","video/mpeg"}, {".mpeg","video/mpeg"}, {".mpg","video/mpeg"}, {".mpp","application/vnd.ms-project"}, {".mpv2","video/mpeg"}, {".mqv","video/quicktime"}, {".ms","application/x-troff-ms"}, {".mvb","application/x-msmediaview"}, {".mws","application/x-maple"}, {".nb","application/mathematica"}, {".nws","message/rfc822"}, {".oda","application/oda"}, {".odf","application/vnd.oasis.opendocument.formula"}, {".odg","application/vnd.oasis.opendocument.graphics"}, {".odp","application/vnd.oasis.opendocument.presentation"}, {".ods","application/vnd.oasis.opendocument.spreadsheet"}, {".odt","application/vnd.oasis.opendocument.text"}, {".ogg","application/ogg"}, {".one","application/msonenote"}, {".p12","application/x-x509-ca-cert"}, {".patch","text/x-patch"}, {".pbm","image/x-portable-bitmap"}, {".pcd","image/x-photo-cd"}, {".pct","image/x-pict"}, {".pdf","application/pdf"}, {".pfx","application/x-pkcs12"}, {".pgm","image/x-portable-graymap"}, {".php","application/x-php"}, {".pic","image/x-pict"}, {".pict","image/x-pict"}, {".pjpeg","image/jpeg"}, {".pl","application/x-perl"}, {".pls","audio/x-mpegurl"}, {".pko","application/ynd.ms-pkipko"}, {".pm","application/x-perl"}, {".pmc","application/x-perfmon"}, {".png","image/png"}, {".pnm","image/x-portable-anymap"}, {".pod","text/x-pod"}, {".potm","application/vnd.ms-powerpoint.template.macroEnabled.12"}, {".potx","application/vnd.openxmlformats-officedocument.presentationml.template"}, {".ppam","application/vnd.ms-powerpoint.addin.macroEnabled.12"}, {".ppm","image/x-portable-pixmap"}, {".pps","application/vnd.ms-powerpoint"}, {".ppsm","application/vnd.ms-powerpoint.slideshow.macroEnabled.12"}, {".ppsx","application/vnd.openxmlformats-officedocument.presentationml.slideshow"}, {".ppt","application/vnd.ms-powerpoint"}, {".pptm","application/vnd.ms-powerpoint.presentation.macroEnabled.12"}, {".pptx","application/vnd.openxmlformats-officedocument.presentationml.presentation"}, {".prf","application/pics-rules"}, {".ps","application/postscript"}, {".psd","application/photoshop"}, {".pub","application/vnd.ms-publisher"}, {".py","text/x-python"}, {".qt","video/quicktime"}, {".ra","audio/vnd.rn-realaudio"}, {".ram","audio/vnd.rn-realaudio"}, {".rar","application/rar"}, {".ras","image/x-cmu-raster"}, {".rgb","image/x-rgb"}, {".rm","application/vnd.rn-realmedia"}, {".rmi","audio/mid"}, {".roff","application/x-troff"}, {".rpm","audio/vnd.rn-realaudio"}, {".rtf","application/rtf"}, {".rtx","application/rtf"}, {".rv","video/vnd.rn-realvideo"}, {".sas","application/sas"}, {".sav","application/spss"}, {".scd","application/x-msschedule"}, {".scm","text/x-script.scheme"}, {".sct","text/scriptlet"}, {".sd2","application/spss"}, {".sea","application/x-sea"}, {".sh","application/x-sh"}, {".shar","application/x-shar"}, {".shtml","text/html"}, {".sit","application/stuffit"}, {".smil","application/smil"}, {".snd","audio/basic"}, {".spl","application/x-shockwave-flash"}, {".spo","application/spss"}, {".sql","text/x-sql"}, {".src","application/x-wais-source"}, {".sst","application/vnd.ms-pkicertstore"}, {".stl","application/vnd.ms-pkistl"}, {".stm","text/html"}, {".swa","application/x-director"}, {".swf","application/x-shockwave-flash"}, {".sxw","application/vnd.sun.xml.writer"}, {".t","application/x-troff"}, {".tar","application/tar"}, {".tcl","application/x-tcl"}, {".tex","application/x-tex"}, {".tga","image/x-targa"}, {".tgz","application/gzip"}, {".tif","image/tiff"}, {".tiff","image/tiff"}, {".tnef","application/ms-tnef"}, {".tr","application/x-troff"}, {".trm","application/x-msterminal"}, {".tsv","text/tsv"}, {".twb","application/twb"}, {".twbx","application/twb"}, {".txt","text/plain"}, {".uls","text/iuls"}, {".ustar","application/x-ustar"}, {".vcf","text/x-vcard"}, {".vrml","x-world/x-vrml"}, {".vsd","application/vnd.visio"}, {".w3d","application/x-director"}, {".war","application/x-webarchive"}, {".wav","audio/wav"}, {".wcm","application/vnd.ms-works"}, {".wdb","application/vnd.ms-works"}, {".wks","application/vnd.ms-works"}, {".wma","audio/x-ms-wma"}, {".wmf","image/x-wmf"}, {".wmv","video/x-ms-wmv"}, {".wmz","application/x-ms-wmz"}, {".wpd","application/wordperfect"}, {".wps","application/vnd.ms-works"}, {".wri","application/x-mswrite"}, {".wrl","x-world/x-vrml"}, {".wrz","x-world/x-vrml"}, {".xbm","image/x-xbitmap"}, {".xhtml","text/html"}, {".xla","application/vnd.ms-excel"}, {".xlam","application/vnd.ms-excel.addin.macroEnabled.12"}, {".xlc","application/vnd.ms-excel"}, {".xll","application/vnd.ms-excel"}, {".xlm","application/vnd.ms-excel"}, {".xls","application/vnd.ms-excel"}, {".xlsb","application/vnd.ms-excel.sheet.binary.macroEnabled.12"}, {".xlsm","application/vnd.ms-excel.sheet.macroEnabled.12"}, {".xlsx","application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"}, {".xlt","application/vnd.ms-excel"}, {".xltm","application/vnd.ms-excel.template.macroEnabled.12"}, {".xltx","application/vnd.openxmlformats-officedocument.spreadsheetml.template"}, {".xlw","application/vnd.ms-excel"}, {".xml","text/xml"}, {".xpm","image/x-xpixmap"}, {".xps","application/vnd.ms-xpsdocument"}, {".xsl","text/xsl"}, {".xwd","image/x-xwindowdump"}, {".z","application/x-compress"}, {".zip","application/zip"} };

void HttpServerHandler(struct evhttp_request* req, void* arg)
{
    Worker* worker=(Worker*)arg;
    const char* uri=evhttp_request_uri(req);
    std::string cleanUrl="",valueString="";
    struct evkeyvalq *headers;
    struct evkeyval *header;
    Worker::HTTP_METHOD method = Worker::EV_UNKNOWN;
    std::map<std::string,std::string> nameVals;
    char* decoded_uri=evhttp_decode_uri(uri);
    std::string decodeUri=decoded_uri;
    free(decoded_uri);

    switch (evhttp_request_get_command(req))
    {
    case EVHTTP_REQ_GET: method = Worker::EV_GET; break;
    case EVHTTP_REQ_POST: method = Worker::EV_POST; break;
    case EVHTTP_REQ_HEAD: method = Worker::EV_HEAD; break;
    case EVHTTP_REQ_PUT: method = Worker::EV_PUT; break;
    case EVHTTP_REQ_DELETE: method = Worker::EV_DELETE; break;
    case EVHTTP_REQ_OPTIONS: method = Worker::EV_OPTIONS; break;
    case EVHTTP_REQ_TRACE: method = Worker::EV_TRACE; break;
    case EVHTTP_REQ_CONNECT: method = Worker::EV_CONNECT; break;
    case EVHTTP_REQ_PATCH: method = Worker::EV_PATCH; break;
    default: method = Worker::EV_UNKNOWN; break;
    }

    headers = evhttp_request_get_input_headers(req);
    for (header = headers->tqh_first; header;
         header = header->next.tqe_next)
    {
        nameVals[header->key]=header->value;
    }

    char* post_data=(char *)EVBUFFER_DATA(req->input_buffer);
    if(post_data)
        valueString=post_data;
    std::string::size_type pos=decodeUri.find('?');
    if(pos != std::string::npos)
    {
        cleanUrl=decodeUri.substr(0,pos);
        if(valueString == "")
            valueString=decodeUri.substr(pos+1);
        else
            valueString+="&"+decodeUri.substr(pos+1);
    }
    else
        cleanUrl=decodeUri;

    std::vector<std::string> pairs;
    hl::strsplit(pairs,valueString,"&");
    for(auto str:pairs)
    {
        std::vector<std::string> pair;
        hl::strsplit(pair,str,"=");
        if(pair.size()==2)
            nameVals[pair[0]]=pair[1];
    }

    int RESPONS_CODE=HTTP_NOTFOUND;
    std::string ostr="";
    std::string opath="";
    int fd=-1;
    struct evbuffer* buf = evbuffer_new();
    std::map<std::string,ROUTE_FUNCTION_TYPE>::iterator it=worker->serv_->router_.find(cleanUrl);
    evhttp_add_header(req->output_headers, "Server", "myhttpserver v 0.0.1");
    evhttp_add_header(req->output_headers, "Connection", "close");
    if(it!=worker->serv_->router_.end())
    {
        it->second(method,nameVals,ostr,opath);
        if(opath != "")
        {
            if ((fd = open(opath.c_str(),O_RDONLY)) >= 0)
            {
                std::string ct=gmime[hl::pathext(opath)];
                if(ct == "")
                    ct="text/plain";
                evhttp_add_header(req->output_headers,"Content-Type", ct.c_str());
                evhttp_add_header(req->output_headers,"Content-Disposition", ("attachment;filename="+hl::pathname(opath)).c_str());
                evbuffer_add_file(buf, fd, 0, hl::filelen(opath));
                RESPONS_CODE=HTTP_OK;
            }
            else
            {
                RESPONS_CODE=HTTP_INTERNAL;
            }
        }
        else if(ostr != "")
        {
            evhttp_add_header(req->output_headers, "Content-Type", "text/plain; charset=UTF-8");
            evbuffer_add_printf(buf, "%s", ostr.c_str());
            RESPONS_CODE=HTTP_OK;
        }
        else
        {
            RESPONS_CODE=HTTP_NOTFOUND;
        }
    }
    else
    {
        evbuffer_add_printf(buf, "%s", "NOT FOUND!!!");
        RESPONS_CODE=HTTP_NOTFOUND;
    }
    evhttp_send_reply(req, RESPONS_CODE, "OK", buf);
    evbuffer_free(buf);
    if(fd!=-1)
        close(fd);
}

void HttpExitHandler(evutil_socket_t fd, short events, void* arg)
{
    (void)fd;(void)events;
    Worker* hs = (Worker*)arg;
    hs->Exit();
}

Worker::Worker()
{
    
}

Worker::~Worker()
{

}

bool Worker::Init(HttpServerM* serv,int fd)
{
    bool retBool=false;
    serv_=serv;
#ifdef __linux
    if(evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, exitSocks_) < 0)
        return false;
#else
    if(evutil_socketpair(AF_INET, SOCK_STREAM, 0, exitSocks_) < 0)
        return false;
#endif
    evutil_make_socket_nonblocking(exitSocks_[0]);
    evutil_make_socket_nonblocking(exitSocks_[1]);
    base_ = event_base_new();
    evHttpServ_ = evhttp_new(base_);
    if (evHttpServ_)
    {
        if(evhttp_accept_socket(evHttpServ_, fd) == 0)
        {
            evhttp_set_gencb(evHttpServ_, HttpServerHandler, (void*)this);
            exitEv_ = event_new(base_, exitSocks_[0], EV_READ|EV_PERSIST, HttpExitHandler, (void*)this);
            event_add(exitEv_, NULL);
            retBool=true;
        }
        else
        {
            evhttp_free(evHttpServ_);
            event_base_free(base_);
        }
    }
    else
    {
        event_base_free(base_);
    }
    return retBool;
}

void Worker::Run()
{
    event_base_dispatch(base_);
    event_free(exitEv_);
    evhttp_free(evHttpServ_);
    event_base_free(base_);
    close(exitSocks_[0]);
    close(exitSocks_[1]);
}

void Worker::Stop()
{
    char buf[1] = {'-'};
    send(exitSocks_[1], buf, 1,0);
}

void Worker::Exit()
{
    if(base_)
        event_base_loopexit(base_,0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
#define _MIN_(a, b) (a)>=(b)?(b):(a)
#define _MAX_(a, b) (a)>=(b)?(a):(b)

HttpServerM::HttpServerM()
{
    port_ = 80;
    workers_n_=10;
    fd_=-1;
#ifndef __linux
    WSADATA WSAData;
    WSAStartup(MAKEWORD(1, 1), &WSAData);
#endif
}

HttpServerM::~HttpServerM()
{
#ifndef __linux
    WSACleanup();
#endif
}

bool HttpServerM::Run(int port,int workerNum)
{
    port_=port;
    workers_n_ = _MIN_(_MAX_(workerNum, 1), 100);

    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ < 0)
        return false;
    int one = 1;
    int r = setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(int));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port_);

    r = bind(fd_, (struct sockaddr*)&addr, sizeof(addr));
    if (r < 0)
        return false;
    r = listen(fd_, 1024);
    if (r < 0)
        return false;

#ifdef __linux
    int flags;
    if ((flags = fcntl(fd_, F_GETFL, 0)) < 0 || fcntl(fd_, F_SETFL, flags | O_NONBLOCK) < 0)
        return false;
#else
    unsigned long flags = 1;
    ioctlsocket(nfd, FIONBIO, &flags);
#endif

    for(int i=0; i<workers_n_; i++)
    {
        if(workers_[i].Init(this,fd_))
            worker_threads_.push_back(std::shared_ptr<std::thread>(new std::thread(&Worker::Run, &workers_[i])));
        else
            return false;
    }

    return true;
}

void HttpServerM::Stop()
{
    for(int i=0; i<workers_n_; i++)
        workers_[i].Stop();
    close(fd_);
    for(auto& t:worker_threads_)
        t->join();
}

void HttpServerM::AddRouter(std::string path,ROUTE_FUNCTION_TYPE cb)
{
    router_[path]=cb;
}
