#ifndef RECORDSOAPREQUESTINDB_H
#define RECORDSOAPREQUESTINDB_H


#include "base/baseTool.h"
#include "db/dbquery/dbinterface.h"
class RecordSoapRequestInDB:public _c_dbTask{
public:
    std::string todayRequestTimes ;
    std::string todayPermitTimes ;
    std::string maxSoapRequest ;
    std::string lastestUpdateTime ;
    std::string today ;
    std::string otherInfo ;
    RecordSoapRequestInDB(){
        tableName = "RecordSoapRequestTimes";
        memberVector.push_back({"todayRequestTimes", "todayRequestTimes", &todayRequestTimes, "todayRequestTimes", DBOPTION_DEFAULT});
        memberVector.push_back({"maxSoapRequest", "maxSoapRequest", &maxSoapRequest, "maxSoapRequest", DBOPTION_DEFAULT});
        memberVector.push_back({"lastestUpdateTime", "lastestUpdateTime", &lastestUpdateTime, "lastestUpdateTime", DBOPTION_DEFAULT});
        memberVector.push_back({"today", "today", &today, "today", DBOPTION_DEFAULT});
        memberVector.push_back({"otherInfo", "otherInfo", &otherInfo, "otherInfo", DBOPTION_DEFAULT});
        memberVector.push_back({"todayPermitTimes", "todayPermitTimes", &todayPermitTimes, "todayPermitTimes", DBOPTION_DEFAULT});
    }

    virtual std::string getSql(){
        //TODO
        // 1. 如果没有记录 则插入
        // 2. 如果有记录则 update
        bool isExist = false ;
        Json::Value retjs = queryRecordSoapTimes() ;
        if(retjs.size() > 0 ){
            std::string today = retjs[(unsigned int )0]["today"].asString();

            std::cout << "++++++++++++++++++++++++++++++++++++++ today:"<<today <<  "dangtianriqi:" <<baseTool::getDangTianRiQi() <<  std::endl;
            if ( today == baseTool::getDangTianRiQi() ){
                isExist =  true  ;
            }
        }
        std::string  sql = "";
        if( !isExist ){
            sql = _c_dbTask::getSql();
        }else{
            today = baseTool::getDangTianRiQi();
            lastestUpdateTime =baseTool::getCurTime();
            sql = "update RecordSoapRequestTimes set todayRequestTimes ='"+todayRequestTimes+"' , maxSoapRequest = '"+
                    maxSoapRequest+"', lastestUpdateTime='"+lastestUpdateTime+"' , otherInfo='"+otherInfo+"' , todayPermitTimes='"+
                    todayPermitTimes+"' where today = '"+today+"'";
        }
        return sql;
    }
};

class RecordSoapRequestTimes {
public:
   unsigned int  currentDayRequestTimes = 0  ;
   unsigned int  permitTimes = 0 ;
   unsigned int  *maxSoapRequest  = NULL;
   bool          isOpenCheck  = true ;
   bool          enableFlag  = true ;
   // unsigned int  unRecordTimes = 0 ;
   void clear(){
        currentDayRequestTimes = 0 ;
        permitTimes = 0 ;
        enableFlag = true ;
   }
   void disableToday(){
        enableFlag = false ;
   }

   //从数据库记录里拿出来
   void init(  unsigned int*  maxTimes ,bool isOpenCheck = true){
       maxSoapRequest = maxTimes ;
       this->isOpenCheck = isOpenCheck ;
   }

   unsigned int getCurrentDayRequestTimes(){
       return currentDayRequestTimes;
   }

   void addCount(){
        currentDayRequestTimes ++ ;
   }
   void addPermitCount(){
        permitTimes ++ ;
   }

   bool isOk(){
      // std::cout<< "#################isOk####################"<<std::endl ;
       bool permit = check() > 0 ;
       if (permit){
           addPermitCount();
       }
       addCount();
       return permit ;
   }

   std::string checkErrmsg(int retcode){
        std::string retmsg = "soap 当天请求次数,检测正常";
        switch(retcode)
        {
            case -1:
               retmsg = "soap 请求数超出限定值" ;
            break;
            case -2:
                retmsg = " 返回码出现 code =12 ,达到平台上限要求";
                break;
            case -3:
                retmsg = " soap 阈值,正在初始化 ...";
                break;
            default:
            break;
        }
        return retmsg ;
   }

   int check(){
       if (isOpenCheck) {
           if (!maxSoapRequest) return -3;
           if (*maxSoapRequest <= currentDayRequestTimes) return -1;
           if ( !enableFlag ) return -2 ;
       }
       return 1 ;
   }

   bool needFree(){
       return false ;
   }

   RecordSoapRequestTimes(){
   }
   RecordSoapRequestInDB* generateRecordSoapRequestInDB(){
       RecordSoapRequestInDB* p =   new RecordSoapRequestInDB();
       p->todayRequestTimes = ns_baseTool::number2str<unsigned int>(currentDayRequestTimes,"%u");
       p->maxSoapRequest = ns_baseTool::number2str<unsigned int >(*maxSoapRequest,"%u") ;
       p->today =baseTool::getDangTianRiQi();
       p->lastestUpdateTime =  baseTool::getCurTime() ;
       p->otherInfo = checkErrmsg(check() );
       p->todayPermitTimes = ns_baseTool::number2str<unsigned int>(permitTimes,"%u");

       return p ;
   }

};


#endif
