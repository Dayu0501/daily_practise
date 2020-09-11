
#include "_c_vehicle_SuZhou.h"
#include "base/baseTool.h"
#include "alg/_c_algTaskCenter.h"

static string  suzhou_algname[]={"01","02","03","04","05","06","07","08","09"};
static PicType suzhou_algcode[]={eH0001,eH0002,eH0003,eH0004,eH0005,eH0006,eH0007,eH0008,eH0009};

// 7000  nginx 根目录 /home/java/new_chejian/web
bool _c_vehicle_SuZhou::loadAlgTask()
{
 //  _c_vehicle::loadAlgTask();

    string url = "http://"+baseTool::getLocalIp()+":7000/third_photo/";
   for(unsigned int i = 0  ; i < sizeof(suzhou_algcode)/sizeof(PicType) ; i++ )
    {
        string  strPhotoName = baseTool::getDangTianRiQi()+"/"+suzhou_algname[i]+"_"+this->liuShuiHao;
        _c_photo *ph = new _c_photo();
        ph->loadUuid();
        ph->algCode = suzhou_algname[i];
        ph->photoUrl = url + strPhotoName;
        ph->cheLiangUid = uuid;
        ph->algTaskInit();
        ph->localPath = strPhotoName+"_"+this->haoPaiHaoMa+"_"+this->cheLiangShiBieDaiHao;// "/"+baseTool::getDangTianRiQi()+"/"+ algname[i] ;//zhaoPianClassVector[i]->algCode;
        algTaskVector.push_back(ph);
        zhaoPianClassVector.push_back(ph);
        LOG(SOAP,INFO,"URL:[%s] LOCALPATH:[%s]",ph->photoUrl.c_str(),ph->localPath.c_str() );
    }
    return true ;
}
