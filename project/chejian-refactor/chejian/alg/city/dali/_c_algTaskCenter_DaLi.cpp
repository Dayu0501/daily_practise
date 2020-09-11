#include "_c_algTaskCenter_DaLi.h"

bool CompareCodeTask(_c_algTask* point_lhs,_c_algTask* point_rhs)
{
    return point_lhs->algCode < point_rhs->algCode;
}

_c_algTaskCenter_DaLi::_c_algTaskCenter_DaLi(CityType cityType,PREDIS_PARAM redisParam):_c_algTaskCenter(cityType,redisParam)
{

}

#if 0
//所有针对一辆车检测之后，图片与图片之间关联判定的逻辑就在此实现。
E_ZZJG _c_algTaskCenter_DaLi::subAfterAlgCheck(E_ZZJG baseResult, _c_session *pSession, std::string& sessionReason)
{
    UNUSED(sessionReason);
    UNUSED(baseResult);

    std::vector<_c_algTask *>* algTaskVector = &pSession->algTaskVector;
    if(!algTaskVector)
    {
        LOG(SESSION,ERR,"this vehicle lack all must pictures \n");
        return SOFT_PASS;
    }

    std::sort(algTaskVector->begin(),algTaskVector->end(),CompareCodeTask);
    std::vector<std::string> vec_lack_pics;
    getLackPicTypes(vec_must_picTypes,algTaskVector,vec_lack_pics);

    std::string ccdjrq = baseTool::getObjectItemValueByName(&pSession->paramVector,"chuCiDengJiRiQi");
    bool isTenYear = baseTool::isTenYears(ccdjrq);
    LOG(ALG, INFO, "%s : isTenYesr = [%d]", __PRETTY_FUNCTION__, isTenYear);
    if(isTenYear) //如果车辆等级时间 > 10 年
    {
        getLackPicTypes(vec_must_picTypes_tenYears,algTaskVector,vec_lack_pics);
    } 

    //如果没有电子保单，需要判定0203照片是否存在.
    bool bfind = false;
    for (unsigned int i = 0; i < pSession->pWangLuoJieKouReturnVector->size(); i++)
    {
        std::string biaoShi = baseTool::getWangLuoJieKouReturnInfoBiaoShi(pSession->pWangLuoJieKouReturnVector->at(i));
        if (biaoShi == "18C23")
        {
            bfind = true;
        }
    }

    //如果没有电子保单，需要判定0203照片是否存在.
    if(bfind == false)
    {
        std::string code0203 = getAlgCodeByType(e0203);
        _c_algTask* algTask0203 = baseTool::seachPhotoByZpType(algTaskVector,code0203);
        if(!algTask0203)
        {
            vec_lack_pics.push_back(code0203);
        }
    }

    _c_algTask* first_pic_type = algTaskVector->at(0);
    std::string strErrorMsg = first_pic_type->reason;
    for(auto vt:vec_lack_pics)
    {
        strErrorMsg = strErrorMsg + "[" + "缺少：" + vt + getAlgCodeNameByCode(vt) + "]"; 
    }

//    int result = baseTool::str2Int(first_pic_type->result);
    if(vec_lack_pics.size() > 0)
    {
        first_pic_type->setAlgTaskResult(5, strErrorMsg); 
    }

    return SOFT_PASS;
}

void _c_algTaskCenter_DaLi::getLackPicTypes(std::vector<std::string>& vec_must_picTypes,std::vector<_c_algTask *>* algTaskVector,
    std::vector<std::string>& vec_lack_pics)
{
    bool bfind = false;
    for(auto vt:vec_must_picTypes)
    {
        bfind = false;
        for(auto vtt: *algTaskVector)
        {
            if(vtt->algCode == vt)
            {
                bfind = true;
                break;
            }
        }

        if(!bfind)
        {
            vec_lack_pics.push_back(vt);
        }
    }

}
#endif

std::string _c_algTaskCenter_DaLi::getAlgCodeNameByCode(std::string& code)
{
    std::vector<algItem>* algVector= getAlgVector();

    for(auto vt:*algVector)
    {
        if(vt.code == code )
        {
            return vt.name;
        }
    }

    return "";
}

bool _c_algTaskCenter_DaLi::checkComplete(bool isTenYears, _c_session *pSession, std::string& sessionReason)
{
    UNUSED(sessionReason);
    std::vector<_c_algTask *> *algTaskVector = &pSession->algTaskVector;
    std::sort(algTaskVector->begin(),algTaskVector->end(),CompareCodeTask);
    std::vector<algItem>* algTaskVector_need = getAlgVector();
    std::vector<std::string> vec_lack_pics;
    bool bfind = false;
    //遍历支持的算法列表
     for(unsigned int i = 0; i < algTaskVector_need->size(); i++)
     {
         //判断算法是否启用 且 是否是必检测项
         if(algTaskVector_need->at(i).isOpen && algTaskVector_need->at(i).isMust)
         {
             bfind = false;
             //判断algvector中 出现的启用类型且需要检测的类型 在algTaskVector中是否出现
             for(unsigned int j = 0; j < algTaskVector->size(); j++)
             {
                 //如果出现则算法类型通过，否则不通过
                 if(algTaskVector_need->at(i).code == (*algTaskVector)[j]->algCode)//fix 这两个是否是同一个属性
                 {
                     bfind = true;
                     break;
                 }
             }

             //判断没找到的算法类型是不是网络接口
             for (unsigned int k = 0; k < pSession->pWangLuoJieKouReturnVector->size(); k++)
             {
                 _c_object *obj = (*pSession->pWangLuoJieKouReturnVector)[k];
                 objectMember* isGetData = baseTool::getObjectItemByName(&obj->memberVector, "isGetData");
                 objectMember* photoCode = baseTool::getObjectItemByName(&obj->memberVector, "photoCode");

                 if (*photoCode->value == algTaskVector_need->at(i).code)
                 {
                     //如果有获取到网络数据
                    if (*isGetData->value == "true")
                    {
                        bfind = true;
//                        printf("############################################ 0203 skip!\n");
                        break;
                    }
                 }
             }

             //如果缺少选项
             if(!bfind)
             {
                 if(algTaskVector_need->at(i).isTenYears && !isTenYears) //如果是十年车的选项检测，但是此车不是十年车
                 {
                     continue;
                 }
                 vec_lack_pics.push_back(algTaskVector_need->at(i).code);
             }
         }
     }

    _c_algTask* first_pic_type = algTaskVector->at(0);
    std::string strErrorMsg = first_pic_type->reason;
    for(auto vt:vec_lack_pics)
    {
        strErrorMsg = strErrorMsg + "[" + "缺少：" + vt + getAlgCodeNameByCode(vt) + "]"; 
    }
    //    int result = baseTool::str2Int(first_pic_type->result);
    if(vec_lack_pics.size() > 0)
    {
        first_pic_type->setAlgTaskResult(5, strErrorMsg); 
    }

     return true;

}
