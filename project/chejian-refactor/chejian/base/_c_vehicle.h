#ifndef _C_VEHICLE_H
#define _C_VEHICLE_H
#include "_c_session.h"
#include "_c_photo.h"
#include "_c_runTime.h"
#include "_c_video.h"

#include "alg/algTaskBase.h"

#define NOREPEAT "0"
#define REPEAT "1"

class _c_vehicle:public _c_session{
public:
    std::string liuShuiHao;
    std::string jianYanJiGouBianHao;
    std::string jianYanLeiBie;
    std::string haoPaiZhongLei;
    std::string haoPaiHaoMa;
    std::string cheLiangShiBieDaiHao;
    std::string shiYongRen;
    std::string shouJiHaoMa;
    std::string shengXiaoRiQi;
    std::string zhongZhiRiQi;
    std::string cheLiangLeiXing;
    std::string shiYongXingZhi;
    std::string zhengBeiZhiLiang;
    std::string jianYanKaiShiShiJian;
    std::string jianYanJieShuShiJian;
    std::string faDongJiHao;
    std::string cheLiangPinPai;
    std::string cheLiangXingHao;
    std::string chuCiDengJiRiQi;
    std::string chuChangRiQi;
    std::string cheLiangWaiGuanJianYanYuan;
    std::string xingShiZhengBianHao;
    std::string xingShiZhengFaZhengRiQi;
    std::string ranLiangZhongLei;
    std::string xuYaoDuiBiZhaoPianZongShu;
    std::string xuYaoDuiBiShiPinZongShu;
    std::string duiBiBuHeGeShu;
    std::string cheShenYanSe;
    std::string paiLiang;
    std::string gongLv;
    std::string zhuanXiangXingShi;
    std::string cheWaiKuoChang;
    std::string cheWaiKuoKuan;
    std::string cheWaiKuoGao;
    std::string huoXiangNeiBuChangDu;
    std::string huoXiangNeiBuKuanDu;
    std::string huoXiangNeiBuGaoDu;
    std::string gangBanTanPianShu;
    std::string zhouShu;
    std::string zhouJu;
    std::string qianLunJu;
    std::string houLunJu;
    std::string lunTaiGuiGe;
    std::string lunTaiShu;
    std::string zongZhiLiang;
    std::string heDingZaiZhiLiang;
    std::string heDingZaiKe;
    std::string zhunQianYinZhiLiang;
    std::string jiaShiShiQianPaiZaiKeRenShu;
    std::string jiaShiShiHouPaiZaiKeRenShu;
    std::string cheLiangYongTu;
    std::string yongTuShuXing;
    std::string shiFouXinNengYuanQiChe;
    std::string xinNengYuanZhongLei;
    std::string yanYnaYouXiaoQiZhi;
    std::string faZhengJiGuan;
    std::string huanBaoDaBiaoQingKuang;
    std::string qiangZhiBaoFeiQiZhi;
    std::string guanLiXiaQu;
    std::string guoChanJinKou;
    std::string diYanBiaoJi;
    std::string zhiZaoGuo;
    std::string yinWenPinPai;
    std::string jianYanHeGeBiaoJi;
    std::string shiFouMianJian;
    std::string jiDongCheZhuangTai;
    std::string zuiJinDingJianRiQi;
    std::string faDongJiXingHao;
    std::string zhuSuoDiZhiXingZhengQuHua;
    std::string lianXiDiZhiXingZhengQuHua;
    std::string shiGuSunShangBuWeiQingKuang;
    std::string buMianJianYuanYin;
    std::string guanLiBuMen;
    std::string zhiZaoChangMingCheng;
    std::string jianYanLiuShuiHao;
    std::string isRepeat;
    std::string shenQingShenHeShiJian;
    std::string javaFlat;
    std::string downloadVideoState;
    std::string soapReplyCode;

    //视频信息相关
    std::string cityCode;
    VIDEOCHECK_INFO videoCheckInfo;
    std::vector<VIDEOJYJGBH> *videoJyjgbhConfig = NULL;

    //网络接口相关
    std::vector<_c_object *> wangLuoJieKouReturnVector;
    std::vector<wangLuoJieKouMap> wangLuoJieKouPicMap = {
        {"18C23", e0203, e0201},
    };

    std::vector<_c_photo *> zhaoPianClassVector; //存放从数据库拿过来的一辆车的所有照片。

    //车辆信息相关
    _c_vehicle(){
        videoCheckInfo.isNeedLoadVideoInfo = false;
        videoCheckInfo.shiPinDownloadIsFinished = false;
        videoCheckInfo.shiPinClassVector.clear();
        wangLuoJieKouReturnVector.clear();

        tableName = "vehicle_info";

        memberVector.push_back({"uuid", "UUID", &uuid, "UUID", DBOPTION_DEFAULT});
        memberVector.push_back({"lsh", "liuShuiHao", &liuShuiHao, "流水号", DBOPTION_DEFAULT});
        memberVector.push_back({"jyjgbh", "jianYanJiGouBianHao", &jianYanJiGouBianHao, "检验机构编号", DBOPTION_DEFAULT});
        memberVector.push_back({"jylb", "jianYanLeiBie", &jianYanLeiBie, "检验类别", DBOPTION_DEFAULT});
        memberVector.push_back({"hpzl", "haoPaiZhongLei", &haoPaiZhongLei, "号牌种类", DBOPTION_DEFAULT});
        memberVector.push_back({"hphm", "chePaiHao", &haoPaiHaoMa, "号牌号码", DBOPTION_DEFAULT});//车牌号
        memberVector.push_back({"clsbdh", "cheJiaHao", &cheLiangShiBieDaiHao, "车辆识别代号", DBOPTION_DEFAULT});//车检号
        memberVector.push_back({"syr", "shiYongRen", &shiYongRen, "使用人", DBOPTION_DEFAULT});
        memberVector.push_back({"sjhm", "shouJiHaoMa", &shouJiHaoMa, "手机号码", DBOPTION_DEFAULT});
        memberVector.push_back({"sxrq", "shengXiaoRiQi", &shengXiaoRiQi, "保险生效日期", DBOPTION_DEFAULT});
        memberVector.push_back({"zzrq", "zhongZhiRiQi", &zhongZhiRiQi, "保险终止日期", DBOPTION_DEFAULT});
        memberVector.push_back({"cllx", "cheLiangLeiXing", &cheLiangLeiXing, "车辆类型", DBOPTION_DEFAULT});
        memberVector.push_back({"syxz", "shiYongXingZhi", &shiYongXingZhi, "使用性质", DBOPTION_DEFAULT});
        memberVector.push_back({"zbzl", "zhengBeiZhiLiang", &zhengBeiZhiLiang, "整备质量", DBOPTION_DEFAULT});
        memberVector.push_back({"kssj", "jianYanKaiShiShiJian", &jianYanKaiShiShiJian, "检验开始时间", DBOPTION_DEFAULT});
        memberVector.push_back({"jssj", "jianYanJieShuShiJian", &jianYanJieShuShiJian, "检验结束时间", DBOPTION_DEFAULT});
        memberVector.push_back({"fdjh", "faDongJiHao", &faDongJiHao, "发动机/电动机号码", DBOPTION_DEFAULT});
        memberVector.push_back({"clpp1", "cheLiangPinPai", &cheLiangPinPai, "车辆品牌", DBOPTION_DEFAULT});
        memberVector.push_back({"clxh", "cheLiangXingHao", &cheLiangXingHao, "车辆型号", DBOPTION_DEFAULT});
        memberVector.push_back({"ccdjrq", "chuCiDengJiRiQi", &chuCiDengJiRiQi, "初次登记日期", DBOPTION_DEFAULT});
        memberVector.push_back({"ccrq", "zhiZaoRiQi", &chuChangRiQi, "出厂日期", DBOPTION_DEFAULT});
        memberVector.push_back({"wgjcjyy", "cheLiangWaiGuanJianYanYuan", &cheLiangWaiGuanJianYanYuan, "车辆外观检验员", DBOPTION_DEFAULT});
        memberVector.push_back({"xszbh", "xingShiZhengXinBianHao", &xingShiZhengBianHao, "行驶证编号", DBOPTION_DEFAULT});//行驶证(芯片)编号
        memberVector.push_back({"fzrq", "faZhengRiQi", &xingShiZhengFaZhengRiQi, "行驶证发证日期", DBOPTION_DEFAULT});//发证日期
        memberVector.push_back({"rlzl", "ranLiangZhongLei", &ranLiangZhongLei, "燃料种类", DBOPTION_DEFAULT});
        memberVector.push_back({"zpzs", "xuYaoDuiBiZhaoPianZongShu", &xuYaoDuiBiZhaoPianZongShu, "需要对比照片总数", DBOPTION_DEFAULT});
        memberVector.push_back({"spzs", "xuYaoDuiBiShiPinZongShu", &xuYaoDuiBiShiPinZongShu, "需要对比视频总数", DBOPTION_DEFAULT});
        memberVector.push_back({"dbbhgs", "duiBiBuHeGeShu", &duiBiBuHeGeShu, "对比不合格数", DBOPTION_DEFAULT});
        memberVector.push_back({"csys", "cheLiangYanSe", &cheShenYanSe, "车辆颜色", DBOPTION_DEFAULT});
        memberVector.push_back({"pl", "paiLiang", &paiLiang, "排量", DBOPTION_DEFAULT});
        memberVector.push_back({"gl", "gongLv", &gongLv, "功率", DBOPTION_DEFAULT});
        memberVector.push_back({"zxxs", "zhuanXiangXingShi", &zhuanXiangXingShi, "转向形式", DBOPTION_DEFAULT});
        memberVector.push_back({"cwkc", "cheWaiKuoChang", &cheWaiKuoChang, "车外廓长", DBOPTION_DEFAULT});
        memberVector.push_back({"cwkk", "cheWaiKuoKuan", &cheWaiKuoKuan, "车外廓宽", DBOPTION_DEFAULT});
        memberVector.push_back({"cwkg", "cheWaiKuoGao", &cheWaiKuoGao, "车外廓高", DBOPTION_DEFAULT});
        memberVector.push_back({"hxnbcd", "huoXiangNeiBuChangDu", &huoXiangNeiBuChangDu, "货箱内部长度", DBOPTION_DEFAULT});
        memberVector.push_back({"hxnbkd", "huoXiangNeiBuKuanDu", &huoXiangNeiBuKuanDu, "货箱内部宽度", DBOPTION_DEFAULT});
        memberVector.push_back({"hxnbgd", "huoXiangNeiBuGaoDu", &huoXiangNeiBuGaoDu, "货箱内部高度", DBOPTION_DEFAULT});
        memberVector.push_back({"gbthps", "gangBanTanPianShu", &gangBanTanPianShu, "钢板弹簧片数", DBOPTION_DEFAULT});
        memberVector.push_back({"zs", "zhouShu", &zhouShu, "轴数", DBOPTION_DEFAULT});
        memberVector.push_back({"zj", "zhouJu", &zhouJu, "轴距", DBOPTION_DEFAULT});
        memberVector.push_back({"qlj", "qianLunJu", &qianLunJu, "前轮距", DBOPTION_DEFAULT});
        memberVector.push_back({"hlj", "houLunJu", &houLunJu, "后轮距", DBOPTION_DEFAULT});
        memberVector.push_back({"ltgg", "lunTaiGuiGe", &lunTaiGuiGe, "轮胎规格", DBOPTION_LONG});
        memberVector.push_back({"lts", "lunTaiShu", &lunTaiShu, "轮胎数", DBOPTION_DEFAULT});
        memberVector.push_back({"zzl", "zongZhiLiang", &zongZhiLiang, "总质量", DBOPTION_DEFAULT});
        memberVector.push_back({"hdzzl", "heDingZaiZhiLiang", &heDingZaiZhiLiang, "核定载质量", DBOPTION_DEFAULT});
        memberVector.push_back({"hdzk", "heDingZaiKeShu", &heDingZaiKe, "核定载客", DBOPTION_DEFAULT});//核定载客数
        memberVector.push_back({"zqyzl", "zhunQianYinZhiLiang", &zhunQianYinZhiLiang, "准牵引质量", DBOPTION_DEFAULT});
        memberVector.push_back({"qpzk", "jiaShiShiQianPaiZaiKeRenShu", &jiaShiShiQianPaiZaiKeRenShu, "驾驶室前排载客人数", DBOPTION_DEFAULT});
        memberVector.push_back({"hpzk", "jiaShiShiHouPaiZaiKeRenShu", &jiaShiShiHouPaiZaiKeRenShu, "驾驶室后排载客人数", DBOPTION_DEFAULT});
        memberVector.push_back({"clyt", "cheLiangYongTu", &cheLiangYongTu, "车辆用途", DBOPTION_DEFAULT});
        memberVector.push_back({"ytsx", "yongTuShuXing", &yongTuShuXing, "用途属性", DBOPTION_DEFAULT});
        memberVector.push_back({"sfxny", "shiFouXinNengYuanQiChe", &shiFouXinNengYuanQiChe, "是否新能源汽车", DBOPTION_DEFAULT});
        memberVector.push_back({"xnyzl", "xinNengYuanZhongLei", &xinNengYuanZhongLei, "新能源种类", DBOPTION_DEFAULT});
        memberVector.push_back({"yxqz", "yanYnaYouXiaoQiZhi", &yanYnaYouXiaoQiZhi, "检验有效期止", DBOPTION_DEFAULT});
        memberVector.push_back({"fzjg", "faZhengJiGuan", &faZhengJiGuan, "发证机关", DBOPTION_DEFAULT});
        memberVector.push_back({"hbdbqk", "huanBaoDaBiaoQingKuang", &huanBaoDaBiaoQingKuang, "环保达标情况", DBOPTION_TOOLONG});
        memberVector.push_back({"qzbfqz", "qiangZhiBaoFeiQiZhi", &qiangZhiBaoFeiQiZhi, "强制报废期止", DBOPTION_DEFAULT});
        memberVector.push_back({"xzqh", "guanLiXiaQu", &guanLiXiaQu, "管理辖区", DBOPTION_DEFAULT});
        memberVector.push_back({"gcjk", "guoChanJinKou", &guoChanJinKou, "国产/进口", DBOPTION_DEFAULT});
        memberVector.push_back({"dybj", "diYanBiaoJi", &diYanBiaoJi, "抵押标记", DBOPTION_DEFAULT});
        memberVector.push_back({"zzg", "zhiZaoGuo", &zhiZaoGuo, "制造国", DBOPTION_DEFAULT});
        memberVector.push_back({"clpp2", "yinWenPinPai", &yinWenPinPai, "英文品牌", DBOPTION_DEFAULT});
        memberVector.push_back({"jyhgbzbh", "jianYanHeGeBiaoJi", &jianYanHeGeBiaoJi, "检验合格标志", DBOPTION_DEFAULT});
        memberVector.push_back({"sfmj", "shiFouMianJian", &shiFouMianJian, "是否免检", DBOPTION_DEFAULT});
        memberVector.push_back({"zt", "jiDongCheZhuangTai", &jiDongCheZhuangTai, "机动车状态", DBOPTION_DEFAULT});
        memberVector.push_back({"djrq", "zuiJinDingJianRiQi", &zuiJinDingJianRiQi, "最近定检日期", DBOPTION_DEFAULT});
        memberVector.push_back({"zsxzqh", "zhuSuoDiZhiXingZhengQuHua", &zhuSuoDiZhiXingZhengQuHua, "住所地址行政区划", DBOPTION_DEFAULT});
        memberVector.push_back({"zzxzqh", "lianXiDiZhiXingZhengQuHua", &lianXiDiZhiXingZhengQuHua, "联系地址行政区划", DBOPTION_DEFAULT});
        memberVector.push_back({"fdjxh", "faDongJiXingHao", &faDongJiXingHao, "发动机型号", DBOPTION_DEFAULT});
        memberVector.push_back({"sgcssbwqk", "shiGuSunShangBuWeiQingKuang", &shiGuSunShangBuWeiQingKuang, "事故车损伤部位情况", DBOPTION_DEFAULT});
        memberVector.push_back({"bmjyy", "buMianJianYuanYin", &buMianJianYuanYin, "不免检原因", DBOPTION_TOOLONG });
        memberVector.push_back({"glbm", "guanLiBuMen", &guanLiBuMen, "管理部门", DBOPTION_DEFAULT});
        memberVector.push_back({"zzcmc", "zhiZaoChangMingCheng", &zhiZaoChangMingCheng, "制造厂名称", DBOPTION_DEFAULT});
        memberVector.push_back({"jylsh", "jianYanLiuShuiHao", &jianYanLiuShuiHao, "检验流水号", DBOPTION_DEFAULT});
        memberVector.push_back({"isPass", "isPass", &sessionResult, "整车通过", DBOPTION_DEFAULT});
        memberVector.push_back({"isPassReason", "isPassReason", &sessionReason, "整车说明", DBOPTION_DEFAULT});
        memberVector.push_back({"isRepeat", "isRepeat", &isRepeat, "是否重复", DBOPTION_DEFAULT});
        memberVector.push_back({"shenQingShenHeShiJian", "shenQingShenHeShiJian", &shenQingShenHeShiJian, "申请审核时间", DBOPTION_DEFAULT});
        memberVector.push_back({"centerStatus", "centerStatus", &javaFlat, "监管中心确认状态", DBOPTION_DEFAULT});
        memberVector.push_back({"downloadVideoState", "downloadVideoState", &downloadVideoState, "视频信息下载状态", DBOPTION_DEFAULT});
        memberVector.push_back({"soapReplyCode", "soapReplyCode", &soapReplyCode, "soap状态响应码", DBOPTION_DEFAULT});
        pRunTime = new _c_runTime();
        pRunTime->loadUuid();
    }

    virtual ~_c_vehicle(){} //用于释放内存（必须）
    void extraDbWork();
    virtual bool loadAlgTask();
    bool loadAllParam();
    bool processWangLuoJieKou();
    bool wangLuoJieKouResultEdit(void *p);
    int analyseVideoInfoJson(std::string &data);

    virtual void checkJiaoQiangXianReturnInfo(_c_object *obj);
    virtual void editJiaoQiangXianResult(_c_object *obj, void *p);

protected:
    PicType getWangLuojieKouOwnPicType(std::string biaoshi);
    PicType getWangLuojieKouXieRuPicType(std::string biaoshi);

    //获取视频信息相关
    void loadVehicleVideoInfo();
};
#endif // _C_SESSION_H
