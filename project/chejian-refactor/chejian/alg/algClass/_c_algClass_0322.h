#ifndef _C_ALGCLASS_0322_H
#define _C_ALGCLASS_0322_H
#include "_c_algBaseClass.h"

class _c_algClass_0322 : public _c_algBaseClass {
public:
	ALG_PARM_MEMBER chePaiHao = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhiDongLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhouLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER cheLiangLeiXing = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER gunTong1 = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER shuiYinRiQi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER youDeng = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhiDong = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zuoDeng = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER zhiDongDeng = ALG_PARAM_DEFAULT;

	std::vector <memberItem> inMemberList = {
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
		{"shuiYinRiQi", "水印日期", &shuiYinRiQi, true, CONFIG_DEFAULT},
		{"zhiDongLeiXing", "制动类型", &zhiDongLeiXing, true, CONFIG_DEFAULT},
		{"zhouLeiXing", "轴类型", &zhouLeiXing, true, CONFIG_DEFAULT}
	};

	std::vector <memberItem> resultMemberList = {
		{"zhiDong", "车轮位置不对", &zhiDong, true, CONFIG_DEFAULT},
		{"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"shuiYinRiQi", "照片水印日期过期", &shuiYinRiQi, true, CONFIG_NOCHECK},
		{"gunTong", "滚筒(平板)", &gunTong1, false, CONFIG_NOCHECK},
		//调用灯光接口
		{"zuoDeng", "左灯未亮", &zuoDeng, true, CONFIG_NOCHECK},
		{"youDeng", "右灯未亮", &youDeng, true, CONFIG_NOCHECK},
		{"zhiDongDeng", "制动灯未亮", &zhiDongDeng, true, CONFIG_NOCHECK}
	};

	std::vector <memberItem> inMemberList_moTuo = {

		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
		{"zhiDongLeiXing", "制动类型", &zhiDongLeiXing, true, CONFIG_DEFAULT},
		{"zhouLeiXing", "轴类型", &zhouLeiXing, true, CONFIG_DEFAULT}
	};

	std::vector <memberItem> resultMemberList_moTuo = {
		{"zhiDong", "车轮位置不对", &zhiDong, true, CONFIG_DEFAULT},
		{"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"zuoDeng", "左灯未亮", &zuoDeng, true, CONFIG_NOCHECK},
		{"youDeng", "右灯未亮", &youDeng, true, CONFIG_NOCHECK}
	};

	ALG_PARM_MEMBER shiYongXingZhi = ALG_PARAM_DEFAULT;
	std::vector <memberItem> inMemberList_video = {
		{"chePaiHao", "车牌号", &chePaiHao, true, CONFIG_DEFAULT},
		{"cheLiangLeiXing", "车辆类型", &cheLiangLeiXing, true, CONFIG_DEFAULT},
		{"shiYongXingZhi", "使用性质", &shiYongXingZhi, true, CONFIG_DEFAULT},
	};

	ALG_PARM_MEMBER cheLunTaiQi = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER renCunZai = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER dengGuang = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER gunTong = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER shiJian = ALG_PARAM_DEFAULT;
	ALG_PARM_MEMBER yiZhou = ALG_PARAM_DEFAULT;
	std::vector <memberItem> resultMemberList_video = {
		{"chePaiHao", "车牌号不正确", &chePaiHao, true, CONFIG_DEFAULT},
		{"yiZhou", "车轮位置不对", &yiZhou, true, CONFIG_DEFAULT},
		{"cheLunTaiQi", "轮胎没有抬起", &cheLunTaiQi, true, CONFIG_DEFAULT},
		{"renCunZai", "检测到人", &renCunZai, true, CONFIG_DEFAULT},
		{"dengGuang", "尾灯不亮", &dengGuang, true, CONFIG_DEFAULT},
		{"gunTong", "不在滚筒(平板)区域", &gunTong, true, CONFIG_DEFAULT},
		{"shiJian", "检验时间不够", &shiJian, true, CONFIG_DEFAULT},
	};

	virtual ~_c_algClass_0322() {}
	virtual bool seekMemberListPointer();
	virtual bool InParamEdit();
	virtual bool ResultEdit();
	virtual std::string getPhotoName(std::string algcode);
	void setAlgIds() override;
};

#endif // _C_ALGCLASS_0322_H
