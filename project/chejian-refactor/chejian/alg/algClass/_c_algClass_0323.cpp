#include "_c_algClass_0323.h"
#include "../base/baseTool.h"

bool _c_algClass_0323::seekMemberListPointer()
{
    mainPhotoType = e0323;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    inListVector.push_back({"moTuo",&inMemberList_moTuo});
    inListVector.push_back({"video",&inMemberList_video});
    resultListVector.push_back({"default",&resultMemberList});
    resultListVector.push_back({"moTuo",&resultMemberList_moTuo});
    resultListVector.push_back({"video",&resultMemberList_video});

    return true;
}

void _c_algClass_0323::setAlgIds() {
	algIDs.push_back(_algType);
	algIDs.push_back(algShuiYinRiQi);
}

bool _c_algClass_0323::InParamEdit()
{
    shuiYinRiQi.inData = baseTool::formatingDate(shuiYinRiQi.inData);
    if( baseTool::checkCllxIsMx(pAllParamVector) ){
        pInMemberList = &inMemberList_moTuo ;
        pResultMemberList = &resultMemberList_moTuo ;
    }

    if (isVideo)
    {
        pInMemberList = &inMemberList_video;
        pResultMemberList = &resultMemberList_video;
        _algType = alg0323;
    }

    return true;
}

bool _c_algClass_0323::ResultEdit()
{
    if (!isVideo)
    {
        //新车不检车牌
        if(baseTool::checkIsNewCar(pAllParamVector))
        {
            chePaiHao.result = true;
        }

        //大车不捡车牌
        if (baseTool::checkCllxIsK3xOrK4x(pAllParamVector))
        {
            chePaiHao.result = true;
        }
    }

    return true;
}
