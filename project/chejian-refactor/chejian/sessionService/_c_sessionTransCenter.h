#ifndef _C_SESSIONTRANSCENTER_H
#define _C_SESSIONTRANSCENTER_H
#include "base/baseInc.h"
#include "base/_c_session.h"
#include "config/_c_configCenter.h"

class _c_sessionTransCenter {
public:
    static _c_sessionTransCenter *createdCenter(PDEVICE_BOOT_CONFIG bootConfig,_c_configCenter *pConfig);
    _c_sessionTransCenter();
    virtual ~_c_sessionTransCenter(){}
    bool startSessionTransCenter();
    virtual bool queryData();
    virtual bool queryReponseData();
    virtual bool pushQueue(_c_session *pSession);
    virtual bool pushDbQueue(_c_dbTask *pDbTask);
    virtual bool reponseData(_c_session *pSession);
    virtual std::string getBaseTableName(){return "vehicle_info";}
    virtual bool clearData();

    bool isClose();
    bool clearDataOpen();
    bool clearDataClose();

    void setIsOpenFilterJianYanJiGou(std::string* isOpen ){
        OpenFilterJianYanJiGou = isOpen ;
    }
    void setJianYanJiGou(std::vector<JYJG>* jyjg ){
        __JYJG = jyjg ;
    }
    bool  filterJyjg(std::string strJyjg) {
        for(unsigned int i = 0 ;i < __JYJG->size() ; i++ )
        {
            JYJG&  jg = (*__JYJG)[i] ;
            if ( jg.bh ==  strJyjg ){
                return true ;
            }
        }
        return  ( __JYJG->size() == 0 ) || false ;
    }
    bool getIsOpenFilterJianYanJiGou(){
        return *OpenFilterJianYanJiGou == "true" ;
    }
    threadInfo *getSessionTransQueryThread() {return &SessionTransQueryThread;}
    threadInfo *getSessionTransReponseThread() {return &SessionTransReponseThread;}

    void setWorkMode(WorkMode mode);
    WorkMode getWorkMode();


protected:
    unsigned int _timeOutMilliseconds;
    unsigned int _threadSleepMilliseconds;
    WorkMode workMode;
    std::string *OpenFilterJianYanJiGou ;
    std::vector<JYJG>* __JYJG;

private:
//    std::thread *__pSessionTransQueryThread;
//    std::thread *__pSessionTransReponseThread;

    threadInfo SessionTransQueryThread;
    threadInfo SessionTransReponseThread;

    bool __clearData;
    unsigned int __threadSleep;
};
#endif // _C_SESSIONTRANSCENTER_H
