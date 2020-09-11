#include "dbinterface.h"
#include "db/mysql/MySQL_DB.h"
#include "base/json/json.h"
#include "db_photoinfo.h"
#include "db_vehicleinfo.h"
#include "db_passper.h"
#include "base/baseTool.h"
#include "base/dataCenter.h"
#include "base/soapApi/RecordSoapRequestInDB.h"

Json::Value getPhotoInfoVectorJson(std::string vehicleId)
{
    db_photoInfo dbPhotoInfo;
    std::vector<std::string> WhereVector;
    PDB_PARAM pConfig = loadSystemConfig()->getStructDbParam();

    WhereVector.push_back("and cheLiangUid ='"+vehicleId+"'");

    dbPhotoInfo.query("photo_info", &WhereVector, pConfig->strHost.c_str(), pConfig->port, pConfig->strUserName.c_str(), pConfig->strPassword.c_str(), pConfig->strDbName.c_str());

    return dbPhotoInfo.getVectorJson();
}

Json::Value getPhotoInfoOrderJson()
{
    db_photoInfo dbPhotoInfo;

    return dbPhotoInfo.getOrderJson();
}

Json::Value getVehicleInfoVectorJson(std::string tableName, std::string chePai,std::string startTime,std::string endTime)
{
    UNUSED(chePai);
    db_vehicleInfo dbVehicleInfo;
    std::vector<std::string> WhereVector;
    PDB_PARAM pConfig = loadSystemConfig()->getStructDbParam();

    WhereVector.push_back("and inDbTime > '"+startTime+"'");
    WhereVector.push_back("and inDbTime < '"+endTime+"'");
    WhereVector.push_back("order by inDbTime desc");
    WhereVector.push_back("limit 0,300");
    dbVehicleInfo.query(tableName, &WhereVector, pConfig->strHost.c_str(), pConfig->port, pConfig->strUserName.c_str(), pConfig->strPassword.c_str(), pConfig->strDbName.c_str());
    return dbVehicleInfo.getVectorJson();
}

Json::Value getVehicleInfoOrderJson()
{
    db_vehicleInfo dbVehicleInfo;

    return dbVehicleInfo.getOrderJson();
}

Json::Value getPassListInfoOrderJson()
{
    db_passPer db;
    return db.getOrderJson();
}

Json::Value getPassListInfoVectorJson(std::vector<std::string> zplxVector,std::string startTime,std::string endTime)
{
    db_passPer db;
    std::vector<std::string> WhereVector;
    PDB_PARAM pConfig = loadSystemConfig()->getStructDbParam();

    std::string categoryStr = " ";

    for (unsigned int i = 0; i < zplxVector.size(); i++) {
        categoryStr += "'"+zplxVector[i]+"',";
    }
    categoryStr.pop_back();

    WhereVector.push_back("and jieGuo in ('1')");
    WhereVector.push_back("and zhaoPianLeiXing in ("+categoryStr+")");
    WhereVector.push_back("and inDbTime > '"+startTime+"'");
    WhereVector.push_back("and inDbTime < '"+endTime+"'");

    db.query("", &WhereVector, pConfig->strHost.c_str(), pConfig->port, pConfig->strUserName.c_str(), pConfig->strPassword.c_str(), pConfig->strDbName.c_str());

    return db.getVectorJson();
}

Json::Value getPassInfoOrderJson()
{
    db_passPer db;
    return db.getOrderJson();
}

Json::Value getPassInfoVectorJson(std::string zplx,std::string startTime,std::string endTime)
{
    db_passPer db;
    std::vector<std::string> WhereVector;
    PDB_PARAM pConfig = loadSystemConfig()->getStructDbParam();

    WhereVector.push_back("and jieGuo in ('1','5')");
    WhereVector.push_back("and zhaoPianLeiXing in ('"+zplx+"')");
    WhereVector.push_back("and inDbTime > '"+startTime+"'");
    WhereVector.push_back("and inDbTime < '"+endTime+"'");


    db.query("", &WhereVector, pConfig->strHost.c_str(), pConfig->port, pConfig->strUserName.c_str(), pConfig->strPassword.c_str(), pConfig->strDbName.c_str());

    return db.getVectorJson();
}

Json::Value getPhotoInfoVectorJsonByReason(std::string category,std::string reason,std::string startTime,std::string endTime)
{
    db_photoInfo dbPhotoInfo;
    std::vector<std::string> WhereVector;
    PDB_PARAM pConfig = loadSystemConfig()->getStructDbParam();

    WhereVector.push_back("and zhaoPianLeiXing = '"+category+"'");
    WhereVector.push_back("and shuoMing = '"+reason+"'");
    WhereVector.push_back("and inDbTime > '"+startTime+"'");
    WhereVector.push_back("and inDbTime < '"+endTime+"'");
    WhereVector.push_back("order by inDbTime desc");

    dbPhotoInfo.query("photo_info", &WhereVector, pConfig->strHost.c_str(), pConfig->port, pConfig->strUserName.c_str(), pConfig->strPassword.c_str(), pConfig->strDbName.c_str());

    return dbPhotoInfo.getVectorJson();
}




class db_jiNanTouPing:public dbBaseClass{
public:

    std::string uuid;
    std::string shenFenZheng;
    std::string jsonMsg;

    dbBaseClass *getDbClass(){
        return new db_jiNanTouPing();
    }

    db_jiNanTouPing(){
        memberVector.push_back({"UUID", "UUID","UUID", &uuid,true});
        memberVector.push_back({"shenFenZheng", "shenFenZheng","shenFenZheng", &shenFenZheng,true});
        memberVector.push_back({"jsonMsg", "jsonMsg","jsonMsg", &jsonMsg,true});
    }
};

class db_jiNanTouPingIsSend:public _c_dbTask{
public:
    virtual ~db_jiNanTouPingIsSend(){} //用于释放内存（必须）

    db_jiNanTouPingIsSend(){
        tableName = "jiNanTouPing_info";
    }

    virtual std::string getSql()
    {
        std::string sqlStr = "update jiNanTouPing_info set isSend='1' where UUID='"+uuid+"'";

        return sqlStr;
    }

};


class db_jiNanYouXianTou:public dbBaseClass{
public:
    virtual ~db_jiNanYouXianTou(){} //用于释放内存（必须）
    std::string shenFenZheng_;
    dbBaseClass *getDbClass(){
        return new db_jiNanYouXianTou();
    }

    virtual std::string getSql(std::vector<std::string> *pWhereVector,std::string table)
    {
        UNUSED(pWhereVector);UNUSED(table);
        std::string sqlStr = "select uuid from chaYanYuan_info where inDbTime > '"+baseTool::getDangTianRiQi()+"' and shenFenZheng = '"+shenFenZheng_+"' limit 0,1";

        return sqlStr;
    }

    static bool checkIsGreenChan( std::string shenFenZheng)
    {
        db_jiNanYouXianTou dbTask;
        std::vector<std::string> WhereVector;
        PDB_PARAM pConfig = loadSystemConfig()->getStructDbParam();
        dbTask.shenFenZheng_ = shenFenZheng;

        dbTask.query("chaYanYuan_info", &WhereVector, pConfig->strHost.c_str(), pConfig->port, pConfig->strUserName.c_str(), pConfig->strPassword.c_str(), pConfig->strDbName.c_str());
        if(dbTask.queryVector.size()>0)
        {
            return true;
        }

        return false;
    }

};

bool checkGreenChannelByShenFenZheng(std::string shenFenZheng)
{

    return db_jiNanYouXianTou::checkIsGreenChan(shenFenZheng);
}


Json::Value queryJiNanTouPingMsgBySheBeiId(std::string sheBeiId)
{
    std::string dangTianRiQi = baseTool::getDangTianRiQi();
    db_jiNanTouPing jiNanTouPing;
    PDB_PARAM pConfig = loadSystemConfig()->getStructDbParam();
    std::vector<std::string> WhereVector;
    WhereVector.push_back("and isSend = '0'");
    WhereVector.push_back("and inDbTime > '"+dangTianRiQi+"'");
    WhereVector.push_back("and shenFenZheng in (select shenFenZheng from chaYanYuan_info where sheBeiId = '"+sheBeiId+"' and inDbTime > '"+dangTianRiQi+"')");
    WhereVector.push_back("order by inDbTime");
    WhereVector.push_back("limit 0,1");

    jiNanTouPing.query("jiNanTouPing_info", &WhereVector, pConfig->strHost.c_str(), pConfig->port, pConfig->strUserName.c_str(), pConfig->strPassword.c_str(), pConfig->strDbName.c_str());

    Json::Value dbDate = jiNanTouPing.getVectorJson();
    if(dbDate.size() > 0)
    {
        if(jiNanTouPing.queryVector.size() > 0)
        {
            if(jiNanTouPing.queryVector[0]->memberVector.size() > 0)
            {
                db_jiNanTouPingIsSend *pSetIsSend = new db_jiNanTouPingIsSend();
                pSetIsSend->uuid = jiNanTouPing.queryVector[0]->memberVector[0].value->c_str();
                pSetIsSend->dbWork();
            }
        }
    }

    return jiNanTouPing.getVectorJson();
}

class db_RecordSoapRequest:public dbBaseClass{
public:
    std::string todayRequestTimes ;
    std::string maxSoapRequest ;
    std::string lastestUpdateTime ;
    std::string today ;
    std::string todayPermitTimes ;
    std::string otherInfo ;
    dbBaseClass *getDbClass(){
        return new db_RecordSoapRequest();
    }
    db_RecordSoapRequest(){
        memberVector.push_back({"todayRequestTimes", "todayRequestTimes","todayRequestTimes", &todayRequestTimes,true});
        memberVector.push_back({"maxSoapRequest", "maxSoapRequest","maxSoapRequest", &maxSoapRequest,true});
        memberVector.push_back({"lastestUpdateTime", "lastestUpdateTime","lastestUpdateTime", &lastestUpdateTime,true});
        memberVector.push_back({"today", "today","today", &today,true});
        memberVector.push_back({"todayPermitTimes", "todayPermitTimes","todayPermitTimes", &todayPermitTimes,true});
        memberVector.push_back({"otherInfo", "otherInfo","otherInfo", &otherInfo,true});
    }
};
Json::Value queryRecordSoapTimes(int lastestCount )
{
    PDB_PARAM pConfig = loadSystemConfig()->getStructDbParam();
    std::vector<std::string> WhereVector;
    if (lastestCount > 10  ) lastestCount = 10 ;
    if (lastestCount < 1  ) lastestCount = 1 ;
    char buf[20] = {0};
    sprintf(buf,"limit 0,%d",lastestCount) ;
    WhereVector.push_back(" order by today desc ");
    WhereVector.push_back(buf);
    db_RecordSoapRequest record;
    record.query("RecordSoapRequestTimes", &WhereVector, pConfig->strHost.c_str(), pConfig->port, pConfig->strUserName.c_str(), pConfig->strPassword.c_str(), pConfig->strDbName.c_str());
    return record.getVectorJson();
}
