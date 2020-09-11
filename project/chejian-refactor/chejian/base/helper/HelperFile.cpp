#include "HelperFile.h"
#include <algorithm>
#include <memory.h>
#include <fstream>
#include <regex>
#ifdef __linux
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#else
#include <windows.h>
#include "shlwapi.h"
#include <ShlObj.h>
#pragma comment(lib,"Shlwapi.lib")
#endif
namespace hl
{
std::string ownerfolder()
{
#ifdef __linux
    char path[1024]={0};
    int cnt = readlink("/proc/self/exe", path, 1024);
    if(cnt < 0|| cnt >= 1024)
        return "";
    for(int i = cnt; i >= 0; --i)
    {
        if(path[i]=='/')
        {
            path[i + 1]='\0';
            break;
        }
    }
    return path;
#else
    CHAR path[MAX_PATH];
    ::GetModuleFileNameA(NULL, path, MAX_PATH);
    int cnt = strlen(path);
    for (int i = cnt; i >= 0; --i)
    {
        if (path[i] == '\\')
        {
            path[i + 1] = '\0';
            break;
        }
    }
    return path;
#endif
}
std::string higher_level_folder(std::string path)
{
	if(path == "" || path == "/" || path == "\\")
		return path;
#ifdef __linux
	char spliter = '/';
	if (path[path.length() - 1] == '/')
		path[path.length() - 1] = '\0';
#else
	char spliter = '\\';
	if (path[path.length() - 1] == '\\')
		path[path.length() - 1] = '\0';
#endif
	std::string::size_type pos=path.rfind(spliter);
	if (pos == std::string::npos)
 #ifdef __linux
        return "/";
 #else
        return "\\";
 #endif
	return path.substr(0,pos+1);
}
bool pathexist(std::string path)
{
#ifdef __linux
    struct stat buf;
    if(-1 == stat(path.c_str(),&buf))
        return false;
    return true;
#else
    return ::PathFileExistsA(path.c_str())==TRUE;
#endif
}
int filelen(std::string path)
{
    std::fstream in;
    in.open(path,std::ios::in|std::ios::binary);
    in.seekg(0,std::ios::end);
    int len=(int)in.tellg();
    in.close();
    return len;
}
std::time_t file_modify_time(std::string path)
{
#ifdef __linux
    struct stat buf;
    if(-1 == stat(path.c_str(),&buf))
        return 0;
    return buf.st_mtim.tv_sec;
#else
    FILETIME time;
    SYSTEMTIME systime;
    WIN32_FILE_ATTRIBUTE_DATA lpinf;
    GetFileAttributesExA(path.c_str(),GetFileExInfoStandard,&lpinf);
    FileTimeToLocalFileTime(&lpinf.ftLastWriteTime,&time);
    FileTimeToSystemTime(&time, &systime);
    struct tm time_tm;
    time_tm.tm_year = systime.wYear - 1900;
    time_tm.tm_mon = systime.wMonth - 1;
    time_tm.tm_mday = systime.wDay;
    time_tm.tm_hour = systime.wHour;
    time_tm.tm_min = systime.wMinute;
    time_tm.tm_sec = systime.wSecond;
    time_tm.tm_isdst = 0;
    return std::mktime(&time_tm);
#endif
}
std::time_t file_create_time(std::string path)
{
#ifdef __linux
    struct stat buf;
    if(-1 == stat(path.c_str(),&buf))
        return 0;
    return buf.st_ctim.tv_sec;
#else
    FILETIME time;
    SYSTEMTIME systime;
    WIN32_FILE_ATTRIBUTE_DATA lpinf;
    GetFileAttributesExA(path.c_str(),GetFileExInfoStandard,&lpinf);
    FileTimeToLocalFileTime(&lpinf.ftCreationTime,&time);
    FileTimeToSystemTime(&time, &systime);
    struct tm time_tm;
    time_tm.tm_year = systime.wYear - 1900;
    time_tm.tm_mon = systime.wMonth - 1;
    time_tm.tm_mday = systime.wDay;
    time_tm.tm_hour = systime.wHour;
    time_tm.tm_min = systime.wMinute;
    time_tm.tm_sec = systime.wSecond;
    time_tm.tm_isdst = 0;
    return std::mktime(&time_tm);
#endif
}
std::string pathfolder(std::string path)
{
	if (path == "" || path == "/" || path == "\\")
		return path;
#ifdef __linux
    char spliter='/';
#else
    char spliter='\\';
#endif
    std::string::size_type pos=path.rfind(spliter);
	if(pos == std::string::npos)
		return path;
    return path.substr(0,pos+1);
}
std::string pathname(std::string path)
{
#ifdef __linux
    char spliter='/';
#else
    char spliter='\\';
#endif
    std::string::size_type pos=path.rfind(spliter);
    return path.substr(pos+1);
}
std::string pathext(std::string path)
{
    std::string::size_type pos=path.rfind('.');
    if(pos==std::string::npos)
        return "";
    return path.substr(pos);
}
std::string pathname_no_ext(std::string path)
{
#ifdef __linux
    char spliter='/';
#else
    char spliter='\\';
#endif
    std::string::size_type pos=path.rfind(spliter);
    std::regex reg("\\.\\w{1,}$");
    return std::regex_replace(path.substr(pos+1),reg,"").c_str();
}
bool creatdir(std::string dirpath)
{
#ifdef __linux
    system(("mkdir -p "+dirpath).c_str());
    return hl::pathexist(dirpath);
#else
    int ret = SHCreateDirectoryExA(NULL,dirpath.c_str(),NULL);
    if(ret==ERROR_SUCCESS || ret==ERROR_FILE_EXISTS || ret==ERROR_ALREADY_EXISTS)
        return true;
    return false;
#endif
}
bool isdir(std::string path)
{
#ifdef __linux
    struct stat buf;
    if(-1 == stat(path.c_str(),&buf))
        return false;
    if(S_ISDIR(buf.st_mode))
        return true;
    return false;
#else
    if (path[path.length() - 1] == '\\')
        path[path.length() - 1] = '\0';
    bool retb=false;
    WIN32_FIND_DATAA wfd;
    HANDLE hFind = FindFirstFileA(path.c_str(), &wfd);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        if (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
            retb=true;
        FindClose(hFind);
    }
    return retb;
#endif
}
bool delpath(std::string path)
{
#ifdef __linux
    system(("rm -rf \""+path+"\"").c_str());
    return !hl::pathexist(path);
#else
    if(hl::isdir(path))
    {
        std::string _cmd="rd/s/q \""+path+"\"";
        system(_cmd.c_str());
    }
    else
    {
        std::string _cmd="del/f/s/q \""+path+"\"";
        system(_cmd.c_str());
    }
    return !hl::pathexist(path);
#endif
}
bool enumfiles(std::string folder,std::vector<std::string>& paths,bool isincfolder,bool isincfiles)
{
#ifdef __linux
    if(!hl::isdir(folder))
        return false;
    struct dirent* fileObj;
    DIR* dir=opendir(folder.c_str());
    if(NULL == dir)
        return false;
    while((fileObj=readdir(dir))!=NULL)
    {
        if( std::string(fileObj->d_name)[0] == '.')
            continue;
        char filePath[256]={0};
        if(folder[folder.size()-1] == '/')
            sprintf(filePath,"%s%s",folder.c_str(),fileObj->d_name);
        else
            sprintf(filePath,"%s/%s",folder.c_str(),fileObj->d_name);
        if(hl::isdir(filePath))
        {
            if(isincfolder)
                paths.push_back(filePath);
        }
        else
        {
            if(isincfiles)
                paths.push_back(filePath);
        }
    }
    closedir(dir);
    return true;
#else
    CHAR szFind[MAX_PATH];
    lstrcpyA(szFind, folder.c_str());
    if (szFind[strlen(szFind) - 1] != '\\')
        lstrcatA(szFind, "\\");
    lstrcatA(szFind, "*.*");
    WIN32_FIND_DATAA wfd;
    HANDLE hFind = FindFirstFileA(szFind, &wfd);
    if (hFind == INVALID_HANDLE_VALUE)
        return false;
    do
    {
        if (wfd.cFileName[0] == '.')
            continue;
        CHAR filePath[MAX_PATH] = { 0 };
        if (folder[folder.size() - 1] == '\\')
            sprintf(filePath, "%s%s", folder.c_str(),wfd.cFileName);
        else
            sprintf(filePath, "%s\\%s", folder.c_str(),wfd.cFileName);
        if (hl::isdir(filePath))
        {
            if (isincfolder)
                paths.push_back(filePath);
        }
        else
        {
            if (isincfiles)
                paths.push_back(filePath);
        }
    } while (FindNextFileA(hFind, &wfd));
    FindClose(hFind);
    return true;
#endif
}
bool enumfiles_all(std::string folder,std::vector<std::string>& paths)
{
    hl::enumfiles(folder,paths,false,true);
    std::vector<std::string> fs;
    hl::enumfiles(folder,fs,true,false);
    for(auto p : fs)
        enumfiles_all(p,paths);
    return true;
}
}
