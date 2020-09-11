#ifndef _C_CHAYANVEHICLE_H
#define _C_CHAYANVEHICLE_H
#include "_c_session.h"
#include "_c_photo.h"
#include "_c_runTime.h"

#define NOREPEAT "0"
#define REPEAT "1"

class _c_chaYanVehicle:public _c_session{
public:
    std::string liuShuiHao;
    std::string yeWuLeiXing;//ywlx 业务类型
    std::string yeWuYuanYin;//ywyy 业务原因
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
    std::string zhiZaoChangMingCheng;//制造厂名称
    std::string yinWenPinPai;
    std::string jianYanHeGeBiaoJi;
    std::string shiFouMianJian;
    std::string jiDongCheZhuangTai;
    std::string zuiJinDingJianRiQi;
    std::string faDongJiXingHao;
    std::string zhuSuoDiZhiXingZhengQuHua;
    std::string lianXiDiZhiXingZhengQuHua;
    std::string chaYanQuXuhao;//cyqxh 查验区序号
    std::string guanLiBuMen;
    std::string jiDongCheXuHao;//xh 机动车序号
    std::string chaYanYuanShenFenZhengMingHao;// cyry 查验员身份证明号码
    std::string faDengJiZhengShuRiQi;//fdjrq 发登记证书日期
    std::string faHeGeBiaoZhiRiQi;//fhgzrq 发合格标志日期
    std::string waiGuanBiaoDanBiaoZhi;// model 外观表单标志
    std::string sheBeiIP;//device_ip 设备IP
    std::string gongWeiBianHao;//gongwei_code 工位编号
    std::string shenQingShenHeShiJian;//sqshsj 申请审核时间
    std::string isRepeat;
    std::string centerStatus;
//    std::string javaFlat;

    std::vector<_c_object *> wangLuoJieKouReturnVector;
    std::vector<_c_photo *> zhaoPianClassVector;

    _c_chaYanVehicle(){
        wangLuoJieKouReturnVector.clear();

        tableName = "chaYanVehicle_info";

        memberVector.push_back({"uuid", "UUID", &uuid, "UUID", DBOPTION_DEFAULT});
        memberVector.push_back({"lsh", "liuShuiHao", &liuShuiHao, "流水号", DBOPTION_DEFAULT});
        memberVector.push_back({"ywlx", "yeWuLeiXing", &yeWuLeiXing, "业务类别", DBOPTION_DEFAULT});
        memberVector.push_back({"ywyy", "yeWuYuanYin", &yeWuYuanYin, "业务原因", DBOPTION_DEFAULT});
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
        memberVector.push_back({"ccrq", "zhiZaoRiQi", &chuChangRiQi, "出厂日期", DBOPTION_DEFAULT});//chuChangRiQi
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
        memberVector.push_back({"zzcmc", "zhiZaoChangMingCheng", &zhiZaoChangMingCheng, "制造厂名称", DBOPTION_DEFAULT});
        memberVector.push_back({"clpp2", "yinWenPinPai", &yinWenPinPai, "英文品牌", DBOPTION_DEFAULT});
        memberVector.push_back({"jyhgbzbh", "jianYanHeGeBiaoJi", &jianYanHeGeBiaoJi, "检验合格标志", DBOPTION_DEFAULT});
        memberVector.push_back({"sfmj", "shiFouMianJian", &shiFouMianJian, "是否免检", DBOPTION_DEFAULT});
        memberVector.push_back({"zt", "jiDongCheZhuangTai", &jiDongCheZhuangTai, "机动车状态", DBOPTION_DEFAULT});
        memberVector.push_back({"djrq", "zuiJinDingJianRiQi", &zuiJinDingJianRiQi, "最近定检日期", DBOPTION_DEFAULT});
        memberVector.push_back({"zsxzqh", "zhuSuoDiZhiXingZhengQuHua", &zhuSuoDiZhiXingZhengQuHua, "住所地址行政区划", DBOPTION_DEFAULT});
        memberVector.push_back({"zzxzqh", "lianXiDiZhiXingZhengQuHua", &lianXiDiZhiXingZhengQuHua, "联系地址行政区划", DBOPTION_DEFAULT});
        memberVector.push_back({"fdjxh", "faDongJiXingHao", &faDongJiXingHao, "发动机型号", DBOPTION_DEFAULT});
        memberVector.push_back({"glbm", "guanLiBuMen", &guanLiBuMen, "查验区序号", DBOPTION_DEFAULT});
        memberVector.push_back({"cyqxh", "chaYanQuXuhao", &chaYanQuXuhao, "查验区序号", DBOPTION_DEFAULT});
        memberVector.push_back({"xh", "jiDongCheXuHao", &jiDongCheXuHao, "机动车序号", DBOPTION_DEFAULT});
        memberVector.push_back({"cyry", "chaYanYuanShenFenZhengMingHao", &chaYanYuanShenFenZhengMingHao, "查验员身份证明号码", DBOPTION_DEFAULT});
        memberVector.push_back({"fdjrq", "faDengJiZhengShuRiQi", &faDengJiZhengShuRiQi, "发登记证书日期", DBOPTION_DEFAULT});
        memberVector.push_back({"fhgzrq", "faHeGeBiaoZhiRiQi", &faHeGeBiaoZhiRiQi, "发合格标志日期", DBOPTION_DEFAULT});
        memberVector.push_back({"model", "waiGuanBiaoDanBiaoZhi", &waiGuanBiaoDanBiaoZhi, "外观表单标志", DBOPTION_DEFAULT});
        memberVector.push_back({"device_ip", "sheBeiIP", &sheBeiIP, "设备IP", DBOPTION_DEFAULT});
        memberVector.push_back({"gongwei_code", "gongWeiBianHao", &gongWeiBianHao, "工位编号", DBOPTION_DEFAULT});
        memberVector.push_back({"sqshsj", "shenQingShenHeShiJian", &shenQingShenHeShiJian, "申请审核时间", DBOPTION_DEFAULT});

        memberVector.push_back({"isPass", "isPass", &sessionResult, "整车通过", DBOPTION_DEFAULT});
        memberVector.push_back({"isPassReason", "isPassReason", &sessionReason, "整车说明", DBOPTION_DEFAULT});
        memberVector.push_back({"isRepeat", "isRepeat", &isRepeat, "是否重复", DBOPTION_DEFAULT});
        memberVector.push_back({"centerStatus", "centerStatus", &centerStatus, "监管中心确认状态", DBOPTION_DEFAULT});
        memberVector.push_back({"greenChannel", "greenChannel", &greenChannel, "是否使用优先处理", DBOPTION_DEFAULT});

        pRunTime = new _c_runTime();
        pRunTime->loadUuid();
    }

    virtual ~_c_chaYanVehicle(){} //用于释放内存（必须）
    void extraDbWork();
    bool loadAlgTask();
    bool loadAllParam();
};
#endif // _C_CHAYANVEHICLE_H
