
#include "_c_vehicle_DongGuan.h"
#include "base/baseTool.h"
#include "alg/_c_algTaskCenter.h"

bool _c_vehicle_DongGuan::loadAlgTask()
{
    _c_vehicle::loadAlgTask();
    string algname[] = {"eH0111" , "eH0112" , "eH0113" };
    PicType algcode[] = {eH0111, eH0112, eH0113 } ;
    string paremeterName[] = {"&zpzl=0111&zpxh=19&zpcc=200" , "&zpzl=0112&zpxh=24&zpcc=200" , "&zpzl=0113&zpxh=21&zpcc=200" };

    //http://213.150.90.17:9080/pnweb/vehisphoto.vehis?method=getVehIsPhotoBlob&lsh=19103044003805047398&zpzl=0111&zpxh=19&zpcc=200
    //http://213.150.90.17:9080/pnweb/vehisphoto.vehis?method=getVehIsPhotoBlob&lsh=19103044003805047398&zpzl=0112&zpxh=24&zpcc=200
    //http://213.150.90.17:9080/pnweb/vehisphoto.vehis?method=getVehIsPhotoBlob&lsh=19103044003805047398&zpzl=0113&zpxh=21&zpcc=200

    string ipaddr="213.150.90.17";
    string port = "9080" ;
   for(unsigned int i = 0  ; i < sizeof(algcode)/sizeof(PicType) ; i++ )
    {
        _c_photo *ph = new _c_photo();
        ph->loadUuid();
        ph->algCode = "H"+std::to_string(i+1);
        ph->photoUrl = "http://"+ipaddr+":"+port + "/pnweb/vehisphoto.vehis?method=getVehIsPhotoBlob&lsh="+liuShuiHao+paremeterName[i];
        ph->cheLiangUid = uuid;
        ph->algTaskInit();
        ph->localPath = "/"+baseTool::getDangTianRiQi()+"/"+ algname[i] ;//zhaoPianClassVector[i]->algCode;
        ph->localPath += "_"+haoPaiHaoMa;
        ph->localPath += "_"+cheLiangShiBieDaiHao;
        algTaskVector.push_back(ph);
        zhaoPianClassVector.push_back(ph);
        LOG(SOAP,INFO,"URL:[%s] LOCALPATH:[%s]",ph->photoUrl.c_str(),ph->localPath.c_str() );
    }
    return true ;
}
