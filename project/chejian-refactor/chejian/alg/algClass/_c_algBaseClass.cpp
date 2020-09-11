#include "_c_algBaseClass.h"
#include "base/baseTool.h"

void _c_algBaseClass::setBaseParam(CityType cityType,PicType type, std::string algName)
{
    _type = type;
    _algType = (AlgType)type;
    _algName = algName;
    _cityType = cityType;
    pInMemberList = NULL;
    pResultMemberList = NULL;
    mainPhotoType = eNULL;
    subPhotoType = eNULL;
}

void _c_algBaseClass::resetBaseParam(PicType type)
{
    _type = type ;
    mainPhotoType = type ;
}
void  _c_algBaseClass::setAlgType(AlgType type)
{
    _algType = type ;
}

void _c_algBaseClass::initAlgClass()
{
    //setAlgIds();
    seekMemberListPointer();
    subClassLoadNewResultMember();
    loadAlgClassConfig();
}

void _c_algBaseClass::loadAlgClassConfig()
{
    std::ifstream fin;
    std::string algconfigpath = _configRoot+"/algConfig/algClassConfig_"+std::to_string(_cityType)+"/algClass_"+std::to_string(_type)+".json";

    fin.open(algconfigpath);
    if (fin.is_open()) {
        Json::Value  root;
        Json::Reader reader;
        if (reader.parse(fin, root, false))
        {
           setResultConfig(root["algClass"]);
        }
    }
    fin.close();

}

void _c_algBaseClass::setResultConfig(Json::Value root)
{
    if(resultListVector.size()>0)
    {
         for (unsigned int i = 0; i < resultListVector.size(); i++) {
             Json::Value subRoot =root[resultListVector[i].name];
             for(unsigned int j=0; j <  resultListVector[i].pVector->size(); j++)
             {
                 for(unsigned int k=0;k<subRoot.size();k++)
                 {

                     if((*resultListVector[i].pVector)[j].name == subRoot[k]["name"].asString())
                     {
                         if(!subRoot[k]["descOpen"].empty())
                             (*resultListVector[i].pVector)[j].config.descOpen = subRoot[k]["descOpen"].asBool();
                         if((*resultListVector[i].pVector)[j].config.descOpen)
                         {
                             if(!subRoot[k]["desc"].empty())
                                 (*resultListVector[i].pVector)[j].desc = subRoot[k]["desc"].asString();
                         }
                         if(!subRoot[k]["isOpen"].empty())
                             (*resultListVector[i].pVector)[j].config.isOpen = subRoot[k]["isOpen"].asBool();
                         if(!subRoot[k]["errLevel"].empty())
                             (*resultListVector[i].pVector)[j].config.errLevel = (E_JG)subRoot[k]["errLevel"].asInt();
                         //printf("name:%s isOpen:%d\n",(*resultListVector[i].pVector)[j].name.c_str(),(*resultListVector[i].pVector)[j].config.isOpen);
                     }

                 }
            }
        }
    }
}

Json::Value _c_algBaseClass::getResultMemberListJson()
{
    Json::Value root;


    if(resultListVector.size()>0)
    {
        for (unsigned int i = 0; i < resultListVector.size(); i++) {
            Json::Value memberRoot;
            for(unsigned int j=0; j <  resultListVector[i].pVector->size(); j++)
            {
                Json::Value subRoot;
                subRoot["name"] = (*resultListVector[i].pVector)[j].name;
                subRoot["desc"] = (*resultListVector[i].pVector)[j].desc;
                //subRoot["output"] = (*resultListVector[i].pVector)[j].output;
                subRoot["isOpen"] = (*resultListVector[i].pVector)[j].config.isOpen;
                subRoot["descOpen"] = (*resultListVector[i].pVector)[j].config.descOpen;
                subRoot["errLevel"] = (*resultListVector[i].pVector)[j].config.errLevel;
                memberRoot.append(subRoot);
            }
            root[resultListVector[i].name]=memberRoot;
        }
    }
    //printf("save:%s\n",root.toStyledString().c_str());
    return root;
}


void _c_algBaseClass::saveResultConfig()
{
    std::ofstream ofs;
    Json::Value  root;
    std::string path = _configRoot+"/algConfig/algClassConfig_"+std::to_string(_cityType);
    baseTool::CheckDir(path);
    std::string algconfigpath = path+"/algClass_"+std::to_string(_type)+".json";

    root["algClass"] = getResultMemberListJson();

    ofs.open(algconfigpath);
    ofs << root.toStyledString();
    ofs.close();
}

void _c_algBaseClass::setAllParam(std::vector<objectMember *> *pVector)
{
    pAllParamVector = pVector;
}

Json::Value _c_algBaseClass::getInParamJson(std::string keyCode,unsigned int timeOut, bool isVideo, std::string reponseChan)
{
    Json::Value root;

    if(pInMemberList!=NULL)
    {
        Json::Value memberRoot;
        for (unsigned int i = 0; i < pInMemberList->size(); i++) {

            Json::Value subRoot;
            subRoot["name"] = (*pInMemberList)[i].name;
            subRoot["value"] = (*pInMemberList)[i].value->inData;
            memberRoot.append(subRoot);
        }
        root["param"] = memberRoot;
    }

    Json::Value photoRoot;
    photoRoot["mainPhoto"] = _mainPhoto;
    photoRoot["subPhoto"] = _subPhoto;
    photoRoot["mainPhotoPath"] = _mainPath;
    photoRoot["subPhotoPath"] = _subPath;
    root["photo"] = photoRoot;
    if (isVideo) {
        root["algID"] = _algType + evideo;
    } else {
	    Json::Value algIdArray;
	    for (const auto & item : algIDs) {
			algIdArray.append(item);
    }

        root["algIDs"] = algIdArray;
    }

    root["algTaskKeyCode"] = keyCode;
    root["encodeKey"] = baseTool::Crc16String((uint8_t*)keyCode.c_str(), keyCode.size());

    Json::Value otherRoot;

    otherRoot["inSystemTime"] = baseTool::getNowDate();  //发送json时间
    otherRoot["timeoutSecond"] = std::to_string(timeOut);     //算法收到判断超时时间
    otherRoot["reponseChan"] = reponseChan;     //算法收到判断超时时间
    root["other"] = otherRoot;

    //return root.toStyledString();
    //Json::FastWriter writer;
    //return writer.write(root);
    return root;
}

void _c_algBaseClass::setPhoto(std::string mainPhoto, std::string mainPath, std::string subPhoto, std::string subPath)
{
    _mainPhoto = mainPhoto;
    _subPhoto = subPhoto;


    _mainPath = mainPath;
    _subPath = subPath;
}

E_JG _c_algBaseClass::getResult(std::string *pReason)
{
    bool isPass = true;
    E_JG errjg = PASS;
    std::string errsm;
    std::string subErrsm;

    if(pResultMemberList != NULL)
    {
        //遍历参数类基类中结果成员别表
        for (unsigned int i = 0; i < pResultMemberList->size(); i++) {
            //判断成员的配置打开且需要输出
            if((*pResultMemberList)[i].config.isOpen&&(*pResultMemberList)[i].output)
            {
 //                printf("3name:%s result:%d\n",(*pResultMemberList)[i].name.c_str(),(*pResultMemberList)[i].value->result);
                //如果该输出项为false 将isPass设置为false 并记录错误原因
                if(!(*pResultMemberList)[i].value->result)
                {
                    isPass = false;
                    //如果结果的错误严重等级更大则使用严重等级大的错误类型来当做判断结果
                    if(errjg < (*pResultMemberList)[i].config.errLevel)
                        errjg = (*pResultMemberList)[i].config.errLevel;

                    errsm +="[" + (*pResultMemberList)[i].desc /* + ERROR_STR*/ + "] ";
                }
            }
        }
        //如果isPass为true则填充通过，否则填充错误类型和错误说明
        if(isPass)
        {
            *pReason = "[通过]";
            return PASS;
        }
        else
        {
            *pReason = _algName+":"+errsm;
            return errjg;
        }
    }
    *pReason = "[无处理信息]";
    return NOT_PASS;
}

void _c_algBaseClass::setResultMember(std:: string memberName, memberItem *pResultMember)
{
    if(resultListVector.size()>0)
    {
        for (unsigned int i = 0; i < resultListVector.size(); i++) {
            if(resultListVector[i].name == memberName)
            {
                for(unsigned int j=0; j <  resultListVector[i].pVector->size(); j++)
                {
                    if((*resultListVector[i].pVector)[j].name == pResultMember->name)
                    {

                        if(!pResultMember->desc.empty())
                            (*resultListVector[i].pVector)[j].desc = pResultMember->desc;

                        (*resultListVector[i].pVector)[j].config.isOpen = pResultMember->config.isOpen;
                        (*resultListVector[i].pVector)[j].config.descOpen = pResultMember->config.descOpen;

                        if(pResultMember->config.errLevel > 0)
                            (*resultListVector[i].pVector)[j].config.errLevel = pResultMember->config.errLevel;
                    }
                }
            }
        }
    }
}

//参数pvector是算法回复的结果集
bool _c_algBaseClass::LoadResult(std::string redisRet, std::vector<objectMember> *pVector)
{
    if(redisRet == "1")
    {
        if(pVector!=NULL)
        {
            for (unsigned int k = 0; k < resultListVector.size();k++) {
                for (unsigned int i = 0; i < resultListVector[k].pVector->size(); i++) {
                    for (unsigned int j = 0; j < pVector->size(); j++) {

                        if((*resultListVector[k].pVector)[i].name == (*pVector)[j].codeName)
                        {

                            if(*(*pVector)[j].value == "true")
                            {
                                (*resultListVector[k].pVector)[i].value->result = true;
                            }
                            else if (*(*pVector)[j].value == "false")
                            {
                                (*resultListVector[k].pVector)[i].value->result = false;
                            }
                            else
                            {
                                (*resultListVector[k].pVector)[i].value->OutData = (*pVector)[j].value->c_str();
                            }
                        }
                    }
                }
            }
        }

    }
    return true;
}

std::string _c_algBaseClass::getObjectItemValueByName(const char *attrName)
{
    return baseTool::getObjectItemValueByName(pAllParamVector,attrName);
}
std::string _c_algBaseClass::getObjectItemValueFormatByName(const char *attrName)
{
    return GetPhotoAttrValueFileNameFormating( getObjectItemValueByName(attrName) );
}

memberItem*  _c_algBaseClass::getOutputMemberItem(const char *attrName)
{
    return baseTool::getMemberItemByName(pResultMemberList,attrName);
}

bool _c_algBaseClass::checkMemberItemAndSetAllUnOutput(const char *attrName,bool isMust,std::vector<memberItem>*pResult)
{
  if( !pResult)
  {
    pResult = pResultMemberList ;
  }

  return  baseTool::checkMemberItemAndSetAllUnOutput(pResult, baseTool::getMemberItemByName(pResult, attrName ),isMust);
}

std::string _c_algBaseClass::getPhotoName(std::string algcode)
{
    std::string defaultPhotoName = algcode;
    {
        std::string result ;
        std::string haoPaiHaoMa = getObjectItemValueByName("chePaiHao");
        std::string cheLiangShiBieDaiHao = getObjectItemValueByName("cheJiaHao");
        std::string cheLiangLeiXing = getObjectItemValueByName("cheLiangLeiXing");

        std::string hphm = GetPhotoAttrValue(haoPaiHaoMa);
        std::string clsbdh = GetPhotoAttrValue(cheLiangShiBieDaiHao);
        std::string cllx = GetPhotoAttrValue(cheLiangLeiXing);

        result ="_" + hphm + "_" + clsbdh +"_"+cllx;
        defaultPhotoName += result;
    }

    return defaultPhotoName;
}

std::string _c_algBaseClass::getPhotoBaseName(std::string algcode)
{
    std::string haoPaiHaoMa = getObjectItemValueByName("chePaiHao");
    std::string cheLiangShiBieDaiHao = getObjectItemValueByName("cheJiaHao");
    std::string cheLiangLeiXing = getObjectItemValueByName("cheLiangLeiXing");
    std::string hphm = GetPhotoAttrValue(haoPaiHaoMa);
    std::string clsbdh = GetPhotoAttrValue(cheLiangShiBieDaiHao);
    std::string cllx = GetPhotoAttrValue(cheLiangLeiXing);
    return algcode+"_" + hphm + "_" + clsbdh+ "_" + cllx;
}
bool _c_algBaseClass::beforeResultEdit()
{
	//判断照片类型是否正确  如果不正确直接 跳过结果编辑
    bool retValue = !checkMemberItemAndSetAllUnOutput("zhaoPianLeiXing",true);

    return retValue ;
}

void _c_algBaseClass::setAlgIds() {
    algIDs.push_back(_algType);
}

bool _c_algBaseClass::setInParamEdit() {
	bool res = InParamEdit();
	setAlgIds();

	return res;
}