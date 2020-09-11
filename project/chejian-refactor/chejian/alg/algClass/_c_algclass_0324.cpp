#include "_c_algclass_0324.h"

bool _c_algClass_0324::seekMemberListPointer()
{
    mainPhotoType = e0324;

    pInMemberList = &inMemberList;
    pResultMemberList = &resultMemberList;
    inListVector.push_back({"default",&inMemberList});
    resultListVector.push_back({"default",&resultMemberList});

    return true;
}

void _c_algClass_0324::setAlgIds() {
	algIDs.push_back(alg0324);
}

bool _c_algClass_0324::InParamEdit() {
	return true;
}

