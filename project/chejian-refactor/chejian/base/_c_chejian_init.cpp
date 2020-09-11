#include "base/_c_chejian_init.h"
#include "base/baseInc.h"

_c_white_list_center g_whitelist ;
#define WHITE_FILE "/opt/vehicle/program/CheJianConfig/whiteList.json"

void coreDumpFileInit(bool isopen)
{
    string option = " -disable ";
    if (isopen)
    {
        option = "  -init ";
    }
    string installPath =INSTALL_PATH;
    installPath +=  "processCoredump.sh   " ;
    std::string  cmd = "chmod +x "+installPath + " && " + installPath+option+"  && " +installPath + " -clear ";
    printf("cmd:%s\n",cmd.c_str() );
    int val = system(cmd.c_str());
    printf("cmd:%s;\n retcode:%d \n",cmd.c_str(),val );
}

void coreDumpFileClear()
{
    string installPath =INSTALL_PATH;
    installPath +=  "processCoredump.sh   " ;
    std::string  cmd =   installPath + " -clear ";
    printf("cmd:%s \n",cmd.c_str() );
    system(cmd.c_str());
}
void whiteListInit()
{
    g_whitelist.readJsonWhiteList(WHITE_FILE) ;
    std::cout<<"白名单初始化----------"<<std::endl;
    g_whitelist.printWhiteList();
}
std::string _c_white_list_center::DefaultConfig()
{
    Json::Value root;
    root["ShuoMing"]="httpPermit  用于添加http ip地址白名单 , thirdService 用于添加 第三方服务的ip地址白名单" ;
    root["httpPermit"]=Json::arrayValue ;
    root["httpPermit"].append("127.0.0.1");
    root["thirdService"] =Json::arrayValue ;
  //  std::cout<<root.toStyledString()<<std::endl;
    return root.toStyledString() ;
}

int _c_white_list_center::readJsonWhiteList(std::string path)
{
    std::ifstream ifs;
    ifs.open( path.c_str() );
    if (ifs.is_open())
    {
        std::cout<<"配置文件不存在 读取白名单失败！"<<std::endl;
    }else{
        //文件 不存在 , 输出流写入文件
        std::cout<<"创建默认白名单"<<std::endl;
        std::ofstream ofs;
        ofs.open(path);
        if( ofs.is_open() )
        {
            std::cout<<"请填写白名单并重启"<<WHITE_FILE <<std::endl;
            ofs<<DefaultConfig() ;
        }
        ofs.close();
        return  0 ;
    }
    Json::Value val;
    Json::Reader reader;

    if (!reader.parse(ifs, val)) {
        ifs.close();
        return -1;
    }
    map<string,vector<string> >::iterator it;
    for(it = whitelist.begin() ; it != whitelist.end() ; it++){
        string keyname = it->first;
        int sz = val[keyname.c_str()].size();
        for (int i = 0; i < sz; ++i) {
            it->second.push_back( val[keyname.c_str()][i].asString() );
        }
    }
    ifs.close();
    return 0 ;
}

int _c_white_list_center::printWhiteList()
{
    map<string,vector<string> >::iterator it;
    for(it = whitelist.begin() ; it != whitelist.end() ; it++){
        string keyname = it->first;
        std::cout<<"keyname:" <<keyname <<std::endl;
        std::vector<std::string>& item=it->second ;
        for( int i =0 ;i< item.size() ; i++ )
        {
            std::cout<<item[i]<<std::endl;
        }
    }
    return 0;
}

int _c_white_list_center::isInWhite(std::string ipaddr,std::string keyname)
{
    if (ipaddr.size() == 0 ) return  false ;
    std::vector<std::string> item = whitelist[keyname] ;

//    printf("size:%d,item_size:%d\n",whitelist.size() ,whitelist[keyname].size() );

 //   printWhiteList();
    std::cout<<item.size() <<std::endl;
    for(unsigned int i =0 ;i< item.size() ; i++ )
    {
        std::cout<<item[i]<<std::endl;
       if(ipaddr == item[i] )
       {
           return true ;
       }
    }
    return false ;
}

void test_print()
{
    _c_white_list_center lc;
    lc.readJsonWhiteList("/home/yuyang/develop/cplusplus/test/testwhite.json") ;
    lc.printWhiteList();
}
