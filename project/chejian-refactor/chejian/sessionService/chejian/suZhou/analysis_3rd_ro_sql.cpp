#include <vector>
#include <dirent.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>
#include <event2/http_struct.h>
#include <event2/keyvalq_struct.h>
#include <thread>
#include "db/mysql/MySQL_DB.h"
#include "base/helper/HelperString.h"
#include "base/helper/HelperFile.h"
#include "base/BlockQueue.h"
#include "base/http/HttpServer.h"

#include "base/xml/Markup.h"
#include "base/log/logApi.h"
#include "config/_c_configCenter.h"

#include "alg/city/suzhou/_c_vehicle_SuZhou.h"


#define ERROR_POST          1
#define ANALYSIS_OK         0
#define ANALYSIS_UNKNOWN_IP 1
#define ANALYSIS_ERR_XML    2
#define ANALYSIS_UNKNOWN_INFO 3
#define UNUSED(x) (void)x




//#define DATA_PRINT  LOG
//#define LEVEL_INFO  COMMON,INFO
#define DBPWD "ju3eizd1;57?"

#define LEVEL_INFO INFO
#define LEVEL_ERROR ERR
#define LEVEL_DEBUG DEBUG
#define DATA_PRINT(lever, ...) LOG(COMMON,lever,__VA_ARGS__)


typedef unsigned char       BYTE;
typedef unsigned long       DWORD;
typedef unsigned int        UINT;


extern bool b_ok;
extern _c_configCenter *__pConfigCenter ;

unsigned int g_device_ID = 1 ;
std::string g_master_IP;	/* 从机记录主机的IP */
bool g_Interface ;
bool g_3rdInterface ;
static PDB_PARAM g_dbconf ;        // 数据库配置

#define CONNECT_MYSQL_DB_3RD_USEDB(_db_con,_loc_ip,_loc_port,_loc_user,_loc_pass,_loc_dbname)  _db_con->connect(_loc_ip, _loc_port, _loc_user, _loc_pass, _loc_dbname)
#define CONNECT_MYSQL_DB_3RD_DEFAULT_USEDB(_db_con) CONNECT_MYSQL_DB_3RD_USEDB(_db_con,g_dbconf->strHost.c_str(),g_dbconf->port,g_dbconf->strUserName.c_str() ,g_dbconf->strPassword.c_str(),g_dbconf->strDbName.c_str() )


#define CONNECT_MYSQL_DB_3RD(_loc_ip,_loc_port,_loc_user,_loc_pass,_loc_dbname)  db.connect(_loc_ip, _loc_port, _loc_user, _loc_pass, _loc_dbname)
#define CONNECT_MYSQL_DB_3RD_DEFAULT() CONNECT_MYSQL_DB_3RD(g_dbconf->strHost.c_str(),g_dbconf->port,g_dbconf->strUserName.c_str() ,g_dbconf->strPassword.c_str(),g_dbconf->strDbName.c_str() )


typedef struct third_vehicle_info
{
    // vehicle general information
    std::string     type;
    std::string     general_lsh;
    std::string     jylsh;
    std::string     cllx;
    std::string     hphm;
    std::string     clsbdh;
    std::string     hdzk;
    std::string     ltgg;
    std::string     lts;

    // photo node information
    std::string     photo_info_lsh;
    std::string     zpzl;
    std::string     zp;

    std::string     device_id;
}THIRD_VEHICLE_INFO;

typedef struct photo_node_info
{
    std::string     type;
    std::string     lsh;
    std::string     zpzl;
    std::string     b64zp;
}PHOTO_NODE_INFO;

pthread_mutex_t vec_info_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sql_mutex = PTHREAD_MUTEX_INITIALIZER;

std::vector<THIRD_VEHICLE_INFO *> g_v_vehicle_info;
std::vector<std::string> g_v_allow_ip; // save 白名单ip


bool update_write_ispass_suzhou(_c_vehicle_SuZhou *_pVehicle) ;

// callback function
void* cb_analysis_data(void*);
void* cb_save_to_db(void *);
void cb_httpserver_handle(struct evhttp_request *, void *);
void *cb_recv_data(void *);
// 算法处理结果写入数据库
void fun_write_each_result();
void fun_write_ispass();
// 解析数据
UINT fun_analyse_urlbuf_data(struct evhttp_request *);
// 发送响应信息
void fun_send_post_result(struct evhttp_request*, std::string, std::string);
// 获取白名单ip
bool fun_read_white_list(void);
// get当前时间
void fun_get_current_time(std::string &);
// 创建目录
void fun_mkdir(std::string dir_path);
// 写文件
std::string fun_write_new_file(std::string, std::string, std::string);
// url decode
//BYTE fromHex(const BYTE &x);
//std::string URLDecode(const string &sIn);
// B64 decode
std::string b64Decode(const char* Data, int DataByte);
std::string fun_get_cur_fullpath(const char * path);

static char _key[10] = {5,8,6,1,8,6,3,4,2};
std::string getDBPassWord(std::string passWord)
{
    char pwd[1024] = {0};
    char outPwd[1024] = {0};

    sprintf(pwd,"%s",passWord.c_str());
    unsigned int pwdLen = strlen(pwd);

    for (unsigned int i = 0; i < pwdLen; i++) {
        char subKey = _key[i%10];

        if(subKey + pwd[i] <= 128)
        {
            outPwd[i] = pwd[i] - subKey;
        }
        else
        {
            outPwd[i] = pwd[i];
        }
    }
    return outPwd;
}
// 从配置文件初始化 全局变量
void init_global_value()
{
    /* 由于苏州不是所有机器都开启这个接口，因此在判断城市编号后，还要判定开关文件是否存在 */
    if (access("Interface", F_OK) == 0) {
        g_Interface = true;
    } else {
        g_Interface = false;
    }
    /* 由于苏州不是所有机器都开启这个接口，因此在判断城市编号后，还要判定开关文件是否存在，暂时只有217机器开启该接口 */
    if (access("3rdInterface.xml", F_OK) == 0) {
        g_3rdInterface = true;
    } else {
        g_3rdInterface = false;
    }
}

bool creat_database_suzhou()
{
    printf("pwd:%s \n",getDBPassWord(DBPWD).c_str() );
    printf("port:%d,user:%s pass:%s dbname:%s  \n",g_dbconf->port,g_dbconf->strUserName.c_str() ,g_dbconf->strPassword.c_str(),g_dbconf->strDbName.c_str() ) ;

    MySQL_DB db ;
    MySQL_DB::initialize_MySQL_library();
    if (CONNECT_MYSQL_DB_3RD_DEFAULT()) {
        DATA_PRINT(LEVEL_INFO, "Start updating the database to version [18] ...... \n");

        std::string sqlString = "(";
        sqlString += "id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '主键',";  /* 1 */
        sqlString += "lsh VARCHAR(64) COMMENT '流水号',";                            /* 2 */
        sqlString += "jylsh VARCHAR(64) COMMENT '检验流水号',";               /* 3 */
        sqlString += "cllx VARCHAR(64) COMMENT '车辆类型',";                  /* 4 */
        sqlString += "hphm VARCHAR(64) COMMENT '号牌号码',";                  /* 5 */ // 号牌号码(带汉字，完整车牌，例如：苏E12345)
        sqlString += "sbdh VARCHAR(64) COMMENT '识别代号',";                  /* 6 */
        sqlString += "hdzk VARCHAR(64) COMMENT '核定载客',";                  /* 7 */
        sqlString += "ltgg VARCHAR(128) COMMENT '轮胎规格',";                 /* 8 */
        sqlString += "lts VARCHAR(64) COMMENT '轮胎数',";                     /* 9 */
        sqlString += "created_at DATETIME COMMENT '本行创建时间',";
        sqlString += "`device_id` int(10) unsigned DEFAULT NULL COMMENT '设备ID',";
        sqlString += "`ispass` int(10)  DEFAULT NULL COMMENT '整车结果',";

        sqlString += "KEY `index_lsh` (`lsh`)";
        sqlString += ")";
        if (!db.createTable("suzhou_3rd_general_info", sqlString.c_str())) {
            return false;
        }

        sqlString = "(";
        sqlString += "id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '主键',";  /* 1 */
        sqlString += "lsh VARCHAR(128) COMMENT '流水号',";                               /* 2 */
        sqlString += "zpzl VARCHAR(32) COMMENT '照片种类',";                    /* 3 */
        sqlString += "zplj VARCHAR(128) COMMENT '照片路径',";                   /* 4 */
        sqlString += "result INT(10) UNSIGNED NULL DEFAULT 0 COMMENT '结果',"; /* 5 */
        sqlString += "reason VARCHAR(128) COMMENT '照片结果描述',";              /* 6 */
        sqlString += "created_at DATETIME COMMENT '本行创建时间',";              /* 7 */
        sqlString += "`device_id` int(10) unsigned DEFAULT NULL COMMENT '设备ID',";

        sqlString += "KEY `index_lsh` (`lsh`)";
        sqlString += ")";
        if (!db.createTable("suzhou_3rd_photo_info", sqlString.c_str())) {
            return false;
        }
        db.disconnect();
  }

    return true;
}

void test_insert_value() //g_v_vehicle_info.push_back(pinfo)
{
    //std::vector<THIRD_VEHICLE_INFO *> g_v_vehicle_info;

    {
        THIRD_VEHICLE_INFO *th_info = new THIRD_VEHICLE_INFO ;
        th_info->type = "information";
        th_info->general_lsh = "111111111" ;
        th_info->jylsh = "1234567";
        th_info->cllx  = "K32";
        th_info->hphm  = "苏A12323X0";
        th_info->clsbdh = "29383feufeuv8heve98";
        th_info->hdzk = "9";
        th_info->ltgg = "wnenev";
        th_info->lts = "3";
        th_info->device_id = "123";
        g_v_vehicle_info.push_back(th_info);
    }
    {
        THIRD_VEHICLE_INFO *th_info = new THIRD_VEHICLE_INFO ;
        th_info->type = "information";
        th_info->general_lsh = "1111111" ;
        th_info->jylsh = "1234597";

        g_v_vehicle_info.push_back(th_info);
    }
    {
        THIRD_VEHICLE_INFO *th_info = new THIRD_VEHICLE_INFO ;
        th_info->type = "photo";
        th_info->photo_info_lsh = "1234567";
        th_info->zpzl = "03";
        th_info->zp = "null";
        th_info->device_id = "1";


        g_v_vehicle_info.push_back(th_info);
    }

    {
        MySQL_DB * db = new MySQL_DB;
        // save data to local DB and master DB.
        cb_save_to_db(db);
        printf("save it ============================================================\n ");
    }
    {
        MySQL_DB * db = new MySQL_DB;
        // save data to local DB and master DB.
        cb_save_to_db(db);
        printf("save it ============================================================\n ");
    }
    {
        MySQL_DB * db = new MySQL_DB;
        // save data to local DB and master DB.
        cb_save_to_db(db);
        printf("save it ============================================================\n ");
    }
}

// 启动第三方车检程序
void* start_receive_data_suzhou()
{
    assert(__pConfigCenter);
    g_dbconf= __pConfigCenter->getStructDbParam();
    if(!creat_database_suzhou() )
    {
        printf("数据连接失败!\n");
        DATA_PRINT(LEVEL_INFO, "数据库创建失败 \n");
        return NULL;
    }

//    {
//        test_insert_value();
//    }

    pthread_t pthread_recv_id;
    if (0 != pthread_create(&pthread_recv_id, NULL, cb_recv_data, NULL) ) {
        DATA_PRINT(LEVEL_INFO, "<3rd httpserver> new thread of received data. \n");
        return NULL;
    }


}

void* fun_3rd_part_interface(void *args)
{
    UNUSED(args);
    sleep(20);
    // 获取白名单ip
    if (!fun_read_white_list()) {
        DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> 获取白名单列表失败. \n");
        return NULL;
    }
    for (unsigned int i = 0; i < g_v_allow_ip.size(); i++)
    {
        DATA_PRINT(LEVEL_INFO, "IP白名单： [%s]\n", g_v_allow_ip.at(i).c_str());
    }
    DATA_PRINT(LEVEL_INFO, "IP白名单数量：%u\n", g_v_allow_ip.size());

    // 启动接收照片线程
    pthread_t pthread_recv_id;
    if (0 != pthread_create(&pthread_recv_id, NULL, cb_recv_data, NULL) ) {
        DATA_PRINT(LEVEL_INFO, "<3rd httpserver> new thread of received data. \n");
        return NULL;
    }
    return NULL;
}

UINT fun_analyse_urlbuf_data(struct evhttp_request *req)
{
    // 是否在ip白名单里
    std::string remote_ip(req->remote_host);
    //bool b_allow = false;
    bool b_allow = true;// 暂不检测白名单
    std::vector<std::string>::iterator iter;
    for (iter = g_v_allow_ip.begin(); iter != g_v_allow_ip.end(); ++iter)
    {
        if (remote_ip.find(*iter) == 0) {
            b_allow = true;
            break;
        }
    }

    // 不在白名单的机器返回 404 (白名单暂未使用)
    if (!b_allow) {
        evhttp_send_error(req, HTTP_NOTFOUND, NULL);
        return ANALYSIS_UNKNOWN_IP;
    }

    struct evkeyvalq *headers;
    struct evkeyval *header;
    char* data;
    UINT len = 0;
    const char *uri = evhttp_request_get_uri(req);
    evhttp_request_get_evhttp_uri(req);
    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> %s\n", uri);
    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> headers:\n");
    headers = evhttp_request_get_input_headers(req);
    for (header = headers->tqh_first; header; header = header->next.tqe_next) {
        DATA_PRINT(LEVEL_INFO, "<3rd httpserver> key[%s]:value[%s] \n", header->key, header->value);
    }

    struct evbuffer * buf;
    buf = evhttp_request_get_input_buffer(req);
    len = (UINT)evbuffer_get_length(buf);
    data = (char*)malloc(len + 1);
    evbuffer_copyout(buf, data, len);
    *(data + len) = 0;
    std::string strurl = URLDecode(data);
    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> strurl [%s]\n", strurl.c_str());
    free(data);

/*    <?xml version="1.0" encoding="utf-8"?>
    <vehicle>
        <type>information</type>
        <body>
            ……(节点名称见下表)
        </body>
    </vehicle>
*/
    CMarkup xml;
    THIRD_VEHICLE_INFO * pinfo = new THIRD_VEHICLE_INFO;
    pinfo->device_id = std::to_string(g_device_ID);
    xml.SetDoc(strurl);
    xml.ResetMainPos();

    // 解析收到的数据并存储
    if (xml.FindElem("vehicle")) {
        if (xml.FindChildElem("type")) {
            std::string str_type(xml.GetChildData());
            if (0 == str_type.compare("information")) {
                pinfo->type = str_type;
            } else if (0 == str_type.compare("photo")) {
                pinfo->type = str_type;
            } else {
                pinfo->type = std::string("unknown");
                DATA_PRINT(LEVEL_ERROR, "上传类型不在处理范围\n");
                return ANALYSIS_UNKNOWN_INFO;
            }
            DATA_PRINT(LEVEL_INFO, "<3rd httpserver> xml 上传数据类型 ===> [%s] \n", pinfo->type.c_str());
        }
        if (xml.FindChildElem("body")) {
            xml.IntoElem();
            // 车辆基本信息
            if (0 == pinfo->type.compare("information")) {
                if (xml.FindChildElem("lsh")) {// 车辆基本信息流水号
                    pinfo->general_lsh = xml.GetChildData();
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 基本信息流水号:[%s] \n", pinfo->general_lsh.c_str());
                }
                if (xml.FindChildElem("jylsh")) {// 检验流水号
                    pinfo->jylsh = xml.GetChildData();
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 基本信息检验流水号:[%s] \n", pinfo->jylsh.c_str());
                } else {
                    DATA_PRINT(LEVEL_ERROR, "错误的xml结构，基本信息[检验流水号]字段未找到！！！\n");
                    return ANALYSIS_ERR_XML;
                }
                if (xml.FindChildElem("cllx")) { // 车辆类型
                    pinfo->cllx = xml.GetChildData();
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 基本信息车辆类型:[%s] \n", pinfo->cllx.c_str());
                } else {
                    DATA_PRINT(LEVEL_ERROR, "错误的xml结构，基本信息[车辆类型]字段未找到！！！\n");
                    return ANALYSIS_ERR_XML;
                }
                if (xml.FindChildElem("hphm")) { // 号牌号码(带汉字，完整车牌，例如：苏E12345)
                    pinfo->hphm = xml.GetChildData();
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 基本信息号牌号码:[%s] \n", pinfo->hphm.c_str());
                } else {
                    DATA_PRINT(LEVEL_ERROR, "错误的xml结构，基本信息[号牌号码]字段未找到！！！\n");
                    return ANALYSIS_ERR_XML;
                }
                if (xml.FindChildElem("clsbdh")) { // 车辆识别代号
                    pinfo->clsbdh = xml.GetChildData();
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 基本信息车辆识别代号:[%s] \n", pinfo->clsbdh.c_str());
                } else {
                    DATA_PRINT(LEVEL_ERROR, "错误的xml结构，基本信息[车辆识别代号]字段未找到！！！\n");
                    return ANALYSIS_ERR_XML;
                }
                if (xml.FindChildElem("hdzk")) {
                    pinfo->hdzk = xml.GetChildData();
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 核定载客:[%s] \n", pinfo->hdzk.c_str());
                } else {
                    DATA_PRINT(LEVEL_ERROR, "错误的xml结构，基本信息[核定载客]字段未找到！！！\n");
                    return ANALYSIS_ERR_XML;
                }
                if (xml.FindChildElem("ltgg")) { // 轮胎规格
                    pinfo->ltgg = xml.GetChildData();
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 基本信息轮胎规格:[%s] \n", pinfo->ltgg.c_str());
                } else {
                    DATA_PRINT(LEVEL_ERROR, "错误的xml结构，基本信息[轮胎规格]字段未找到！！！\n");
                    return ANALYSIS_ERR_XML;
                }
                if (xml.FindChildElem("lts")) { // 轮胎数
                    pinfo->lts = xml.GetChildData();
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 基本信息轮胎数:[%s] \n", pinfo->lts.c_str());
                } else {
                    DATA_PRINT(LEVEL_ERROR, "错误的xml结构，基本信息[轮胎数]字段未找到！！！\n");
                    return ANALYSIS_ERR_XML;
                }
            }
            if (0 == pinfo->type.compare("photo")) { // 车辆图片信息
                if (xml.FindChildElem("lsh")) {// 车辆图片信息流水号
                    pinfo->photo_info_lsh = xml.GetChildData();
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 图片信息流水号:[%s]\n", pinfo->photo_info_lsh.c_str());
                } else {
                    DATA_PRINT(LEVEL_ERROR, "错误的xml结构，图片信息[流水号]字段未找到！！！\n");
                    return ANALYSIS_ERR_XML;
                }
                if (xml.FindChildElem("zpzl")) { // 照片种类
                    pinfo->zpzl = xml.GetChildData();
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 图片信息照片种类:[%s] \n", pinfo->zpzl.c_str());
                } else {
                    DATA_PRINT(LEVEL_ERROR, "错误的xml结构，图片信息[照片种类]字段未找到！！！\n");
                    return ANALYSIS_ERR_XML;
                }
                if (xml.FindChildElem("zp")) {
                    std::string str;
                    str = xml.GetChildData(); // 照片数据 使用base64编码
                    std::string zp_binary(b64Decode(str.c_str(), str.size()));
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 照片decode完成\n");
                    std::string zp_name(pinfo->zpzl);
                    zp_name += "_" + pinfo->photo_info_lsh;
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 照片名称%s\n", zp_name.c_str());
                    // 保存图片
                    std::string zplj = fun_write_new_file(DIR_PATH, zp_name, zp_binary);
                    pinfo->zp = zplj;
                    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 照片路径:[%s] \n", pinfo->zp.c_str());
                } else {
                    DATA_PRINT(LEVEL_ERROR, "错误的xml结构，图片信息[照片]字段未找到！！！\n");
                    return ANALYSIS_ERR_XML;
                }
            }
        }

        // lock
        if(pthread_mutex_lock(&vec_info_mutex) != 0) {
            perror("mutex_lock vec_info_mutex");
            exit(EXIT_FAILURE);
        }
        g_v_vehicle_info.push_back(pinfo);
        // unlock
        if(pthread_mutex_unlock(&vec_info_mutex) != 0) {
            perror("mutex_unlock vec_info_mutex");
            exit(EXIT_FAILURE);
        }
    } else {
        DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 没有合法的XML结构. \n");
        return ANALYSIS_ERR_XML;
    }

    return ANALYSIS_OK;
}

/*<?xml version="1.0" encoding="utf-8"?>
    <response>
    <status>
        <code>0</code>
        <message>数据上传成功</message>
    </status>
    </response>*/
void fun_send_post_result(struct evhttp_request* req, std::string code, std::string msg)
{
    evbuffer* buf = evbuffer_new();
    std::string resultxml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    resultxml += "<response>";
    resultxml += "<status>";
    resultxml += "<code>";
    resultxml += code;
    resultxml += "</code>";
    resultxml += "<message>";
    resultxml += msg;
    resultxml += "</message>";
    resultxml += "</status>";
    resultxml += "</response>";

    evbuffer_add(buf, resultxml.c_str(), strlen((char *)resultxml.c_str()));
    evhttp_add_header(req->output_headers, "Content-Type", "text/xml");

    int n_code = atoi(code.c_str());
    switch (n_code) {
    case 0: evhttp_send_reply(req, HTTP_OK, "OK", buf); break;
    case 1: evhttp_send_reply(req, HTTP_OK, "OK", buf); break;
    case 2: evhttp_send_reply(req, HTTP_OK, "OK", buf); break;
    default: break;
    }

    evbuffer_free(buf);
}

// 获取白名单
bool fun_read_white_list()
{
    bool ret = false;
    CMarkup xml;
    if (!xml.Load("3rdInterface.xml")) {
        DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> can't open 3rdInterface.xml! \n");
        return ret;
    }
    xml.ResetMainPos();

    if (xml.FindElem("config")) {
        if (xml.FindChildElem("list")) {
            xml.IntoElem();
            while (true)
            {
                if(xml.FindChildElem("ip")) {
                    std::string tmpip(xml.GetChildData());
                    g_v_allow_ip.push_back(tmpip);
                    ret = true;
                } else {
                    return ret;
                }
            }
        } else {
            DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> 查找\"list\"字段失败 \n");
            return ret;
        }
    } else {
        DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> 查找\"config\"字段失败. \n");
        return ret;
    }
}

void fun_get_current_time(std::string &cur_time)
{
    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);
    char timearray[128] = { 0 };
    sprintf(timearray, "%d-%02d-%02d %02d:%02d:%02d", st->tm_year+1900, st->tm_mon+1, st->tm_mday, st->tm_hour, st->tm_min, st->tm_sec);
    cur_time = std::string(timearray);
}

void fun_mkdir(std::string dir_path)
{
    DIR *dp = opendir(dir_path.c_str());
    if (dp != NULL) {
        closedir(dp);
    } else {
        mkdir(dir_path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    }
}

std::string fun_get_cur_fullpath(const char * path)
{
    char curr_path[128] = {0};
    getcwd(curr_path, 128);
    std::string open_file = std::string(curr_path);
    open_file.append("/");
    open_file.append(path);
    return open_file;
}

std::string fun_write_new_file(std::string dir_path, std::string file_name, std::string file_binary)
{
    // 创建当前日期的目录
    std::string photo_dir(dir_path);
    std::time_t t = std::time(NULL);
    std::tm *st = std::localtime(&t);
    char tmpArray[128] = { 0 };
    sprintf(tmpArray, "%d-%02d-%02d", st->tm_year + 1900, st->tm_mon + 1, st->tm_mday);
    std::string strCurTime = tmpArray;
    photo_dir += strCurTime;
    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> 图片路径 >>>> [%s]\n", photo_dir.c_str());

    struct stat st_buf = {};
    stat(photo_dir.c_str(), &st_buf);
    if (!hl::pathexist(photo_dir)) {
        hl::creatdir(photo_dir);
        mkdir(photo_dir.c_str(), 0777);
    }
    photo_dir += "/";

    std::string open_file = photo_dir;
    open_file.append(file_name);
    FILE *pf = fopen(open_file.c_str(), "wb");
    if (NULL == pf) {
        DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> file_name:[%s]", file_name.c_str());
        return NULL;
    }
    DATA_PRINT(LEVEL_INFO, "<3rd httpserver> image name >>>> [%s]\n", open_file.c_str());
    fwrite(file_binary.c_str(), 1, file_binary.size(), pf);

    fclose(pf);
    return open_file;
}

// 接收数据 存储数据
void cb_httpserver_handle(struct evhttp_request *req, void *arg)
{
    UNUSED(arg);
    const char *cmdtype;
    UINT result = 0;
    pthread_t pthread_save2db_id;
    switch (evhttp_request_get_command(req)) {
    case EVHTTP_REQ_GET: cmdtype = "GET"; break;
    case EVHTTP_REQ_POST: cmdtype = "POST"; break;
    case EVHTTP_REQ_HEAD: cmdtype = "HEAD"; break;
    case EVHTTP_REQ_PUT: cmdtype = "PUT"; break;
    case EVHTTP_REQ_DELETE: cmdtype = "DELETE"; break;
    case EVHTTP_REQ_OPTIONS: cmdtype = "OPTIONS"; break;
    case EVHTTP_REQ_TRACE: cmdtype = "TRACE"; break;
    case EVHTTP_REQ_CONNECT: cmdtype = "CONNECT"; break;
    case EVHTTP_REQ_PATCH: cmdtype = "PATCH"; break;
    default: cmdtype = "unknown"; break;
    }

    //获取请求的URI
    const char *uri = evhttp_request_get_uri(req);
    DATA_PRINT(LEVEL_DEBUG, "<3rd httpserver> received a request(Method:%s, URI:%s) \n", cmdtype, uri);

    if (strstr(uri, "/AppendCheck") != NULL) {
        result = fun_analyse_urlbuf_data(req);
        if (ANALYSIS_OK == result) {
            std::string code = "0";
            std::string msg = std::string("数据上传成功");
            fun_send_post_result(req, code, msg);

            // lock
            if(pthread_mutex_lock(&sql_mutex) != 0) {
                perror("mutex_lock sql_mutex");
                exit(EXIT_FAILURE);
            }
            MySQL_DB * db = new MySQL_DB;

            // save data to local DB and master DB.
            if (0 != pthread_create(&pthread_save2db_id, NULL, cb_save_to_db, db) ) {
                DATA_PRINT(LEVEL_DEBUG, "<3rd httpserver> pthread_save2db error !!! \n");
                return;
            }

            // waitting for save2db pthread.
            pthread_join(pthread_save2db_id, NULL);
            return;
        } else if (ANALYSIS_UNKNOWN_IP == result) {
            std::string code = "1";
            std::string msg = std::string("数据来源于未知IP，无法进行处理");
            fun_send_post_result(req, code, msg);
        } else if (ANALYSIS_ERR_XML == result) {
            std::string code = "2";
            std::string msg = std::string("没有合法的XML结构");
            fun_send_post_result(req, code, msg);
        } else if (ANALYSIS_UNKNOWN_INFO == result) {
            std::string code = "3";
            std::string msg = std::string("无法处理的数据类型，不是information 或者 photo");
            fun_send_post_result(req, code, msg);
        }
    } else {
        // respons error
        evhttp_send_error(req, HTTP_NOTFOUND, NULL);
        DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> the query uri[%s] is undefined! \n", uri);
        return;
    }
    return;
}

void *cb_recv_data(void *arg)
{
    UNUSED(arg);
    HttpServer httpserver;
    const char* ip = "0.0.0.0";
    int port = 9179;
    httpserver.startHttpServer(ip, port, cb_httpserver_handle, NULL);
    return nullptr;
}



int  queryLiuShuiHao_suzhou( std::vector<std::string>& lsh_vector)
{
    MySQL_DB db;
    // 连接本机数据库查找数据 一次查10辆车
    if (CONNECT_MYSQL_DB_3RD_DEFAULT()) {
        std::string sqls("select lsh, cllx from chejian_refactor.suzhou_3rd_general_info where ispass is null and lsh is not null limit 0, 10");
        MYSQL_RES *result = db.getResult(sqls.c_str());
        MYSQL_ROW row = NULL;
        // 获取一条基本信息获取
        while ((row = mysql_fetch_row(result)) != NULL)
        {
            std::string tmp_lsh = std::string(row[0]); // 流水号
            std::string tmp_cllx = std::string(row[1]); // 车辆类型
            if (!tmp_lsh.empty()) {
               // p_3rdvehicle->m_jylsh = tmp_lsh;

            } else {
                DATA_PRINT(LEVEL_ERROR, "未获取到[基本信息流水号], continue.\n");
                continue;
            }
            if (!tmp_cllx.empty()) {
               // p_3rdvehicle->m_cllx = tmp_cllx;
            } else {
                DATA_PRINT(LEVEL_ERROR, "未获取到[基本信息车辆类型], continue.\n");
                continue;
            }

            lsh_vector.push_back(tmp_lsh);
        }
        db.freeResult(result);
        db.disconnect();
    } else {
        DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> 连接数据库错误.\n");
    }
    return lsh_vector.size();
}
_c_vehicle  * queryInputParameter_suzhou( string lsh)
{
   // 放入车检处理队列

    MySQL_DB db;
    _c_vehicle_SuZhou *pvehs =NULL;
    // 连接本机数据库查找数据 一次查10辆车
    if (CONNECT_MYSQL_DB_3RD_DEFAULT()) {
     //   printf("---------------------------tets--------------lsh:%s\n",lsh.c_str());
        std::string sqls;
        sqls="select lsh, cllx, hphm, sbdh, hdzk, ltgg, lts from chejian_refactor.suzhou_3rd_general_info where lsh= '" +lsh+"' and ispass is null limit 1 ";
     //   printf("8888888888888888888888888\n");
        MYSQL_RES *result = db.getResult(sqls.c_str());
        MYSQL_ROW row = NULL;
    //    printf("11111111111111111111111111\n");
        // 获取一条基本信息获取
        while ((row = mysql_fetch_row(result)) != NULL)
        {
            std::string tmp_lsh = std::string(row[0]); // 流水号
            std::string tmp_cllx = std::string(row[1]); // 车辆类型
            std::string tmp_hphm = std::string(row[2]); // 检验流水号
            std::string tmp_sbdh = std::string(row[3]); // 识别代号
            std::string tmp_hdzk = std::string(row[4]); // 核定载客
            std::string tmp_ltgg = std::string(row[5]); // 轮胎规格
            std::string tmp_lts = std::string(row[6]); // 轮胎数
          //  printf("2222222222222222222222222222222222\n");
            {
                if (!tmp_lsh.empty()) {
                   // p_3rdvehicle->m_jylsh = tmp_lsh;

                } else {
                    DATA_PRINT(LEVEL_ERROR, "未获取到[基本信息流水号], continue.\n");
                    continue;
                }
                if (!tmp_cllx.empty()) {
                   // p_3rdvehicle->m_cllx = tmp_cllx;
                } else {
                    DATA_PRINT(LEVEL_ERROR, "未获取到[基本信息车辆类型], continue.\n");
                    continue;
                }
                if (!tmp_hphm.empty()) {
                    //p_3rdvehicle->m_hphm = tmp_hphm;
                } else {
                    DATA_PRINT(LEVEL_ERROR, "未获取到[基本信息号牌号码].\n");
                }
                if (tmp_sbdh.empty()) {
                    DATA_PRINT(LEVEL_ERROR, "未获取到[基本信息识别代号].\n");
                } else {
                   // p_3rdvehicle->m_clsbdh = tmp_sbdh;
                }
                if (tmp_hdzk.empty()) {
                    DATA_PRINT(LEVEL_INFO, "未获取到[基本信息核定载客]\n");
                } else {
                    //p_3rdvehicle->m_hdzk = tmp_hdzk;
                }
                if (tmp_ltgg.empty()) {
                    DATA_PRINT(LEVEL_ERROR, "未获取到[基本信息轮胎规格].\n");
                } else {
                    //p_3rdvehicle->m_ltgg = tmp_ltgg;
                }
                if (tmp_lts.empty()) {
                    DATA_PRINT(LEVEL_ERROR, "未获取到[基本信息轮胎数].\n");
                } else {
                    //p_3rdvehicle->m_lts = tmp_lts;
                }
            }
           // _c_vehicle_SuZhou vehs;
            pvehs  = new _c_vehicle_SuZhou ;
            pvehs->liuShuiHao = tmp_lsh ;
            pvehs->cheLiangLeiXing = tmp_cllx ;
            pvehs->haoPaiHaoMa = tmp_hphm ;
            pvehs->cheLiangShiBieDaiHao = tmp_sbdh;
            pvehs->heDingZaiKe = tmp_hdzk ;
            pvehs->lunTaiGuiGe = tmp_ltgg ;
            pvehs->lunTaiShu = tmp_lts ;
            pvehs->shiYongXingZhi = "A";
        }
         db.freeResult(result);
        db.disconnect();
    } else {
        DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> 连接数据库错误.\n");
    }
    return pvehs ;
}

bool update_write_ispass_suzhou(_c_vehicle_SuZhou *_pVehicle)
{
    MySQL_DB db;
   if ( CONNECT_MYSQL_DB_3RD_DEFAULT() )
   {
         printf("-------------------------------------------------------------------------------\n");
         //更改图片列表 算法识别结果
         vector<_c_algTask*>& itemtask =_pVehicle->algTaskVector ;
         //只更新后面九种
       //  string sql_photos ="";
         for(unsigned int i = 0 ; i < _pVehicle->algTaskVector.size() ; i++)
         {
             _c_algTask* algitem= (_c_algTask*)(itemtask[i]) ;
             string sql_photo = "update suzhou_3rd_photo_info SET result=" +algitem->result+ " , reason='"+algitem->reason+"' where lsh='"
                     +_pVehicle->liuShuiHao+ "' and zpzl='"+algitem->algCode+"'";
            //printf("extraReponseData:%s \n",sql_photo.c_str() );
            db.noReturnWork(sql_photo.c_str() );
         }

        printf("_pVehicle->sessionResult:%s sessionreason:%s \n",_pVehicle->sessionResult.c_str(),_pVehicle->sessionReason.c_str() );
         //更改  单辆车会话的审查结果
        string b_ispass = _pVehicle->sessionResult;
        string sqlString = "update suzhou_3rd_general_info  SET ispass="+ b_ispass  +"  where lsh= '" + _pVehicle->liuShuiHao + "'";
        DATA_PRINT(LEVEL_DEBUG, "update ispass: %s ,sessionreason: %s \n", sqlString.c_str(),_pVehicle->sessionReason );
        db.noReturnWork(sqlString.c_str() ) ;
        db.disconnect();
    }else{
        return false ;
    }

    return true ;
}

void* cb_save_to_db(void *args)
{
    MySQL_DB * db = (MySQL_DB *)args;
    int num = 0;
    // 写入本机数据库
    //if (db->connect(NULL, 6033, "root", getDBPassWord(DBPWD).c_str(), "chejian_refactor"))
    if(CONNECT_MYSQL_DB_3RD_DEFAULT_USEDB(db) )
    {
        DATA_PRINT(LEVEL_INFO, "事后审核连接数据库成功.\n");
        printf("事后审核\n");
        db->selectDB("chejian_refactor");
        num = g_v_vehicle_info.size();
        if (num > 0) {
            THIRD_VEHICLE_INFO * pinfo_tmp = NULL;
            pinfo_tmp = g_v_vehicle_info.back();

            if (pinfo_tmp->type.compare("information") == 0) {
                std::string sqlString, cur_time;
                sqlString = "(lsh, jylsh, cllx, hphm, sbdh, hdzk, ltgg, lts, created_at, device_id) VALUES (";
                sqlString += pinfo_tmp->general_lsh + ", ";    // add 流水号
                sqlString += "'" + pinfo_tmp->jylsh + "', ";   // add 检验流水号
                sqlString += "'" + pinfo_tmp->cllx  + "', ";   // add 车辆类型
                sqlString += "'" + pinfo_tmp->hphm  + "', ";   // add 号牌号码
                sqlString += "'" + pinfo_tmp->clsbdh+ "', ";   // add 车辆识别代号
                sqlString += "'" + pinfo_tmp->hdzk  + "', ";   // add 核定载客
                sqlString += "'" + pinfo_tmp->ltgg  + "', ";   // add 轮胎规格
                sqlString += "'" + pinfo_tmp->lts   + "', ";   // add 轮胎数
                fun_get_current_time(cur_time);
                sqlString += "'" + cur_time + "', ";           // add 创建时间
                sqlString += "'" + pinfo_tmp->device_id + "')";

                // 上传重要信息检查
                if (pinfo_tmp->jylsh.empty()) {
                    DATA_PRINT(LEVEL_ERROR, "事后审核[检验流水号]为空，跳过数据库存储\n");
                    goto END_FUNC ;
                    //return NULL;
                }
                if (pinfo_tmp->hphm.empty()) {
                    DATA_PRINT(LEVEL_ERROR, "事后审核[号牌号码]为空，跳过数据库存储\n");
                    goto END_FUNC ;
                   // return NULL;
                }
                if (pinfo_tmp->clsbdh.empty()) {
                    DATA_PRINT(LEVEL_ERROR, "事后审核[车辆识别代号]为空，跳过数据库存储\n");
                    goto END_FUNC ;
                   // return NULL;
                }

                if (!db->insert("suzhou_3rd_general_info", sqlString.c_str())) { // 本机数据库
                    DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> 本机基本信息表插入失败 \'suzhou_3rd_general_info\' error number[%ud]! \n", db->getErrorNumber());
                }

                // 1 写入主机数据库
//                MySQL_DB * db_master = new MySQL_DB;
//                if (db_master->connect(g_master_IP.c_str(),6033, "root", getDBPassWord(DBPWD).c_str(), "chejian_refactor")) {
//                    if (!db_master->insert("suzhou_3rd_general_info", sqlString.c_str())) {
//                        DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> 主机基本信息表插入失败 \'suzhou_3rd_general_info\' error number[%ud]! \n", db_master->getErrorNumber());
//                    }
//                }


//                db_master->disconnect();
//                delete db_master;
//                db_master = NULL;
            } else if (pinfo_tmp->type.compare("photo") == 0) {
                std::string sqlString, cur_time;
                sqlString = "(lsh, zpzl, zplj, created_at, device_id) VALUES (";
                sqlString += pinfo_tmp->photo_info_lsh + ", ";  // add 流水号
                sqlString += "'" + pinfo_tmp->zpzl + "', ";      // add 照片种类
                sqlString += "'" + pinfo_tmp->zp + "', ";        // add 照片路径
                fun_get_current_time(cur_time);
                sqlString += "'" + cur_time + "', ";             // add 创建时间
                sqlString += "'" + pinfo_tmp->device_id + "')";

                if (pinfo_tmp->photo_info_lsh.empty()) {
                    DATA_PRINT(LEVEL_ERROR, "事后审核[照片流水号]为空，忽略无效数据\n");
                   // return NULL;
                    goto END_FUNC ;
                }
                if (pinfo_tmp->zpzl.empty()) {
                    DATA_PRINT(LEVEL_ERROR, "事后审核[照片种类]为空，忽略不正确数据\n");
                    goto END_FUNC ;
                  //  return NULL;
                }
                if (pinfo_tmp->zp.empty()) {
                    DATA_PRINT(LEVEL_ERROR, "事后审核[照片流水号]为空，忽略无效数据\n");
                    goto END_FUNC ;
                   // return NULL;
                }

                if (!db->insert("suzhou_3rd_photo_info", sqlString.c_str())) {
                    DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> 本机照片信息表插入失败 \'suzhou_3rd_photo_info\' rror number[%ud]! \n", db->getErrorNumber());
                }

                //2 write to master DB
//                MySQL_DB * db_master = new MySQL_DB;
//                if (db_master->connect(g_master_IP.c_str(),6033, "root", getDBPassWord(DBPWD).c_str(), "chejian_refactor")) {
//                    if (!db_master->insert("suzhou_3rd_photo_info", sqlString.c_str())) {
//                        DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> 主机照片信息表插入失败  \'suzhou_3rd_photo_info\' error number[%ud]! \n", db_master->getErrorNumber());
//                    }
//                }

//                delete db_master;
//                db_master = NULL;
            } else if (pinfo_tmp->type.compare("unknown") == 0) {
                DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> unknown type !!! \n");
            } else {
                DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> other type !!! \n");
            }

            // lock
            if(pthread_mutex_lock(&vec_info_mutex) != 0) {
                perror("mutex_lock vec_info_mutex");
                exit(EXIT_FAILURE);
            }
            free(pinfo_tmp);
            g_v_vehicle_info.pop_back();
            // unlock
            if(pthread_mutex_unlock(&vec_info_mutex) != 0) {
                perror("mutex_unlock vec_info_mutex");
                exit(EXIT_FAILURE);
            }

            if (pinfo_tmp != NULL)
                pinfo_tmp = NULL;
        } else {
            sleep(10);
        }
    } else {
       // delete(db);
        printf("连接失败\n");
        DATA_PRINT(LEVEL_ERROR, "<3rd httpserver> the query uri is undefined! \n");
        goto END_FUNC_DISCONNECT;
    }

END_FUNC:
    db->disconnect();

END_FUNC_DISCONNECT:
    delete db;
    db = NULL;
    if(pthread_mutex_unlock(&sql_mutex) != 0) {
        perror("mutex_unlock sql_mutex");
        exit(EXIT_FAILURE);
    }
    return NULL;
}

std::string b64Decode(const char* Data, int DataByte)
{
    unsigned char *pData = (unsigned char *)Data;
    //解码表
    const char DecodeTable[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        62, // '+'
        0, 0, 0,
        63, // '/'
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
        0, 0, 0, 0, 0, 0, 0,
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
        0, 0, 0, 0, 0, 0,
        26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
        39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
    };
    //返回值
    string strDecode;
    int nValue;
    int i = 0;
    while (i < DataByte) {
        if (*pData != '\r' && *pData != '\n') {
            nValue = DecodeTable[*pData++] << 18;
            nValue += DecodeTable[*pData++] << 12;
            strDecode += (nValue & 0x00FF0000) >> 16;
            if (*pData != '=') {
                nValue += DecodeTable[*pData++] << 6;
                strDecode += (nValue & 0x0000FF00) >> 8;
                if (*pData != '=') {
                    nValue += DecodeTable[*pData++];
                    strDecode += nValue & 0x000000FF;
                }
            }
            i += 4;
        } else// 回车换行,跳过
        {
            pData++;
            i++;
        }
    }
    return strDecode;
}


