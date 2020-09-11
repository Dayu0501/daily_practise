#include "_c_vehicle.h"
#include "dataCenter.h"
#include "base/baseTool.h"
#include "base/http/HttpClient.h"

void _c_vehicle::extraDbWork()
{
    for (unsigned int i = 0; i < zhaoPianClassVector.size(); i++) {
        zhaoPianClassVector[i]->dbWork();
    }

    if(pRunTime != NULL)
    {
        pRunTime->dbWork();
    }

    for (unsigned int i = 0; i < wangLuoJieKouReturnVector.size(); i++) {
        _c_dbTask *pDbTask = static_cast<_c_dbTask *>(wangLuoJieKouReturnVector[i]);
        pDbTask->dbWork();
    }

    //需要等待视频请求处理完成
//    while (!videoCheckInfo.shiPinDownloadIsFinished)
//    {
//        std::this_thread::sleep_for(std::chrono::milliseconds(30));
//    }
//    for (unsigned int i = 0; i < videoCheckInfo.shiPinClassVector.size(); i++) {
//        videoCheckInfo.shiPinClassVector[i]->dbWork();
//    }
}

bool _c_vehicle::loadAlgTask()
{
//    if (videoCheckInfo.isNeedLoadVideoInfo)
//        loadVehicleVideoInfo();
//    else
//        videoCheckInfo.shiPinDownloadIsFinished = true;

    for (unsigned int i = 0; i < zhaoPianClassVector.size(); i++)
    {
        zhaoPianClassVector[i]->cheLiangUid = uuid;
        zhaoPianClassVector[i]->algTaskInit();
        //zhaoPianClassVector[i]->localPath = "/"+baseTool::getDangTianRiQi()+"/";
        zhaoPianClassVector[i]->localPath = "/"+baseTool::getDangTianRiQi()+"/"+zhaoPianClassVector[i]->algCode;
        zhaoPianClassVector[i]->localPath += "_"+haoPaiHaoMa;
        zhaoPianClassVector[i]->localPath += "_"+cheLiangShiBieDaiHao;

        zhaoPianClassVector[i]->pVideoCheckInfo = &videoCheckInfo;
        algTaskVector.push_back(zhaoPianClassVector[i]);
    }
    return true;
}

bool _c_vehicle::loadAllParam()
{
    for (unsigned int i = 0; i < memberVector.size(); i++)
    {
        paramVector.push_back(&memberVector[i]);
    }

    pWangLuoJieKouReturnVector = &wangLuoJieKouReturnVector;
    return true;
}

PicType _c_vehicle::getWangLuojieKouOwnPicType(std::string biaoshi)
{
    for (unsigned int i = 0; i < wangLuoJieKouPicMap.size(); i++) {
        if (biaoshi == wangLuoJieKouPicMap[i].biaoShi)
            return (PicType)wangLuoJieKouPicMap[i].biaoShiPicType;
    }
    return eNULL;
}

PicType _c_vehicle::getWangLuojieKouXieRuPicType(std::string biaoshi)
{
    for (unsigned int i = 0; i < wangLuoJieKouPicMap.size(); i++) {
        if (biaoshi == wangLuoJieKouPicMap[i].biaoShi)
            return (PicType)wangLuoJieKouPicMap[i].xieRuXiangPicType;
    }
    return eNULL;
}

bool _c_vehicle::wangLuoJieKouResultEdit(void *p)
{
    for (unsigned int i = 0; i < wangLuoJieKouReturnVector.size(); i++)
    {
        std::string biaoShi = baseTool::getWangLuoJieKouReturnInfoBiaoShi(wangLuoJieKouReturnVector[i]);
        if (biaoShi == "18C23")
        {
            editJiaoQiangXianResult(wangLuoJieKouReturnVector[i], p);
        }
    }
    return true;
}

bool _c_vehicle::processWangLuoJieKou()
{
    for (unsigned int i = 0; i < wangLuoJieKouReturnVector.size(); i++)
    {
        std::string biaoShi = baseTool::getWangLuoJieKouReturnInfoBiaoShi(wangLuoJieKouReturnVector[i]);
        if (biaoShi == "18C23")
        {
            checkJiaoQiangXianReturnInfo(wangLuoJieKouReturnVector[i]);
            return true;
        }
    }
    return false;
}

void _c_vehicle::checkJiaoQiangXianReturnInfo(_c_object *obj)
{
    //保险单号 车辆识别代码 保险有效期始 保险有效期止 车船税纳税情况 只要任何一项为空则不过
    std::string isGetData = baseTool::getObjectItemValueByName(&obj->memberVector, "isGetData");
    std::string baoXianDanHao = baseTool::getObjectItemValueByName(&obj->memberVector, "baoXianDanHao");
    std::string cheLiangShiBieDaiHao = baseTool::getObjectItemValueByName(&obj->memberVector, "cheLiangShiBieDaiHao");
    std::string shengXiaoRiQi = baseTool::getObjectItemValueByName(&obj->memberVector, "shengXiaoRiQi");
    std::string zhongZhiRiQi = baseTool::getObjectItemValueByName(&obj->memberVector, "zhongZhiRiQi");
    std::string cheChuanShuiNaShuiQingKuang = baseTool::getObjectItemValueByName(&obj->memberVector, "cheChuanShuiNaShuiQingKuang");

    std::string dangTianRiQi = baseTool::getDangTianRiQi();
    std::string jianYanJieShuShiJian = baseTool::getObjectItemValueByName(&memberVector, "jianYanJieShuShiJian");

    objectMember* dataIsValid = baseTool::getObjectItemByName(&obj->memberVector, "dataIsValid");
    objectMember* isPass = baseTool::getObjectItemByName(&obj->memberVector, "isPass");
    objectMember* reason = baseTool::getObjectItemByName(&obj->memberVector, "reason");

    //没有获取电子
    if (isGetData == "false")
    {
        *dataIsValid->value = "false";
        *isPass->value = "false";
        *reason->value = "电子交强险:[没有电子信息]";
        return;
    }

    if (baoXianDanHao == "无数据" || cheLiangShiBieDaiHao == "无数据" || shengXiaoRiQi == "无数据" || zhongZhiRiQi == "无数据" || cheChuanShuiNaShuiQingKuang == "无数据")
    {
        *dataIsValid->value = "false";
        *isPass->value = "false";
        *reason->value = "电子交强险:[电子信息不完整]";
        return;
    }

    *dataIsValid->value = "true";

    if (!baseTool::checkDateIsExpired(dangTianRiQi, shengXiaoRiQi, zhongZhiRiQi))
    {
        *isPass->value = "false";
        *reason->value = "电子交强险:[不在保险有效期内]";
        return;
    }

    *isPass->value = "true";
    *reason->value = "[通过]";
    LOG(SOAP,INFO,"%s dataIsValid:%s reason:%s\n", __func__, (*dataIsValid->value).c_str(), (*reason->value).c_str());
}

//如果通过。不做任何处理。如果不通过有照片 不做任何处理
//如果不通过 没照片则写结果(两种结果)
void _c_vehicle::editJiaoQiangXianResult(_c_object *obj, void *p)
{
    bool picIsExist = false;
    objectMember* dataIsValid = baseTool::getObjectItemByName(&obj->memberVector, "dataIsValid");
    objectMember* isPass = baseTool::getObjectItemByName(&obj->memberVector, "isPass");
    objectMember* reason = baseTool::getObjectItemByName(&obj->memberVector, "reason");
    objectMember* isGetData = baseTool::getObjectItemByName(&obj->memberVector, "isGetData");
    objectMember* photoIsExist = baseTool::getObjectItemByName(&obj->memberVector, "photoIsExist");
    objectMember* photoCode = baseTool::getObjectItemByName(&obj->memberVector, "photoCode");

    *photoCode->value = baseTool::getAlgItemCodeByPicType(getWangLuojieKouOwnPicType("18C23"), p);

    //判断有没有照片
    picIsExist = baseTool::photoIsExist(&algTaskVector, *photoCode->value);
    if (picIsExist)
        *photoIsExist->value = "true";
    else
        *photoIsExist->value = "false";

    if (picIsExist)
    {
        //如果有电子信息,有照片
        if (*isGetData->value == "true")
        {
            //以电子信息为主 把结果写入照片算法项
            _c_algTask *pAlgTask = baseTool::seachPhotoByZpType(&algTaskVector, *photoCode->value);
            if (*isPass->value == "true")
            {
                baseTool::writeResultByJGAndSM(pAlgTask, PASS, *reason->value);
            }
            else
            {
                baseTool::writeResultByJGAndSM(pAlgTask, NOT_PASS, *reason->value);
            }
        }

        //如果没有电子信息,结果以照片为准 不做任何处理
    }
    else
    {
        //如果没有照片项, 并且没有电子信息
        if (*isGetData->value == "false")
        {
            if (*reason->value == "电子交强险:[没有电子信息]")
                *reason->value = "电子交强险:[没有电子信息和照片信息]";

            baseTool::writeResultInExistAlg(&algTaskVector, NOT_PASS, *reason->value, baseTool::getAlgItemCodeByPicType(getWangLuojieKouXieRuPicType("18C23"), p));
        }
        else
        {
            if (*isPass->value == "false")
                baseTool::writeResultInExistAlg(&algTaskVector, NOT_PASS, *reason->value, baseTool::getAlgItemCodeByPicType(getWangLuojieKouXieRuPicType("18C23"), p));

            //如果通过,那么不做任何操作
        }
    }
    LOG(SOAP,INFO,"%s dataIsValid:%s reason:%s\n", __func__, (*dataIsValid->value).c_str(), (*reason->value).c_str());
//    printf("%s dataIsValid:%s reason:%s\n", __func__, (*dataIsValid->value).c_str(), (*reason->value).c_str());
}

void getVideoInfoThreadHandle(std::string uri, _c_vehicle *pVehicle)
{
    //等待远程服务器处理完毕
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
//    printf("%s uri:%s \n", __func__, uri.c_str());
    LOG(SOAP, INFO, "getVideoInfo: %s\n", uri.c_str());

    int state = -1;
    //可能远端还没处理完成或者远端服务器异常,所以需要多发几次
    for (int i = 0; i < 2; i++)
    {
        HttpClient clientGet;
        clientGet.set_retries_timeout(2, 12);//超时暂时设定为12秒
        clientGet.m_request_text_type = RESPONSE_JSON;
        if (!clientGet.init_data(uri.c_str(), REQUEST_GET_FLAG, NULL, NULL))
        {
            printf("getVideoInfo uri init error %s.\n",uri.c_str());
        }

        clientGet.startHttpClient();

        if (clientGet.d_success_flag)
        {
            if (!clientGet.ResponseStringData.empty())
            {
                state = pVehicle->analyseVideoInfoJson(clientGet.ResponseStringData);
                //2表示远端数据还没处理完,则继续请求
                if (state != 2)
                    break;
            }
        }
        else
        {
            //如果直接请求失败 就没必要再请求了
            state = -2;
//            printf("@@@@@@ getVideoInfoThreadHandle server exception!\n");
            LOG(SOAP, ERR, "getVideoInfoThreadHandle server exception!\n");
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

//    printf("%s uri:%s state：%d\n", __func__, uri.c_str(), state);
    LOG(SOAP, INFO, "getVideoInfo state：%d\n", state);
    if (state == 0)
        pVehicle->downloadVideoState = "该车没有视频信息";
    else if (state == 1)
        pVehicle->downloadVideoState = "视频信息请求失败";
    else if (state == 3)
        pVehicle->downloadVideoState = "视频信息请求成功";
    else if (state == -1)
        pVehicle->downloadVideoState = "视频信息解析失败";
    else if (state == -2)
        pVehicle->downloadVideoState = "视频本地请求失败";

    pVehicle->videoCheckInfo.shiPinDownloadIsFinished = true;
}

void _c_vehicle::loadVehicleVideoInfo()
{
    //先要判断是否是本地部署
    std::string portIp = "127.0.0.1:10001";
    bool isInList = false;

    if (videoJyjgbhConfig != NULL)
    {
        for (unsigned int i = 0; i < videoJyjgbhConfig->size(); i++)
        {
            if ((*videoJyjgbhConfig)[i].jyjgbh == jianYanJiGouBianHao)
            {
                if ((*videoJyjgbhConfig)[i].tongXunFangShi == "remote")
                {
                    portIp = (*videoJyjgbhConfig)[i].portIp;
                }
                isInList = true;
                break;
            }
        }
    }

    if (!isInList)
    {
        downloadVideoState = "该检验机构暂未提供视频";
        videoCheckInfo.shiPinDownloadIsFinished = true;
        LOG(SOAP, INFO, "loadVehicleVideoInfo jyjgbh not match!\n");
        return;
    }

    std::string uri = "";
    uri += "http://";
    uri += portIp;
    uri += "/getVideoInfoJson?";
    uri += "city=" + cityCode + "&";
    uri += "cheLiangUid=" + uuid;

    //先采用非阻塞式的
    std::thread *sendThread = new std::thread(getVideoInfoThreadHandle, uri, this);
    sendThread->detach();
    delete sendThread;
}

int _c_vehicle::analyseVideoInfoJson(std::string &data)
{
    Json::Value  root;
    Json::Reader reader;
    if (reader.parse(data, root, false))
    {
        int state = root["dataIsValid"].asInt();
        if (state == 0 || state == 1 || state == 2)
            return state;

        Json::Value subroot = root["videoInfoArray"];
        for (unsigned int i = 0; i < subroot.size(); i++)
        {
            _c_video *pVideo = new _c_video;
            pVideo->loadUuid();
            pVideo->cheLiangUid = root["cheLiangUid"].asString();
            pVideo->videoAlgType = subroot[i]["spAlgType"].asInt();
            pVideo->videoCode = subroot[i]["spzl"].asString();
            pVideo->videoUrl = subroot[i]["spUrl"].asString();

            pVideo->localPath = "/" + baseTool::getDangTianRiQi() + "/V" + pVideo->videoCode;
            pVideo->localPath += "_" + haoPaiHaoMa;
            pVideo->localPath += "_" + cheLiangShiBieDaiHao;
            if(pVideo->videoUrl.find(".mp4") != string::npos)
            {
                pVideo->localPath += ".mp4";
            }
            else if(pVideo->videoUrl.find(".flv") != string::npos)
            {
                pVideo->localPath +=  ".flv";
            }
            else if(pVideo->videoUrl.find(".avi") != string::npos)
            {
                pVideo->localPath +=  ".avi";
            }

//            printf("%s algType:%d code:%s url:%s\n", __func__, pVideo->videoAlgType, pVideo->videoCode.c_str(), pVideo->videoUrl.c_str());
            videoCheckInfo.shiPinClassVector.push_back(pVideo);
        }
        return state;
    }
    else
    {
        return -1;
    }
}
