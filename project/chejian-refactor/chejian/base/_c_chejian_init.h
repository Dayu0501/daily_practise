#ifndef _C_CHEJIAN_INIT_H
#define _C_CHEJIAN_INIT_H

#include "base/baseInc.h"

class _c_white_list_center{
public:
    _c_white_list_center(){
        whitelist["httpPermit"] = std::vector<std::string>();
        whitelist["thirdService"] = std::vector<std::string>();
    }
    std::string  DefaultConfig();
    int readJsonWhiteList(std::string path);
    int printWhiteList();
    int isInWhite(std::string ipaddr,std::string keyname);
public:
    map<std::string,std::vector<std::string > > whitelist;
    Json::Value val;
};

extern _c_white_list_center g_whitelist ;


//coredump file init
void coreDumpFileInit(bool isopen);
void coreDumpFileClear();
void whiteListInit();
void test_print();


#endif
