#include "_c_algClass_0186_NanChong.h"
#include "../base/baseTool.h"

bool _c_algClass_0186_NanChong::seekMemberListPointer()
{
    mainPhotoType = e0323;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;

    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

bool _c_algClass_0186_NanChong::InParamEdit()
{
	printf("0186 %s", __PRETTY_FUNCTION__);

	algIDs.clear();
	algIDs.push_back(alg0323);

    return true;
}

bool _c_algClass_0186_NanChong::ResultEdit()
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
