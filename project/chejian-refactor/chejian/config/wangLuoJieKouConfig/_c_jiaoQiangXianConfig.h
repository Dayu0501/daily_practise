#ifndef _C_JIAOQIANGXIANCONFIG_H
#define _C_JIAOQIANGXIANCONFIG_H
#include "base/_c_dbTask.h"
#include "base/baseTool.h"

class _c_jiaoQiangXianConfig:public _c_dbTask{
public:
    std::string yeWuMingCheng = "交强险(电子)";
    std::string isOpen = "false";
    std::string jieKouBiaoShi = "18C23";
    std::string shouQuanMa = "791D0909030517040015E6F77C0882C886998A81828A9FF3FCC8A787D5C2B287BCE0B9DCD6C7C4DCC9F3BACBCFB5CDB3A3A8BDD3C8EBBCE0B9DCB0B2C8ABD2AAC7F3A3A9";

    _c_jiaoQiangXianConfig()
    {
        tableName = "jqx_config";
        memberVector.push_back({"yeWuMingCheng", "yeWuMingCheng", &yeWuMingCheng, "业务名称", DBOPTION_DEFAULT});
        memberVector.push_back({"isOpen", "isOpen", &isOpen, "交强险接口是否开启", DBOPTION_DEFAULT});
        memberVector.push_back({"jieKouBiaoShi", "jieKouBiaoShi", &jieKouBiaoShi, "交强险接口标识", DBOPTION_DEFAULT});
        memberVector.push_back({"shouQuanMa", "shouQuanMa", &shouQuanMa, "交强险接口授权码", DBOPTION_LONGLONGLONG});
    }

    bool needFree(){return false;}
};
#endif // _C_JIAOQIANGXIANCONFIG_H
