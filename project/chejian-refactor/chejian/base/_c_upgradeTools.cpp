#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "base/json/json.h"
#include "base/md5/md5.h"
#include "_c_upgradeTools.h"



//void createJsonData(Json::Value& pointJsonDir ,const std::string&  rootdir ,const std::string&  filepath )
//{
//   // std::string tmppath = filepath.substr( rootdir.size() ,filepath.size()) ;
//    //pointJsonDir[tmppath.c_str() ] =Json::Value( MD5().FileDigest(filepath)) ;
//}

void createJsonDataAbsPath(Json::Value& pointJsonDir ,const std::string&  rootdir ,const std::string&  filepath )
{
    UNUSED(rootdir);
    pointJsonDir[filepath.c_str() ] =Json::Value( MD5().FileDigest(filepath)) ;
}

static int CreatDir(char *pszDir);
static std::string formatingPath(const char *path);
static int CheckDir(std::string Path);
static std::string Getfilepath(const char *path, const char *filename);
static int copyFile(std::string src, std::string des);



DirProcess::DirProcess(std::string path){
    pointJsonDir = NULL ;
    subRootDir.push_back(formatingPath(path.c_str() ));
}

DirProcess::DirProcess(std::vector<std::string>& pathArray)
{
    pointJsonDir = NULL;
    for (unsigned int i = 0; i < pathArray.size() ; ++i)
    {
        subRootDir.push_back(formatingPath(pathArray[i].c_str()));
    }
}

void DirProcess::COPY(std::string diffstr, string dst_path)
{
    Json::Value diffjson;
    Json::Reader rd;
    rd.parse(diffstr ,diffjson) ;
    this->copy(diffjson ,dst_path );
}
void DirProcess::copy(Json::Value& diffJson, string& dstPath)
{
    //mkdir -p
    std::string dst_path = formatingPath(dstPath.c_str() ) ;
    CheckDir(dst_path) ;
    Json::Value::Members mem = diffJson.getMemberNames();
    for (auto iter = mem.begin(); iter != mem.end(); iter++)
    {
        string subPath =  (*iter) ;
        string newpath = dst_path+subPath ;
        string dirpath = newpath ;
        size_t pos  = newpath.rfind("/") ;
        if( pos!=string::npos )
        {
            dirpath = newpath.substr(0,pos) ;
            //std::cout<< newpath.size() << ":"<<pos<<"="<<dirpath<<std::endl;
        }
        CheckDir(dirpath ) ;
        copyFile( subPath , newpath);
    }
    string tarpath = dst_path.substr(0,dst_path.size() -1) ;
    std::string tarStr = "tar zcvf "+tarpath+".tar.gz "+tarpath;
    printf("cmd:%s\n",tarStr.c_str());
    system(tarStr.c_str());
}
void DirProcess::UpdatePackage(std::string diffstr , std::string   diffPackagePath)
{
    Json::Value diffJson;
    Json::Reader rd;
    rd.parse(diffstr ,diffJson) ;
    updatePackage(  diffJson ,    diffPackagePath) ;
}
void DirProcess::updatePackage(Json::Value& diffJson , std::string&  diffPackagePath)
{
    std::string dst_path = formatingPath(diffPackagePath.c_str() ) ;
    //CheckDir(dst_path) ;
    Json::Value::Members mem = diffJson.getMemberNames();
    for (auto iter = mem.begin(); iter != mem.end(); iter++)
    {
        string subPath =  (*iter) ;
        std::string newpath = dst_path + subPath ;
        string dirpath = newpath   ;
        size_t pos  = newpath.rfind("/") ;
        if( pos!=string::npos )
        {
            dirpath = newpath.substr(0,pos) ;
           // std::cout<< newpath.size() << ":"<<pos<<"="<<dirpath<<std::endl;
            std::cout<<dirpath<<std::endl;
        }
        CheckDir(dirpath ) ;
        copyFile(  newpath,subPath );
    }
}

std::string DirProcess::buildMd5MsgMulti(){
    this->pfunc = createJsonDataAbsPath ;
    this->pointJsonDir =  &(this->jsonDirOutput) ;
    for(unsigned int i = 0 ; i < this->subRootDir.size() ; i++ )
    {
        std::string rootdir = this->subRootDir[i];
        traverseDir( rootdir.c_str()  )  ;
    }
    return this->jsonDirOutput.toStyledString();

}



bool DirProcess::getDiff(Json::Value& localJson,Json::Value& remoteJsondir,Json::Value& base)
{
    bool retcode = false ;

    Json::Value::Members mem = localJson.getMemberNames();
    for (auto iter = mem.begin(); iter != mem.end(); iter++)
    {
        //std::cout<<*iter<<"="<<localJson[*iter].asString()<<std::endl;
        //std::cout<<remoteJsondir[*iter].asString()<<std::endl;
        string strLocal = localJson[*iter].asString() ;
        string strRemote = remoteJsondir[*iter].asString();
        if( strLocal != strRemote )
        {
            base[*iter] = strLocal ;
            retcode = true ;
        }

    }
    return retcode ;
}

bool DirProcess::getDiffWithStr(std::string& localStr ,std::string& remoteStr,std::string& diff)
{
    Json::Value localJson,remoteJson;
    Json::Reader rd;
    rd.parse(remoteStr ,remoteJson) ;
    rd.parse(localStr,localJson);
    Json::Value base ;
    bool retcode = getDiff( localJson,remoteJson,base) ;
    diff = base.toStyledString();
    return retcode;
}



bool DirProcess::traverseDir(const char* path)
{
    DIR *dir;
    struct dirent *dirinfo;
    struct stat statbuf;
    //char filepath[256] = {0};
    lstat(path, &statbuf);

    if (S_ISREG(statbuf.st_mode))//判断是否是常规文件
    {
    //    std::cout<<"file:"<<path<<std::endl;
        string filepath = path ;
        this->pfunc(*pointJsonDir,"",filepath);
    }
    else if (S_ISDIR(statbuf.st_mode))//判断是否是目录
    {
        if ((dir = opendir(path)) == NULL)
            return 1;

        while ((dirinfo = readdir(dir)) != NULL)
        {
            if (strcmp(dirinfo->d_name, ".") == 0 || strcmp(dirinfo->d_name, "..") == 0)//判断是否是特殊目录
            continue;
            string dirname =   dirinfo->d_name ;
            std::string  filepath = Getfilepath(path, dirinfo->d_name);
            lstat(filepath.c_str(), &statbuf);
            bool isdir = S_ISDIR(statbuf.st_mode) ;
         //   std::cout<< "path:" <<  filepath <<"  dirname:"<<dirname <<" IS_DIR:"<< S_ISDIR(statbuf.st_mode) <<std::endl;
            if(isdir ){
                traverseDir(filepath.c_str() );
            }
            else{
                this->pfunc(*pointJsonDir,"",filepath);
            }
        }
        closedir(dir);
    }
    return 0;
}


////////////////////////////////////////////////////////////////////////////////

static std::string formatingPath(const char* path)
{
    string rootdir = path;
    if(rootdir.size() > 0 && rootdir.at(rootdir.size() -1 ) != '/' ) rootdir+="/";
    return rootdir;
}
static int CheckDir(std::string Path)
{

    if (access(Path.c_str(), 0) != 0)
    {
        char c_Path[2048] = { 0 };
        sprintf(c_Path,"%s", Path.c_str());
        printf("creat path:%s\n",Path.c_str());
        CreatDir(c_Path);
    }else {
         printf("is path:%s\n",Path.c_str());
    }
    return 1;
}

static std::string Getfilepath(const char *path, const char *filename)
{
    return formatingPath(path)+filename;
}

static int copyFile(std::string src, std::string des)
{
    printf("copyFile %s >> %s   ",src.c_str(),des.c_str());

    int nRet = 0;
    FILE* pSrc = NULL, *pDes = NULL;
    pSrc = fopen(src.c_str(), "r");
    pDes = fopen(des.c_str(), "w+");


    if (pSrc && pDes)
    {
        int nLen = 0;
        char szBuf[1024] = {0};
        while((nLen = fread(szBuf, 1, sizeof szBuf, pSrc)) > 0)
        {
            fwrite(szBuf, 1, nLen, pDes);
        }
        printf("\033[32m OK \033[0m\n");
    }
    else
    {
        nRet = -1;
        printf("\033[31m ERR\033[0m\n");
    }


    if (pSrc)
        fclose(pSrc), pSrc = NULL;

    if (pDes)
        fclose(pDes), pDes = NULL;

    return nRet;
}

static int CreatDir(char *pszDir)
{
    int i = 0;
    int iRet;
    int iLen = strlen(pszDir);
    if (pszDir[iLen - 1] != '\\' && pszDir[iLen - 1] != '/')
    {
        pszDir[iLen] = '/';
        pszDir[iLen + 1] = '\0';
    }
    for (i = 0; i <= iLen; i++)
    {
        if ((pszDir[i] == '\\' || pszDir[i] == '/')&&i!=0)
        {
            pszDir[i] = '\0';
            iRet = access(pszDir, 0);
            if (iRet != 0)
            {
                iRet = mkdir(pszDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                if (iRet != 0)
                {
                    return -1;
                }
            }
            //支持linux,将所有\换成/
            pszDir[i] = '/';
        }
    }
    return 0;
}

void  parseJsonArray(std::string& jsonpath,std::vector<std::string>& paths)
{
    paths.clear();

    Json::Value arrayObj ;
    Json::Reader rd;
    rd.parse(jsonpath ,arrayObj) ;
    for (unsigned int i=0; i<arrayObj.size(); i++)
    {
        string pathitem = arrayObj[i].asString() ;
        std::cout<< pathitem<<std::endl;
        if(pathitem.size() > 0 ){
            paths.push_back(pathitem);
        }
    }
}
