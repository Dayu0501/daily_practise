#ifndef  _C_UPGRADE_TOOLS
#define  _C_UPGRADE_TOOLS

#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <algorithm>
#include "base/json/json.h"

typedef void (*DefaultCallBack)(Json::Value& jsonDir ,const std::string&  rootdir,const std::string&  filepath);

class DirProcess
{
public:
    DirProcess(){}
    DirProcess(std::string path);
    DirProcess(std::vector<std::string>& pathArray);
    //生成文件夹 md5结构
    std::string buildMd5MsgMulti();
    //获取差异比对结果 (true :有差异  , false: 无差异)
    bool getDiffWithStr(std::string& localjson ,std::string& remoteJson,std::string&  diffjson) ;
    //通过差异json 生成差异文件
    void COPY(std::string remotestr, std::string dst_path);
     /*
      * diffJson :差异文件结构
      * diffPackagePath：差异包暂存路径
      */
    void UpdatePackage(std::string diffJson , std::string   diffPackagePath);
private:
    //文件夹遍历
    bool traverseDir(const char* path) ;
    bool getDiff(Json::Value& localJson,Json::Value& remoteJson,Json::Value&  diffjson) ;
    void copy(Json::Value& diffJson, std::string& dst_path);
    void updatePackage(Json::Value& diffJson , std::string&  diffPackagePath);
public:
    //std::string rootdir ;
    std::vector<std::string> subRootDir;
private:

    DefaultCallBack pfunc ;
    Json::Value* pointJsonDir;
    Json::Value  jsonDirOutput;
};


void parseJsonArray(std::string& jsonpath,std::vector<std::string>& paths);





#endif
