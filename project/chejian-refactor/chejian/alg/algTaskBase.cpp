#include "algTaskBase.h"
#include "_c_algTaskCenter.h"
#include "algClass/_c_algClass_0111.h"
#include "algClass/_c_algClass_0112.h"
#include "algClass/_c_algClass_0113.h"
#include "algClass/_c_algClass_0114.h"
#include "algClass/_c_algClass_0115.h"
#include "algClass/_c_algClass_0119.h"
#include "algClass/_c_algClass_0136.h"
#include "algClass/_c_algClass_0155.h"
#include "algClass/_c_algClass_0156.h"
#include "algClass/_c_algClass_0160.h"
#include "algClass/_c_algClass_0157.h"
#include "algClass/_c_algClass_0166.h"
#include "algClass/_c_algClass_0167.h"
#include "algClass/_c_algClass_0168.h"
#include "algClass/_c_algClass_0175.h"
#include "algClass/_c_algClass_0177.h"
#include "algClass/_c_algClass_0186.h"
#include "algClass/_c_algClass_0201.h"
#include "algClass/_c_algClass_0202.h"
#include "algClass/_c_algClass_0203.h"
#include "algClass/_c_algClass_0204.h"
#include "algClass/_c_algClass_0205.h"
#include "algClass/_c_algClass_0206.h"
#include "algClass/_c_algClass_0208.h"
#include "algClass/_c_algClass_0209.h"
#include "algClass/_c_algClass_0216.h"
#include "algClass/_c_algClass_0218.h"
#include "algClass/_c_algClass_0219.h"
#include "algClass/_c_algClass_0234.h"
#include "algClass/_c_algClass_0287.h"
#include "algClass/_c_algClass_0288.h"
#include "algClass/_c_algClass_0292.h"
#include "algClass/_c_algClass_0297.h"
#include "algClass/_c_algClass_0321.h"
#include "algClass/_c_algClass_0322.h"
#include "algClass/_c_algClass_0323.h"
#include "algClass/_c_algClass_0342.h"
#include "algClass/_c_algClass_0344.h"
#include "algClass/_c_algClass_0348.h"
#include "algClass/_c_algClass_0351.h"
#include "algClass/_c_algClass_0352.h"
#include "algClass/_c_algClass_0144.h"
#include "algClass/_c_algClass_0158.h"
#include "algClass/_c_algClass_0159.h"
#include "algClass/_c_algClass_0120.h"
#include "algClass/_c_algClass_0121.h"
#include "algClass/_c_algClass_0122.h"
#include "algClass/_c_algClass_0123.h"
#include "algClass/_c_algClass_0211.h"
#include "algClass/_c_algClass_0212.h"
#include "algClass/_c_algClass_0213.h"
#include "algClass/_c_algClass_0214.h"
#include "algClass/_c_algClass_0215.h"
#include "algClass/_c_algClass_0217.h"
#include "algClass/_c_algClass_0220.h"
#include "algClass/_c_algClass_0221.h"
#include "algClass/_c_algClass_0222.h"
#include "algClass/_c_algClass_0223.h"
#include "algClass/_c_algClass_0224.h"
#include "algClass/_c_algClass_0225.h"
#include "algClass/_c_algClass_0226.h"
#include "algClass/_c_algClass_0227.h"
#include "algClass/_c_algClass_0228.h"
#include "algClass/_c_algClass_0354.h"
#include "algClass/_c_algClass_0296.h"
#include "algClass/_c_algClass_0260.h"
#include "algClass/_c_algClass_0286.h"
#include "algClass/_c_algClass_0135.h"
#include "algClass/_c_algClass_0343.h"
#include "algClass/_c_algClass_0341.h"
#include "algClass/_c_algClass_0151.h"
#include "algClass/_c_algClass_0360.h"
#include "algClass/_c_algClass_0361.h"
#include "algClass/_c_algclass_0324.h"


_c_algBaseClass *_c_algTaskCenter::loadAlgBaseClassByPicType(CityType cityType, std::string algName, PicType type, bool subParamClass)
{
    _c_algBaseClass *pClass;

    //判断是否使用非基类提供的参数类
    if(subParamClass)
    {
        //返回虚函数子类参数类加载的返回值(一般用于提供的默认算法参数类不满足派生类使用)
        return subClassLoadAlgBaseClassByPicType(cityType,algName,type);
    }

    switch (type) {
        case e0111:
        {
            pClass = new _c_algClass_0111();
        }
        break;
        case e0112:
        {
            pClass = new _c_algClass_0112();
        }
        break;
        case e0113:
        {
            pClass = new _c_algClass_0113();
        }
        break;
        case e0114:
        {
            pClass = new _c_algClass_0114();
        }
        break;
        case e0115:
        {
            pClass = new _c_algClass_0115();
        }
        break;
        case e0119:
        {
            pClass = new _c_algClass_0119();
        }
        break;
        case e0120:
        {
            pClass = new _c_algClass_0120();
        }
        break;

        case e0136:
        {
            pClass = new _c_algClass_0136();
        }
        break;
        case e0155:
        {
            pClass = new _c_algClass_0155();
        }
        break;
        case e0156:
        {
            pClass = new _c_algClass_0156();
        }
        break;
        case e0160:
        {
            pClass = new _c_algClass_0160();
        }
        break;
        case e0157:
        {
            pClass = new _c_algClass_0157();
        }
        break;
        case e0166:
        {
            pClass = new _c_algClass_0166();
        }
        break;
        case e0167:
        {
            pClass = new _c_algClass_0167();
        }
        break;
        case e0168:
        {
            pClass = new _c_algClass_0168();
        }
        break;
        case e0175:
        {
            pClass = new _c_algClass_0175();
        }
        break;
        case e0177:
        {
            pClass = new _c_algClass_0177();
        }
        break;
        case e0186:
        {
            pClass = new _c_algClass_0186();
        }
        break;
        case e0201:
        {
            pClass = new _c_algClass_0201();
        }
        break;
        case e0202:
        {
            pClass = new _c_algClass_0202();
        }
        break;
        case e0203:
        {
            pClass = new _c_algClass_0203();
        }
        break;
        case e0204:
        {
            pClass = new _c_algClass_0204();
        }
        break;
        case e0205:
        {
            pClass = new _c_algClass_0205();
        }
        break;
        case e0206:
        {
            pClass = new _c_algClass_0206();
        }
        break;
        case e0208:
        {
            pClass = new _c_algClass_0208();
        }
        break;
        case e0209:
        {
            pClass = new _c_algClass_0209();
        }
        break;
        case e0216:
        {
            pClass = new _c_algClass_0216();
        }
        break;
        case e0218:
        {
            pClass = new _c_algClass_0218();
        }
        break;
        case e0219:
        {
            pClass = new _c_algClass_0219();
        }
        break;
        case e0234:
        {
            pClass = new _c_algClass_0234();
        }
        break;
        case e0260:
        {
            pClass = new _c_algClass_0260();
        }
        break;
        case e0287:
        {
            pClass = new _c_algClass_0287();
        }
        break;
        case e0288:
        {
            pClass = new _c_algClass_0288();
        }
        break;
        case e0292:
        {
            pClass = new _c_algClass_0292();
        }
        break;
        case e0297:
        {
            pClass = new _c_algClass_0297();
        }
        break;
        case e0321:
        {
            pClass = new _c_algClass_0321();
        }
        break;
        case e0322:
        {
            pClass = new _c_algClass_0322();
        }
        break;
        case e0323:
        {
            pClass = new _c_algClass_0323();
        }
        break;
        case e0324:
        {
            pClass = new _c_algClass_0324();
        }
        break;
        case e0342:
        {
            pClass = new _c_algClass_0342();
        }
        break;
        case e0344:
        {
            pClass = new _c_algClass_0344();
        }
        break;
        case e0343:
        {
            pClass = new _c_algClass_0343();
        }
        break;
        case e0341:
        {
            pClass = new _c_algClass_0341();
        }
        break;
        case e0348:
        {
            pClass = new _c_algClass_0348();
        }
        break;
        case e0351:
        {
            pClass = new _c_algClass_0351();
        }
        break;
        case e0352:
        {
            pClass = new _c_algClass_0352();
        }
        break;
        case e0144:
        {
            pClass = new _c_algClass_0144();
        }
        break;
        case e0158:
        {
            pClass = new _c_algClass_0158();
        }
        break;
        case e0159:
        {
            pClass = new _c_algClass_0159();
        }
        break;
        case e0121:
        {
            pClass = new _c_algClass_0121();
        }
        break;
        case e0122:
        {
            pClass = new _c_algClass_0122();
        }
        break;
        case e0123:
        {
            pClass = new _c_algClass_0123();
        }
        break;
        case e0135:
        {
            pClass = new _c_algClass_0135();
        }
        break;
        case e0211:
        {
            pClass = new _c_algClass_0211();
        }
        break;
        case e0212:
        {
            pClass = new _c_algClass_0212();
        }
        break;
        case e0213:
        {
            pClass = new _c_algClass_0213();
        }
        break;
        case e0214:
        {
            pClass = new _c_algClass_0214();
        }
        break;
        case e0215:
        {
            pClass = new _c_algClass_0215();
        }
        break;
        case e0217:
        {
            pClass = new _c_algClass_0217();
        }
        break;
        case e0220:
        {
            pClass = new _c_algClass_0220();
        }
        break;
        case e0221:
        {
            pClass = new _c_algClass_0221();
        }
        break;
        case e0222:
        {
            pClass = new _c_algClass_0222();
        }
        break;
        case e0223:
        {
            pClass = new _c_algClass_0223();
        }
        break;
        case e0224:
        {
            pClass = new _c_algClass_0224();
        }
        break;
        case e0225:
        {
            pClass = new _c_algClass_0225();
        }
        break;
        case e0226:
        {
            pClass = new _c_algClass_0226();
        }
        break;
        case e0227:
        {
            pClass = new _c_algClass_0227();
        }
        break;
        case e0354:
        {
            pClass = new _c_algClass_0354();
        }
        break;
        case e0296:
        {
            pClass = new _c_algClass_0296();
        }
        break;
        case e0228:
        {
             pClass = new _c_algClass_0228();
        }
        break;
        case e0286:
        {
             pClass = new _c_algClass_0286();
        }
        break;
        case e0151:
        {
            pClass = new _c_algClass_0151();
        }
        break ;
        case e0360:
        {
             pClass = new _c_algClass_0286();
        }
        break;
        case e0361:
        {
             pClass = new _c_algClass_0286();
        }
        break;
        default:
        {
            //如果type不能识别返回虚函数子类参数类加载的返回值(让派生类自己实现参数类，一般用于新增城市私有算法接口)
            pClass = subClassLoadAlgBaseClassByPicType(cityType,algName,type);
        }
        break;

    }
    pClass->setBaseParam(cityType, type, algName);
    pClass->initAlgClass();

    return pClass;
}

Json::Value _c_algTaskCenter::getAlgCheckConflictJson()
{
     Json::Value root;
     vector<std::string> baseCode ;
     std::set<std::string> sbase ;
     for(unsigned int i = 0 ;i < __algVector.size() ;i++ )
     {
        baseCode.push_back(__algVector[i].code);
     }
     for(unsigned int i = 0 ;i <baseCode.size() ;i++){
        if( !(sbase.insert(baseCode[i]).second)  ){
            Json::Value subroot ;
            subroot["code"] = baseCode[i] ;
            root.append(subroot) ;
        }
     }
     return root ;
}

Json::Value _c_algTaskCenter::getAlgVectorJson()
{
    Json::Value root;

    for(unsigned int i = 0; i < __algVector.size(); i++)
    {
        Json::Value subRoot;
        subRoot["type"] =__algVector[i].type;
        subRoot["isOpen"] =__algVector[i].isOpen;
        subRoot["code"] =__algVector[i].code;
        subRoot["name"] =__algVector[i].name;
        subRoot["needCheck"] =__algVector[i].needCheck;
        subRoot["isTenYears"] =__algVector[i].isTenYears;
        //subRoot["subAlgClass"] =__algVector[i].subAlgClass;
        subRoot["isMust"]=__algVector[i].isMust;
        subRoot["link"]=__algVector[i].link;

#if 0 //把示例照片路径上传给网页端,暂不打开此功能,等后续网页优化后打开
        Json::Value picArray;
        if (__algVector[i].examplePics.size() > 0)
        {
            for(unsigned int j = 0; j < __algVector[i].examplePics.size(); j++)
            {
                picArray.append(__algVector[i].examplePics[j]);
            }
        }
        else
        {
            picArray.append("无");
        }
        subRoot["picExamples"] = picArray;
#endif
        root.append(subRoot);
    }
    return root;
}

_c_algBaseClass *_c_algTaskCenter::loadAlgBaseClassByPicType(PicType type)
{
    Json::Value root;
    //遍历algVector 并找到 type相对应的 algItem
    for(unsigned int i = 0; i < __algVector.size(); i++)
    {
        if(__algVector[i].type == type)
        {
            //根据type类型加载algClass实体
             _c_algBaseClass *pAlgParam = loadAlgBaseClassByPicType(__cityType,__algVector[i].name,__algVector[i].type, __algVector[i].subAlgClass);
             return pAlgParam;
        }
    }

    return new _c_algBaseClass();
}

