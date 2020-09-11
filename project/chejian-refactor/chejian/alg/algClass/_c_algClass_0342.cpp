#include "_c_algClass_0342.h"
#include "../base/baseTool.h"

bool _c_algClass_0342::seekMemberListPointer()
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

void _c_algClass_0342::setAlgIds() {
	algIDs.push_back(alg0344);
	algIDs.push_back(algShuiYinRiQi);
}

bool _c_algClass_0342::InParamEdit()
{
    if( baseTool::checkCllxIsMx(pAllParamVector) )
    {
        pInMemberList = &inMemberList_moTuo ;
        pResultMemberList =&resultMemberList_moTuo ;
    }

    if (isVideo)
    {
        pInMemberList = &inMemberList_video;
        pResultMemberList = &resultMemberList_video;
        _algType = alg0342;
    }
    return false;
}

bool _c_algClass_0342::ResultEdit()
{
    if(!isVideo)
    {
        //如果有缺少照片的情况则只输出缺少照片的错误
        _c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector, baseTool::getAlgItemCodeByPicType(e0344, pAllAlgItemVector));
        memberItem *pqueShaoKaiShiZhaoPian = baseTool::getMemberItemByName(pResultMemberList, "queShaoKaiShiZhaoPian");
        if (pqueShaoKaiShiZhaoPian) {
            if (algTask) {
                pqueShaoKaiShiZhaoPian->value->result = true;
            } else {
                baseTool::checkMemberItemAndSetAllUnOutput(pResultMemberList, pqueShaoKaiShiZhaoPian);
            }
        }

//
        if (baseTool::checkCllxIsMx(pAllParamVector)) {
//                  memberItem* pqueShaoKaiShiZhaoPian=baseTool::getMemberItemByName(pResultMemberList,"queShaoKaiShiZhaoPian") ;
//                  memberItem* pcheTou=baseTool::getMemberItemByName(pResultMemberList,"cheTou") ;
//                  memberItem* pcunZai=baseTool::getMemberItemByName(pResultMemberList,"cunZai") ;
//                  if (pqueShaoKaiShiZhaoPian->config.isOpen && pcheTou->config.isOpen )
//                  {
//                      pcunZai->value->result = pcheTou->value->result && pqueShaoKaiShiZhaoPian->value->result ;
//                  }
//
        }
    }

    return true;
}
