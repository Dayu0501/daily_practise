#include "_c_algClass_0167_FuZhou.h"
#include "base/baseTool.h"

_c_algClass_0167_FuZhou::_c_algClass_0167_FuZhou() {
    resultMemberList.clear();
    inMemberList.clear();
    
    inMemberList.push_back({"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT});
    inMemberList.push_back({"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT});

    resultMemberList.push_back({"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT});
    resultMemberList.push_back({"chePaiHao_kaishi", "车牌还开始(不做输出)", &chePaiHaoKaiShi, false, CONFIG_DEFAULT});
    resultMemberList.push_back({"chePaiHao_jieshu", "车牌号结束(不做输出)", &chePaiHaoJieShu, false, CONFIG_DEFAULT});
}

bool _c_algClass_0167_FuZhou::subClassLoadNewResultMember()
{
    printf("_c_algClass_0167_FuZhou subClassLoadNewResultMember 111\n");
    _algType = alg0344;

    return true;
}

bool _c_algClass_0167_FuZhou::InParamEdit() {
    cheLiangLeiXing.inData = "1";
    return true;
}
bool _c_algClass_0167_FuZhou::ResultEdit() {
    printf("%s", __PRETTY_FUNCTION__ );
    chePaiHao.result = chePaiHaoJieShu.result || chePaiHaoKaiShi.result;

    return true;
}
