#ifndef _C_YINGXIANGVEHICLE_H
#define _C_YINGXIANGVEHICLE_H
#include "base/_c_session.h"
#include "base/_c_photo.h"
#include "base/_c_runTime.h"

#define NOREPEAT "0"
#define REPEAT "1"

class _c_yingXiangVehicle:public _c_session{
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
    std::string cheLiangPinPaiZhongWen;
    std::string cheLiangPinPaiYingWen;
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
    std::string faHeGeZhengRiQi;
    std::string baoXianZhongZhiRiQi;
    std::string cheLiangLaiYuan;

    std::string qianPaiZaiKe;
    std::string houPaiZaiKe;
    std::string diPanID;
    std::string huoDeFangShi;
    std::string laiLiPingZheng1;
    std::string pingZhengBianHao1;
    std::string laiLiPingZheng2;
    std::string pingZhengBianHao2;
    std::string xiaoShouDanWei;
    std::string xiaoShouJiaGe;
    std::string xiaoShouRiQi;
    std::string jinKouPingZheng;
    std::string jinKouPingZhengHaoMa;
    std::string heGeZhengBianHao;
    std::string naShuiZhengMing;
    std::string naShuiZhengMingBianHao;
    std::string xiangGuanZiLiao;
    std::string qianMoBianHao;
    std::string houMoBianHao;
    std::string baoXianPingZhengHao;
    std::string baoXianJinEr;
    std::string baoXianGongSi;
    std::string suoYouQuan;
    std::string shenFenZhengMingMingCheng;
    std::string shenFenZhengMingHaoMa;
    std::string suoYouRen;
    std::string zhuSuoXiangXiDiZhi;
    std::string youZhengBianMa1;
    std::string lianXiDianHua;
    std::string zanZhuZheng;
    std::string zanZhuXingZhengQuHua;
    std::string zanZhuXiangXiDiZhi;
    std::string youZhengBianMa2;
    std::string yeWuLeiXing;
    std::string yeWuYuanYin;
    std::string diPanHeGeZhengBianHao;
    std::string dianZiYouXiang;
    std::string zhongDianCheLiangXinXi;
    std::string daiLiRenXingMing;
    std::string daiLiRenShenFenZhengMingHaoMa;
    std::string daiLiRenShouJiHaoMa;
    std::string daiLiRenSuoShuDanWei;
    std::string JBRID;
    std::string JBR;
    std::string shangPaiCheGuanSuo;
    std::string yuYueShangPaiShiJian;
    std::string jiDongCheDongJiRenID;
    std::string jiDongCheDongJiRenXingMing;
    std::string jiDongCheDongJiBuMen;
    std::string jiDongCheDengJiShiJian;
    std::string suoYouRenDengJiShiJian;
    std::string suoShuDanWei;
    std::string zhuangTai;
    std::string beiZhu;
    std::string chuanShuBiaoJi;
    std::string jinKouPingZhengQianFaRiQi;
    std::string jiLuZhuangTai;
    std::string shenFenZhengMingYouXiaoQiShi;
    std::string shenFenZhengMingYouXiaoQiZhi;
    std::string shiFouZanZhuRenKou;
    std::string gengXinShiJian;
    std::string shiFouChangZhuRenKou;
    std::string youHao;
    std::string zhouHe;
    std::string zaiZhiLiangLiYongXiShu;
    std::string banGuaCheAnZuoZuiDaYunXuZhiLiang;
    std::string zuiGaoSheJiShiSu;
    std::string cheLiangZhiZaoRiQi;
    std::string shiFouDaiLi;
    std::string youJiDiZhi;
    std::string xuHao;
    std::string zhuHeTongHao;
    std::string diYaHeTongHao;
    std::string diYaJinEr;
    std::string diYaDengJiRiQi;
    std::string diYaJingBanRen;
    std::string diYaQuanRen;
    std::string diYaQuanRenShenFenZhengMingMingCheng;
    std::string diYaQuanRenShenFenZhengMingHaoMa;
    std::string diYaQuanRenXingZhengQuHua;
    std::string diYaQuanRenXiangXiDiZhi;
    std::string diYaQuanRenYouZhengBianMa;
    std::string diYaQuanRenLianXiDianHua;
    std::string jieChuRiQi;
    std::string diYaGuanLiBuMen;
    std::string jiLuSuoShuFuWuZhan;
    std::string jiLuSuoShuCheGuanSuo;
    std::string tuPian;
    std::string bianHao;
    //std::string createTime = "NOW()";

    //std::vector<_c_filephotoinfo *> zhaoPianClassVector;
    std::vector<_c_photo *> zhaoPianClassVector;

    _c_yingXiangVehicle(){
        tableName = "yingXiangVehicle_info";

        memberVector.push_back({"uuid", "UUID", &uuid, "UUID", DBOPTION_DEFAULT});
        memberVector.push_back({"lsh", "liuShuiHao", &liuShuiHao, "流水号", DBOPTION_DEFAULT});
        memberVector.push_back({"hphm", "chePaiHao", &haoPaiHaoMa, "号牌号码", DBOPTION_DEFAULT});//车牌号
        memberVector.push_back({"clsbdh", "cheJiaHao", &cheLiangShiBieDaiHao, "车辆识别代号", DBOPTION_DEFAULT});//车检号
        memberVector.push_back({"clpp1", "cheLiangPinPai", &cheLiangPinPai, "车辆品牌", DBOPTION_DEFAULT});
        memberVector.push_back({"clxh", "cheLiangXingHao", &cheLiangXingHao, "车辆型号", DBOPTION_DEFAULT});
        memberVector.push_back({"clpp2", "yinWenPinPai", &yinWenPinPai, "英文品牌", DBOPTION_DEFAULT});
        memberVector.push_back({"gcjk", "guoChanJinKou", &guoChanJinKou, "国产/进口", DBOPTION_DEFAULT});
        memberVector.push_back({"zzg", "zhiZaoGuo", &zhiZaoGuo, "制造国", DBOPTION_DEFAULT});
        memberVector.push_back({"zzcmc", "zhiZaoChangMingCheng", &zhiZaoChangMingCheng, "制造厂名称", DBOPTION_DEFAULT});
        memberVector.push_back({"fdjh", "faDongJiHao", &faDongJiHao, "发动机号", DBOPTION_DEFAULT});
        memberVector.push_back({"cllx", "cheLiangLeiXing", &cheLiangLeiXing, "车辆类型", DBOPTION_DEFAULT});
        memberVector.push_back({"csys", "cheLiangYanSe", &cheShenYanSe, "车身颜色", DBOPTION_DEFAULT});
        memberVector.push_back({"fzjg", "faZhengJiGuan", &faZhengJiGuan, "发证机关", DBOPTION_DEFAULT});
        memberVector.push_back({"glbm", "guanLiBuMen", &guanLiBuMen, "管理部门", DBOPTION_DEFAULT});
        memberVector.push_back({"fhgzrq", "faHeGeZhengRiQi", &faHeGeZhengRiQi, "发合格证日期", DBOPTION_DEFAULT});
        memberVector.push_back({"bxzzrq", "baoXianZhongZhiRiQi", &baoXianZhongZhiRiQi, "保险终止日期", DBOPTION_DEFAULT});
        memberVector.push_back({"dybj", "diYanBiaoJi", &diYanBiaoJi, "抵押标记", DBOPTION_DEFAULT});
        memberVector.push_back({"clly", "cheLiangLaiYuan", &cheLiangLaiYuan, "车辆来源", DBOPTION_DEFAULT});
        memberVector.push_back({"fdjxh", "faDongJiXingHao", &faDongJiXingHao, "发动机型号", DBOPTION_DEFAULT});
        memberVector.push_back({"rlzl", "ranLiangZhongLei", &ranLiangZhongLei, "燃料种类", DBOPTION_DEFAULT});
        memberVector.push_back({"sfxny", "shiFouXinNengYuanQiChe", &shiFouXinNengYuanQiChe, "是否新能源汽车", DBOPTION_DEFAULT});
        memberVector.push_back({"xnyzl", "xinNengYuanZhongLei", &xinNengYuanZhongLei, "新能源种类", DBOPTION_DEFAULT});
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
        memberVector.push_back({"ltgg", "lunTaiGuiGe", &lunTaiGuiGe, "轮胎规格", DBOPTION_DEFAULT});
        memberVector.push_back({"lts", "lunTaiShu", &lunTaiShu, "轮胎数", DBOPTION_DEFAULT});
        memberVector.push_back({"zzl", "zongZhiLiang", &zongZhiLiang, "总质量", DBOPTION_DEFAULT});
        memberVector.push_back({"zbzl", "zhengBeiZhiLiang", &zhengBeiZhiLiang, "整备质量", DBOPTION_DEFAULT});
        memberVector.push_back({"hdzzl", "heDingZaiZhiLiang", &heDingZaiZhiLiang, "核定载质量", DBOPTION_DEFAULT});
        memberVector.push_back({"hdzk", "heDingZaiKeShu", &heDingZaiKe, "核定载客", DBOPTION_DEFAULT});//核定载客数
        memberVector.push_back({"zqyzl", "zhunQianYinZhiLiang", &zhunQianYinZhiLiang, "准牵引总质量", DBOPTION_DEFAULT});
        memberVector.push_back({"qpzk", "jiaShiShiQianPaiZaiKeRenShu", &jiaShiShiQianPaiZaiKeRenShu, "驾驶室前排载客人数", DBOPTION_DEFAULT});
        memberVector.push_back({"hpzk", "jiaShiShiHouPaiZaiKeRenShu", &jiaShiShiHouPaiZaiKeRenShu, "驾驶室后排载客人数", DBOPTION_DEFAULT});
        memberVector.push_back({"bh", "bianHao", &bianHao, "编号", DBOPTION_DEFAULT});
        memberVector.push_back({"dpid", "diPanID", &diPanID, "底盘ID", DBOPTION_DEFAULT});
        memberVector.push_back({"hbdbqk", "huanBaoDaBiaoQingKuang", &huanBaoDaBiaoQingKuang, "环保达标情况", DBOPTION_TOOLONG});
        memberVector.push_back({"ccrq", "chuChangRiQi", &chuChangRiQi, "出厂日期", DBOPTION_DEFAULT});//chuChangRiQi
        memberVector.push_back({"hdfs", "huoDeFangShi", &huoDeFangShi, "获得方式", DBOPTION_DEFAULT});
        memberVector.push_back({"llpz1", "laiLiPingZheng1", &laiLiPingZheng1, "来历凭证1", DBOPTION_DEFAULT});
        memberVector.push_back({"pzbh1", "pingZhengBianHao1", &pingZhengBianHao1, "凭证编号1", DBOPTION_DEFAULT});
        memberVector.push_back({"llpz2", "laiLiPingZheng2", &laiLiPingZheng2, "来历凭证2", DBOPTION_DEFAULT});
        memberVector.push_back({"pzbh2", "pingZhengBianHao2", &pingZhengBianHao2, "凭证编号2", DBOPTION_DEFAULT});
        memberVector.push_back({"xsdw", "xiaoShouDanWei", &xiaoShouDanWei, "销售单位", DBOPTION_DEFAULT});
        memberVector.push_back({"xsjg", "xiaoShouJiaGe", &xiaoShouJiaGe, "销售价格", DBOPTION_DEFAULT});
        memberVector.push_back({"xsrq", "xiaoShouRiQi", &xiaoShouRiQi, "销售日期", DBOPTION_DEFAULT});
        memberVector.push_back({"jkpz", "jinKouPingZheng", &jinKouPingZheng, "进口凭证", DBOPTION_DEFAULT});
        memberVector.push_back({"jkpzhm", "jinKouPingZhengHaoMa", &jinKouPingZhengHaoMa, "进口凭证号码", DBOPTION_DEFAULT});
        memberVector.push_back({"hgzbh", "heGeZhengBianHao", &heGeZhengBianHao, "合格证编号", DBOPTION_DEFAULT});
        memberVector.push_back({"nszm", "naShuiZhengMing", &naShuiZhengMing, "纳税证明", DBOPTION_DEFAULT});
        memberVector.push_back({"nszmbh", "naShuiZhengMingBianHao", &naShuiZhengMingBianHao, "纳税证明编号", DBOPTION_DEFAULT});
        memberVector.push_back({"xgzl", "xiangGuanZiLiao", &xiangGuanZiLiao, "相关资料", DBOPTION_DEFAULT});
        memberVector.push_back({"qmbh", "qianMoBianHao", &qianMoBianHao, "前膜编号", DBOPTION_DEFAULT});
        memberVector.push_back({"hmbh", "houMoBianHao", &houMoBianHao, "后膜编号", DBOPTION_DEFAULT});
        memberVector.push_back({"bxpzh", "baoXianPingZhengHao", &baoXianPingZhengHao, "保险凭证号", DBOPTION_DEFAULT});
        memberVector.push_back({"bxje", "baoXianJinEr", &baoXianJinEr, "保险金额", DBOPTION_DEFAULT});
        memberVector.push_back({"sxrq", "shengXiaoRiQi", &shengXiaoRiQi, "生效日期", DBOPTION_DEFAULT});
        memberVector.push_back({"zzrq", "zhongzhiRiQi", &zhongZhiRiQi, "终止日期", DBOPTION_DEFAULT});
        memberVector.push_back({"bxgs", "baoXianGongSi", &baoXianGongSi, "保险公司", DBOPTION_DEFAULT});
        memberVector.push_back({"syq", "suoYouQuan", &suoYouQuan, "所有权", DBOPTION_DEFAULT});
        memberVector.push_back({"sfzmmc", "shenFenZhengMingMingCheng", &shenFenZhengMingMingCheng, "身份证明名称", DBOPTION_DEFAULT});
        memberVector.push_back({"sfzmhm", "shenFenZhengMingHaoMa", &shenFenZhengMingHaoMa, "身份证明号码", DBOPTION_DEFAULT});
        memberVector.push_back({"syr", "shiYongRen", &shiYongRen, "使用人", DBOPTION_DEFAULT});
        memberVector.push_back({"sjhm", "shouJiHaoMa", &shouJiHaoMa, "手机号码", DBOPTION_DEFAULT});
        memberVector.push_back({"syxz", "shiYongXingZhi", &shiYongXingZhi, "使用性质", DBOPTION_DEFAULT});
        memberVector.push_back({"zsxzqh", "zhuSuoDiZhiXingZhengQuHua", &zhuSuoDiZhiXingZhengQuHua, "住所地址行政区划", DBOPTION_DEFAULT});
        memberVector.push_back({"zsxxdz", "zhuSuoXiangXiDiZhi", &zhuSuoXiangXiDiZhi, "住所详细地址", DBOPTION_DEFAULT});
        memberVector.push_back({"yzbm1", "youZhengBianMa1", &youZhengBianMa1, "住所邮政编码", DBOPTION_DEFAULT});
        memberVector.push_back({"lxdh", "lianXiDianHua", &lianXiDianHua, "联系电话", DBOPTION_DEFAULT});
        memberVector.push_back({"zzz", "zanZhuZheng", &zanZhuZheng, "暂住居住证明", DBOPTION_DEFAULT});
        memberVector.push_back({"zzxzqh", "zanZhuXingZhengQuHua", &zanZhuXingZhengQuHua, "暂住行政区划", DBOPTION_DEFAULT});
        memberVector.push_back({"zzxxdz", "zanZhuXiangXiDiZhi", &zanZhuXiangXiDiZhi, "暂住详细地址", DBOPTION_DEFAULT});
        memberVector.push_back({"yzbm2", "youZhengBianMa2", &youZhengBianMa2, "暂住邮政编码", DBOPTION_DEFAULT});
        memberVector.push_back({"ywlx", "yeWuLeiXing", &yeWuLeiXing, "业务种类", DBOPTION_DEFAULT});
        memberVector.push_back({"ywyy", "yeWuYuanYin", &yeWuYuanYin, "业务原因", DBOPTION_DEFAULT});
        memberVector.push_back({"dphgzbh", "diPanHeGeZhengBianHao", &diPanHeGeZhengBianHao, "底盘合格证编号", DBOPTION_DEFAULT});
        memberVector.push_back({"dzyx", "dianZiYouXiang", &dianZiYouXiang, "电子邮箱", DBOPTION_DEFAULT});
        memberVector.push_back({"zdclxx", "zhongDianCheLiangXinXi", &zhongDianCheLiangXinXi, "重点车辆信息", DBOPTION_DEFAULT});
        memberVector.push_back({"dlrxm", "dlrxm", &daiLiRenXingMing, "代理人姓名", DBOPTION_DEFAULT});
        memberVector.push_back({"dlrsfzmhm", "dlrsfzmhm", &daiLiRenShenFenZhengMingHaoMa, "代理人身份证明号码", DBOPTION_DEFAULT});
        memberVector.push_back({"dlrsjhm", "dlrsjhm", &daiLiRenShouJiHaoMa, "代理人手机号码", DBOPTION_DEFAULT});
        memberVector.push_back({"dlrssdw", "dlrssdw", &daiLiRenSuoShuDanWei, "代理人所属单位", DBOPTION_DEFAULT});
        memberVector.push_back({"jbrid", "jbrid", &JBRID, "所有人登记人ID", DBOPTION_DEFAULT});
        memberVector.push_back({"jbr", "jbr", &JBR, "所有人登记人", DBOPTION_DEFAULT});
        memberVector.push_back({"spcgs", "spcgs", &shangPaiCheGuanSuo, "上牌车管所", DBOPTION_DEFAULT});
        memberVector.push_back({"yyspsj", "yyspsj", &yuYueShangPaiShiJian, "预约上牌时间", DBOPTION_DEFAULT});
        memberVector.push_back({"jdcdjrid", "jdcdjrid", &jiDongCheDongJiRenID, "机动车登记人ID", DBOPTION_DEFAULT});
        memberVector.push_back({"jdcdjrxm", "jdcdjrxm", &jiDongCheDongJiRenXingMing, "机动车登记人姓名", DBOPTION_DEFAULT});
        memberVector.push_back({"jdcdjbm", "jdcdjbm", &jiDongCheDongJiBuMen, "机动车登记部门", DBOPTION_DEFAULT});
        memberVector.push_back({"jdcdjsj", "jdcdjsj", &jiDongCheDengJiShiJian, "机动车登记时间", DBOPTION_DEFAULT});
        memberVector.push_back({"syrdjsj", "syrdjsj", &suoYouRenDengJiShiJian, "所有人登记时间", DBOPTION_DEFAULT});
        memberVector.push_back({"ssdw", "ssdw", &suoShuDanWei, "记录所属单位", DBOPTION_DEFAULT});
        memberVector.push_back({"zt", "zz", &zhuangTai, "状态", DBOPTION_DEFAULT});
        memberVector.push_back({"bz", "bz", &beiZhu, "备注", DBOPTION_DEFAULT});
        memberVector.push_back({"csbj", "csbj", &chuanShuBiaoJi, "传输标记", DBOPTION_DEFAULT});
        memberVector.push_back({"jkpzqfrq", "jkpzqfrq", &jinKouPingZhengQianFaRiQi, "进口凭证签发日期", DBOPTION_DEFAULT});        
        memberVector.push_back({"jlzt", "jlzt", &jiLuZhuangTai, "记录状态", DBOPTION_DEFAULT});//0
        memberVector.push_back({"sfzmyxqs", "sfzmyxqs", &shenFenZhengMingYouXiaoQiShi, "身份证明有效期始", DBOPTION_DEFAULT});
        memberVector.push_back({"sfzmyxqz", "sfzmyxqz", &shenFenZhengMingYouXiaoQiZhi, "身份证明有效期止", DBOPTION_DEFAULT});
        memberVector.push_back({"hpzl", "haoPaiZhongLei", &haoPaiZhongLei, "号牌种类", DBOPTION_DEFAULT});//0
        memberVector.push_back({"sfzzrk", "sfzzrk", &shiFouZanZhuRenKou, "是否暂住人口", DBOPTION_DEFAULT});
        memberVector.push_back({"gxsj", "gxsj", &gengXinShiJian, "更新时间", DBOPTION_DEFAULT});//0
        memberVector.push_back({"sfczrk", "sfczrk", &shiFouChangZhuRenKou, "是否常住人口", DBOPTION_DEFAULT});
        memberVector.push_back({"yh", "yh", &youHao, "油耗", DBOPTION_DEFAULT});
        memberVector.push_back({"zh", "zh", &zhouHe, "轴荷", DBOPTION_DEFAULT});
        memberVector.push_back({"zzllyxs", "zzllyxs", &zaiZhiLiangLiYongXiShu, "载质量利用系数", DBOPTION_DEFAULT});
        memberVector.push_back({"bgcazzdyxzzl", "bgcazzdyxzzl", &banGuaCheAnZuoZuiDaYunXuZhiLiang, "半挂车鞍座最大允许质量", DBOPTION_DEFAULT});
        memberVector.push_back({"zgsjss", "zgsjss", &zuiGaoSheJiShiSu, "最高设计时速", DBOPTION_DEFAULT});
        memberVector.push_back({"clzzrq", "clzzrq", &cheLiangZhiZaoRiQi, "车辆制造日期", DBOPTION_DEFAULT});
        memberVector.push_back({"sfdl", "sfdl", &shiFouDaiLi, "是否代理", DBOPTION_DEFAULT});//0
        memberVector.push_back({"yjdz", "yjdz", &youJiDiZhi, "邮寄地址", DBOPTION_DEFAULT});//0
        memberVector.push_back({"xh", "xh", &xuHao, "机动车序号(抵押)", DBOPTION_DEFAULT});//0
        memberVector.push_back({"zhth", "zhth", &zhuHeTongHao, "主合同号(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"dyhth", "dyhth", &diYaHeTongHao, "抵押合同号(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"dyje", "dyje", &diYaJinEr, "抵押金额(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"dydjrq", "dydjrq", &diYaDengJiRiQi, "抵押登记日期(抵押)", DBOPTION_DEFAULT});//0
        memberVector.push_back({"dyjbr", "dyjbr", &diYaJingBanRen, "经办人(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"dyqr", "dyqr", &diYaQuanRen, "抵押权人(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"dyqrsfzmmc", "dyqrsfzmmc", &diYaQuanRenShenFenZhengMingMingCheng, "身份证明名称(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"dyqrsfzmhm", "dyqrsfzmhm", &diYaQuanRenShenFenZhengMingHaoMa, "身份证明号码(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"dyqrxzqh", "dyqrxzqh", &diYaQuanRenXingZhengQuHua, "抵押权人行政区划(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"dyqrxxdz", "dyqrxxdz", &diYaQuanRenXiangXiDiZhi, "详细地址(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"dyqryzbm", "dyqryzbm", &diYaQuanRenYouZhengBianMa, "邮政编码(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"dyqrlxdh", "dyqrlxdh", &diYaQuanRenLianXiDianHua, "联系电话(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"jcqr", "jcqr", &jieChuRiQi, "解除日期(抵押)", DBOPTION_DEFAULT});//
        memberVector.push_back({"dyglbm", "dyglbm", &diYaGuanLiBuMen, "管理部门(抵押)", DBOPTION_DEFAULT});
        memberVector.push_back({"jlssfwz", "jlssfwz", &jiLuSuoShuFuWuZhan, "记录所属服务站(抵押)", DBOPTION_DEFAULT});//0
        memberVector.push_back({"jlsscgs", "jlsscgs", &jiLuSuoShuCheGuanSuo, "记录所属车管所(抵押)", DBOPTION_DEFAULT});//0
        memberVector.push_back({"tp", "tp", &tuPian, "图片", DBOPTION_LONGLONGLONG});

        pRunTime = new _c_runTime();
        pRunTime->loadUuid();
    }

    virtual ~_c_yingXiangVehicle(){} //用于释放内存（必须）
    void extraDbWork();
    bool loadAlgTask();
    bool loadAllParam();

    bool CreatPath(string path);
};
#endif // _C_YINGXIANGVEHICLE_H
