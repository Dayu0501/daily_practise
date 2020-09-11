#include "_c_algTaskCenter.h"
#include "base/baseTool.h"

bool _c_algTaskCenter::checkHeiMingDan(std::string chePai, std::vector<_c_algTask *> *algTaskVector)
{
     if(__HMD.size() > 0)
     {
         for (unsigned int k = 0; k < __HMD.size(); k++) {
             if (chePai == __HMD[k]) {
                 for(unsigned int i = 0; i < algTaskVector->size(); i++)
                 {
                     baseTool::writeResultByJGAndSM((*algTaskVector)[i],NOT_PASS, "黑名单车辆");
                 }
                 return false;
             }
         }
         return true;
     }
     return true;
}

bool _c_algTaskCenter::checkCjhHeiMingDan(std::string cheJiaHao, std::vector<_c_algTask *> *algTaskVector)
{
     if(__CjhHMD.size() > 0)
     {
         for (unsigned int k = 0; k < __CjhHMD.size(); k++) {
             if (cheJiaHao == __CjhHMD[k]) {
                 for(unsigned int i = 0; i < algTaskVector->size(); i++)
                 {
                     baseTool::writeResultByJGAndSM((*algTaskVector)[i],NOT_PASS, "车架号黑名单车辆");
                 }
                 return false;
             }
         }
         return true;
     }
     return true;
}
bool _c_algTaskCenter::checkHttpBaiMingDan(std::string ipaddr)
{
     for (unsigned int k = 0; k < __HttpMD.size(); k++) {
         if (ipaddr == __HttpMD[k]) {
             return true;
         }
     }
     return false;
}

bool _c_algTaskCenter::checkJianYanLeiBie(std::string jylb, std::vector<_c_algTask *> *algTaskVector)
{
    if(jylb.empty())
    {
        return true;
    }

    if(__JYLB.size() > 0)
    {
        int nullcnt = 0 ;
        for (unsigned int k = 0; k < __JYLB.size(); k++) {
            if (jylb == __JYLB[k]) {
                return true;
            }else if(__JYLB[k] == ""){
                nullcnt ++ ;
            }
        }
        if(nullcnt == __JYLB.size() )
        {
            return true ;
        }

        for(unsigned int i = 0; i < algTaskVector->size(); i++)
        {
            baseTool::writeResultByJGAndSM((*algTaskVector)[i],UNABLE_IDENTIFY, "检验类别不在软件处理范围内");
        }

        return false;
    }
    return true;
}

bool _c_algTaskCenter::checkShiYongXingZhi(std::string syxz, std::vector<_c_algTask *> *algTaskVector)
{
    if(__SYXZ.size() > 0)
    {
        int nullcnt = 0;//统计被删除的数量
        for (unsigned int k = 0; k < __SYXZ.size(); k++) {
            if (syxz == __SYXZ[k]) {
                return true;
            }else if(__SYXZ[k] == ""){
               nullcnt++ ;
            }
        }
        if(nullcnt == __SYXZ.size() )// 全部被删除 默认含义为所有使用性质都适用
        {
            return true ;
        }
        for(unsigned int i = 0; i < algTaskVector->size(); i++)
        {
             baseTool::writeResultByJGAndSM((*algTaskVector)[i],UNABLE_IDENTIFY, "使用性质不在软件处理范围");
        }
        return false;
    }
    return true;
}

bool _c_algTaskCenter::checkCheLiangZhongLei(std::string clzl, std::vector<_c_algTask *> *algTaskVector)
{
    if(__CLZL.size() > 0)
    {
        for (unsigned int k = 0; k < __CLZL.size(); k++) {
            if (clzl == __CLZL[k]) {
                return true;
            }
        }
        for(unsigned int i = 0; i < algTaskVector->size(); i++)
        {
            baseTool::writeResultByJGAndSM((*algTaskVector)[i],UNABLE_IDENTIFY, "车辆类型不在软件处理范围内");
        }

        return false;
    }
    return true;
}

bool _c_algTaskCenter::checkJianYanJiGou(std::string bh, std::string ip, std::vector<_c_algTask *> *algTaskVector)
{
    int errType = 0;
    int nullcnt = 0;
    if(__JYJG.size() > 0)
    {
        for (unsigned int k = 0; k < __JYJG.size(); k++) {
            if (bh == __JYJG[k].bh) {
                if(ip == __JYJG[k].ip || __JYJG[k].ip == "0")
                {
                    return true;
                }
                errType = 1;
            }else if( (__JYJG[k].bh =="" ) && (__JYJG[k].ip =="") )
            {
                nullcnt++;
            }
        }
        //全部被删除的含义为不检测 故返回true
        if( nullcnt == __JYJG.size() )
        {
            return true ;
        }
        for(unsigned int i = 0; i < algTaskVector->size(); i++)
        {
            if(errType)
            {
                baseTool::writeResultByJGAndSM((*algTaskVector)[i],UNABLE_IDENTIFY, "指定的机器(IP:" + ip + ")没有在线，无法处理");
            }else {
                baseTool::writeResultByJGAndSM((*algTaskVector)[i],UNABLE_IDENTIFY, "检验机构不在软件处理范围内");
            }
        }
        return false;
    }
    return true;
}

bool _c_algTaskCenter::checkXinRenJianYanJiGou(std::string bh, std::string ip, std::vector<_c_algTask *> *algTaskVector)
{
    UNUSED(algTaskVector);UNUSED(ip);
    if(__XRJYJG.size() > 0)
    {
        int nullcnt = 0;
        for (unsigned int k = 0; k < __XRJYJG.size(); k++) {
            if (bh == __XRJYJG[k].bh) {
                if(ip == __XRJYJG[k].ip || __XRJYJG[k].ip == "0")
                {
                    return true;
                }
            }else if ( (__XRJYJG[k].bh == "") &&  (__XRJYJG[k].ip =="") ){
                nullcnt++ ;
            }
        }
        if( nullcnt == __XRJYJG.size() )
        {
            return true ;
        }
        return false;
    }
    return true;
}

bool _c_algTaskCenter::checkFuJianCheLiang(std::string mode, std::string isRepeat, std::vector<_c_algTask *> *algTaskVector)
{
    UNUSED(algTaskVector);
    if(__fuJianCheLiangMode == 1 && mode == "1")
    {
        if(isRepeat == "2")
        {
            for(unsigned int i = 0; i < algTaskVector->size(); i++)
            {
                baseTool::writeResultByJGAndSM((*algTaskVector)[i],UNABLE_IDENTIFY, "复检车辆,请注意!");
            }
            return false;
        }
    }else if(__fuJianCheLiangMode == 2 && mode == "2"){
        if(isRepeat == "2")
        {
            return false;
        }
    }
    return true;
}

bool _c_algTaskCenter::checkHeDingZaiKeShu(std::string hdzks, std::vector<_c_algTask *> *algTaskVector)
{
   unsigned int HeDingZaiKeShu = 7;
   std::string outMsg = "当前值";

   //当车辆类型默认未
   if(hdzks != "" && hdzks != "无数据")
   {
       HeDingZaiKeShu = baseTool::str2Int(hdzks);
   }else {
       outMsg += "(默认)";
   }

   if(__HDZKS != 0)
   {
       if(HeDingZaiKeShu > __HDZKS)
       {
           return false;
       }
   }
   UNUSED(algTaskVector);
   return true;
}


bool _c_algTaskCenter::editQianHouSanJiaoJia( _c_session *pSession)
{
    _c_algTask *algTask0111 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0111));
    _c_algTask *algTask0112 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0112));

    //如果有一个为空，就没有必要在做联合赋值
    if (!algTask0111 || !algTask0111->pClass || !algTask0112 || !algTask0112->pClass)
        return SOFT_PASS;

    memberItem *pSanJiaoJia0111 = baseTool::getMemberItemByName(algTask0111->pClass->pResultMemberList, "sanJiaoJia");
    memberItem *pSanJiaoJia0112 = baseTool::getMemberItemByName(algTask0112->pClass->pResultMemberList,"sanJiaoJia");
    //
    memberItem *pisOpenSanJiaoJiaJoin = baseTool::getMemberItemByName(algTask0111->pClass->pResultMemberList,"isOpenSanJiaoJiaJoin");//isOpenSanJiaoJiaJoin

    if( pSanJiaoJia0111 && pSanJiaoJia0112 && pisOpenSanJiaoJiaJoin && pisOpenSanJiaoJiaJoin->config.isOpen)
    {
        bool val = pSanJiaoJia0112->value->result ||  pSanJiaoJia0111->value->result ;
        if(val)
        {
            pSanJiaoJia0111->value->result = true;
            pSanJiaoJia0112->value->result = true;
            {
                std::string reason = "";
                E_JG result = algTask0111->pClass->getResult(&reason);
                algTask0111->setAlgTaskResult((int)result, reason); //对0111的结果重新赋值
            }
            {
                std::string reason = "";
                E_JG result = algTask0112->pClass->getResult(&reason);
                algTask0112->setAlgTaskResult((int)result, reason); //对0112的结果重新赋值
            }
        }
    }
    return SOFT_PASS;

}


bool _c_algTaskCenter::editJiaoQiangXianWanShuiZhengMing( _c_session *pSession)
{
    _c_algTask *algTask0203 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0203));
    _c_algTask *algTask0206 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0206));

    //如果有一个为空，就没有必要在做联合赋值
    if (!algTask0203 || !algTask0203->pClass || !algTask0206 || !algTask0206->pClass)
        return SOFT_PASS;

    memberItem *pcheChuanShui0203 = baseTool::getMemberItemByName(algTask0203->pClass->pResultMemberList, "cheChuanShui");
    memberItem *pcheChuanShui0206 = baseTool::getMemberItemByName(algTask0206->pClass->pResultMemberList, "cheChuanShui");


    if( pcheChuanShui0203 && pcheChuanShui0206  )
    {
        bool val = pcheChuanShui0203->value->result ||  pcheChuanShui0206->value->result ;
        if(val)
        {
            pcheChuanShui0203->value->result = true;
            pcheChuanShui0206->value->result = true;
            {
                std::string reason = "";
                E_JG result = algTask0203->pClass->getResult(&reason);
                algTask0203->setAlgTaskResult((int)result, reason); //对0111的结果重新赋值
            }
            {
                baseTool::closeMemberItemWriteResultByName(algTask0206->pClass->pResultMemberList);
                std::string reason = "";
                E_JG result = algTask0206->pClass->getResult(&reason);
                algTask0206->setAlgTaskResult((int)result, reason); //对0112的结果重新赋值
            }
        }
    }
    return SOFT_PASS;
}

bool _c_algTaskCenter::editZuoYouDengGuang( _c_session *pSession)
{
    _c_algTask *algTask0321 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0321));
    _c_algTask *algTask0352 = baseTool::seachPhotoByZpType(&pSession->algTaskVector, getAlgCodeByType(e0352));
    if(!algTask0321 || !algTask0352 )
    {
        return SOFT_PASS;//不是左右灯光 直接跳过
    }

    if(algTask0321->pClass == NULL || algTask0352->pClass==NULL)
    {
        return SOFT_PASS;//不是左右灯光 直接跳过
    }

    if(algTask0352->result == "4" || algTask0321->result == "4")
    {
         return SOFT_PASS;//有异常清空不需要执行联合判定了
    }
	
	memberItem *chePaiHao1 = baseTool::getMemberItemByName(algTask0321->pClass->pResultMemberList,"chePaiHao"); //拿到左灯光照片的车牌号
    memberItem *chePaiHao2 = baseTool::getMemberItemByName(algTask0352->pClass->pResultMemberList,"chePaiHao"); //拿到右灯光照片的车牌号
    //左右灯光车牌号 正确一个即为通过
    if(chePaiHao1 && chePaiHao2 )
    {
        bool lvalue = chePaiHao1->value->result || chePaiHao2->value->result ;
        chePaiHao1->value->result = lvalue ;
        chePaiHao2->value->result = lvalue ;
    }

    memberItem *pZuoDeng1 = baseTool::getMemberItemByName(algTask0321->pClass->pResultMemberList,"zuoDeng"); //拿到左灯光照片的左灯判定结果
    memberItem *pZuoDeng2 = baseTool::getMemberItemByName(algTask0321->pClass->pResultMemberList,"youDeng"); //拿到左灯光照片的右灯判定结果
    memberItem *pYouDeng1 = baseTool::getMemberItemByName(algTask0352->pClass->pResultMemberList,"zuoDeng"); //拿到右灯光照片的左灯判定结果
    memberItem *pYouDeng2 = baseTool::getMemberItemByName(algTask0352->pClass->pResultMemberList,"youDeng"); //拿到左灯光照片的右灯判定结果
    //左图亮右灯，右图亮左灯
    //左图两灯都亮，右图两灯都不亮。
    //左图两灯都不亮，右图两灯都亮。
    //左图亮左灯，右图亮右灯。
    if (!(pZuoDeng1 && pZuoDeng2 && pYouDeng1 && pYouDeng2 ) )
    {
         return SOFT_PASS;//有空指针 跳过
    }

  //  string cllx = baseTool::getObjectItemValueByName(algTask0321->pClass->pAllParamVector,"cheLiangLeiXing")  ;
  //  if( (cllx.size() > 1 ) && (cllx.at(1) == 'M' ) )// 摩托车
    if(baseTool::checkCllxIsMx(algTask0321->pClass->pAllParamVector) )
    {
        bool val = pZuoDeng1->value->result || pZuoDeng2->value->result || pYouDeng1->value->result || pYouDeng2->value->result ;
        pZuoDeng1->value->result = val;
        pYouDeng1->value->result = val;
    }
    else
    {
        if((pZuoDeng2->value->result && pYouDeng1->value->result) || (pZuoDeng1->value->result && pZuoDeng2->value->result) ||
            (pYouDeng1->value->result && pYouDeng2->value->result) || (pZuoDeng1->value->result && pYouDeng2->value->result))
        {
            pZuoDeng1->value->result = true;
            pZuoDeng2->value->result = true;
            pYouDeng1->value->result = true;
            pYouDeng2->value->result = true;
        }
    }

    std::string reason = "";
    E_JG result =algTask0321->pClass->getResult(&reason);
    algTask0321->setAlgTaskResult((int)result, reason); //对0321的结果重新赋值
    std::string reason1 = "";
    E_JG result1 =algTask0352->pClass->getResult(&reason1);
    algTask0352->setAlgTaskResult((int)result1, reason1); //对0352的结果重新赋值

    return SOFT_PASS;
}

bool _c_algTaskCenter::checkIsSamllVehicle(std::string clzl, std::vector<_c_algTask *> *algTaskVector)
{
     UNUSED(algTaskVector);
     if(__smallVehicle.size() > 0)
     {
         for (unsigned int k = 0; k < __smallVehicle.size(); k++) {
             if (clzl == __smallVehicle[k]) {
                 return true;
             }
         }
         return false;
     }
     return true;
}

//照片列表是否包含全部类型
bool _c_algTaskCenter::checkComplete(bool isTenYears, _c_session *pSession ,std::string& detailReason)
{
     bool  retcode = true ;
     std::vector<_c_algTask *> *algTaskVector = &pSession->algTaskVector;

     detailReason = "[" ;
     //遍历支持的算法列表
     for(unsigned int i = 0; i < __algVector.size(); i++)
     {
         //判断算法是否启用 且 是否是必检测项
         if(__algVector[i].isOpen && __algVector[i].isMust)
         {
             bool isOk = false;
             //判断algvector中 出现的启用类型且需要检测的类型 在algTaskVector中是否出现
             for(unsigned int j = 0; j < algTaskVector->size(); j++)
             {
                 //如果出现则算法类型通过，否则不通过
                 if(__algVector[i].code == (*algTaskVector)[j]->algCode)
                 {
                     isOk = true;
                     break;
                 }
             }

             //如果algTaskVector中未有__algVector中的类型
             //判断下是否是网络接口
             for (unsigned int k = 0; k < pSession->pWangLuoJieKouReturnVector->size(); k++)
             {
                 _c_object *obj = (*pSession->pWangLuoJieKouReturnVector)[k];
                 objectMember* isGetData = baseTool::getObjectItemByName(&obj->memberVector, "isGetData");
                 objectMember* photoCode = baseTool::getObjectItemByName(&obj->memberVector, "photoCode");

                 if (*photoCode->value == __algVector[i].code)
                 {
                     //如果有获取到网络数据
                    if (*isGetData->value == "true")
                    {
                        isOk = true;
//                        printf("############################################## 0203 skip!\n");
                        break;
                    }
                 }
             }

             //判断一下是否是十年免检类型
             if(!isOk&&__algVector[i].isTenYears)
             {
                 //如果是不是十年车则判定通过
                if(!isTenYears)
                {
                   isOk = true;
                }
             }

             //如果出现判定不同则直接退出检测返回完整性判定失败
             if(!isOk)
             {
                 //return false;
                 retcode = false ;
                 detailReason += __algVector[i].code + " " ;

             }
         }
     }
     detailReason+="]" ;
     return retcode;
}

E_ZZJG _c_algTaskCenter::checkUnqualified(bool isTenYears, std::vector<_c_algTask *> *algTaskVector, std::string& sessionReason)
{
    UNUSED(isTenYears);
    E_ZZJG result = SOFT_PASS;
    //遍历车辆图片列表
    for(unsigned int j = 0; j < algTaskVector->size(); j++)
    {
        //遍历程序支持的照片列表
        for(unsigned int i = 0; i < __algVector.size(); i++)
        {
            //如果照片的加入整车判定
            if(__algVector[i].code == (*algTaskVector)[j]->algCode && __algVector[i].isOpen && (__algVector[i].needCheck || __algVector[i].isMust))
            {
                //无关联项
                if (__algVector[i].link == "无" || __algVector[i].link.empty() || __algVector[i].link.size() < 4)
                {
                    //照片判定不通过则不通过
                    if((*algTaskVector)[j]->result == std::to_string(NOT_PASS))
                    {
                        sessionReason = "["+__algVector[i].name + "]-审核不通过";
                        return SOFT_NOTPASS;
                    }
                    //照片判定为需要人工这继续判定其他照片s
                    else if((*algTaskVector)[j]->result == std::to_string(UNABLE_IDENTIFY))
                    {
                        sessionReason = "["+__algVector[i].name + "]-需要人工";
                        result = SOFT_ERR;
                    }
                }
                else
                {
                    //如果需要关联判定则以关联判定后结果为该照片的结果
                    std::vector<std::string> splitVector;
                    splitVector.clear();
                    baseTool::split(";", __algVector[i].link, splitVector);
                    bool b_result = ((*algTaskVector)[j]->result == std::to_string(PASS));
                    for (unsigned int k = 0; k < splitVector.size(); k++)
                    {
                        if(splitVector[k].size() < 3)
                        {
                            continue;
                        }
                        std::string code = splitVector[k].substr(2, splitVector[k].size() - 2);
                        _c_algTask *algTask = baseTool::seachPhotoByZpType(algTaskVector, code);
                        if(algTask)
                        {
                            if(splitVector[k][0] == 'q')
                            {
                                b_result = b_result&&(algTask->result == std::to_string(PASS));
                            }
                            else if(splitVector[k][0] == 'h')
                            {
                                b_result = b_result||(algTask->result == std::to_string(PASS));
                            }
                        }
                        else
                        {
                            if(splitVector[k][0] == 'q')
                            {
                               b_result = false;
                            }
                        }
                        //E_JG ret = baseTool::checkAlgItemLinkResult((*algTaskVector)[j]->result, splitVector[k], algTaskVector);
                    }
                    if (!b_result)
                    {
                         sessionReason = "["+__algVector[i].name + "]-link审核不通过";
                         return SOFT_NOTPASS;
                    }
                }
                break;
            }
        }
    }

    return result;
}

_c_algTask *_c_algTaskCenter::getAlgTaskByGuid(std::string algTaskGuid)
{
   unsigned int timeOut = __timeOutMilliSeconds * 950;//任务在超时时间95%内则正常返回，用于防止超时回收和任务回收冲突
   for (unsigned int i = 0; i < _TaskMap.size(); i++) {
       if(_TaskMap[i]->checkUuid(algTaskGuid)&&_TaskMap[i]->getInSystemTime() < timeOut)
       {
           return _TaskMap[i];
       }
   }
   return NULL;
}


std::string _c_algTaskCenter::getAlgCodeByType(PicType type)
{
    for (unsigned int i = 0; i < __algVector.size(); i++) {
        if(type == __algVector[i].type)
        {
            return __algVector[i].code;
        }
    }
    return " ";
}

void _c_algTaskCenter::getSubAlgClass(algItem *pAlgItem)
{
    for(unsigned int i = 0; i < __algVector.size(); i++)
    {
        if(pAlgItem->type == __algVector[i].type)
        {
            pAlgItem->subAlgClass = __algVector[i].subAlgClass;
            return ;
        }
    }
}

bool _c_algTaskCenter::changeAlgVectorByType(algItem *pAlgItem)
{
    //遍历__algVector 并找到 类型匹配的算法algItem
    for(unsigned int i = 0; i < __algVector.size(); i++)
    {
        if(pAlgItem->type == __algVector[i].type)
        {
            //设置参数
            if(pAlgItem->code != "")
                __algVector[i].code = pAlgItem->code;
            if(pAlgItem->name != "")
                __algVector[i].name = pAlgItem->name;

            __algVector[i].isOpen = pAlgItem->isOpen;
            __algVector[i].needCheck = pAlgItem->needCheck;
            __algVector[i].subAlgClass = pAlgItem->subAlgClass;
            __algVector[i].isTenYears = pAlgItem->isTenYears;
            __algVector[i].isMust = pAlgItem->isMust;

            if(pAlgItem->link.empty())
            {
                pAlgItem->link = "无";
            }

            std::string tip = baseTool::checkAlgItemLinkIsValid(pAlgItem->link, &__algVector);
            if (tip.empty())
            {
                __algVector[i].link = pAlgItem->link;
            }
            else
            {
                __algVector[i].link = pAlgItem->link + tip;
            }

            return true;
        }
    }
    return false;
}

bool _c_algTaskCenter::addAlgVectorByItem(algItem item)
{
    //遍历__algVector 并找到 类型匹配的算法algItem
    for(unsigned int i = 0; i < __algVector.size(); i++)
    {
        if(item.type == __algVector[i].type)
        {
            return false;
        }
    }
    __algVector.push_back(item);
    return true;

}

Json::Value _c_algTaskCenter::getOpenAlg()
{
    Json::Value root;
    for(unsigned int i=0; i <  __algVector.size(); i++)
    {
        if(__algVector[i].isOpen)
        {
            Json::Value subRoot;
            subRoot["name"]=__algVector[i].code;
            root.append(subRoot);
        }
    }
    return root;
}

void _c_algTaskCenter::saveConfig()
{
    Json::Value  root;
    root["algVector"] = getAlgVectorJson(&__algVector);
    root["smallVehicle"] = getSmallVehicleVectorJson();
    root["checkCllx"] = getCLZLVectorJson();

    root["cityShortName"] = __cityShortName;
    root["isOpenCoreDump"] = __IsOpenCoreDump;
    root["isOpenFilterJianYanJiGou"] = __isOpenFilterJianYanJiGou;
    root["jianYanLeiBie"] = getJYLBVectorJson();
    root["shiYongXingZhi"] = getSYXZVectorJson();
    root["jianYanJiGou"] = getJYJGVectorJson();
    root["xinRenJianYanJiGou"] = getXinRenJYJGVectorJson();
    root["heDingZaiKeShu"] = __HDZKS;
    root["heiMingDan"] = getHMDVectorJson();
    root["cjhHeiMingDan"] = getCjhHMDVectorJson();
    root["httpBaiMingDan"] = getHttpBMDVectorJson();
    root["chaoShiShiJian"] = __timeOutMilliSeconds;
    root["fuJianCheLiangMode"] = __fuJianCheLiangMode;
    root["soapMaxReqTimes"] = __soapMaxReqTimes ;

    std::ofstream ofs;
    std::string path =__configRoot + "/algConfig";
    baseTool::CheckDir(path);

    char configPath[2048]={0};
    sprintf(configPath,"%s/processClassConfig_%d.json",path.c_str(),__cityType);

    ofs.open(configPath);
//    printf("json:%s\n",root.toStyledString().c_str());
    ofs << root.toStyledString();

    ofs.close();

}

Json::Value _c_algTaskCenter::getAlgVectorJson(std::vector<algItem> *pAlgVector)
{
    Json::Value root;
    for(unsigned int i=0; i <  pAlgVector->size(); i++)
    {
        Json::Value subRoot;
        subRoot["type"]=(*pAlgVector)[i].type;
        subRoot["name"]=(*pAlgVector)[i].name;
        subRoot["code"]=(*pAlgVector)[i].code;
        subRoot["isOpen"]=(*pAlgVector)[i].isOpen;
        subRoot["isTenYears"]=(*pAlgVector)[i].isTenYears;
        subRoot["needCheck"]=(*pAlgVector)[i].needCheck;
        subRoot["isMust"]=(*pAlgVector)[i].isMust;
        subRoot["link"]=(*pAlgVector)[i].link;

        root.append(subRoot);
    }
    return root;
}

void _c_algTaskCenter::loadConfig()
{
    std::ifstream fin;
    char configPath[2048]={0};
    sprintf(configPath,"%s/algConfig/processClassConfig_%d.json",__configRoot.c_str(),__cityType);

    fin.open(configPath);
    if (fin.is_open()) {
        Json::Value  root;
        Json::Reader reader;
        if (reader.parse(fin, root, false))
        {
           if(!root["algVector"].empty())
                setAlgVectorConfig(root["algVector"],&__algVector);

           __smallVehicle.clear();
           if(!root["smallVehicle"].empty())
                setSmallVehicleVectorConfig(root["smallVehicle"],&__smallVehicle);

           __CLZL.clear();
           if(!root["checkCllx"].empty())
                setCLZLVectorConfig(root["checkCllx"],&__CLZL);
           if(!root["cityShortName"].empty())
                setCityShortNameConfig(root["cityShortName"].asString());

           if(!root["isOpenCoreDump"].empty())
                setOpenCoredumpConfig(root["isOpenCoreDump"].asString());
           if(!root["isOpenFilterJianYanJiGou"].empty())
                setOpenFilterJianYanJiGou(root["isOpenFilterJianYanJiGou"].asString());

           __JYLB.clear();
           if(!root["jianYanLeiBie"].empty())
                setJYLBVectorConfig(root["jianYanLeiBie"],&__JYLB);

           __SYXZ.clear();
           if(!root["shiYongXingZhi"].empty())
                setSYXZVectorConfig(root["shiYongXingZhi"],&__SYXZ);

           __JYJG.clear();
           if(!root["jianYanJiGou"].empty())
                setJYJGVectorConfig(root["jianYanJiGou"],&__JYJG);

           __XRJYJG.clear();
           if(!root["xinRenJianYanJiGou"].empty())
                setJYJGVectorConfig(root["xinRenJianYanJiGou"],&__XRJYJG);

           if(!root["heDingZaiKeShu"].empty())
                setHeDingZaiKeShuConfig(root["heDingZaiKeShu"].asInt());

           if(!root["fuJianCheLiangMode"].empty())
                setFuJianCheLiangMode(root["fuJianCheLiangMode"].asInt());
           if(!root["soapMaxReqTimes"].empty())
                setsoapMaxReqTimes(root["soapMaxReqTimes"].asInt());

           if(!root["chaoShiShiJian"].empty())
                setChaoShiShiJianConfig(root["chaoShiShiJian"].asInt());

           __HMD.clear();
           if(!root["heiMingDan"].empty()){
                setHMDVectorConfig(root["heiMingDan"],&__HMD);
            }
           __CjhHMD.clear();
           if(!root["cjhHeiMingDan"].empty()){
                setCjhHMDVectorConfig(root["cjhHeiMingDan"],&__CjhHMD);
           }
           __HttpMD.clear();
           if(!root["httpBaiMingDan"].empty())
                setHttpMDVectorConfig(root["httpBaiMingDan"],&__HttpMD);
        }
    }
    fin.close();

    std::string jyjgstr ="检验机构[";
    for(unsigned int i = 0; i <  __JYJG.size(); i++)
    {
        jyjgstr+="{\"bh\":\""+__JYJG[i].bh+"\",\"ip\":\""+__JYJG[i].ip+"\"}";
        if( i+1 < __JYJG.size())
        {
            jyjgstr += ", ";
        }
    }
    jyjgstr += "]";
//    baseTool::msgOut(baseTool::MSG, __FILE__, __LINE__,  jyjgstr);

    std::string jylbstr = "检验类别[";
    for(unsigned int i = 0; i <  __JYLB.size(); i++)
    {
       jylbstr +="{\"jylb\":\""+__JYLB[i]+"\"}";
        if( i+1 < __JYLB.size())
        {
            jylbstr +=", ";
        }
    }
    jylbstr +="]";
//    baseTool::msgOut(baseTool::MSG, __FILE__, __LINE__,  jylbstr);

    std::string syxzstr = "使用性质[";
    for(unsigned int i = 0; i <  __SYXZ.size(); i++)
    {
       syxzstr +="{\"syxz\":\""+__SYXZ[i]+"\"}";
        if( i+1 < __SYXZ.size())
        {
            syxzstr +=", ";
        }
    }
    syxzstr +="]";
//    baseTool::msgOut(baseTool::MSG, __FILE__, __LINE__,  syxzstr);

    std::string cllxstr = "车辆类型[";
    for(unsigned int i = 0; i <  __CLZL.size(); i++)
    {
        cllxstr +="{\"cllx\":\""+__CLZL[i]+"\"}";
        if( i+1 < __CLZL.size())
        {
            cllxstr +=", ";
        }
    }
    cllxstr +="]";
//    baseTool::msgOut(baseTool::MSG, __FILE__, __LINE__,  cllxstr);

//    baseTool::msgOut(baseTool::MSG, __FILE__, __LINE__,  "核定载客数:"+std::to_string(__HDZKS));

    std::string xiaoChestr = "小车车辆类型[";
    for(unsigned int i = 0; i <  __smallVehicle.size(); i++)
    {
        xiaoChestr +="{\"cllx\":\""+__smallVehicle[i]+"\"}";
        if( i+1 < __smallVehicle.size())
        {
            xiaoChestr +=", ";
        }
    }
    xiaoChestr +="]";
//    baseTool::msgOut(baseTool::MSG, __FILE__, __LINE__,  xiaoChestr);

    std::string heiMingDanStr = "黑名单[";
    for(unsigned int i = 0; i <  __HMD.size(); i++)
    {
        heiMingDanStr +="{\"hmd\":\""+__HMD[i]+"\"}";
        if( i+1 < __HMD.size())
        {
            heiMingDanStr +=", ";
        }
    }
    heiMingDanStr +="]";
//    baseTool::msgOut(baseTool::MSG, __FILE__, __LINE__,  heiMingDanStr);
   std::string cjhHeiMingDanStr = "车架号黑名单[";
    for(unsigned int i = 0; i <  __CjhHMD.size(); i++)
    {
        cjhHeiMingDanStr +="{\"cjhHmd\":\""+__CjhHMD[i]+"\"}";
        if( i+1 < __CjhHMD.size())
        {
            cjhHeiMingDanStr +=", ";
        }
    }
    cjhHeiMingDanStr +="]";
    std::string httpBaiMingDanStr = "http白名单[";
    for(unsigned int i = 0; i <  __HttpMD.size(); i++)
    {
        httpBaiMingDanStr +="{\"httpBmd\":\""+__HttpMD[i]+"\"}";
        if( i+1 < __HttpMD.size())
        {
            httpBaiMingDanStr +=", ";
        }
    }
    httpBaiMingDanStr +="]";
//    baseTool::msgOut(baseTool::MSG, __FILE__, __LINE__,  heiMingDanStr);

    std::string algClassstr = "算法关系表[\n";
    for(unsigned int i = 0; i <  __algVector.size(); i++)
    {
       algClassstr +="{\"PicType\":\""+std::to_string(__algVector[i].type)+"\", \"code\":\""+__algVector[i].code+"\", \"isOpen\":"+std::to_string(__algVector[i].isOpen)+", \"needCheck\":"+std::to_string(__algVector[i].needCheck)+", \"subAlgClass\":"+std::to_string(__algVector[i].subAlgClass)+", \"isTenYears\":"+std::to_string(__algVector[i].isTenYears)+", \"name\":\""+__algVector[i].name+"\"}";
        if( i+1 < __algVector.size())
        {
            algClassstr +=",\n";
        }
    }
    algClassstr +="]";
   // baseTool::msgOut(baseTool::MSG, __FILE__, __LINE__,  algClassstr);
}

void _c_algTaskCenter::setAlgVectorConfig(Json::Value root,std::vector<algItem> *pAlgVector)
{
    for(unsigned int i=0;i<root.size();i++)
    {
        for(unsigned int j=0; j <  pAlgVector->size(); j++)
        {
            if((*pAlgVector)[j].type == root[i]["type"].asInt())
            {
                if(!root[i]["code"].empty())
                    (*pAlgVector)[j].code = root[i]["code"].asString();
                if(!root[i]["name"].empty())
                    (*pAlgVector)[j].name = root[i]["name"].asString();
                if(!root[i]["isOpen"].empty())
                    (*pAlgVector)[j].isOpen = root[i]["isOpen"].asBool();
                if(!root[i]["needCheck"].empty())
                    (*pAlgVector)[j].needCheck = root[i]["needCheck"].asBool();
                if(!root[i]["isTenYears"].empty())
                    (*pAlgVector)[j].isTenYears = root[i]["isTenYears"].asBool();
                if(!root[i]["isMust"].empty())
                    (*pAlgVector)[j].isMust = root[i]["isMust"].asBool();
                if(!root[i]["link"].empty())
                    (*pAlgVector)[j].link = root[i]["link"].asString();
            }
        }
    }
}

Json::Value _c_algTaskCenter::getSYXZVectorJson()
{
    Json::Value root;
    for(unsigned int i=0; i <  __SYXZ.size(); i++)
    {
        if(!__SYXZ[i].empty())
        {
            Json::Value subRoot;
           subRoot["syxz"]=__SYXZ[i];
           root.append(subRoot);
        }
    }
    return root;
}

void _c_algTaskCenter::setSYXZVectorConfig(Json::Value root,std::vector<std::string> *pVector)
{
    if(!(root.size() > 0))
    {
        return;
    }
    pVector->clear();
    for(unsigned int i=0;i<root.size();i++)
    {
        std::string syxz = root[i]["syxz"].asString();
        pVector->push_back(syxz);
    }
}

void _c_algTaskCenter::deleteCheckShiYongXingZhiByKey(std::string key)
{
    for(unsigned int i=0; i <  __SYXZ.size(); i++)
    {
        if(__SYXZ[i]==key)
        {
            __SYXZ[i] = "";
        }
    }
}

void _c_algTaskCenter::addCheckShiYongXingZhiByKey(std::string key)
{
    if(!key.empty())
    {
        for(unsigned int i=0; i <  __SYXZ.size(); i++)
        {
            if(__SYXZ[i]==key)
            {
                return;
            }
        }
        __SYXZ.push_back(key);
    }
}



Json::Value _c_algTaskCenter::getCLZLVectorJson()
{
    Json::Value root;
    for(unsigned int i=0; i <  __CLZL.size(); i++)
    {
        if(!__CLZL[i].empty())
        {
            Json::Value subRoot;
            subRoot["cllx"]=__CLZL[i];
            root.append(subRoot);
        }
    }

    return root;

}

void _c_algTaskCenter::setCLZLVectorConfig(Json::Value root,std::vector<std::string> *pVector)
{
    if(!(root.size() > 0))
    {
        return;
    }
    pVector->clear();
    for(unsigned int i=0;i<root.size();i++)
    {
        std::string cllx = root[i]["cllx"].asString();
        //if(baseTool::checkCllx(cllx))
        {
            pVector->push_back(cllx);
        }
    }
}

void _c_algTaskCenter::deleteCheckCheLiangZhongLeiByKey(std::string key)
{
    for(unsigned int i=0; i <  __CLZL.size(); i++)
    {
        if(__CLZL[i]==key)
        {
            __CLZL[i] = "";
        }
    }
}

void _c_algTaskCenter::addCheckCheLiangZhongLeiByKey(std::string key)
{
    if(!key.empty())
    {
        for(unsigned int i=0; i <  __CLZL.size(); i++)
        {
            if(__CLZL[i]==key)
            {
                return;
            }
        }
        __CLZL.push_back(key);
    }
}

Json::Value _c_algTaskCenter::getSmallVehicleVectorJson()
{
    Json::Value root;
    for(unsigned int i=0; i <  __smallVehicle.size(); i++)
    {
        if(!__smallVehicle[i].empty())
        {
            Json::Value subRoot;
            subRoot["cllx"]=__smallVehicle[i];
            root.append(subRoot);
        }
    }
    return root;
}

void _c_algTaskCenter::deleteCheckSmallVehicleVectorByKey(std::string key)
{
    for(unsigned int i=0; i <  __smallVehicle.size(); i++)
    {
        if(__smallVehicle[i]==key)
        {
            __smallVehicle[i] = "";
        }
    }
}

void _c_algTaskCenter::addCheckSmallVehicleVectorByKey(std::string key)
{
    if(!key.empty())
    {
        for(unsigned int i=0; i <  __smallVehicle.size(); i++)
        {
            if(__smallVehicle[i]==key)
            {
                return;
            }
        }
        __smallVehicle.push_back(key);
    }
}

Json::Value _c_algTaskCenter::getJYLBVectorJson()
{
    Json::Value root;
    for(unsigned int i=0; i <  __JYLB.size(); i++)
    {
        if(!__JYLB[i].empty())
        {
            Json::Value subRoot;
            subRoot["jylb"]=__JYLB[i];
            root.append(subRoot);
        }
    }
    return root;

}

void _c_algTaskCenter::setJYLBVectorConfig(Json::Value root,std::vector<std::string> *pVector)
{
    if(!(root.size() > 0))
    {
        return;
    }
    pVector->clear();
    for(unsigned int i=0;i<root.size();i++)
    {
        std::string jylb = root[i]["jylb"].asString();
        pVector->push_back(jylb);
    }
}

void _c_algTaskCenter::deleteCheckJianYanLeiBieByKey(std::string key)
{
    for(unsigned int i=0; i <  __JYLB.size(); i++)
    {
        if(__JYLB[i]==key)
        {
            __JYLB[i] = "";
        }
    }
}

void _c_algTaskCenter::addCheckJianYanLeiBieByKey(std::string key)
{
    if(!key.empty())
    {
        for(unsigned int i=0; i <  __JYLB.size(); i++)
        {
            if(__JYLB[i]==key)
            {
                return;
            }
        }
        __JYLB.push_back(key);
    }
}

Json::Value _c_algTaskCenter::getJYJGVectorJson()
{
    Json::Value root;
    for(unsigned int i=0; i <  __JYJG.size(); i++)
    {
        if(!__JYJG[i].bh.empty())
        {
            Json::Value subRoot;
            subRoot["bh"]=__JYJG[i].bh;
            subRoot["ip"]=__JYJG[i].ip;
            root.append(subRoot);
        }
    }
    return root;

}

void _c_algTaskCenter::deleteCheckJianYanJiGouByKey(std::string bh)
{
    for(unsigned int i=0; i <  __JYJG.size(); i++)
    {
        if(__JYJG[i].bh==bh)
        {
            __JYJG[i].bh = "";
            __JYJG[i].ip = "";
        }
    }
}

void _c_algTaskCenter::addCheckJianYanJiGouByKey(std::string bh,std::string ip)
{
    if(!bh.empty()&&!ip.empty())
    {
        for(unsigned int i=0; i <  __JYJG.size(); i++)
        {
            if(__JYJG[i].bh == bh&&__JYJG[i].ip==ip)
            {
                return;
            }
        }
        JYJG jyjg;
        jyjg.ip = ip;
        jyjg.bh = bh;
        __JYJG.push_back(jyjg);
    }
}

void _c_algTaskCenter::setJYJGVectorConfig(Json::Value root,std::vector<JYJG> *pVector)
{
    if(!(root.size() > 0))
    {
        return;
    }
    pVector->clear();
    for(unsigned int i=0;i<root.size();i++)
    {
        JYJG jyjg;
        jyjg.bh = root[i]["bh"].asString();
        jyjg.ip = root[i]["ip"].asString();
        pVector->push_back(jyjg);
    }
}

Json::Value _c_algTaskCenter::getXinRenJYJGVectorJson()
{
    Json::Value root;
    for(unsigned int i=0; i <  __XRJYJG.size(); i++)
    {
        if(!__XRJYJG[i].bh.empty())
        {
            Json::Value subRoot;
            subRoot["bh"]=__XRJYJG[i].bh;
            subRoot["ip"]=__XRJYJG[i].ip;
            root.append(subRoot);
        }
    }
    return root;
}

void _c_algTaskCenter::deleteCheckXinRenJianYanJiGouByKey(std::string bh)
{
    for(unsigned int i=0; i <  __XRJYJG.size(); i++)
    {
        if(__XRJYJG[i].bh==bh)
        {
            __XRJYJG[i].bh = "";
            __XRJYJG[i].ip = "";
        }
    }
}

void _c_algTaskCenter::addCheckXinRenJianYanJiGouByKey(std::string bh,std::string ip)
{
    if(!bh.empty()&&!ip.empty())
    {
        for(unsigned int i=0; i <  __XRJYJG.size(); i++)
        {
            if(__XRJYJG[i].bh == bh&&__XRJYJG[i].ip==ip)
            {
                return;
            }
        }
        JYJG jyjg;
        jyjg.ip = ip;
        jyjg.bh = bh;
        __XRJYJG.push_back(jyjg);
    }
}

void _c_algTaskCenter::setXinRenJYJGVectorConfig(Json::Value root,std::vector<JYJG> *pVector)
{
    if(!(root.size() > 0))
    {
        return;
    }
    pVector->clear();
    for(unsigned int i=0;i<root.size();i++)
    {
        JYJG jyjg;
        jyjg.bh = root[i]["bh"].asString();
        jyjg.ip = root[i]["ip"].asString();
        pVector->push_back(jyjg);
    }
}

Json::Value _c_algTaskCenter::getHMDVectorJson()
{
    Json::Value root;
    for(unsigned int i=0; i <  __HMD.size(); i++)
    {
        if(!__HMD[i].empty())
        {
            Json::Value subRoot;
            subRoot["hmd"]=__HMD[i];
            root.append(subRoot);
        }
    }
    return root;
}
Json::Value _c_algTaskCenter::getCjhHMDVectorJson()
{
    Json::Value root;
    for(unsigned int i=0; i <  __CjhHMD.size(); i++)
    {
        if(!__CjhHMD[i].empty())
        {
            Json::Value subRoot;
            subRoot["cjhHmd"]=__CjhHMD[i];
            root.append(subRoot);
        }
    }
    return root;
}
Json::Value _c_algTaskCenter::getHttpBMDVectorJson()
{
    Json::Value root;
    for(unsigned int i=0; i <  __HttpMD.size(); i++)
    {
        if(!__HttpMD[i].empty())
        {
            Json::Value subRoot;
            subRoot["httpBmd"]=__HttpMD[i];
            root.append(subRoot);
        }
    }
    return root;
}
void _c_algTaskCenter::setHMDVectorConfig(Json::Value root,std::vector<std::string> *pVector)
{
    if(!(root.size() > 0))
    {
        return;
    }
    pVector->clear();

    printf("setHMDVectorConfig : %d \n",root.size());

    for(unsigned int i=0;i<root.size();i++)
    {
        std::string hdm = root[i]["hmd"].asString();
        {
            pVector->push_back(hdm);
        }
    }
}
void _c_algTaskCenter::setCjhHMDVectorConfig(Json::Value root,std::vector<std::string> *pVector)
{
    if(!(root.size() > 0))
    {
        return;
    }
    pVector->clear();
    printf("setCjhHMDVectorConfig : %d \n",root.size());
    for(unsigned int i=0;i<root.size();i++)
    {
        std::string hdm = root[i]["cjhHmd"].asString();
        //if(baseTool::checkCllx(cllx))
        {
            pVector->push_back(hdm);
        }
    }
}
void _c_algTaskCenter::setHttpMDVectorConfig(Json::Value root,std::vector<std::string> *pVector)
{
    if(!(root.size() > 0))
    {
        return;
    }
    pVector->clear();

    printf("setHttpMDVectorConfig : %d \n",root.size());

    for(unsigned int i=0;i<root.size();i++)
    {
        std::string hdm = root[i]["httpBmd"].asString();
        //if(baseTool::checkCllx(cllx))
        {
            pVector->push_back(hdm);
        }
    }
}
void _c_algTaskCenter::deleteHeiMingDanByChePai(std::string chePai)
{
    for(unsigned int i=0; i <  __HMD.size(); i++)
    {
        if(__HMD[i]==chePai)
        {
            __HMD[i] = "";
        }
    }

}
void _c_algTaskCenter::deleteCjhHeiMingDanByCheJiaHao(std::string cheJiaHao)
{
    for(unsigned int i=0; i <  __CjhHMD.size(); i++)
    {
        if(__CjhHMD[i]==cheJiaHao)
        {
            __CjhHMD[i] = "";
        }
    }
}
void _c_algTaskCenter::deleteHttpBaiMingDanByIpAddr(std::string ipaddr)
{
    for(unsigned int i=0; i <  __HttpMD.size(); i++)
    {
        if(__HttpMD[i]==ipaddr)
        {
            __HttpMD[i] = "";
        }
    }
}

void _c_algTaskCenter::addHeiMingDanByChePai(std::string chePai)
{
    if(!chePai.empty())
    {
        for(unsigned int i=0; i <  __HMD.size(); i++)
        {
            if(__HMD[i]==chePai)
            {
                return;
            }
        }
        __HMD.push_back(chePai);
    }
}
void _c_algTaskCenter::addCjhHeiMingDanByCheJiaHao(std::string cheJiaHao)
{
    if(!cheJiaHao.empty())
    {
        for(unsigned int i=0; i <  __CjhHMD.size(); i++)
        {
            if(__CjhHMD[i]==cheJiaHao)
            {
                return;
            }
        }
        __CjhHMD.push_back(cheJiaHao);
    }

}

void _c_algTaskCenter::addHttpBaiMingDanByipaddr(std::string ipaddr)
{
    if(!ipaddr.empty())
    {
        for(unsigned int i=0; i <  __HttpMD.size(); i++)
        {
            if(__HttpMD[i]==ipaddr)
            {
                return;
            }
        }
        __HttpMD.push_back(ipaddr);
    }

}

//超时时间
void _c_algTaskCenter::setChaoShiShiJianConfig(unsigned int timeOut)
{
    __timeOutMilliSeconds = timeOut;
}

unsigned int _c_algTaskCenter::getChaoShiShiJian()
{
    return __timeOutMilliSeconds;
}


void _c_algTaskCenter::setHeDingZaiKeShuConfig(unsigned int hdzks)
{
    __HDZKS = hdzks;
}

unsigned int _c_algTaskCenter::getHeDingZaiHeShu()
{
    return __HDZKS;
}

void _c_algTaskCenter::setsoapMaxReqTimes(unsigned int  soapMaxReqTimes)
{
    __soapMaxReqTimes =  soapMaxReqTimes;
}
unsigned int _c_algTaskCenter::getsoapMaxReqTimes()
{
    return __soapMaxReqTimes;
}
void _c_algTaskCenter::setFuJianCheLiangMode(unsigned int fuJianCheLiangMode)
{
    __fuJianCheLiangMode = fuJianCheLiangMode;
}

unsigned int _c_algTaskCenter::getFuJianCheLiangMode()
{
    return __fuJianCheLiangMode;
}


void _c_algTaskCenter::setCityShortNameConfig(std::string shortName)
{
    __cityShortName = shortName;
}

void _c_algTaskCenter::setOpenCoredumpConfig(std::string isopen)
{
    if( isopen == "true" || isopen == "TRUE"  ){
        isopen = "true" ;
    }else{
        isopen = "false" ;
    }
    __IsOpenCoreDump = isopen;
}
void _c_algTaskCenter::setOpenFilterJianYanJiGou(std::string isopen)
{
    if( isopen == "true" || isopen == "TRUE"  ){
        isopen = "true" ;
    }else{
        isopen = "false" ;
    }
    __isOpenFilterJianYanJiGou = isopen ;
}

std::string _c_algTaskCenter::getCityShortNmae()
{
    return __cityShortName;
}
std::string _c_algTaskCenter::getOpenCoredump()
{
    return __IsOpenCoreDump;
}
std::string _c_algTaskCenter::getOpenFilterJianYanJiGou()
{
    return __isOpenFilterJianYanJiGou;
}
std::string _c_algTaskCenter::getCityType()
{
    return std::to_string(__cityType);
}

void _c_algTaskCenter::setSmallVehicleVectorConfig(Json::Value root,std::vector<std::string> *pVector)
{
    if(!(root.size() > 0))
    {
        return;
    }
    pVector->clear();
    for(unsigned int i=0;i<root.size();i++)
    {
        std::string cllx = root[i]["cllx"].asString();
        //if(baseTool::checkCllx(cllx))
        {
            pVector->push_back(cllx);
        }
    }
}

void _c_algTaskCenter::getAlgVectorCategory(std::vector<std::string> *pCategoryVector)
{
    for(unsigned int j = 0; j < __algVector.size(); j++)
    {
            if( __algVector[j].isOpen)
            {
                pCategoryVector->push_back(__algVector[j].code);
            }
    }
}

