#include "_c_yingXiangVehicle.h"
#include "base/dataCenter.h"
#include "base/baseTool.h"

#include <regex>
#include <algorithm>

void _c_yingXiangVehicle::extraDbWork()
{
    for (unsigned int i = 0; i < zhaoPianClassVector.size(); i++) {
        zhaoPianClassVector[i]->dbWork();
    }
    if(pRunTime != NULL)
    {
        pRunTime->dbWork();
    }
}


bool _c_yingXiangVehicle::loadAlgTask()
{
     for (unsigned int i = 0; i < zhaoPianClassVector.size(); i++)
     {
         zhaoPianClassVector[i]->cheLiangUid = uuid;
         zhaoPianClassVector[i]->algTaskInit();

         std::string photoName;
         std::vector<std::string> splitVector;
         if (!zhaoPianClassVector[i]->photoUrl.empty())
         {
             std::regex reg("/");
             std::sregex_token_iterator begin(zhaoPianClassVector[i]->photoUrl.begin(), zhaoPianClassVector[i]->photoUrl.end(), reg ,-1), end;
             std::copy(begin, end, std::back_inserter(splitVector));
         }

         if (splitVector.size() > 0)
            photoName = splitVector[splitVector.size()-1];

         zhaoPianClassVector[i]->localPath = "/"+baseTool::getDangTianRiQi()+"/"+photoName;
         printf("localPath is:%s\n", zhaoPianClassVector[i]->localPath.c_str());

         algTaskVector.push_back(zhaoPianClassVector[i]);
     }
     return true;
}

bool _c_yingXiangVehicle::loadAllParam()
{
    for (unsigned int i = 0; i < memberVector.size(); i++)
    {
        paramVector.push_back(&memberVector[i]);
    }
    return true;
}

