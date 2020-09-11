#include "_c_algClass_0344.h"
#include "../base/baseTool.h"

bool _c_algClass_0344::seekMemberListPointer()
{
    mainPhotoType = e0342;
    subPhotoType = e0344;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;
    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    inListVector.push_back({"moTuo",&inMemberList_moTuo});
    resultListVector.push_back({"moTuo",&resultMemberList_moTuo});

    inListVector.push_back({"video",&inMemberList_video});
    resultListVector.push_back({"video",&resultMemberList_video});

    return true;
}

void _c_algClass_0344::setAlgIds() {
	algIDs.push_back(alg0344);
	algIDs.push_back(algShuiYinRiQi);
}

bool _c_algClass_0344::InParamEdit()
{
    std::string cllx = baseTool::getObjectItemValueByName(pAllParamVector,"cheLiangLeiXing");
    if(cllx.substr(0, 1)=="M")
    {
        cheLiangLeiXing.inData = "2";
    }
    else
    {
        cheLiangLeiXing.inData = "1";
    }

    if( baseTool::checkCllxIsMx(pAllParamVector) )
    {
        pInMemberList = &inMemberList_moTuo ;
        pResultMemberList =&resultMemberList_moTuo ;
    }

    if (isVideo)
    {
        pInMemberList = &inMemberList_video;
        pResultMemberList = &resultMemberList_video;
        mainPhotoType = e0344;
        _algType = alg0344;
    }

    return true;
}

bool _c_algClass_0344::loadExtAlgClass(std::vector<_c_algTask *> *pVector)
{
    _c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector, baseTool::getAlgItemCodeByPicType(e0342, pAllAlgItemVector));
    if(algTask)
    {
         pVector->push_back(algTask);
    }

    return true;
}

_c_algTask *_c_algClass_0344::loadExtAlgTask()
{
    printf("0344 loadExtAlgTask\n");
    _c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector, baseTool::getAlgItemCodeByPicType(e0342, pAllAlgItemVector));
    if(algTask)
    {
        return algTask;
    }
}

bool _c_algClass_0344::ResultEdit()
{
    if (!isVideo)
    {
	    //如果有缺少照片的情况则只输出缺少照片的错误
	    _c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector, baseTool::getAlgItemCodeByPicType(e0342, pAllAlgItemVector));
	    memberItem *pqueShaoJieShuZhaoPian = baseTool::getMemberItemByName(pResultMemberList, "queShaoJieShuZhaoPian");
	    if (pqueShaoJieShuZhaoPian) {
	        if (algTask) {
	            pqueShaoJieShuZhaoPian->value->result = true;
	        } else {
	            baseTool::checkMemberItemAndSetAllUnOutput(pResultMemberList, pqueShaoJieShuZhaoPian);
	        }
	    }

	    if (baseTool::checkCllxIsMx(pAllParamVector)) {
//	      memberItem* pqueShaoJieShuZhaoPian=baseTool::getMemberItemByName(pResultMemberList,"queShaoJieShuZhaoPian") ;
//	      memberItem* pcheWei=baseTool::getMemberItemByName(pResultMemberList,"cheWei") ;
//	      memberItem* pcunZai=baseTool::getMemberItemByName(pResultMemberList,"cunZai") ;
//	      if (pqueShaoJieShuZhaoPian->config.isOpen && pcheWei->config.isOpen )
//	      {
//	          pcunZai->value->result = pcheWei->value->result && pqueShaoJieShuZhaoPian->value->result ;
//	      }
//
	    }
    }

    return true;
}
