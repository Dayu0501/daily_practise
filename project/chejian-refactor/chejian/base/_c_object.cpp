#include "_c_object.h"
#include "baseTool.h"

std::string _c_object::loadUuid()
{
     uuid = baseTool::newGuid();
     return uuid;
}

bool _c_object::checkUuid(std::string id)
{
    return (uuid == id);
}

void _c_object::analyseJson(Json::Value &root)
{
    for (unsigned int i = 0; i < memberVector.size(); i++) {
        if (!root[(memberVector[i].soapName.c_str())].empty())
        {
            std::string str = root[(memberVector[i].soapName.c_str())].asString();
//            printf("[%s]:%s\n", memberVector[i].soapName.c_str(),str.c_str());
            if (str.length() > 0)
                *memberVector[i].value = str;
            else
                *memberVector[i].value = "无数据";
        }
        else
        {
//            printf("[%s]:not find data \n",memberVector[i].soapName.c_str());
            *memberVector[i].value = "无数据";
        }
    }
}
