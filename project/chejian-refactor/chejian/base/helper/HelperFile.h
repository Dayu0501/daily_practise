#ifndef HELPERFILE_H
#define  HELPERFILE_H
#include <string>
#include <vector>
#include <ctime>

//#pragma  warning(disable:4996)
namespace hl
{
std::string ownerfolder();
std::string higher_level_folder(std::string path);
bool pathexist(std::string path);
int filelen(std::string path);
std::time_t file_modify_time(std::string path);
std::time_t file_create_time(std::string path);
std::string pathfolder(std::string path);
std::string pathname(std::string path);
std::string pathext(std::string path);
std::string pathname_no_ext(std::string path);
bool creatdir(std::string dirpath);
bool isdir(std::string path);
bool delpath(std::string path);
bool enumfiles(std::string folder,std::vector<std::string>& paths,bool isincfolder=true,bool isincfiles=true);\
bool enumfiles_all(std::string folder,std::vector<std::string>& paths);
}

#endif
