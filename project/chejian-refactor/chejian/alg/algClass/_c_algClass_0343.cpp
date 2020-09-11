#include "_c_algClass_0343.h"
#include "base/baseTool.h"

bool _c_algClass_0343::seekMemberListPointer()
{
    mainPhotoType = e0343;
    subPhotoType  = e0341;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;
    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0343::loadExtAlgClass(std::vector<_c_algTask *> *pVector)
{
    _c_algTask *algTask = baseTool::seachPhotoByZpType(pAlgTaskVector, baseTool::getAlgItemCodeByPicType(e0341, pAllAlgItemVector));
    if(algTask)
    {
         pVector->push_back(algTask);
    }

    return true;
}

void _c_algClass_0343::setAlgIds() {
	algIDs.push_back(alg0344);
}

bool _c_algClass_0343::InParamEdit()
{
    return true ;
}
