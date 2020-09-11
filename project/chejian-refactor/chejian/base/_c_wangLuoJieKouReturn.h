#ifndef _C_WANGLUOJIEKOURETURN_H
#define _C_WANGLUOJIEKOURETURN_H
#include "base/_c_dbTask.h"
#include "base/baseTool.h"
#include "base/json/json.h"
#include "base/_c_session.h"

class _c_wangLuoJieKouReturnInfo: public _c_dbTask {
public:
    //必填项 且在解析时不能覆盖
    std::string jieKouBiaoShi;//接口标识

    //是否获取数据
    std::string isGetData;

    //是否有照片项
    std::string photoIsExist;
    std::string photoCode;

    //是否通过及相关理由
    std::string dataIsValid;//网络接口的返回值是否有效,关键内容为空为无效,判定该车没有电子保单
    std::string isPass;//是否通过
    std::string reason;

    //和车辆的关联项
    std::string cheLiangUid;

    _c_wangLuoJieKouReturnInfo()
    {
        memberVector.push_back({"jieKouBiaoShi", "jieKouBiaoShi", &jieKouBiaoShi, "接口标识号", DBOPTION_DEFAULT});

        memberVector.push_back({"isGetData", "isGetData", &isGetData, "是否有电子保单", DBOPTION_DEFAULT});
        memberVector.push_back({"photoIsExist", "photoIsExist", &photoIsExist, "是否有照片项", DBOPTION_DEFAULT});
        memberVector.push_back({"photoCode", "photoCode", &photoCode, "照片类型", DBOPTION_DEFAULT});

        memberVector.push_back({"dataIsValid", "dataIsValid", &dataIsValid, "电子保单数据是否完整", DBOPTION_DEFAULT});
        memberVector.push_back({"isPass", "isPass", &isPass, "是否通过", DBOPTION_DEFAULT});
        memberVector.push_back({"reason", "reason", &reason, "原因", DBOPTION_DEFAULT});

        memberVector.push_back({"cheLiangUid", "cheLiangUid", &cheLiangUid, "车辆UID", DBOPTION_DEFAULT});
    }
};


class _c_jiaoQiangXianJkReturnInfo: public _c_wangLuoJieKouReturnInfo {
public:
    //具体的业务数据 从相关机构获得
    std::string baoXianDanHao;
    std::string baoXianGongSiDaiMa;
    std::string baoXianGongSiMingCheng;
    std::string haoPaiZhongLei;
    std::string haoPaiHaoMa;
    std::string cheLiangShiBieDaiHao;
    std::string shengXiaoRiQi;
    std::string zhongZhiRiQi;
    std::string beiBaoXianRenMingCheng;
    std::string beiBaoXianRenShenFenZheng;
    std::string jiaoQiangXianTouBaoZhuangTai;
    std::string wanShuiPingZhengHaoMa;
    std::string cheChuanShuiNaShuiQingKuang;
    std::string cheChuanShuiNaShuiJinE;
    std::string naShuiRenShiBieHao;
    std::string cheChuanShuiNaShuiRiQi;
    std::string cheChuanShuiNaShuiQiShiRiQi;
    std::string cheChuanShuiNaShuiZhongZhiRiQi;

    _c_jiaoQiangXianJkReturnInfo()
    {
        tableName = "jiaoQiangXian_info";
        jieKouBiaoShi = "18C23";

        memberVector.push_back({"bxdh", "baoXianDanHao", &baoXianDanHao, "保险单号", DBOPTION_DEFAULT});
        memberVector.push_back({"bxgsdm", "baoXianGongSiDaiMa", &baoXianGongSiDaiMa, "保险公司代码", DBOPTION_DEFAULT});
        memberVector.push_back({"bxgs", "baoXianGongSiMingCheng", &baoXianGongSiMingCheng, "数据库用户名称", DBOPTION_LONG});
        memberVector.push_back({"hpzl", "haoPaiZhongLei", &haoPaiZhongLei, "号牌种类", DBOPTION_DEFAULT});
        memberVector.push_back({"hphm", "haoPaiHaoMa", &haoPaiHaoMa, "号牌号码", DBOPTION_DEFAULT});
        memberVector.push_back({"clsbdh", "cheLiangShiBieDaiHao", &cheLiangShiBieDaiHao, "车辆识别代号", DBOPTION_DEFAULT});
        memberVector.push_back({"sxrq", "shengXiaoRiQi", &shengXiaoRiQi, "保险生效日期", DBOPTION_DEFAULT});
        memberVector.push_back({"zzrq", "zhongZhiRiQi", &zhongZhiRiQi, "保险终止日期", DBOPTION_DEFAULT});
        memberVector.push_back({"bbxr", "beiBaoXianRenMingCheng", &beiBaoXianRenMingCheng, "被保险人名称", DBOPTION_LONGLONG});
        memberVector.push_back({"bbxrsfzmhm", "beiBaoXianRenShenFenZheng", &beiBaoXianRenShenFenZheng, "被保险人身份证", DBOPTION_DEFAULT});
        memberVector.push_back({"jqxtbzt", "jiaoQiangXianTouBaoZhuangTai", &jiaoQiangXianTouBaoZhuangTai, "交强险投保状态", DBOPTION_DEFAULT});
        memberVector.push_back({"wspzhm", "wanShuiPingZhengHaoMa", &wanShuiPingZhengHaoMa, "完税凭证号码", DBOPTION_DEFAULT});
        memberVector.push_back({"ccsnsqk", "cheChuanShuiNaShuiQingKuang", &cheChuanShuiNaShuiQingKuang, "车船税纳税情况", DBOPTION_DEFAULT});
        memberVector.push_back({"ccsnsje", "cheChuanShuiNaShuiJinE", &cheChuanShuiNaShuiJinE, "车船税纳税金额", DBOPTION_DEFAULT});
        memberVector.push_back({"nsrsbh", "naShuiRenShiBieHao", &naShuiRenShiBieHao, "车船税纳税人识别号", DBOPTION_DEFAULT});
        memberVector.push_back({"ccsnsrq", "cheChuanShuiNaShuiRiQi", &cheChuanShuiNaShuiRiQi, "车船税纳税日期", DBOPTION_DEFAULT});
        memberVector.push_back({"ccsnsqsrq", "cheChuanShuiNaShuiQiShiRiQi", &cheChuanShuiNaShuiQiShiRiQi, "车船税纳税起始日期", DBOPTION_DEFAULT});
        memberVector.push_back({"ccsnszzrq", "cheChuanShuiNaShuiZhongZhiRiQi", &cheChuanShuiNaShuiZhongZhiRiQi, "车船税纳税终止日期", DBOPTION_DEFAULT});
    }

    void loadJQXJson(Json::Value &root, _c_session *pVehicle)
    {
//        printf("%s\n", root.toStyledString().c_str());
        for (unsigned int i = 0; i < memberVector.size(); i++) {
            if (!root[(memberVector[i].soapName.c_str())].empty())
            {
                std::string str = root[(memberVector[i].soapName.c_str())].asString();
//                printf("[%s]:%s\n", memberVector[i].soapName.c_str(),str.c_str());
                if (str.length() > 0)
                    *memberVector[i].value = str;
                else
                    *memberVector[i].value = "无数据";
            }
            else
            {
//                printf("[%s]:not find data \n",memberVector[i].soapName.c_str());
                if (memberVector[i].soapName != "jieKouBiaoShi")
                {
                    *memberVector[i].value = "无数据";
                }

                if (memberVector[i].soapName == "isGetData")
                {
                    *memberVector[i].value = "true";
                }
            }
        }
    }

    bool needFree(){return false;}
};
#endif // _C_WANGLUOJIEKOURETURN_H
