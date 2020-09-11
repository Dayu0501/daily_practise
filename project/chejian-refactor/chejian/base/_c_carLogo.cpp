#include<iostream>
#include<string>
#include<vector>
#include<cstdio>
#include<string.h>
#include "_c_carLogo.h"

/* 车型 */
class VehicleType {
public:
    VehicleType(std::string name_CHS, std::string name_ENG) : name_CHS(name_CHS), name_ENG(name_ENG) {}

    std::string name_CHS;
    std::string name_ENG;
};

/* 车标 */
class VehicleLogo {
public:
    std::string name_CHS;
    std::string name_ENG;
    std::vector<VehicleType> TypeList;
};

static std::vector<VehicleLogo> logo_list;
void  initLogoList()
{
    VehicleLogo logo;
    logo.name_CHS = "美星华通", logo.name_ENG = "GMC";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "", logo.name_ENG = "SMART";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("精灵", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "", logo.name_ENG = "SMART2";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("精灵", ""));
    logo_list.push_back(logo);


    logo.name_CHS = "豪沃"; logo.name_ENG = "HOWO";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "豪瀚"; logo.name_ENG = "";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "北汽幻速"; logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("北京", ""));
    logo.TypeList.push_back(VehicleType("北汽", ""));
    logo.TypeList.push_back(VehicleType("", "S7"));
    logo.TypeList.push_back(VehicleType("", "S3"));
    logo.TypeList.push_back(VehicleType("", "S5"));
    logo.TypeList.push_back(VehicleType("", "S6"));
    logo.TypeList.push_back(VehicleType("", "H2"));
    logo.TypeList.push_back(VehicleType("", "H6"));
    logo.TypeList.push_back(VehicleType("", "H3"));
    logo.TypeList.push_back(VehicleType("", "S2"));
    logo.TypeList.push_back(VehicleType("", "H5"));
    logo_list.push_back(logo);

    logo.name_CHS = "捷豹"; logo.name_ENG = "Jaguar";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "E-PACE"));
    logo.TypeList.push_back(VehicleType("", "XEL"));
    logo.TypeList.push_back(VehicleType("", "XFL"));
    logo.TypeList.push_back(VehicleType("", "F-PACE"));
    logo.TypeList.push_back(VehicleType("", "XE"));
    logo.TypeList.push_back(VehicleType("", "XF"));
    logo.TypeList.push_back(VehicleType("", "XJ"));
    logo.TypeList.push_back(VehicleType("", "F-TYPE"));
    logo.TypeList.push_back(VehicleType("", "I-PACE"));
    logo.TypeList.push_back(VehicleType("", "S-TYPE"));
    logo.TypeList.push_back(VehicleType("", "XK"));
    logo_list.push_back(logo);

    logo.name_CHS = "捷豹2"; logo.name_ENG = "Jaguar";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "E-PACE"));
    logo.TypeList.push_back(VehicleType("", "XEL"));
    logo.TypeList.push_back(VehicleType("", "XFL"));
    logo.TypeList.push_back(VehicleType("", "F-PACE"));
    logo.TypeList.push_back(VehicleType("", "XE"));
    logo.TypeList.push_back(VehicleType("", "XF"));
    logo.TypeList.push_back(VehicleType("", "XJ"));
    logo.TypeList.push_back(VehicleType("", "F-TYPE"));
    logo.TypeList.push_back(VehicleType("", "I-PACE"));
    logo.TypeList.push_back(VehicleType("", "S-TYPE"));
    logo.TypeList.push_back(VehicleType("", "XK"));
    logo_list.push_back(logo);

    logo.name_CHS = "大发"; logo.name_ENG = "";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "中通"; logo.name_ENG = "";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "北汽威旺"; logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "M20"));
    logo.TypeList.push_back(VehicleType("", "M50F"));
    logo.TypeList.push_back(VehicleType("", "M30"));
    logo.TypeList.push_back(VehicleType("", "M60"));
    logo.TypeList.push_back(VehicleType("", "S50"));
    logo.TypeList.push_back(VehicleType("306", ""));
    logo.TypeList.push_back(VehicleType("307", ""));
    logo.TypeList.push_back(VehicleType("205", ""));
    logo.TypeList.push_back(VehicleType("", "M35"));
    logo.TypeList.push_back(VehicleType("北京", ""));
    logo.TypeList.push_back(VehicleType("北汽", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "黑豹"; logo.name_ENG = "";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "奥迪", logo.name_ENG = "Audi";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "A1"));
    logo.TypeList.push_back(VehicleType("", "A3"));
    logo.TypeList.push_back(VehicleType("", "A4"));
    logo.TypeList.push_back(VehicleType("", "A5"));
    logo.TypeList.push_back(VehicleType("", "A6"));
    logo.TypeList.push_back(VehicleType("", "A7"));
    logo.TypeList.push_back(VehicleType("", "A8"));
    logo.TypeList.push_back(VehicleType("", "Q1"));
    logo.TypeList.push_back(VehicleType("", "Q2"));
    logo.TypeList.push_back(VehicleType("", "Q3"));
    logo.TypeList.push_back(VehicleType("", "Q5"));
    logo.TypeList.push_back(VehicleType("", "Q7"));
    logo.TypeList.push_back(VehicleType("", "TT"));
    logo.TypeList.push_back(VehicleType("", "TTS"));
    logo.TypeList.push_back(VehicleType("", "TTRS"));
    logo.TypeList.push_back(VehicleType("", "R8"));
    logo.TypeList.push_back(VehicleType("", "S3"));
    logo.TypeList.push_back(VehicleType("", "S4"));
    logo.TypeList.push_back(VehicleType("", "S5"));
    logo.TypeList.push_back(VehicleType("", "S6"));
    logo.TypeList.push_back(VehicleType("", "S7"));
    logo.TypeList.push_back(VehicleType("", "S8"));
    logo.TypeList.push_back(VehicleType("", "RS3"));
    logo.TypeList.push_back(VehicleType("", "RS6"));
    logo.TypeList.push_back(VehicleType("", "RS7"));
    logo.TypeList.push_back(VehicleType("", "SQ5"));
    logo_list.push_back(logo);

    logo.name_CHS = "保时捷", logo.name_ENG = "Porsche";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "911"));
    logo.TypeList.push_back(VehicleType("", "Cayenne"));
    logo.TypeList.push_back(VehicleType("", "Panamera"));
    logo.TypeList.push_back(VehicleType("", "Macan"));
    logo.TypeList.push_back(VehicleType("", "718"));
    logo.TypeList.push_back(VehicleType("", "凯宴"));
    logo.TypeList.push_back(VehicleType("帕纳美拉", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "宝骏", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "730"));
    logo.TypeList.push_back(VehicleType("", "560"));
    logo.TypeList.push_back(VehicleType("", "310"));
    logo.TypeList.push_back(VehicleType("", "510"));
    logo.TypeList.push_back(VehicleType("", "530"));
    logo.TypeList.push_back(VehicleType("", "360"));
    logo.TypeList.push_back(VehicleType("", "100"));
    logo.TypeList.push_back(VehicleType("", "200"));
    logo_list.push_back(logo);

    logo.name_CHS = "宝马", logo.name_ENG = "BMW";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("1系", ""));
    logo.TypeList.push_back(VehicleType("2系", ""));
    logo.TypeList.push_back(VehicleType("3系", ""));
    logo.TypeList.push_back(VehicleType("4系", ""));
    logo.TypeList.push_back(VehicleType("5系", ""));
    logo.TypeList.push_back(VehicleType("6系", ""));
    logo.TypeList.push_back(VehicleType("7系", ""));
    logo.TypeList.push_back(VehicleType("", "X1"));
    logo.TypeList.push_back(VehicleType("", "X3"));
    logo.TypeList.push_back(VehicleType("", "X4"));
    logo.TypeList.push_back(VehicleType("", "X5"));
    logo.TypeList.push_back(VehicleType("", "X6"));
    logo.TypeList.push_back(VehicleType("", "i3"));
    logo.TypeList.push_back(VehicleType("", "i8"));
    logo.TypeList.push_back(VehicleType("", "M3"));
    logo.TypeList.push_back(VehicleType("", "M2"));
    logo.TypeList.push_back(VehicleType("", "M4"));
    logo.TypeList.push_back(VehicleType("", "M5"));
    logo.TypeList.push_back(VehicleType("", "M6"));
    logo_list.push_back(logo);

    logo.name_CHS = "北京", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("北京汽车", "")); /* 车标别名，不是车型 */
    logo.TypeList.push_back(VehicleType("", "BJ20"));
    logo.TypeList.push_back(VehicleType("", "BJ40"));
    logo.TypeList.push_back(VehicleType("", "BJ80"));
    logo_list.push_back(logo);

    logo.name_CHS = "现代", logo.name_ENG = "HYUNDAI";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("北京现代", "")); /* 车标别名，不是车型 */
    logo.TypeList.push_back(VehicleType("途胜", ""));
    logo.TypeList.push_back(VehicleType("悦动", ""));
    logo.TypeList.push_back(VehicleType("", "ix25"));
    logo.TypeList.push_back(VehicleType("", "ix35"));
    logo.TypeList.push_back(VehicleType("飞思", ""));
    logo.TypeList.push_back(VehicleType("辉翼", ""));
    logo.TypeList.push_back(VehicleType("瑞纳", "VERNA"));
    logo.TypeList.push_back(VehicleType("朗动", ""));
    logo.TypeList.push_back(VehicleType("全新胜达", ""));
    logo.TypeList.push_back(VehicleType("名图", "MISTRA"));
    logo.TypeList.push_back(VehicleType("瑞奕", ""));
    logo.TypeList.push_back(VehicleType("捷恩斯", ""));
    logo.TypeList.push_back(VehicleType("伊兰特", ""));
    logo.TypeList.push_back(VehicleType("华泰圣达菲", ""));
    logo.TypeList.push_back(VehicleType("维拉克斯", ""));
    logo.TypeList.push_back(VehicleType("酷派", ""));
    logo.TypeList.push_back(VehicleType("胜达", ""));

    logo_list.push_back(logo);

    logo.name_CHS = "奔驰", logo.name_ENG = "Mercedes-Benz";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("A级", ""));
    logo.TypeList.push_back(VehicleType("B级", ""));
    logo.TypeList.push_back(VehicleType("C级", ""));
    logo.TypeList.push_back(VehicleType("CL级", ""));
    logo.TypeList.push_back(VehicleType("CLK级", ""));
    logo.TypeList.push_back(VehicleType("CLS级", ""));
    logo.TypeList.push_back(VehicleType("E级", ""));
    logo.TypeList.push_back(VehicleType("S级", ""));
    logo.TypeList.push_back(VehicleType("SL级", ""));
    logo.TypeList.push_back(VehicleType("SLC级", ""));
    logo.TypeList.push_back(VehicleType("SLK级", ""));
    logo.TypeList.push_back(VehicleType("SLR级", ""));
    logo.TypeList.push_back(VehicleType("G级", ""));
    logo.TypeList.push_back(VehicleType("GLK级", ""));
    logo.TypeList.push_back(VehicleType("M级", ""));
    logo.TypeList.push_back(VehicleType("R级", ""));
    logo.TypeList.push_back(VehicleType("AMG车系", ""));
    logo.TypeList.push_back(VehicleType("威霆", "Vito"));
    logo.TypeList.push_back(VehicleType("威雷", "Vario"));
    logo.TypeList.push_back(VehicleType("凌特", "Sprinter"));
    logo.TypeList.push_back(VehicleType("", "Travego"));
    logo.TypeList.push_back(VehicleType("", "Tourismo"));
    logo.TypeList.push_back(VehicleType("", "Travego"));
    logo.TypeList.push_back(VehicleType("", "Tourino"));
    logo.TypeList.push_back(VehicleType("豪华商用车（MPV）", "Minibus"));
    logo.TypeList.push_back(VehicleType("唯雅诺", "Viano"));
    logo.TypeList.push_back(VehicleType("梅赛德斯", "Mercedes"));
    logo.TypeList.push_back(VehicleType("嘉恒", ""));
    logo.TypeList.push_back(VehicleType("宇通", ""));
    logo.TypeList.push_back(VehicleType("新凯", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "本田", logo.name_ENG = "hongda";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("奥德赛", ""));
    logo.TypeList.push_back(VehicleType("缤智", ""));
    logo.TypeList.push_back(VehicleType("飞度", ""));
    logo.TypeList.push_back(VehicleType("锋范", ""));
    logo.TypeList.push_back(VehicleType("冠道", ""));
    logo.TypeList.push_back(VehicleType("歌诗图", ""));
    logo.TypeList.push_back(VehicleType("凌派", ""));
    logo.TypeList.push_back(VehicleType("雅阁", ""));
    logo.TypeList.push_back(VehicleType("雅阁锐·混动", ""));
    logo.TypeList.push_back(VehicleType("", "CR-Z"));
    logo.TypeList.push_back(VehicleType("", "Insight"));
    logo.TypeList.push_back(VehicleType("飞度", ""));
    logo.TypeList.push_back(VehicleType("艾力绅", ""));
    logo.TypeList.push_back(VehicleType("CR-V锐·混动", ""));
    logo.TypeList.push_back(VehicleType("", "UR-V"));
    logo.TypeList.push_back(VehicleType("", "XR-V"));
    logo.TypeList.push_back(VehicleType("缤智", ""));
    logo.TypeList.push_back(VehicleType("飞度", ""));
    logo.TypeList.push_back(VehicleType("锋范", ""));
    logo.TypeList.push_back(VehicleType("冠道", ""));
    logo.TypeList.push_back(VehicleType("歌诗图", ""));
    logo.TypeList.push_back(VehicleType("凌派", ""));
    logo.TypeList.push_back(VehicleType("雅阁", ""));
    logo.TypeList.push_back(VehicleType("雅阁锐·混动", ""));
    logo.TypeList.push_back(VehicleType("", "CR-Z"));
    logo.TypeList.push_back(VehicleType("", "Insight"));
    logo.TypeList.push_back(VehicleType("飞度", ""));
    logo.TypeList.push_back(VehicleType("艾力绅", ""));
    logo.TypeList.push_back(VehicleType("CR-V锐·混动", ""));
    logo.TypeList.push_back(VehicleType("哥瑞", ""));
    logo.TypeList.push_back(VehicleType("INSPIRE锐·混动", ""));
    logo.TypeList.push_back(VehicleType("杰德", ""));
    logo.TypeList.push_back(VehicleType("竞瑞", ""));
    logo.TypeList.push_back(VehicleType("思铂睿", ""));
    logo.TypeList.push_back(VehicleType("思铂睿锐·混动", ""));
    logo.TypeList.push_back(VehicleType("思域", ""));
    logo.TypeList.push_back(VehicleType("思域新能源", ""));
    logo.TypeList.push_back(VehicleType("时韵", ""));
    logo.TypeList.push_back(VehicleType("炫威", ""));
    logo.TypeList.push_back(VehicleType("思威", ""));
    logo.TypeList.push_back(VehicleType("理念", ""));
    logo.TypeList.push_back(VehicleType("思迪", ""));
    logo.TypeList.push_back(VehicleType("思铭", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "比亚迪", logo.name_ENG = "BYD";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "e6"));
    logo.TypeList.push_back(VehicleType("秦", ""));
    logo.TypeList.push_back(VehicleType("王朝概念车", ""));
    logo.TypeList.push_back(VehicleType("唐", ""));
    logo.TypeList.push_back(VehicleType("", "F0"));
    logo.TypeList.push_back(VehicleType("", "F3"));
    logo.TypeList.push_back(VehicleType("速锐", ""));
    logo.TypeList.push_back(VehicleType("元EV", ""));
    logo.TypeList.push_back(VehicleType("", "G5"));
    logo.TypeList.push_back(VehicleType("秦Pro", ""));
    logo.TypeList.push_back(VehicleType("宋", ""));
    logo.TypeList.push_back(VehicleType("宋MAX", ""));
    logo.TypeList.push_back(VehicleType("", "S7"));
    logo.TypeList.push_back(VehicleType("", "M6"));
    logo.TypeList.push_back(VehicleType("秦Pro DM", ""));
    logo.TypeList.push_back(VehicleType("", "G6"));
    logo.TypeList.push_back(VehicleType("秦Pro EV", ""));
    logo.TypeList.push_back(VehicleType("宋DM", ""));
    logo.TypeList.push_back(VehicleType("宋EV", ""));
    logo.TypeList.push_back(VehicleType("秦100", ""));
    logo.TypeList.push_back(VehicleType("", "e5"));
    logo.TypeList.push_back(VehicleType("唐DM", ""));
    logo.TypeList.push_back(VehicleType("秦EV", ""));
    logo.TypeList.push_back(VehicleType("唐100", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "比亚迪-秦", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "e6"));
    logo.TypeList.push_back(VehicleType("秦", ""));
    logo.TypeList.push_back(VehicleType("王朝概念车", ""));
    logo.TypeList.push_back(VehicleType("唐", ""));
    logo.TypeList.push_back(VehicleType("", "F0"));
    logo.TypeList.push_back(VehicleType("", "F3"));
    logo.TypeList.push_back(VehicleType("速锐", ""));
    logo.TypeList.push_back(VehicleType("元EV", ""));
    logo.TypeList.push_back(VehicleType("", "G5"));
    logo.TypeList.push_back(VehicleType("秦Pro", ""));
    logo.TypeList.push_back(VehicleType("宋", ""));
    logo.TypeList.push_back(VehicleType("宋MAX", ""));
    logo.TypeList.push_back(VehicleType("", "S7"));
    logo.TypeList.push_back(VehicleType("", "M6"));
    logo.TypeList.push_back(VehicleType("秦Pro DM", ""));
    logo.TypeList.push_back(VehicleType("", "G6"));
    logo.TypeList.push_back(VehicleType("秦Pro EV", ""));
    logo.TypeList.push_back(VehicleType("宋DM", ""));
    logo.TypeList.push_back(VehicleType("宋EV", ""));
    logo.TypeList.push_back(VehicleType("秦100", ""));
    logo.TypeList.push_back(VehicleType("", "e5"));
    logo.TypeList.push_back(VehicleType("唐DM", ""));
    logo.TypeList.push_back(VehicleType("秦EV", ""));
    logo.TypeList.push_back(VehicleType("唐100", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "比亚迪-宋", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "e6"));
    logo.TypeList.push_back(VehicleType("秦", ""));
    logo.TypeList.push_back(VehicleType("王朝概念车", ""));
    logo.TypeList.push_back(VehicleType("唐", ""));
    logo.TypeList.push_back(VehicleType("", "F0"));
    logo.TypeList.push_back(VehicleType("", "F3"));
    logo.TypeList.push_back(VehicleType("速锐", ""));
    logo.TypeList.push_back(VehicleType("元EV", ""));
    logo.TypeList.push_back(VehicleType("", "G5"));
    logo.TypeList.push_back(VehicleType("秦Pro", ""));
    logo.TypeList.push_back(VehicleType("宋", ""));
    logo.TypeList.push_back(VehicleType("宋MAX", ""));
    logo.TypeList.push_back(VehicleType("", "S7"));
    logo.TypeList.push_back(VehicleType("", "M6"));
    logo.TypeList.push_back(VehicleType("秦Pro DM", ""));
    logo.TypeList.push_back(VehicleType("", "G6"));
    logo.TypeList.push_back(VehicleType("秦Pro EV", ""));
    logo.TypeList.push_back(VehicleType("宋DM", ""));
    logo.TypeList.push_back(VehicleType("宋EV", ""));
    logo.TypeList.push_back(VehicleType("秦100", ""));
    logo.TypeList.push_back(VehicleType("", "e5"));
    logo.TypeList.push_back(VehicleType("唐DM", ""));
    logo.TypeList.push_back(VehicleType("秦EV", ""));
    logo.TypeList.push_back(VehicleType("唐100", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "比亚迪-唐", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "e6"));
    logo.TypeList.push_back(VehicleType("秦", ""));
    logo.TypeList.push_back(VehicleType("王朝概念车", ""));
    logo.TypeList.push_back(VehicleType("唐", ""));
    logo.TypeList.push_back(VehicleType("", "F0"));
    logo.TypeList.push_back(VehicleType("", "F3"));
    logo.TypeList.push_back(VehicleType("速锐", ""));
    logo.TypeList.push_back(VehicleType("元EV", ""));
    logo.TypeList.push_back(VehicleType("", "G5"));
    logo.TypeList.push_back(VehicleType("秦Pro", ""));
    logo.TypeList.push_back(VehicleType("宋", ""));
    logo.TypeList.push_back(VehicleType("宋MAX", ""));
    logo.TypeList.push_back(VehicleType("", "S7"));
    logo.TypeList.push_back(VehicleType("", "M6"));
    logo.TypeList.push_back(VehicleType("秦Pro DM", ""));
    logo.TypeList.push_back(VehicleType("", "G6"));
    logo.TypeList.push_back(VehicleType("秦Pro EV", ""));
    logo.TypeList.push_back(VehicleType("宋DM", ""));
    logo.TypeList.push_back(VehicleType("宋EV", ""));
    logo.TypeList.push_back(VehicleType("秦100", ""));
    logo.TypeList.push_back(VehicleType("", "e5"));
    logo.TypeList.push_back(VehicleType("唐DM", ""));
    logo.TypeList.push_back(VehicleType("秦EV", ""));
    logo.TypeList.push_back(VehicleType("唐100", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "比亚迪-元", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "e6"));
    logo.TypeList.push_back(VehicleType("秦", ""));
    logo.TypeList.push_back(VehicleType("王朝概念车", ""));
    logo.TypeList.push_back(VehicleType("唐", ""));
    logo.TypeList.push_back(VehicleType("", "F0"));
    logo.TypeList.push_back(VehicleType("", "F3"));
    logo.TypeList.push_back(VehicleType("速锐", ""));
    logo.TypeList.push_back(VehicleType("元EV", ""));
    logo.TypeList.push_back(VehicleType("", "G5"));
    logo.TypeList.push_back(VehicleType("秦Pro", ""));
    logo.TypeList.push_back(VehicleType("宋", ""));
    logo.TypeList.push_back(VehicleType("宋MAX", ""));
    logo.TypeList.push_back(VehicleType("", "S7"));
    logo.TypeList.push_back(VehicleType("", "M6"));
    logo.TypeList.push_back(VehicleType("秦Pro DM", ""));
    logo.TypeList.push_back(VehicleType("", "G6"));
    logo.TypeList.push_back(VehicleType("秦Pro EV", ""));
    logo.TypeList.push_back(VehicleType("宋DM", ""));
    logo.TypeList.push_back(VehicleType("宋EV", ""));
    logo.TypeList.push_back(VehicleType("秦100", ""));
    logo.TypeList.push_back(VehicleType("", "e5"));
    logo.TypeList.push_back(VehicleType("唐DM", ""));
    logo.TypeList.push_back(VehicleType("秦EV", ""));
    logo.TypeList.push_back(VehicleType("唐100", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "比亚迪2", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "e6"));
    logo.TypeList.push_back(VehicleType("秦", ""));
    logo.TypeList.push_back(VehicleType("王朝概念车", ""));
    logo.TypeList.push_back(VehicleType("唐", ""));
    logo.TypeList.push_back(VehicleType("", "F0"));
    logo.TypeList.push_back(VehicleType("", "F3"));
    logo.TypeList.push_back(VehicleType("速锐", ""));
    logo.TypeList.push_back(VehicleType("元EV", ""));
    logo.TypeList.push_back(VehicleType("", "G5"));
    logo.TypeList.push_back(VehicleType("秦Pro", ""));
    logo.TypeList.push_back(VehicleType("宋", ""));
    logo.TypeList.push_back(VehicleType("宋MAX", ""));
    logo.TypeList.push_back(VehicleType("", "S7"));
    logo.TypeList.push_back(VehicleType("", "M6"));
    logo.TypeList.push_back(VehicleType("秦Pro DM", ""));
    logo.TypeList.push_back(VehicleType("", "G6"));
    logo.TypeList.push_back(VehicleType("秦Pro EV", ""));
    logo.TypeList.push_back(VehicleType("宋DM", ""));
    logo.TypeList.push_back(VehicleType("宋EV", ""));
    logo.TypeList.push_back(VehicleType("秦100", ""));
    logo.TypeList.push_back(VehicleType("", "e5"));
    logo.TypeList.push_back(VehicleType("唐DM", ""));
    logo.TypeList.push_back(VehicleType("秦EV", ""));
    logo.TypeList.push_back(VehicleType("唐100", ""));
    logo_list.push_back(logo);


    logo.name_CHS = "标致", logo.name_ENG = "PEUGEOT";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("207三厢", ""));
    logo.TypeList.push_back(VehicleType("206", ""));
    logo.TypeList.push_back(VehicleType("207两厢", ""));
    logo.TypeList.push_back(VehicleType("307三厢", ""));
    logo.TypeList.push_back(VehicleType("408", ""));
    logo.TypeList.push_back(VehicleType("308", ""));
    logo.TypeList.push_back(VehicleType("307两厢", ""));
    logo.TypeList.push_back(VehicleType("301", ""));
    logo.TypeList.push_back(VehicleType("308S", ""));
    logo.TypeList.push_back(VehicleType("407", ""));
    logo.TypeList.push_back(VehicleType("508", ""));
    logo.TypeList.push_back(VehicleType("607", ""));
    logo.TypeList.push_back(VehicleType("3008", ""));
    logo.TypeList.push_back(VehicleType("2008", ""));
    logo.TypeList.push_back(VehicleType("4008", ""));
    logo.TypeList.push_back(VehicleType("5008", ""));
    logo.TypeList.push_back(VehicleType("207CC", ""));
    logo.TypeList.push_back(VehicleType("307CC", ""));
    logo.TypeList.push_back(VehicleType("308CC", ""));
    logo.TypeList.push_back(VehicleType("206", ""));
    logo.TypeList.push_back(VehicleType("", "RCZ"));
    logo.TypeList.push_back(VehicleType("308SW", ""));
    logo.TypeList.push_back(VehicleType("407SW", ""));
    logo.TypeList.push_back(VehicleType("307SW", ""));
    logo.TypeList.push_back(VehicleType("107", ""));
    logo.TypeList.push_back(VehicleType("108", ""));
    logo.TypeList.push_back(VehicleType("2008", ""));
    logo.TypeList.push_back(VehicleType("208", ""));
    logo.TypeList.push_back(VehicleType("208GTI", ""));
    logo.TypeList.push_back(VehicleType("301", ""));
    logo.TypeList.push_back(VehicleType("308", ""));
    logo.TypeList.push_back(VehicleType("308GTi", ""));
    logo.TypeList.push_back(VehicleType("308R", ""));
    logo.TypeList.push_back(VehicleType("403", ""));
    logo.TypeList.push_back(VehicleType("404", ""));
    logo.TypeList.push_back(VehicleType("406", ""));
    logo.TypeList.push_back(VehicleType("5008 MPV", ""));
    logo.TypeList.push_back(VehicleType("508", ""));
    logo.TypeList.push_back(VehicleType("508RXH", ""));
    logo.TypeList.push_back(VehicleType("807", ""));
    logo.TypeList.push_back(VehicleType("", "EX1"));
    logo.TypeList.push_back(VehicleType("", "Fractal"));
    logo.TypeList.push_back(VehicleType("", "HR1"));
    logo.TypeList.push_back(VehicleType("", "iOn"));
    logo.TypeList.push_back(VehicleType("", "Onyx"));
    logo.TypeList.push_back(VehicleType("", "SXC"));
    logo.TypeList.push_back(VehicleType("5008", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "别克", logo.name_ENG = "Buick";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("昂科拉", "Encore"));
    logo.TypeList.push_back(VehicleType("昂科雷", "Enclave"));
    logo.TypeList.push_back(VehicleType("荣御", "Royaum"));
    logo.TypeList.push_back(VehicleType("君威", "Regal"));
    logo.TypeList.push_back(VehicleType("君越", "Larcosse"));
    logo.TypeList.push_back(VehicleType("凯越", "Excelle"));
    logo.TypeList.push_back(VehicleType("英朗", "Excelle GT;Excelle XT"));
    logo.TypeList.push_back(VehicleType("林荫大道", "Park Avenue"));
    logo.TypeList.push_back(VehicleType("", "BUICK"));
    logo_list.push_back(logo);

    logo.name_CHS = "宾利", logo.name_ENG = "bentley";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("雅致", ""));
    logo.TypeList.push_back(VehicleType("慕尚", ""));
    logo.TypeList.push_back(VehicleType("飞驰", ""));
    logo.TypeList.push_back(VehicleType("添越", ""));
    logo.TypeList.push_back(VehicleType("欧陆", ""));
    logo.TypeList.push_back(VehicleType("雅骏", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "昌河", logo.name_ENG = "Changhe";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("爱迪尔", ""));
    logo.TypeList.push_back(VehicleType("北斗星E", ""));
    logo.TypeList.push_back(VehicleType("北斗星X5E", ""));
    logo.TypeList.push_back(VehicleType("北斗星", ""));
    logo.TypeList.push_back(VehicleType("", "M50"));
    logo.TypeList.push_back(VehicleType("", "Q35"));
    logo.TypeList.push_back(VehicleType("福运", ""));
    logo.TypeList.push_back(VehicleType("海豚", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "长安", logo.name_ENG = "CHANA";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("奔奔", ""));
    logo.TypeList.push_back(VehicleType("奔奔EV", ""));
    logo.TypeList.push_back(VehicleType("奔奔i", ""));
    logo.TypeList.push_back(VehicleType("", "CS15"));
    logo.TypeList.push_back(VehicleType("", "CS35"));
    logo.TypeList.push_back(VehicleType("", "CS55"));
    logo.TypeList.push_back(VehicleType("", "CS75"));
    logo.TypeList.push_back(VehicleType("", "CS95"));
    logo.TypeList.push_back(VehicleType("", "CX30"));
    logo.TypeList.push_back(VehicleType("凌轩", ""));
    logo.TypeList.push_back(VehicleType("睿骋", ""));
    logo.TypeList.push_back(VehicleType("睿骋CC", ""));
    logo.TypeList.push_back(VehicleType("逸动", ""));
    logo.TypeList.push_back(VehicleType("逸动DT", ""));
    logo.TypeList.push_back(VehicleType("逸动新能源", ""));
    logo.TypeList.push_back(VehicleType("逸动XT", ""));
    logo.TypeList.push_back(VehicleType("悦翔", ""));
    logo.TypeList.push_back(VehicleType("悦翔V3", ""));
    logo.TypeList.push_back(VehicleType("悦翔V5", ""));
    logo.TypeList.push_back(VehicleType("悦翔V7", ""));
    logo.TypeList.push_back(VehicleType("", "CS35 PLUS"));
    logo_list.push_back(logo);

    logo.name_CHS = "长安2", logo.name_ENG = "CHANA";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("奔奔", ""));
    logo.TypeList.push_back(VehicleType("奔奔EV", ""));
    logo.TypeList.push_back(VehicleType("奔奔i", ""));
    logo.TypeList.push_back(VehicleType("", "CS15"));
    logo.TypeList.push_back(VehicleType("", "CS35"));
    logo.TypeList.push_back(VehicleType("", "CS55"));
    logo.TypeList.push_back(VehicleType("", "CS75"));
    logo.TypeList.push_back(VehicleType("", "CS95"));
    logo.TypeList.push_back(VehicleType("", "CX30"));
    logo.TypeList.push_back(VehicleType("凌轩", ""));
    logo.TypeList.push_back(VehicleType("睿骋", ""));
    logo.TypeList.push_back(VehicleType("睿骋CC", ""));
    logo.TypeList.push_back(VehicleType("逸动", ""));
    logo.TypeList.push_back(VehicleType("逸动DT", ""));
    logo.TypeList.push_back(VehicleType("逸动新能源", ""));
    logo.TypeList.push_back(VehicleType("逸动XT", ""));
    logo.TypeList.push_back(VehicleType("悦翔", ""));
    logo.TypeList.push_back(VehicleType("悦翔V3", ""));
    logo.TypeList.push_back(VehicleType("悦翔V5", ""));
    logo.TypeList.push_back(VehicleType("悦翔V7", ""));
    logo.TypeList.push_back(VehicleType("", "CS35 PLUS"));
    logo_list.push_back(logo);

    logo.name_CHS = "长安3", logo.name_ENG = "CHANA";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("奔奔", ""));
    logo.TypeList.push_back(VehicleType("奔奔EV", ""));
    logo.TypeList.push_back(VehicleType("奔奔i", ""));
    logo.TypeList.push_back(VehicleType("", "CS15"));
    logo.TypeList.push_back(VehicleType("", "CS35"));
    logo.TypeList.push_back(VehicleType("", "CS55"));
    logo.TypeList.push_back(VehicleType("", "CS75"));
    logo.TypeList.push_back(VehicleType("", "CS95"));
    logo.TypeList.push_back(VehicleType("", "CX30"));
    logo.TypeList.push_back(VehicleType("凌轩", ""));
    logo.TypeList.push_back(VehicleType("睿骋", ""));
    logo.TypeList.push_back(VehicleType("睿骋CC", ""));
    logo.TypeList.push_back(VehicleType("逸动", ""));
    logo.TypeList.push_back(VehicleType("逸动DT", ""));
    logo.TypeList.push_back(VehicleType("逸动新能源", ""));
    logo.TypeList.push_back(VehicleType("逸动XT", ""));
    logo.TypeList.push_back(VehicleType("悦翔", ""));
    logo.TypeList.push_back(VehicleType("悦翔V3", ""));
    logo.TypeList.push_back(VehicleType("悦翔V5", ""));
    logo.TypeList.push_back(VehicleType("悦翔V7", ""));
    logo.TypeList.push_back(VehicleType("", "CS35 PLUS"));
    logo_list.push_back(logo);

    logo.name_CHS = "长城", logo.name_ENG = "Great Wall";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("风骏5", ""));
    logo.TypeList.push_back(VehicleType("风骏7", ""));
    logo.TypeList.push_back(VehicleType("风骏6", ""));
    logo.TypeList.push_back(VehicleType("风骏房车", ""));
    logo.TypeList.push_back(VehicleType("", "M4"));
    logo.TypeList.push_back(VehicleType("", "C30"));
    logo.TypeList.push_back(VehicleType("", "C50"));
    logo.TypeList.push_back(VehicleType("C30新能源", ""));
    logo.TypeList.push_back(VehicleType("", "M2"));
    logo.TypeList.push_back(VehicleType("炫丽", ""));
    logo.TypeList.push_back(VehicleType("酷熊", ""));
    logo.TypeList.push_back(VehicleType("", "V80"));
    logo.TypeList.push_back(VehicleType("", "M1"));
    logo.TypeList.push_back(VehicleType("", "C20R"));
    logo.TypeList.push_back(VehicleType("赛弗", ""));
    logo.TypeList.push_back(VehicleType("精灵", ""));
    logo.TypeList.push_back(VehicleType("凌傲", ""));
    logo.TypeList.push_back(VehicleType("风骏3", ""));
    logo.TypeList.push_back(VehicleType("嘉誉", ""));
    logo.TypeList.push_back(VehicleType("赛影", ""));
    logo.TypeList.push_back(VehicleType("金迪尔", ""));
    logo.TypeList.push_back(VehicleType("赛铃", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "长城2", logo.name_ENG = "Great Wall";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("风骏5", ""));
    logo.TypeList.push_back(VehicleType("风骏7", ""));
    logo.TypeList.push_back(VehicleType("风骏6", ""));
    logo.TypeList.push_back(VehicleType("风骏房车", ""));
    logo.TypeList.push_back(VehicleType("", "M4"));
    logo.TypeList.push_back(VehicleType("", "C30"));
    logo.TypeList.push_back(VehicleType("", "C50"));
    logo.TypeList.push_back(VehicleType("C30新能源", ""));
    logo.TypeList.push_back(VehicleType("", "M2"));
    logo.TypeList.push_back(VehicleType("炫丽", ""));
    logo.TypeList.push_back(VehicleType("酷熊", ""));
    logo.TypeList.push_back(VehicleType("", "V80"));
    logo.TypeList.push_back(VehicleType("", "M1"));
    logo.TypeList.push_back(VehicleType("", "C20R"));
    logo.TypeList.push_back(VehicleType("赛弗", ""));
    logo.TypeList.push_back(VehicleType("精灵", ""));
    logo.TypeList.push_back(VehicleType("凌傲", ""));
    logo.TypeList.push_back(VehicleType("风骏3", ""));
    logo.TypeList.push_back(VehicleType("嘉誉", ""));
    logo.TypeList.push_back(VehicleType("赛影", ""));
    logo.TypeList.push_back(VehicleType("金迪尔", ""));
    logo.TypeList.push_back(VehicleType("赛铃", ""));
    logo_list.push_back(logo);


    logo.name_CHS = "大地", logo.name_ENG = "musso";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "RX6478A"));
    logo.TypeList.push_back(VehicleType("", "RX6405"));
    logo.TypeList.push_back(VehicleType("", "RX6400"));
    logo.TypeList.push_back(VehicleType("", "RX6478"));
    logo.TypeList.push_back(VehicleType("", "RX6400Y"));
    logo.TypeList.push_back(VehicleType("", "RX6480"));
    logo.TypeList.push_back(VehicleType("", "RX6481"));
    logo.TypeList.push_back(VehicleType("", "RX6481A"));
    logo.TypeList.push_back(VehicleType("", "RX6473"));
    logo.TypeList.push_back(VehicleType("", "RX6510"));
    logo.TypeList.push_back(VehicleType("", "RX6472Y"));
    logo.TypeList.push_back(VehicleType("", "RX6470Y"));
    logo.TypeList.push_back(VehicleType("", "RX6430Y"));
    logo_list.push_back(logo);

    logo.name_CHS = "大通", logo.name_ENG = "MAXUS";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "G50"));
    logo.TypeList.push_back(VehicleType("", "D90"));
    logo.TypeList.push_back(VehicleType("", "G10"));
    logo.TypeList.push_back(VehicleType("", "V80"));
    logo.TypeList.push_back(VehicleType("", "T60"));
    logo.TypeList.push_back(VehicleType("", "EV30"));
    logo.TypeList.push_back(VehicleType("", "EG10"));
    logo_list.push_back(logo);

    logo.name_CHS = "大众", logo.name_ENG = "Volkswagens";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("朗逸", ""));
    logo.TypeList.push_back(VehicleType("帕萨特", ""));
    logo.TypeList.push_back(VehicleType("途岳", ""));
    logo.TypeList.push_back(VehicleType("途观L", ""));
    logo.TypeList.push_back(VehicleType("凌渡", ""));
    logo.TypeList.push_back(VehicleType("途昂", ""));
    logo.TypeList.push_back(VehicleType("桑塔纳", ""));
    logo.TypeList.push_back(VehicleType("途观", ""));
    logo.TypeList.push_back(VehicleType("波罗", "POLO"));
    logo.TypeList.push_back(VehicleType("辉昂", ""));
    logo.TypeList.push_back(VehicleType("途安L", ""));
    logo.TypeList.push_back(VehicleType("朗行", ""));
    logo.TypeList.push_back(VehicleType("朗境", ""));
    logo.TypeList.push_back(VehicleType("途安", ""));
    logo.TypeList.push_back(VehicleType("高尔", ""));
    logo.TypeList.push_back(VehicleType("", "T-Cross"));
    logo.TypeList.push_back(VehicleType("探岳", ""));
    logo.TypeList.push_back(VehicleType("捷达", ""));
    logo.TypeList.push_back(VehicleType("迈腾", ""));
    logo.TypeList.push_back(VehicleType("探歌", ""));
    logo.TypeList.push_back(VehicleType("速腾", ""));
    logo.TypeList.push_back(VehicleType("宝来", ""));
    logo.TypeList.push_back(VehicleType("", "CC"));
    logo.TypeList.push_back(VehicleType("高尔夫", ""));
    logo.TypeList.push_back(VehicleType("蔚领", ""));
    logo.TypeList.push_back(VehicleType("高尔夫·嘉旅", ""));
    logo.TypeList.push_back(VehicleType("开迪", ""));
    logo.TypeList.push_back(VehicleType("途锐", ""));
    logo.TypeList.push_back(VehicleType("甲壳虫", ""));
    logo.TypeList.push_back(VehicleType("夏朗", ""));
    logo.TypeList.push_back(VehicleType("", "Tiguan"));
    logo.TypeList.push_back(VehicleType("蔚揽", ""));
    logo.TypeList.push_back(VehicleType("迈特威", ""));
    logo.TypeList.push_back(VehicleType("凯路威", ""));
    logo.TypeList.push_back(VehicleType("辉腾", ""));
    logo.TypeList.push_back(VehicleType("尚酷", ""));
    logo.TypeList.push_back(VehicleType("", "Eos"));
    logo.TypeList.push_back(VehicleType("", "Amarok"));
    logo.TypeList.push_back(VehicleType("", "UP!"));
    logo.TypeList.push_back(VehicleType("途观L PHEV", ""));
    logo.TypeList.push_back(VehicleType("帕萨特 PHEV", ""));
    logo.TypeList.push_back(VehicleType("途威", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "道奇", logo.name_ENG = "Dodge";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("酷威", ""));
    logo.TypeList.push_back(VehicleType("", "RAM"));
    logo.TypeList.push_back(VehicleType("酷搏", ""));
    logo.TypeList.push_back(VehicleType("锋哲", ""));
    logo.TypeList.push_back(VehicleType("凯领", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "道奇2", logo.name_ENG = "Dodge";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("酷威", ""));
    logo.TypeList.push_back(VehicleType("", "RAM"));
    logo.TypeList.push_back(VehicleType("酷搏", ""));
    logo.TypeList.push_back(VehicleType("锋哲", ""));
    logo.TypeList.push_back(VehicleType("凯领", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "帝豪", logo.name_ENG = "EMGRAND";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("吉利", ""));
    logo.TypeList.push_back(VehicleType("美日", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "东风", logo.name_ENG = "Dongfeng";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("帅客", ""));
    logo.TypeList.push_back(VehicleType("帅客EV", ""));
    logo.TypeList.push_back(VehicleType("锐骐6", ""));
    logo.TypeList.push_back(VehicleType("锐骐皮卡", ""));
    logo.TypeList.push_back(VehicleType("锐骐厢式车", ""));
    logo.TypeList.push_back(VehicleType("俊风", ""));
    logo.TypeList.push_back(VehicleType("奥丁", ""));
    logo.TypeList.push_back(VehicleType("御轩", ""));
    logo.TypeList.push_back(VehicleType("俊风ER30", ""));
    logo.TypeList.push_back(VehicleType("俊风E11K", ""));
    logo.TypeList.push_back(VehicleType("俊风E17", ""));
    logo.TypeList.push_back(VehicleType("御风S16", ""));
    logo.TypeList.push_back(VehicleType("御风P16", ""));
    logo.TypeList.push_back(VehicleType("御风", ""));
    logo.TypeList.push_back(VehicleType("御风A100", ""));
    logo.TypeList.push_back(VehicleType("俊风EJ30", ""));
    logo.TypeList.push_back(VehicleType("猛士", ""));
    logo.TypeList.push_back(VehicleType("俊风CV03", ""));
    logo.TypeList.push_back(VehicleType("风神", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "东风日产", logo.name_ENG = "Dongfeng Nissan";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("日产", "nissan"));
    logo.TypeList.push_back(VehicleType("轩逸", ""));
    logo.TypeList.push_back(VehicleType("奇骏", ""));
    logo.TypeList.push_back(VehicleType("逍客", ""));
    logo.TypeList.push_back(VehicleType("天籁", ""));
    logo.TypeList.push_back(VehicleType("蓝鸟", ""));
    logo.TypeList.push_back(VehicleType("楼兰", ""));
    logo.TypeList.push_back(VehicleType("劲客", ""));
    logo.TypeList.push_back(VehicleType("骐达", ""));
    logo.TypeList.push_back(VehicleType("阳光", ""));
    logo.TypeList.push_back(VehicleType("骊威", ""));
    logo.TypeList.push_back(VehicleType("西玛", ""));
    logo.TypeList.push_back(VehicleType("颐达", ""));
    logo.TypeList.push_back(VehicleType("玛驰", ""));
    logo.TypeList.push_back(VehicleType("骏逸", ""));
    logo.TypeList.push_back(VehicleType("尼桑", ""));
    logo.TypeList.push_back(VehicleType("风神", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "东南", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("得利卡", ""));
    logo.TypeList.push_back(VehicleType("富利卡", ""));
    logo.TypeList.push_back(VehicleType("菱利", ""));
    logo.TypeList.push_back(VehicleType("V3菱悦", ""));
    logo.TypeList.push_back(VehicleType("君阁", ""));
    logo.TypeList.push_back(VehicleType("蓝瑟", "LANCER"));
    logo.TypeList.push_back(VehicleType("蓝瑟翼神", ""));
    logo.TypeList.push_back(VehicleType("戈蓝", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "法拉利", logo.name_ENG = "ferrari";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("488", ""));
    logo.TypeList.push_back(VehicleType("", "Portofino"));
    logo.TypeList.push_back(VehicleType("812Superfast", ""));
    logo.TypeList.push_back(VehicleType("", "GTC4Lusso"));
    logo.TypeList.push_back(VehicleType("458", ""));
    logo.TypeList.push_back(VehicleType("", "LaFerrari"));
    logo.TypeList.push_back(VehicleType("", "California T"));
    logo.TypeList.push_back(VehicleType("", "F430"));
    logo.TypeList.push_back(VehicleType("", "ENZO"));
    logo.TypeList.push_back(VehicleType("", "F12berlinetta"));
    logo.TypeList.push_back(VehicleType("", "FF"));
    logo.TypeList.push_back(VehicleType("456M", ""));
    logo.TypeList.push_back(VehicleType("599", ""));
    logo.TypeList.push_back(VehicleType("612 Scaglietti", ""));
    logo.TypeList.push_back(VehicleType("360 Modena", ""));
    logo.TypeList.push_back(VehicleType("575M Maranello", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "菲亚特", logo.name_ENG = "FIAT";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("致悦", ""));
    logo.TypeList.push_back(VehicleType("菲翔", ""));
    logo.TypeList.push_back(VehicleType("500", ""));
    logo.TypeList.push_back(VehicleType("菲跃", ""));
    logo.TypeList.push_back(VehicleType("博悦", ""));
    logo.TypeList.push_back(VehicleType("", "Doblo"));
    logo.TypeList.push_back(VehicleType("朋多", ""));
    logo.TypeList.push_back(VehicleType("领雅", ""));
    logo.TypeList.push_back(VehicleType("西耶那", ""));
    logo.TypeList.push_back(VehicleType("派力奥", ""));
    logo.TypeList.push_back(VehicleType("周末风", ""));
    logo.TypeList.push_back(VehicleType("派朗", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "丰田", logo.name_ENG = "Toyota";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("卡罗拉", ""));
    logo.TypeList.push_back(VehicleType("凯美瑞", ""));
    logo.TypeList.push_back(VehicleType("RAV4荣放", ""));
    logo.TypeList.push_back(VehicleType("汉兰达", ""));
    logo.TypeList.push_back(VehicleType("普拉多", "prado"));
    logo.TypeList.push_back(VehicleType("威驰", ""));
    logo.TypeList.push_back(VehicleType("皇冠", ""));
    logo.TypeList.push_back(VehicleType("雷凌", ""));
    logo.TypeList.push_back(VehicleType("YARiS L 致炫", ""));
    logo.TypeList.push_back(VehicleType("普拉多中东版", ""));
    logo.TypeList.push_back(VehicleType("兰德酷路泽", ""));
    logo.TypeList.push_back(VehicleType("奕泽", "IZOA"));
    logo.TypeList.push_back(VehicleType("兰德酷路泽中东版", ""));
    logo.TypeList.push_back(VehicleType("", "C-HR"));
    logo.TypeList.push_back(VehicleType("YARiS L 致享", ""));
    logo.TypeList.push_back(VehicleType("威驰FS", ""));
    logo.TypeList.push_back(VehicleType("逸致", ""));
    logo.TypeList.push_back(VehicleType("塞纳墨版", ""));
    logo.TypeList.push_back(VehicleType("埃尔法", ""));
    logo.TypeList.push_back(VehicleType("塞纳加规版", ""));
    logo.TypeList.push_back(VehicleType("亚洲龙", ""));
    logo.TypeList.push_back(VehicleType("穿越者中东版", ""));
    logo.TypeList.push_back(VehicleType("86", ""));
    logo.TypeList.push_back(VehicleType("普瑞维亚", ""));
    logo.TypeList.push_back(VehicleType("塞纳美规版", ""));
    logo.TypeList.push_back(VehicleType("LC76中东版", ""));
    logo.TypeList.push_back(VehicleType("", "Sienna"));
    logo.TypeList.push_back(VehicleType("普瑞维亚中东版", ""));
    logo.TypeList.push_back(VehicleType("坦途加规版", ""));
    logo.TypeList.push_back(VehicleType("坦途美规版", ""));
    logo.TypeList.push_back(VehicleType("埃尔法欧版", ""));
    logo.TypeList.push_back(VehicleType("红杉墨版", ""));
    logo.TypeList.push_back(VehicleType("柯斯达", ""));
    logo.TypeList.push_back(VehicleType("FJ酷路泽中东版", ""));
    logo.TypeList.push_back(VehicleType("超霸加规版", ""));
    logo.TypeList.push_back(VehicleType("超霸美规版", ""));
    logo.TypeList.push_back(VehicleType("红杉加版", ""));
    logo.TypeList.push_back(VehicleType("", "HIACE"));
    logo.TypeList.push_back(VehicleType("海拉克斯中东版", ""));
    logo.TypeList.push_back(VehicleType("塔库玛美规版", ""));
    logo.TypeList.push_back(VehicleType("考斯特中东版", ""));
    logo.TypeList.push_back(VehicleType("广汽ix4", ""));
    logo.TypeList.push_back(VehicleType("海狮中东版", ""));
    logo.TypeList.push_back(VehicleType("塔库玛加规版", ""));
    logo.TypeList.push_back(VehicleType("世纪", ""));
    logo.TypeList.push_back(VehicleType("霸道", ""));
    logo.TypeList.push_back(VehicleType("巡洋舰", ""));
    logo.TypeList.push_back(VehicleType("飞碟", ""));
    logo.TypeList.push_back(VehicleType("佳美", ""));
    logo.TypeList.push_back(VehicleType("超越", ""));
    logo.TypeList.push_back(VehicleType("爱尔凯普顿2694CC越野车", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "丰田toyot", logo.name_ENG = "Toyota";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("卡罗拉", ""));
    logo.TypeList.push_back(VehicleType("凯美瑞", ""));
    logo.TypeList.push_back(VehicleType("RAV4荣放", ""));
    logo.TypeList.push_back(VehicleType("汉兰达", ""));
    logo.TypeList.push_back(VehicleType("普拉多", "prado"));
    logo.TypeList.push_back(VehicleType("威驰", ""));
    logo.TypeList.push_back(VehicleType("皇冠", ""));
    logo.TypeList.push_back(VehicleType("雷凌", ""));
    logo.TypeList.push_back(VehicleType("YARiS L 致炫", ""));
    logo.TypeList.push_back(VehicleType("普拉多中东版", ""));
    logo.TypeList.push_back(VehicleType("兰德酷路泽", ""));
    logo.TypeList.push_back(VehicleType("奕泽", "IZOA"));
    logo.TypeList.push_back(VehicleType("兰德酷路泽中东版", ""));
    logo.TypeList.push_back(VehicleType("", "C-HR"));
    logo.TypeList.push_back(VehicleType("YARiS L 致享", ""));
    logo.TypeList.push_back(VehicleType("威驰FS", ""));
    logo.TypeList.push_back(VehicleType("逸致", ""));
    logo.TypeList.push_back(VehicleType("塞纳墨版", ""));
    logo.TypeList.push_back(VehicleType("埃尔法", ""));
    logo.TypeList.push_back(VehicleType("塞纳加规版", ""));
    logo.TypeList.push_back(VehicleType("亚洲龙", ""));
    logo.TypeList.push_back(VehicleType("穿越者中东版", ""));
    logo.TypeList.push_back(VehicleType("86", ""));
    logo.TypeList.push_back(VehicleType("普瑞维亚", ""));
    logo.TypeList.push_back(VehicleType("塞纳美规版", ""));
    logo.TypeList.push_back(VehicleType("LC76中东版", ""));
    logo.TypeList.push_back(VehicleType("", "Sienna"));
    logo.TypeList.push_back(VehicleType("普瑞维亚中东版", ""));
    logo.TypeList.push_back(VehicleType("坦途加规版", ""));
    logo.TypeList.push_back(VehicleType("坦途美规版", ""));
    logo.TypeList.push_back(VehicleType("埃尔法欧版", ""));
    logo.TypeList.push_back(VehicleType("红杉墨版", ""));
    logo.TypeList.push_back(VehicleType("柯斯达", ""));
    logo.TypeList.push_back(VehicleType("FJ酷路泽中东版", ""));
    logo.TypeList.push_back(VehicleType("超霸加规版", ""));
    logo.TypeList.push_back(VehicleType("超霸美规版", ""));
    logo.TypeList.push_back(VehicleType("红杉加版", ""));
    logo.TypeList.push_back(VehicleType("", "HIACE"));
    logo.TypeList.push_back(VehicleType("海拉克斯中东版", ""));
    logo.TypeList.push_back(VehicleType("塔库玛美规版", ""));
    logo.TypeList.push_back(VehicleType("考斯特中东版", ""));
    logo.TypeList.push_back(VehicleType("广汽ix4", ""));
    logo.TypeList.push_back(VehicleType("海狮中东版", ""));
    logo.TypeList.push_back(VehicleType("塔库玛加规版", ""));
    logo.TypeList.push_back(VehicleType("世纪", ""));
    logo.TypeList.push_back(VehicleType("霸道", ""));
    logo.TypeList.push_back(VehicleType("陆地巡洋舰", ""));
    logo.TypeList.push_back(VehicleType("飞碟", ""));
    logo.TypeList.push_back(VehicleType("佳美", ""));
    logo.TypeList.push_back(VehicleType("超越", ""));
    logo.TypeList.push_back(VehicleType("爱尔凯普顿2694CC越野车", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "丰田皇冠", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("卡罗拉", ""));
    logo.TypeList.push_back(VehicleType("凯美瑞", ""));
    logo.TypeList.push_back(VehicleType("RAV4荣放", ""));
    logo.TypeList.push_back(VehicleType("汉兰达", ""));
    logo.TypeList.push_back(VehicleType("普拉多", "prado"));
    logo.TypeList.push_back(VehicleType("威驰", ""));
    logo.TypeList.push_back(VehicleType("皇冠", ""));
    logo.TypeList.push_back(VehicleType("雷凌", ""));
    logo.TypeList.push_back(VehicleType("YARiS L 致炫", ""));
    logo.TypeList.push_back(VehicleType("普拉多中东版", ""));
    logo.TypeList.push_back(VehicleType("兰德酷路泽", ""));
    logo.TypeList.push_back(VehicleType("奕泽", "IZOA"));
    logo.TypeList.push_back(VehicleType("兰德酷路泽中东版", ""));
    logo.TypeList.push_back(VehicleType("", "C-HR"));
    logo.TypeList.push_back(VehicleType("YARiS L 致享", ""));
    logo.TypeList.push_back(VehicleType("威驰FS", ""));
    logo.TypeList.push_back(VehicleType("逸致", ""));
    logo.TypeList.push_back(VehicleType("塞纳墨版", ""));
    logo.TypeList.push_back(VehicleType("埃尔法", ""));
    logo.TypeList.push_back(VehicleType("塞纳加规版", ""));
    logo.TypeList.push_back(VehicleType("亚洲龙", ""));
    logo.TypeList.push_back(VehicleType("穿越者中东版", ""));
    logo.TypeList.push_back(VehicleType("86", ""));
    logo.TypeList.push_back(VehicleType("普瑞维亚", ""));
    logo.TypeList.push_back(VehicleType("塞纳美规版", ""));
    logo.TypeList.push_back(VehicleType("LC76中东版", ""));
    logo.TypeList.push_back(VehicleType("", "Sienna"));
    logo.TypeList.push_back(VehicleType("普瑞维亚中东版", ""));
    logo.TypeList.push_back(VehicleType("坦途加规版", ""));
    logo.TypeList.push_back(VehicleType("坦途美规版", ""));
    logo.TypeList.push_back(VehicleType("埃尔法欧版", ""));
    logo.TypeList.push_back(VehicleType("红杉墨版", ""));
    logo.TypeList.push_back(VehicleType("柯斯达", ""));
    logo.TypeList.push_back(VehicleType("FJ酷路泽中东版", ""));
    logo.TypeList.push_back(VehicleType("超霸加规版", ""));
    logo.TypeList.push_back(VehicleType("超霸美规版", ""));
    logo.TypeList.push_back(VehicleType("红杉加版", ""));
    logo.TypeList.push_back(VehicleType("", "HIACE"));
    logo.TypeList.push_back(VehicleType("海拉克斯中东版", ""));
    logo.TypeList.push_back(VehicleType("塔库玛美规版", ""));
    logo.TypeList.push_back(VehicleType("考斯特中东版", ""));
    logo.TypeList.push_back(VehicleType("广汽ix4", ""));
    logo.TypeList.push_back(VehicleType("海狮中东版", ""));
    logo.TypeList.push_back(VehicleType("塔库玛加规版", ""));
    logo.TypeList.push_back(VehicleType("世纪", ""));
    logo.TypeList.push_back(VehicleType("霸道", ""));
    logo.TypeList.push_back(VehicleType("陆地巡洋舰", ""));
    logo.TypeList.push_back(VehicleType("飞碟", ""));
    logo.TypeList.push_back(VehicleType("佳美", ""));
    logo.TypeList.push_back(VehicleType("超越", ""));
    logo.TypeList.push_back(VehicleType("爱尔凯普顿2694CC越野车", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "丰田埃尔法", logo.name_ENG = "Elgrand";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("卡罗拉", ""));
    logo.TypeList.push_back(VehicleType("凯美瑞", ""));
    logo.TypeList.push_back(VehicleType("RAV4荣放", ""));
    logo.TypeList.push_back(VehicleType("汉兰达", ""));
    logo.TypeList.push_back(VehicleType("普拉多", "prado"));
    logo.TypeList.push_back(VehicleType("威驰", ""));
    logo.TypeList.push_back(VehicleType("皇冠", ""));
    logo.TypeList.push_back(VehicleType("雷凌", ""));
    logo.TypeList.push_back(VehicleType("YARiS L 致炫", ""));
    logo.TypeList.push_back(VehicleType("普拉多中东版", ""));
    logo.TypeList.push_back(VehicleType("兰德酷路泽", ""));
    logo.TypeList.push_back(VehicleType("奕泽", "IZOA"));
    logo.TypeList.push_back(VehicleType("兰德酷路泽中东版", ""));
    logo.TypeList.push_back(VehicleType("", "C-HR"));
    logo.TypeList.push_back(VehicleType("YARiS L 致享", ""));
    logo.TypeList.push_back(VehicleType("威驰FS", ""));
    logo.TypeList.push_back(VehicleType("逸致", ""));
    logo.TypeList.push_back(VehicleType("塞纳墨版", ""));
    logo.TypeList.push_back(VehicleType("埃尔法", ""));
    logo.TypeList.push_back(VehicleType("塞纳加规版", ""));
    logo.TypeList.push_back(VehicleType("亚洲龙", ""));
    logo.TypeList.push_back(VehicleType("穿越者中东版", ""));
    logo.TypeList.push_back(VehicleType("86", ""));
    logo.TypeList.push_back(VehicleType("普瑞维亚", ""));
    logo.TypeList.push_back(VehicleType("塞纳美规版", ""));
    logo.TypeList.push_back(VehicleType("LC76中东版", ""));
    logo.TypeList.push_back(VehicleType("", "Sienna"));
    logo.TypeList.push_back(VehicleType("普瑞维亚中东版", ""));
    logo.TypeList.push_back(VehicleType("坦途加规版", ""));
    logo.TypeList.push_back(VehicleType("坦途美规版", ""));
    logo.TypeList.push_back(VehicleType("埃尔法欧版", ""));
    logo.TypeList.push_back(VehicleType("红杉墨版", ""));
    logo.TypeList.push_back(VehicleType("柯斯达", ""));
    logo.TypeList.push_back(VehicleType("FJ酷路泽中东版", ""));
    logo.TypeList.push_back(VehicleType("超霸加规版", ""));
    logo.TypeList.push_back(VehicleType("超霸美规版", ""));
    logo.TypeList.push_back(VehicleType("红杉加版", ""));
    logo.TypeList.push_back(VehicleType("", "HIACE"));
    logo.TypeList.push_back(VehicleType("海拉克斯中东版", ""));
    logo.TypeList.push_back(VehicleType("塔库玛美规版", ""));
    logo.TypeList.push_back(VehicleType("考斯特中东版", ""));
    logo.TypeList.push_back(VehicleType("广汽ix4", ""));
    logo.TypeList.push_back(VehicleType("海狮中东版", ""));
    logo.TypeList.push_back(VehicleType("塔库玛加规版", ""));
    logo.TypeList.push_back(VehicleType("世纪", ""));
    logo.TypeList.push_back(VehicleType("霸道", ""));
    logo.TypeList.push_back(VehicleType("陆地巡洋舰", ""));
    logo.TypeList.push_back(VehicleType("飞碟", ""));
    logo.TypeList.push_back(VehicleType("佳美", ""));
    logo.TypeList.push_back(VehicleType("超越", ""));
    logo.TypeList.push_back(VehicleType("爱尔凯普顿2694CC越野车", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "福汽启腾", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "EX80"));
    logo.TypeList.push_back(VehicleType("", "M70"));
    logo.TypeList.push_back(VehicleType("", "V60"));
    logo.TypeList.push_back(VehicleType("", "M70 EV"));
    logo_list.push_back(logo);

    logo.name_CHS = "福特", logo.name_ENG = "Ford";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("翼搏", ""));
    logo.TypeList.push_back(VehicleType("翼虎", ""));
    logo.TypeList.push_back(VehicleType("锐界", ""));
    logo.TypeList.push_back(VehicleType("福睿斯", ""));
    logo.TypeList.push_back(VehicleType("福克斯", ""));
    logo.TypeList.push_back(VehicleType("蒙迪欧", ""));
    logo.TypeList.push_back(VehicleType("金牛座", ""));
    logo.TypeList.push_back(VehicleType("蒙迪欧", ""));
    logo.TypeList.push_back(VehicleType("撼路者", ""));
    logo.TypeList.push_back(VehicleType("途睿欧", ""));
    logo.TypeList.push_back(VehicleType("全顺", ""));
    logo.TypeList.push_back(VehicleType("新世代全顺", ""));
    logo.TypeList.push_back(VehicleType("探险者", ""));
    logo.TypeList.push_back(VehicleType("福克斯", ""));
    logo.TypeList.push_back(VehicleType("", "MUSTANG"));
    logo.TypeList.push_back(VehicleType("", "F-150"));
    logo.TypeList.push_back(VehicleType("", "Ranger"));
    logo.TypeList.push_back(VehicleType("", "C-MAX"));
    logo.TypeList.push_back(VehicleType("领界", ""));
    logo.TypeList.push_back(VehicleType("嘉年华", ""));
    logo.TypeList.push_back(VehicleType("麦柯斯", ""));
    logo.TypeList.push_back(VehicleType("经典全顺", ""));
    logo.TypeList.push_back(VehicleType("锐界", ""));
    logo.TypeList.push_back(VehicleType("翼虎", ""));
    logo.TypeList.push_back(VehicleType("", "Flex"));
    logo.TypeList.push_back(VehicleType("外交官", ""));
    logo.TypeList.push_back(VehicleType("征服者", ""));
    logo.TypeList.push_back(VehicleType("嘉年华ST", ""));
    logo.TypeList.push_back(VehicleType("E系列", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "福田", logo.name_ENG = "FOTON";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("图雅诺", ""));
    logo.TypeList.push_back(VehicleType("时代驭菱", ""));
    logo.TypeList.push_back(VehicleType("风景G7", ""));
    logo.TypeList.push_back(VehicleType("奥铃捷运", ""));
    logo.TypeList.push_back(VehicleType("蒙派克E", ""));
    logo.TypeList.push_back(VehicleType("风景G9", ""));
    logo.TypeList.push_back(VehicleType("风景", ""));
    logo.TypeList.push_back(VehicleType("时代微卡", ""));
    logo.TypeList.push_back(VehicleType("奥铃CTX", ""));
    logo.TypeList.push_back(VehicleType("祥菱V", ""));
    logo.TypeList.push_back(VehicleType("奥铃TX", ""));
    logo.TypeList.push_back(VehicleType("欧马可", ""));
    logo.TypeList.push_back(VehicleType("时代领航", ""));
    logo.TypeList.push_back(VehicleType("瑞沃工程用车", ""));
    logo.TypeList.push_back(VehicleType("时代康瑞", ""));
    logo.TypeList.push_back(VehicleType("风景V5", ""));
    logo.TypeList.push_back(VehicleType("风景V3", ""));
    logo.TypeList.push_back(VehicleType("祥菱M", ""));
    logo.TypeList.push_back(VehicleType("时代骁运", ""));
    logo.TypeList.push_back(VehicleType("风景快客", ""));
    logo.TypeList.push_back(VehicleType("迷迪", ""));
    logo.TypeList.push_back(VehicleType("传奇X", ""));
    logo.TypeList.push_back(VehicleType("伽途V3", ""));
    logo.TypeList.push_back(VehicleType("海狮", ""));
    logo.TypeList.push_back(VehicleType("风景快捷", ""));
    logo.TypeList.push_back(VehicleType("伽途V5", ""));
    logo.TypeList.push_back(VehicleType("风景冲浪", ""));
    logo.TypeList.push_back(VehicleType("祥菱S", ""));
    logo.TypeList.push_back(VehicleType("拓陆者", ""));
    logo.TypeList.push_back(VehicleType("萨瓦纳", ""));
    logo.TypeList.push_back(VehicleType("伽途ix", ""));
    logo.TypeList.push_back(VehicleType("伽途GT", ""));
    logo.TypeList.push_back(VehicleType("萨普", ""));
    logo.TypeList.push_back(VehicleType("伽途im", ""));
    logo.TypeList.push_back(VehicleType("风景V5EV", ""));
    logo.TypeList.push_back(VehicleType("奥铃EV", ""));
    logo.TypeList.push_back(VehicleType("图雅诺EV", ""));
    logo.TypeList.push_back(VehicleType("风景V3EV", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "观致", logo.name_ENG = "Qoros";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("5", ""));
    logo.TypeList.push_back(VehicleType("3", ""));
    logo.TypeList.push_back(VehicleType("", "Model Young"));
    logo.TypeList.push_back(VehicleType("3 EV", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "传祺", logo.name_ENG = "Trumpchi";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "GM6"));
    logo.TypeList.push_back(VehicleType("", "GS5"));
    logo.TypeList.push_back(VehicleType("", "GA4"));
    logo.TypeList.push_back(VehicleType("", "GM8"));
    logo.TypeList.push_back(VehicleType("", "GS7"));
    logo.TypeList.push_back(VehicleType("", "GS3"));
    logo.TypeList.push_back(VehicleType("", "GS4"));
    logo.TypeList.push_back(VehicleType("", "GS8"));
    logo.TypeList.push_back(VehicleType("", "GA6"));
    logo.TypeList.push_back(VehicleType("", "GA8"));
    logo.TypeList.push_back(VehicleType("", "GA3S"));
    logo.TypeList.push_back(VehicleType("", "GS5 Super"));
    logo.TypeList.push_back(VehicleType("", "GS5"));
    logo.TypeList.push_back(VehicleType("", "GA5"));
    logo_list.push_back(logo);

    logo.name_CHS = "吉奥", logo.name_ENG = "GONOW";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("帅舰", ""));
    logo.TypeList.push_back(VehicleType("", "GS50"));
    logo.TypeList.push_back(VehicleType("", "G5"));
    logo.TypeList.push_back(VehicleType("帅豹", ""));
    logo.TypeList.push_back(VehicleType("", "GX6"));
    logo.TypeList.push_back(VehicleType("", "GX5"));
    logo.TypeList.push_back(VehicleType("星朗", ""));
    logo.TypeList.push_back(VehicleType("财运100", ""));
    logo.TypeList.push_back(VehicleType("吉奥E美", ""));
    logo.TypeList.push_back(VehicleType("财运300", ""));
    logo.TypeList.push_back(VehicleType("财运500", ""));
    logo.TypeList.push_back(VehicleType("吉奥GP150", ""));
    logo.TypeList.push_back(VehicleType("星旺L", ""));
    logo.TypeList.push_back(VehicleType("柴神", ""));
    logo.TypeList.push_back(VehicleType("星旺", ""));
    logo.TypeList.push_back(VehicleType("凯睿", ""));
    logo.TypeList.push_back(VehicleType("奥轩G3", ""));
    logo.TypeList.push_back(VehicleType("星旺CL", ""));
    logo.TypeList.push_back(VehicleType("星旺M1", ""));
    logo.TypeList.push_back(VehicleType("星旺M2", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "哈飞", logo.name_ENG = "HAFEI";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("锐意", ""));
    logo.TypeList.push_back(VehicleType("民意", ""));
    logo.TypeList.push_back(VehicleType("赛豹Ⅲ", ""));
    logo.TypeList.push_back(VehicleType("路宝", ""));
    logo.TypeList.push_back(VehicleType("赛马", ""));
    logo.TypeList.push_back(VehicleType("中意", ""));
    logo.TypeList.push_back(VehicleType("路尊大霸王", ""));
    logo.TypeList.push_back(VehicleType("松花江", ""));
    logo.TypeList.push_back(VehicleType("路尊小霸王", ""));
    logo.TypeList.push_back(VehicleType("赛豹V系", ""));
    logo.TypeList.push_back(VehicleType("骏意", ""));
    logo.TypeList.push_back(VehicleType("单双排", ""));
    logo.TypeList.push_back(VehicleType("普面", ""));
    logo.TypeList.push_back(VehicleType("百利", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "哈弗", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("长城", ""));
    logo.TypeList.push_back(VehicleType("", "H6"));
    logo.TypeList.push_back(VehicleType("", "F5"));
    logo.TypeList.push_back(VehicleType("", "M6"));
    logo.TypeList.push_back(VehicleType("", "H2"));
    logo.TypeList.push_back(VehicleType("", "H2s"));
    logo.TypeList.push_back(VehicleType("", "H9"));
    logo.TypeList.push_back(VehicleType("", "F7"));
    logo.TypeList.push_back(VehicleType("", "H6 Coupe"));
    logo.TypeList.push_back(VehicleType("", "H4"));
    logo.TypeList.push_back(VehicleType("", "H7"));
    logo.TypeList.push_back(VehicleType("", "H5"));
    logo.TypeList.push_back(VehicleType("", "H8"));
    logo.TypeList.push_back(VehicleType("", "H1"));
    logo.TypeList.push_back(VehicleType("", "H3"));
    logo_list.push_back(logo);


    logo.name_CHS = "海格", logo.name_ENG = "HIGER";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "H5C"));
    logo.TypeList.push_back(VehicleType("", "H5V"));
    logo_list.push_back(logo);

    logo.name_CHS = "海格2", logo.name_ENG = "HIGER";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "H5C"));
    logo.TypeList.push_back(VehicleType("", "H5V"));
    logo_list.push_back(logo);

    logo.name_CHS = "海马", logo.name_ENG = "Haima";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "S5"));
    logo.TypeList.push_back(VehicleType("", "M3"));
    logo.TypeList.push_back(VehicleType("S5青春版", ""));
    logo.TypeList.push_back(VehicleType("", "M6"));
    logo.TypeList.push_back(VehicleType("王子", ""));
    logo.TypeList.push_back(VehicleType("福仕达鸿达", ""));
    logo.TypeList.push_back(VehicleType("爱尚", ""));
    logo.TypeList.push_back(VehicleType("福仕达新鸿达", ""));
    logo.TypeList.push_back(VehicleType("福仕达荣达", ""));
    logo.TypeList.push_back(VehicleType("福仕达福卡", ""));
    logo.TypeList.push_back(VehicleType("腾达", ""));
    logo.TypeList.push_back(VehicleType("福仕达腾达", ""));
    logo.TypeList.push_back(VehicleType("福美来F5", ""));
    logo.TypeList.push_back(VehicleType("福美来F7", ""));
    logo.TypeList.push_back(VehicleType("", "S7"));
    logo.TypeList.push_back(VehicleType("马自达323", ""));
    logo.TypeList.push_back(VehicleType("普力马", ""));
    logo.TypeList.push_back(VehicleType("", "M8"));
    logo.TypeList.push_back(VehicleType("丘比特", ""));
    logo.TypeList.push_back(VehicleType("海福星", ""));
    logo.TypeList.push_back(VehicleType("骑士", ""));
    logo.TypeList.push_back(VehicleType("3", ""));
    logo.TypeList.push_back(VehicleType("欢动", ""));
    logo.TypeList.push_back(VehicleType("", "E3"));
    logo.TypeList.push_back(VehicleType("爱尚EV", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "一汽红旗", logo.name_ENG = "Red Flag";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "H5"));
    logo.TypeList.push_back(VehicleType("", "H7"));
    logo.TypeList.push_back(VehicleType("盛世", ""));
    logo.TypeList.push_back(VehicleType("明仕", ""));
    logo.TypeList.push_back(VehicleType("世纪星", ""));
    logo.TypeList.push_back(VehicleType("", "L5"));
    logo.TypeList.push_back(VehicleType("", "HS7"));
    logo_list.push_back(logo);

    logo.name_CHS = "红星", logo.name_ENG = "Red Flag";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("闪闪X2", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "华普", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("海景", ""));
    logo.TypeList.push_back(VehicleType("飚风", ""));
    logo.TypeList.push_back(VehicleType("海锋", ""));
    logo.TypeList.push_back(VehicleType("海尚", ""));
    logo.TypeList.push_back(VehicleType("海迅", ""));
    logo.TypeList.push_back(VehicleType("海炫", ""));
    logo.TypeList.push_back(VehicleType("海域", ""));
    logo.TypeList.push_back(VehicleType("海悦", ""));
    logo.TypeList.push_back(VehicleType("杰士达美鹿", ""));
    logo.TypeList.push_back(VehicleType("朗风", ""));
    logo.TypeList.push_back(VehicleType("M203", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "华颂", logo.name_ENG = "HUASONG";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("7", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "黄海", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "N3"));
    logo.TypeList.push_back(VehicleType("", "N2"));
    logo.TypeList.push_back(VehicleType("", "N1S"));
    logo.TypeList.push_back(VehicleType("", "N1"));
    logo.TypeList.push_back(VehicleType("傲骏", ""));
    logo.TypeList.push_back(VehicleType("旗胜F1", ""));
    logo.TypeList.push_back(VehicleType("挑战者", ""));
    logo.TypeList.push_back(VehicleType("大柴神", ""));
    logo.TypeList.push_back(VehicleType("旗胜V3", ""));
    logo.TypeList.push_back(VehicleType("傲龙CUV", ""));
    logo.TypeList.push_back(VehicleType("翱龙CUV", ""));
    logo.TypeList.push_back(VehicleType("领航者", ""));
    logo.TypeList.push_back(VehicleType("瑞途", ""));
    logo.TypeList.push_back(VehicleType("旗胜CUV", ""));
    logo.TypeList.push_back(VehicleType("曙光骄子", ""));
    logo.TypeList.push_back(VehicleType("征服者", ""));
    logo.TypeList.push_back(VehicleType("翱龙SUV", ""));
    logo.TypeList.push_back(VehicleType("傲羚", ""));
    logo.TypeList.push_back(VehicleType("小柴神", ""));
    logo.TypeList.push_back(VehicleType("翱龙", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "吉利", logo.name_ENG = "Geely Auto";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("缤越", ""));
    logo.TypeList.push_back(VehicleType("缤瑞", ""));
    logo.TypeList.push_back(VehicleType("博越", ""));
    logo.TypeList.push_back(VehicleType("帝豪GS", ""));
    logo.TypeList.push_back(VehicleType("远景X3", ""));
    logo.TypeList.push_back(VehicleType("帝豪GL", ""));
    logo.TypeList.push_back(VehicleType("帝豪", ""));
    logo.TypeList.push_back(VehicleType("博瑞GE", ""));
    logo.TypeList.push_back(VehicleType("远景", ""));
    logo.TypeList.push_back(VehicleType("远景SUV", ""));
    logo.TypeList.push_back(VehicleType("远景S1", ""));
    logo.TypeList.push_back(VehicleType("博瑞", ""));
    logo.TypeList.push_back(VehicleType("远景X1", ""));
    logo.TypeList.push_back(VehicleType("金刚", ""));
    logo.TypeList.push_back(VehicleType("熊猫", ""));
    logo.TypeList.push_back(VehicleType("", "GX7"));
    logo.TypeList.push_back(VehicleType("自由舰", ""));
    logo.TypeList.push_back(VehicleType("", "EC8"));
    logo.TypeList.push_back(VehicleType("", "TX4"));
    logo.TypeList.push_back(VehicleType("中国龙", ""));
    logo.TypeList.push_back(VehicleType("美人豹", ""));
    logo.TypeList.push_back(VehicleType("", "GC7"));
    logo.TypeList.push_back(VehicleType("海景", ""));
    logo.TypeList.push_back(VehicleType("美日", ""));
    logo.TypeList.push_back(VehicleType("豪情SUV", ""));
    logo.TypeList.push_back(VehicleType("", "GX2"));
    logo.TypeList.push_back(VehicleType("", "SX7"));
    logo.TypeList.push_back(VehicleType("英伦C5", ""));
    logo.TypeList.push_back(VehicleType("", "SC3"));
    logo.TypeList.push_back(VehicleType("美日之星", ""));
    logo.TypeList.push_back(VehicleType("豪情", ""));
    logo.TypeList.push_back(VehicleType("优利欧", ""));
    logo.TypeList.push_back(VehicleType("嘉际", ""));
    logo.TypeList.push_back(VehicleType("博瑞GE PHEV", ""));
    logo.TypeList.push_back(VehicleType("帝豪GSe", ""));
    logo.TypeList.push_back(VehicleType("帝豪EV", ""));
    logo.TypeList.push_back(VehicleType("帝豪PHEV", ""));
    logo.TypeList.push_back(VehicleType("嘉际PHEV", ""));
    logo.TypeList.push_back(VehicleType("吉利GE11", ""));
    logo.TypeList.push_back(VehicleType("吉利全球鹰", "GLEAGLE"));
    logo.TypeList.push_back(VehicleType("吉利英伦", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "吉普", logo.name_ENG = "Jeep";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("自由光", ""));
    logo.TypeList.push_back(VehicleType("牧马人", ""));
    logo.TypeList.push_back(VehicleType("指南者", ""));
    logo.TypeList.push_back(VehicleType("自由侠", ""));
    logo.TypeList.push_back(VehicleType("大切诺基", ""));
    logo.TypeList.push_back(VehicleType("大切诺基 SRT", ""));
    logo.TypeList.push_back(VehicleType("大指挥官", ""));
    logo.TypeList.push_back(VehicleType("指挥官", ""));
    logo.TypeList.push_back(VehicleType("大指挥官混动", ""));
    logo.TypeList.push_back(VehicleType("自由光混动", ""));
    logo.TypeList.push_back(VehicleType("悦界PHEV", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "江淮", logo.name_ENG = "Jianghuai";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("瑞风S3", ""));
    logo.TypeList.push_back(VehicleType("瑞风M4", ""));
    logo.TypeList.push_back(VehicleType("瑞风M3", ""));
    logo.TypeList.push_back(VehicleType("瑞风S7", ""));
    logo.TypeList.push_back(VehicleType("瑞风R3", ""));
    logo.TypeList.push_back(VehicleType("帅铃T8", ""));
    logo.TypeList.push_back(VehicleType("瑞风M5", ""));
    logo.TypeList.push_back(VehicleType("瑞风S2", ""));
    logo.TypeList.push_back(VehicleType("瑞风S2mini", ""));
    logo.TypeList.push_back(VehicleType("瑞风S4", ""));
    logo.TypeList.push_back(VehicleType("瑞风S5", ""));
    logo.TypeList.push_back(VehicleType("帅铃T6", ""));
    logo.TypeList.push_back(VehicleType("瑞风M6", ""));
    logo.TypeList.push_back(VehicleType("星锐", ""));
    logo.TypeList.push_back(VehicleType("和悦", ""));
    logo.TypeList.push_back(VehicleType("瑞风A60", ""));
    logo.TypeList.push_back(VehicleType("江淮V7", ""));
    logo.TypeList.push_back(VehicleType("帅铃V6", ""));
    logo.TypeList.push_back(VehicleType("瑞风", ""));
    logo.TypeList.push_back(VehicleType("瑞鹰", ""));
    logo.TypeList.push_back(VehicleType("瑞风M2", ""));
    logo.TypeList.push_back(VehicleType("宾悦", ""));
    logo.TypeList.push_back(VehicleType("和悦A30", ""));
    logo.TypeList.push_back(VehicleType("悦悦", ""));
    logo.TypeList.push_back(VehicleType("和悦A13", ""));
    logo.TypeList.push_back(VehicleType("瑞铃", ""));
    logo.TypeList.push_back(VehicleType("", "iEV6E"));
    logo.TypeList.push_back(VehicleType("", "iEV7S"));
    logo.TypeList.push_back(VehicleType("", "iEVA50"));
    logo.TypeList.push_back(VehicleType("", "iEV4"));
    logo.TypeList.push_back(VehicleType("", "iEV6S"));
    logo.TypeList.push_back(VehicleType("", "iEV7"));
    logo.TypeList.push_back(VehicleType("", "iEVA60"));
    logo.TypeList.push_back(VehicleType("", "iEVS4"));
    logo_list.push_back(logo);

    logo.name_CHS = "江淮-新", logo.name_ENG = "Jianghuai";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("瑞风S3", ""));
    logo.TypeList.push_back(VehicleType("瑞风M4", ""));
    logo.TypeList.push_back(VehicleType("瑞风M3", ""));
    logo.TypeList.push_back(VehicleType("瑞风S7", ""));
    logo.TypeList.push_back(VehicleType("瑞风R3", ""));
    logo.TypeList.push_back(VehicleType("帅铃T8", ""));
    logo.TypeList.push_back(VehicleType("瑞风M5", ""));
    logo.TypeList.push_back(VehicleType("瑞风S2", ""));
    logo.TypeList.push_back(VehicleType("瑞风S2mini", ""));
    logo.TypeList.push_back(VehicleType("瑞风S4", ""));
    logo.TypeList.push_back(VehicleType("瑞风S5", ""));
    logo.TypeList.push_back(VehicleType("帅铃T6", ""));
    logo.TypeList.push_back(VehicleType("瑞风M6", ""));
    logo.TypeList.push_back(VehicleType("星锐", ""));
    logo.TypeList.push_back(VehicleType("和悦", ""));
    logo.TypeList.push_back(VehicleType("瑞风A60", ""));
    logo.TypeList.push_back(VehicleType("江淮V7", ""));
    logo.TypeList.push_back(VehicleType("帅铃V6", ""));
    logo.TypeList.push_back(VehicleType("瑞风", ""));
    logo.TypeList.push_back(VehicleType("瑞鹰", ""));
    logo.TypeList.push_back(VehicleType("瑞风M2", ""));
    logo.TypeList.push_back(VehicleType("宾悦", ""));
    logo.TypeList.push_back(VehicleType("和悦A30", ""));
    logo.TypeList.push_back(VehicleType("悦悦", ""));
    logo.TypeList.push_back(VehicleType("和悦A13", ""));
    logo.TypeList.push_back(VehicleType("瑞铃", ""));
    logo.TypeList.push_back(VehicleType("", "iEV6E"));
    logo.TypeList.push_back(VehicleType("", "iEV7S"));
    logo.TypeList.push_back(VehicleType("", "iEVA50"));
    logo.TypeList.push_back(VehicleType("", "iEV4"));
    logo.TypeList.push_back(VehicleType("", "iEV6S"));
    logo.TypeList.push_back(VehicleType("", "iEV7"));
    logo.TypeList.push_back(VehicleType("", "iEVA60"));
    logo.TypeList.push_back(VehicleType("", "iEVS4"));
    logo_list.push_back(logo);

    logo.name_CHS = "江铃", logo.name_ENG = "Jiangling";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("域虎7", ""));
    logo.TypeList.push_back(VehicleType("特顺", ""));
    logo.TypeList.push_back(VehicleType("域虎3", ""));
    logo.TypeList.push_back(VehicleType("宝典", ""));
    logo.TypeList.push_back(VehicleType("域虎5", ""));
    logo.TypeList.push_back(VehicleType("凯运升级版", ""));
    logo.TypeList.push_back(VehicleType("顺达窄体", ""));
    logo.TypeList.push_back(VehicleType("顺达宽体", ""));
    logo.TypeList.push_back(VehicleType("凯锐800", ""));
    logo.TypeList.push_back(VehicleType("凯锐", ""));
    logo.TypeList.push_back(VehicleType("宝威", ""));
    logo.TypeList.push_back(VehicleType("凯威", ""));
    logo.TypeList.push_back(VehicleType("", "E400"));
    logo.TypeList.push_back(VehicleType("", "E200L"));
    logo.TypeList.push_back(VehicleType("", "E200N"));
    logo.TypeList.push_back(VehicleType("", "E100B"));
    logo.TypeList.push_back(VehicleType("", "E160"));
    logo.TypeList.push_back(VehicleType("易至EV3", ""));
    logo.TypeList.push_back(VehicleType("", "骐铃T7"));
    logo.TypeList.push_back(VehicleType("", "骐铃T100"));
    logo.TypeList.push_back(VehicleType("", "骐铃T5"));
    logo.TypeList.push_back(VehicleType("", "骐铃T3"));
    logo_list.push_back(logo);

    logo.name_CHS = "金杯", logo.name_ENG = "JINBEI";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("海狮", ""));
    logo.TypeList.push_back(VehicleType("阁瑞斯", ""));
    logo.TypeList.push_back(VehicleType("", "F50"));
    logo.TypeList.push_back(VehicleType("大海狮", ""));
    logo.TypeList.push_back(VehicleType("霸道SUV", ""));
    logo.TypeList.push_back(VehicleType("海星", ""));
    logo.TypeList.push_back(VehicleType("华晨金杯S50", ""));
    logo.TypeList.push_back(VehicleType("海狮X30L", ""));
    logo.TypeList.push_back(VehicleType("小海狮X30", ""));
    logo.TypeList.push_back(VehicleType("750", ""));
    logo.TypeList.push_back(VehicleType("新海狮S", ""));
    logo.TypeList.push_back(VehicleType("", "T32"));
    logo.TypeList.push_back(VehicleType("", "T52"));
    logo.TypeList.push_back(VehicleType("", "T30"));
    logo.TypeList.push_back(VehicleType("", "A7"));
    logo.TypeList.push_back(VehicleType("", "T50"));
    logo.TypeList.push_back(VehicleType("", "T20"));
    logo.TypeList.push_back(VehicleType("", "A9"));
    logo.TypeList.push_back(VehicleType("", "T22"));
    logo.TypeList.push_back(VehicleType("", "S70"));
    logo.TypeList.push_back(VehicleType("智尚S35", ""));
    logo.TypeList.push_back(VehicleType("金典", ""));
    logo.TypeList.push_back(VehicleType("大力神K5", ""));
    logo.TypeList.push_back(VehicleType("西部牛仔", ""));
    logo.TypeList.push_back(VehicleType("雷龙", ""));
    logo.TypeList.push_back(VehicleType("小金牛", ""));
    logo.TypeList.push_back(VehicleType("海狮X30L EV", ""));
    logo.TypeList.push_back(VehicleType("观境", ""));
    logo.TypeList.push_back(VehicleType("领坤EV", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "金程", logo.name_ENG = "";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "金龙", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("金威", ""));
    logo.TypeList.push_back(VehicleType("凯歌", ""));
    logo.TypeList.push_back(VehicleType("凯特", ""));
    logo.TypeList.push_back(VehicleType("凯锐浩克", ""));
    logo.TypeList.push_back(VehicleType("金龙海狮", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "金旅", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("海狮", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "晶马", logo.name_ENG = "";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "九龙", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("艾菲", ""));
    logo.TypeList.push_back(VehicleType("商务车", ""));
    logo.TypeList.push_back(VehicleType("考斯特", ""));
    logo.TypeList.push_back(VehicleType("专用车", ""));
    logo.TypeList.push_back(VehicleType("", "EM3"));
    logo.TypeList.push_back(VehicleType("", "EM5"));
    logo_list.push_back(logo);

    logo.name_CHS = "开瑞", logo.name_ENG = "Karry";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "K50"));
    logo.TypeList.push_back(VehicleType("", "K60"));
    logo.TypeList.push_back(VehicleType("优优", ""));
    logo.TypeList.push_back(VehicleType("优劲", ""));
    logo.TypeList.push_back(VehicleType("", "3"));
    logo.TypeList.push_back(VehicleType("优雅", ""));
    logo.TypeList.push_back(VehicleType("爱卡", ""));
    logo.TypeList.push_back(VehicleType("杰虎", ""));
    logo.TypeList.push_back(VehicleType("优胜", ""));
    logo.TypeList.push_back(VehicleType("优翼", ""));
    logo.TypeList.push_back(VehicleType("优派", ""));
    logo.TypeList.push_back(VehicleType("", "K60EV"));
    logo.TypeList.push_back(VehicleType("", "K50EV"));
    logo.TypeList.push_back(VehicleType("优优EV", ""));
    logo.TypeList.push_back(VehicleType("优劲EV", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "凯迪拉克", logo.name_ENG = "Cadillac";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "XT4"));
    logo.TypeList.push_back(VehicleType("", "ATS-L"));
    logo.TypeList.push_back(VehicleType("", "XT5"));
    logo.TypeList.push_back(VehicleType("", "XTS"));
    logo.TypeList.push_back(VehicleType("", "CT6"));
    logo.TypeList.push_back(VehicleType("SLS赛威", ""));
    logo.TypeList.push_back(VehicleType("凯雷德", ""));
    logo.TypeList.push_back(VehicleType("", "CTS"));
    logo.TypeList.push_back(VehicleType("", "SRX"));
    logo.TypeList.push_back(VehicleType("", "ATS"));
    logo.TypeList.push_back(VehicleType("", "XLR"));
    logo.TypeList.push_back(VehicleType("", "XT6"));
    logo_list.push_back(logo);

    logo.name_CHS = "克莱斯勒", logo.name_ENG = "Chrysler";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "300C"));
    logo.TypeList.push_back(VehicleType("大捷龙", ""));
    logo.TypeList.push_back(VehicleType("PT漫步者", ""));
    logo.TypeList.push_back(VehicleType("赛百灵", ""));
    logo.TypeList.push_back(VehicleType("城乡", ""));
    logo.TypeList.push_back(VehicleType("交叉火力", ""));
    logo.TypeList.push_back(VehicleType("铂锐", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "兰博基尼", logo.name_ENG = "Lamborghini";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "Urus"));
    logo.TypeList.push_back(VehicleType("", "Huracán"));
    logo.TypeList.push_back(VehicleType("", "Aventador"));
    logo.TypeList.push_back(VehicleType("", "Asterion"));
    logo.TypeList.push_back(VehicleType("", "Centenario"));
    logo.TypeList.push_back(VehicleType("", "Diablo"));
    logo.TypeList.push_back(VehicleType("", "Egoista"));
    logo.TypeList.push_back(VehicleType("", "Terzo Millennio"));
    logo.TypeList.push_back(VehicleType("", "Veneno"));
    logo.TypeList.push_back(VehicleType("", "LM002"));
    logo.TypeList.push_back(VehicleType("", "Estoque"));
    logo.TypeList.push_back(VehicleType("", "Gallardo"));
    logo.TypeList.push_back(VehicleType("", "Murcielago"));
    logo.TypeList.push_back(VehicleType("", "Reventon"));
    logo.TypeList.push_back(VehicleType("", "Sesto Elemento"));
    logo_list.push_back(logo);

    logo.name_CHS = "雷克萨斯", logo.name_ENG = "LEXUS";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "ES"));
    logo.TypeList.push_back(VehicleType("", "NX"));
    logo.TypeList.push_back(VehicleType("", "RX"));
    logo.TypeList.push_back(VehicleType("", "LX"));
    logo.TypeList.push_back(VehicleType("", "LS"));
    logo.TypeList.push_back(VehicleType("", "CT"));
    logo.TypeList.push_back(VehicleType("", "IS"));
    logo.TypeList.push_back(VehicleType("", "GS"));
    logo.TypeList.push_back(VehicleType("", "LC"));
    logo.TypeList.push_back(VehicleType("", "RC"));
    logo.TypeList.push_back(VehicleType("", "GX"));
    logo.TypeList.push_back(VehicleType("", "SC"));
    logo.TypeList.push_back(VehicleType("", "UX"));
    logo.TypeList.push_back(VehicleType("凌志", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "雷诺", logo.name_ENG = "Renault S.A";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "ESPACE"));
    logo.TypeList.push_back(VehicleType("卡缤", ""));
    logo.TypeList.push_back(VehicleType("梅甘娜", ""));
    logo.TypeList.push_back(VehicleType("科雷傲", ""));
    logo.TypeList.push_back(VehicleType("风朗", ""));
    logo.TypeList.push_back(VehicleType("风景", ""));
    logo.TypeList.push_back(VehicleType("塔利斯曼", ""));
    logo.TypeList.push_back(VehicleType("纬度", ""));
    logo.TypeList.push_back(VehicleType("拉古那", ""));
    logo.TypeList.push_back(VehicleType("威赛帝", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "理念", logo.name_ENG = "linianqiche";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "VE-1"));
    logo.TypeList.push_back(VehicleType("", "S1"));
    logo_list.push_back(logo);

    logo.name_CHS = "力帆", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("320", ""));
    logo.TypeList.push_back(VehicleType("330", ""));
    logo.TypeList.push_back(VehicleType("520", ""));
    logo.TypeList.push_back(VehicleType("520i", ""));
    logo.TypeList.push_back(VehicleType("530", ""));
    logo.TypeList.push_back(VehicleType("620", ""));
    logo.TypeList.push_back(VehicleType("630", ""));
    logo.TypeList.push_back(VehicleType("650", ""));
    logo.TypeList.push_back(VehicleType("720", ""));
    logo.TypeList.push_back(VehicleType("820", ""));
    logo.TypeList.push_back(VehicleType("丰顺", ""));
    logo.TypeList.push_back(VehicleType("福顺", ""));
    logo.TypeList.push_back(VehicleType("乐途", ""));
    logo.TypeList.push_back(VehicleType("X50", ""));
    logo.TypeList.push_back(VehicleType("X60", ""));
    logo.TypeList.push_back(VehicleType("X80", ""));
    logo.TypeList.push_back(VehicleType("兴顺", ""));
    logo.TypeList.push_back(VehicleType("迈威", ""));
    logo.TypeList.push_back(VehicleType("轩朗", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "莲花", logo.name_ENG = "Lotus Cars";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "L3"));
    logo.TypeList.push_back(VehicleType("", "L5"));
    logo.TypeList.push_back(VehicleType("竞悦", ""));
    logo.TypeList.push_back(VehicleType("欧洲之星", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "猎豹", logo.name_ENG = "Leopaard";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "Mattu"));
    logo.TypeList.push_back(VehicleType("", "CS9"));
    logo.TypeList.push_back(VehicleType("", "CS10"));
    logo.TypeList.push_back(VehicleType("", "Q6"));
    logo.TypeList.push_back(VehicleType("", "CT7"));
    logo.TypeList.push_back(VehicleType("黑金刚", ""));
    logo.TypeList.push_back(VehicleType("飞腾", ""));
    logo.TypeList.push_back(VehicleType("6481", ""));
    logo.TypeList.push_back(VehicleType("骐菱", ""));
    logo.TypeList.push_back(VehicleType("", "CS6"));
    logo.TypeList.push_back(VehicleType("CT5皮卡", ""));
    logo.TypeList.push_back(VehicleType("CS7", ""));
    logo.TypeList.push_back(VehicleType("皮卡", ""));
    logo.TypeList.push_back(VehicleType("长丰DUV", ""));
    logo.TypeList.push_back(VehicleType("飞扬皮卡", ""));
    logo.TypeList.push_back(VehicleType("飞腾C5", ""));
    logo.TypeList.push_back(VehicleType("福铃皮卡", ""));
    logo.TypeList.push_back(VehicleType("飞扬SUV", ""));
    logo.TypeList.push_back(VehicleType("飞铃SUV", ""));
    logo.TypeList.push_back(VehicleType("金麒麟", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "林肯", logo.name_ENG = "LINCOLN";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "MKC"));
    logo.TypeList.push_back(VehicleType("", "MKZ"));
    logo.TypeList.push_back(VehicleType("领航员", ""));
    logo.TypeList.push_back(VehicleType("大陆", ""));
    logo.TypeList.push_back(VehicleType("", "MKX"));
    logo.TypeList.push_back(VehicleType("", "MKT"));
    logo.TypeList.push_back(VehicleType("", "MKS"));
    logo.TypeList.push_back(VehicleType("航海家", ""));
    logo.TypeList.push_back(VehicleType("飞行家", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "铃木", logo.name_ENG = "SUZUKI";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("维特拉", ""));
    logo.TypeList.push_back(VehicleType("骁途", ""));
    logo.TypeList.push_back(VehicleType("奥拓", ""));
    logo.TypeList.push_back(VehicleType("雨燕", ""));
    logo.TypeList.push_back(VehicleType("启悦", ""));
    logo.TypeList.push_back(VehicleType("天语 SX4", ""));
    logo.TypeList.push_back(VehicleType("北斗星", ""));
    logo.TypeList.push_back(VehicleType("北斗星X5", ""));
    logo.TypeList.push_back(VehicleType("吉姆尼", ""));
    logo.TypeList.push_back(VehicleType("英格尼斯", ""));
    logo.TypeList.push_back(VehicleType("超级维特拉", ""));
    logo.TypeList.push_back(VehicleType("锋驭", ""));
    logo.TypeList.push_back(VehicleType("羚羊", ""));
    logo.TypeList.push_back(VehicleType("尚悦", ""));
    logo.TypeList.push_back(VehicleType("派喜", ""));
    logo.TypeList.push_back(VehicleType("利亚纳", ""));
    logo.TypeList.push_back(VehicleType("利亚纳A6", ""));
    logo.TypeList.push_back(VehicleType("浪迪", ""));
    logo.TypeList.push_back(VehicleType("速翼特", ""));
    logo.TypeList.push_back(VehicleType("凯泽西", ""));
    logo.TypeList.push_back(VehicleType("长安", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "路虎", logo.name_ENG = "LAND ROVER";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("揽胜", ""));
    logo.TypeList.push_back(VehicleType("运动", ""));
    logo.TypeList.push_back(VehicleType("揽胜星脉", ""));
    logo.TypeList.push_back(VehicleType("发现", ""));
    logo.TypeList.push_back(VehicleType("揽胜极光", ""));
    logo.TypeList.push_back(VehicleType("卫士", ""));
    logo.TypeList.push_back(VehicleType("发现神行", ""));
    logo.TypeList.push_back(VehicleType("神行者", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "陆风", logo.name_ENG = "Landwind";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "X7"));
    logo.TypeList.push_back(VehicleType("逍遥", ""));
    logo.TypeList.push_back(VehicleType("", "X2"));
    logo.TypeList.push_back(VehicleType("", "X8"));
    logo.TypeList.push_back(VehicleType("", "X5"));
    logo.TypeList.push_back(VehicleType("", "X6"));
    logo.TypeList.push_back(VehicleType("风尚", ""));
    logo.TypeList.push_back(VehicleType("", "X9"));
    logo.TypeList.push_back(VehicleType("风华", ""));
    logo.TypeList.push_back(VehicleType("新饰界", ""));
    logo.TypeList.push_back(VehicleType("江陵", ""));
    logo.TypeList.push_back(VehicleType("江铃", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "罗孚", logo.name_ENG = "Rover";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("荣威", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "玛莎拉蒂", logo.name_ENG = "Maserati";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "Levante"));
    logo.TypeList.push_back(VehicleType("", "Ghibli"));
    logo.TypeList.push_back(VehicleType("", "Quattroporte"));
    logo.TypeList.push_back(VehicleType("", "GranCabrio"));
    logo.TypeList.push_back(VehicleType("", "GranTurismo"));
    logo.TypeList.push_back(VehicleType("", "spyder"));
    logo.TypeList.push_back(VehicleType("", "Coupe"));
    logo.TypeList.push_back(VehicleType("", "GranSport"));
    logo_list.push_back(logo);

    logo.name_CHS = "马自达", logo.name_ENG = "Mazda";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("昂克赛拉", ""));
    logo.TypeList.push_back(VehicleType("", "CX-5"));
    logo.TypeList.push_back(VehicleType("", "CX-8"));
    logo.TypeList.push_back(VehicleType("3", ""));
    logo.TypeList.push_back(VehicleType("2", ""));
    logo.TypeList.push_back(VehicleType("3 星骋", ""));
    logo.TypeList.push_back(VehicleType("海马", ""));
    logo.TypeList.push_back(VehicleType("海南", ""));
    logo.TypeList.push_back(VehicleType("红旗", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "迷你", logo.name_ENG = "Mini";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "CLUBMAN"));
    logo.TypeList.push_back(VehicleType("", "COUNTRYMAN"));
    logo.TypeList.push_back(VehicleType("", "CABRIO"));
    logo.TypeList.push_back(VehicleType("", "COUPE"));
    logo.TypeList.push_back(VehicleType("", "PACEMAN"));
    logo.TypeList.push_back(VehicleType("", "ROADSTER"));
    logo.TypeList.push_back(VehicleType("", "JCW COUNTRYMAN"));
    logo.TypeList.push_back(VehicleType("", "JCW"));
    logo.TypeList.push_back(VehicleType("", "JCW CLUBMAN"));
    logo.TypeList.push_back(VehicleType("", "JCW COUPE"));
    logo.TypeList.push_back(VehicleType("", "JCW PACEMAN"));
    logo_list.push_back(logo);

    logo.name_CHS = "名爵", logo.name_ENG = "MorrisGarages";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("6", ""));
    logo.TypeList.push_back(VehicleType("", "HS"));
    logo.TypeList.push_back(VehicleType("", "ZS"));
    logo.TypeList.push_back(VehicleType("", "GS"));
    logo.TypeList.push_back(VehicleType("3", ""));
    logo.TypeList.push_back(VehicleType("7", ""));
    logo.TypeList.push_back(VehicleType("3SW", ""));
    logo.TypeList.push_back(VehicleType("TF", ""));
    logo.TypeList.push_back(VehicleType("5", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "纳智捷", logo.name_ENG = "Luxgen";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "U5 SUV"));
    logo.TypeList.push_back(VehicleType("优6 SUV", ""));
    logo.TypeList.push_back(VehicleType("大7 MPV", ""));
    logo.TypeList.push_back(VehicleType("锐3", ""));
    logo.TypeList.push_back(VehicleType("MASTER CEO", ""));
    logo.TypeList.push_back(VehicleType("大7 SUV", ""));
    logo.TypeList.push_back(VehicleType("纳5", ""));
    logo.TypeList.push_back(VehicleType("", "U5 EV"));
    logo_list.push_back(logo);

    logo.name_CHS = "欧宝", logo.name_ENG = "OPEL";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("威达", ""));
    logo.TypeList.push_back(VehicleType("雅特", ""));
    logo.TypeList.push_back(VehicleType("英速亚", ""));
    logo.TypeList.push_back(VehicleType("安德拉", ""));
    logo.TypeList.push_back(VehicleType("麦瑞纳", ""));
    logo.TypeList.push_back(VehicleType("赛飞利", ""));
    logo.TypeList.push_back(VehicleType("", "GT"));
    logo_list.push_back(logo);

    logo.name_CHS = "讴歌", logo.name_ENG = "Acura";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "CDX"));
    logo.TypeList.push_back(VehicleType("", "RDX"));
    logo.TypeList.push_back(VehicleType("", "TLX-L"));
    logo.TypeList.push_back(VehicleType("", "RDX"));
    logo.TypeList.push_back(VehicleType("", "MDX"));
    logo.TypeList.push_back(VehicleType("", "NSX"));
    logo.TypeList.push_back(VehicleType("", "ZDX"));
    logo.TypeList.push_back(VehicleType("", "CDX"));
    logo.TypeList.push_back(VehicleType("", "ILX"));
    logo.TypeList.push_back(VehicleType("", "TLX"));
    logo.TypeList.push_back(VehicleType("", "RLX"));
    logo.TypeList.push_back(VehicleType("", "TL"));
    logo.TypeList.push_back(VehicleType("", "RL"));
    logo_list.push_back(logo);

    logo.name_CHS = "奇瑞", logo.name_ENG = "Chery";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("爱卡", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽3", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽5", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽7", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽7e", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽EX", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽M7", ""));
    logo.TypeList.push_back(VehicleType("东方之子", ""));
    logo.TypeList.push_back(VehicleType("东方之子Cross", ""));
    logo.TypeList.push_back(VehicleType("风云", ""));
    logo.TypeList.push_back(VehicleType("风云2", ""));
    logo.TypeList.push_back(VehicleType("", "A1"));
    logo.TypeList.push_back(VehicleType("", "A3"));
    logo.TypeList.push_back(VehicleType("", "A5"));
    logo.TypeList.push_back(VehicleType("", "E3"));
    logo.TypeList.push_back(VehicleType("", "E5"));
    logo.TypeList.push_back(VehicleType("", "QQ"));
    logo.TypeList.push_back(VehicleType("", "QQ3"));
    logo.TypeList.push_back(VehicleType("", "QQ6"));
    logo.TypeList.push_back(VehicleType("", "QQme"));
    logo.TypeList.push_back(VehicleType("旗云", ""));
    logo.TypeList.push_back(VehicleType("旗云1", ""));
    logo.TypeList.push_back(VehicleType("旗云2", ""));
    logo.TypeList.push_back(VehicleType("旗云3", ""));
    logo.TypeList.push_back(VehicleType("旗云5", ""));
    logo.TypeList.push_back(VehicleType("瑞虎", ""));
    logo.TypeList.push_back(VehicleType("瑞虎3", ""));
    logo.TypeList.push_back(VehicleType("瑞虎5", ""));
    logo.TypeList.push_back(VehicleType("瑞虎5x", ""));
    logo.TypeList.push_back(VehicleType("瑞虎7", "E3"));
    logo.TypeList.push_back(VehicleType("瑞虎8", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽5e", ""));
    logo.TypeList.push_back(VehicleType("奇瑞eQ", ""));
    logo.TypeList.push_back(VehicleType("瑞虎3xe", ""));
    logo.TypeList.push_back(VehicleType("瑞麒", ""));
    logo.TypeList.push_back(VehicleType("开瑞", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "奇瑞2", logo.name_ENG = "Chery";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("爱卡", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽3", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽5", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽7", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽7e", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽EX", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽M7", ""));
    logo.TypeList.push_back(VehicleType("东方之子", ""));
    logo.TypeList.push_back(VehicleType("东方之子Cross", ""));
    logo.TypeList.push_back(VehicleType("风云", ""));
    logo.TypeList.push_back(VehicleType("风云2", ""));
    logo.TypeList.push_back(VehicleType("", "A1"));
    logo.TypeList.push_back(VehicleType("", "A3"));
    logo.TypeList.push_back(VehicleType("", "A5"));
    logo.TypeList.push_back(VehicleType("", "E3"));
    logo.TypeList.push_back(VehicleType("", "E5"));
    logo.TypeList.push_back(VehicleType("", "QQ"));
    logo.TypeList.push_back(VehicleType("", "QQ3"));
    logo.TypeList.push_back(VehicleType("", "QQ6"));
    logo.TypeList.push_back(VehicleType("", "QQme"));
    logo.TypeList.push_back(VehicleType("旗云", ""));
    logo.TypeList.push_back(VehicleType("旗云1", ""));
    logo.TypeList.push_back(VehicleType("旗云2", ""));
    logo.TypeList.push_back(VehicleType("旗云3", ""));
    logo.TypeList.push_back(VehicleType("旗云5", ""));
    logo.TypeList.push_back(VehicleType("瑞虎", ""));
    logo.TypeList.push_back(VehicleType("瑞虎3", ""));
    logo.TypeList.push_back(VehicleType("瑞虎5", ""));
    logo.TypeList.push_back(VehicleType("瑞虎5x", ""));
    logo.TypeList.push_back(VehicleType("瑞虎7", "E3"));
    logo.TypeList.push_back(VehicleType("瑞虎8", ""));
    logo.TypeList.push_back(VehicleType("艾瑞泽5e", ""));
    logo.TypeList.push_back(VehicleType("奇瑞eQ", ""));
    logo.TypeList.push_back(VehicleType("瑞虎3xe", ""));
    logo.TypeList.push_back(VehicleType("瑞麒", ""));
    logo.TypeList.push_back(VehicleType("开瑞", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "启辰", logo.name_ENG = "Venucia";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "D60"));
    logo.TypeList.push_back(VehicleType("", "T70"));
    logo.TypeList.push_back(VehicleType("", "T90"));
    logo.TypeList.push_back(VehicleType("", "T60"));
    logo.TypeList.push_back(VehicleType("", "M50V"));
    logo.TypeList.push_back(VehicleType("", "T70X"));
    logo.TypeList.push_back(VehicleType("", "R50X"));
    logo.TypeList.push_back(VehicleType("", "D50"));
    logo.TypeList.push_back(VehicleType("", "R50"));
    logo.TypeList.push_back(VehicleType("", "R30"));
    logo.TypeList.push_back(VehicleType("启辰晨风", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "起亚", logo.name_ENG = "KIA";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("福瑞迪", ""));
    logo.TypeList.push_back(VehicleType("", "K2"));
    logo.TypeList.push_back(VehicleType("", "K3"));
    logo.TypeList.push_back(VehicleType("", "K4"));
    logo.TypeList.push_back(VehicleType("", "K5"));
    logo.TypeList.push_back(VehicleType("", "KX3"));
    logo.TypeList.push_back(VehicleType("", "KX5"));
    logo.TypeList.push_back(VehicleType("", "KX7"));
    logo.TypeList.push_back(VehicleType("赛拉图", ""));
    logo.TypeList.push_back(VehicleType("狮跑", ""));
    logo.TypeList.push_back(VehicleType("秀尔", ""));
    logo.TypeList.push_back(VehicleType("智跑", ""));
    logo.TypeList.push_back(VehicleType("霸锐", ""));
    logo.TypeList.push_back(VehicleType("凯尊", ""));
    logo.TypeList.push_back(VehicleType("", "K9"));
    logo.TypeList.push_back(VehicleType("", "VQ"));
    logo.TypeList.push_back(VehicleType("索兰托", ""));
    logo.TypeList.push_back(VehicleType("速迈", ""));
    logo.TypeList.push_back(VehicleType("嘉华", ""));
    logo.TypeList.push_back(VehicleType("佳乐", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "荣威", logo.name_ENG = "ROEWE";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("350", ""));
    logo.TypeList.push_back(VehicleType("360", ""));
    logo.TypeList.push_back(VehicleType("950", ""));
    logo.TypeList.push_back(VehicleType("", "e50"));
    logo.TypeList.push_back(VehicleType("", "e550"));
    logo.TypeList.push_back(VehicleType("", "e950"));
    logo.TypeList.push_back(VehicleType("", "Ei5"));
    logo.TypeList.push_back(VehicleType("", "ei6"));
    logo.TypeList.push_back(VehicleType("", "i5"));
    logo.TypeList.push_back(VehicleType("", "i6"));
    logo.TypeList.push_back(VehicleType("", "RX3"));
    logo.TypeList.push_back(VehicleType("", "RX5"));
    logo.TypeList.push_back(VehicleType("", "RX8"));
    logo.TypeList.push_back(VehicleType("", "W5"));
    logo_list.push_back(logo);

    logo.name_CHS = "萨博", logo.name_ENG = "SAAB";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("9-3", ""));
    logo.TypeList.push_back(VehicleType("9-5", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "三菱", logo.name_ENG = "Mitsubishi";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("帕杰罗", ""));
    logo.TypeList.push_back(VehicleType("蓝瑟", ""));
    logo.TypeList.push_back(VehicleType("欧蓝德", ""));
    logo.TypeList.push_back(VehicleType("劲炫", ""));
    logo.TypeList.push_back(VehicleType("帕杰罗·劲畅", ""));
    logo.TypeList.push_back(VehicleType("伊柯丽斯", ""));
    logo.TypeList.push_back(VehicleType("格蓝迪", ""));
    logo.TypeList.push_back(VehicleType("东南", ""));
    logo.TypeList.push_back(VehicleType("徳宝", ""));
    logo.TypeList.push_back(VehicleType("帕捷罗", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "陕汽通家", logo.name_ENG = "Mitsubishi";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("福家", ""));
    logo.TypeList.push_back(VehicleType("国金GM3", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "双环", logo.name_ENG = "Mitsubishi";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("来宝S-RV", ""));
    logo.TypeList.push_back(VehicleType("小贵族", ""));
    logo.TypeList.push_back(VehicleType("", "SCEO"));
    logo.TypeList.push_back(VehicleType("来旺", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "双环2", logo.name_ENG = "Mitsubishi";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("来宝S-RV", ""));
    logo.TypeList.push_back(VehicleType("小贵族", ""));
    logo.TypeList.push_back(VehicleType("", "SCEO"));
    logo.TypeList.push_back(VehicleType("来旺", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "双龙", logo.name_ENG = "SSANG YONG";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("主席", ""));
    logo.TypeList.push_back(VehicleType("雷斯特G4", ""));
    logo.TypeList.push_back(VehicleType("途凌", ""));
    logo.TypeList.push_back(VehicleType("爱腾", ""));
    logo.TypeList.push_back(VehicleType("雷斯特W", ""));
    logo.TypeList.push_back(VehicleType("柯兰多", ""));
    logo.TypeList.push_back(VehicleType("路帝", ""));
    logo.TypeList.push_back(VehicleType("享御", ""));
    logo.TypeList.push_back(VehicleType("蒂维拉", ""));
    logo.TypeList.push_back(VehicleType("灵御", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "斯巴鲁", logo.name_ENG = "Subaru";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "XV"));
    logo.TypeList.push_back(VehicleType("森林人", ""));
    logo.TypeList.push_back(VehicleType("傲虎", ""));
    logo.TypeList.push_back(VehicleType("力狮", ""));
    logo.TypeList.push_back(VehicleType("", "BRZ"));
    logo.TypeList.push_back(VehicleType("驰鹏", ""));
    logo.TypeList.push_back(VehicleType("翼豹", ""));
    logo.TypeList.push_back(VehicleType("", "WRX"));
    logo_list.push_back(logo);

    logo.name_CHS = "斯柯达", logo.name_ENG = "SKODA";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("柯珞克", ""));
    logo.TypeList.push_back(VehicleType("明锐", ""));
    logo.TypeList.push_back(VehicleType("柯迪亚克", ""));
    logo.TypeList.push_back(VehicleType("柯米克", ""));
    logo.TypeList.push_back(VehicleType("速派", ""));
    logo.TypeList.push_back(VehicleType("昕锐", ""));
    logo.TypeList.push_back(VehicleType("柯迪亚克GT", ""));
    logo.TypeList.push_back(VehicleType("昕动", ""));
    logo.TypeList.push_back(VehicleType("野帝", ""));
    logo.TypeList.push_back(VehicleType("晶锐", ""));
    logo.TypeList.push_back(VehicleType("昊锐", ""));
    logo.TypeList.push_back(VehicleType("明锐", ""));
    logo.TypeList.push_back(VehicleType("", "Yeti"));
    logo.TypeList.push_back(VehicleType("法比亚", ""));
    logo.TypeList.push_back(VehicleType("欧雅", ""));
    logo.TypeList.push_back(VehicleType("速尊", ""));
    logo.TypeList.push_back(VehicleType("昊锐", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "威麟", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "H5"));
    logo.TypeList.push_back(VehicleType("", "H3"));
    logo.TypeList.push_back(VehicleType("", "V5"));
    logo.TypeList.push_back(VehicleType("", "X5"));
    logo_list.push_back(logo);

    logo.name_CHS = "潍柴英致", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("737", ""));
    logo.TypeList.push_back(VehicleType("", "G5"));
    logo.TypeList.push_back(VehicleType("727", ""));
    logo.TypeList.push_back(VehicleType("", "G3"));
    logo.TypeList.push_back(VehicleType("727", ""));
    logo.TypeList.push_back(VehicleType("737EV", ""));
    logo.TypeList.push_back(VehicleType("", "EX1"));
    logo_list.push_back(logo);

    logo.name_CHS = "沃尔沃", logo.name_ENG = "Volvo group";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "C30"));
    logo.TypeList.push_back(VehicleType("", "S40"));
    logo.TypeList.push_back(VehicleType("", "V40"));
    logo.TypeList.push_back(VehicleType("", "S40"));
    logo.TypeList.push_back(VehicleType("", "S60"));
    logo.TypeList.push_back(VehicleType("", "S60 Polestar"));
    logo.TypeList.push_back(VehicleType("", "S60L"));
    logo.TypeList.push_back(VehicleType("", "S80"));
    logo.TypeList.push_back(VehicleType("", "S90"));
    logo.TypeList.push_back(VehicleType("", "S80L"));
    logo.TypeList.push_back(VehicleType("", "XC60"));
    logo.TypeList.push_back(VehicleType("", "XC90"));
    logo.TypeList.push_back(VehicleType("", "XC40"));
    logo.TypeList.push_back(VehicleType("", "XC CLASSIC"));
    logo.TypeList.push_back(VehicleType("", "C70"));
    logo.TypeList.push_back(VehicleType("", "P1800"));
    logo.TypeList.push_back(VehicleType("", "V60"));
    logo.TypeList.push_back(VehicleType("", "V60 Polestar"));
    logo.TypeList.push_back(VehicleType("", "V90"));
    logo_list.push_back(logo);

    logo.name_CHS = "五菱", logo.name_ENG = "SGMW";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("宏光", ""));
    logo.TypeList.push_back(VehicleType("宏光S", ""));
    logo.TypeList.push_back(VehicleType("宏光S1", ""));
    logo.TypeList.push_back(VehicleType("鸿途", ""));
    logo.TypeList.push_back(VehicleType("荣光", ""));
    logo.TypeList.push_back(VehicleType("荣光S", ""));
    logo.TypeList.push_back(VehicleType("荣光V", ""));
    logo.TypeList.push_back(VehicleType("荣光新卡", ""));
    logo.TypeList.push_back(VehicleType("荣光小卡", ""));
    logo.TypeList.push_back(VehicleType("兴旺", ""));
    logo.TypeList.push_back(VehicleType("征程", ""));
    logo.TypeList.push_back(VehicleType("之光", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "五十铃", logo.name_ENG = "ISUZU";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("庆铃TAGA皮卡", ""));
    logo.TypeList.push_back(VehicleType("皮卡", ""));
    logo.TypeList.push_back(VehicleType("N系列", ""));
    logo.TypeList.push_back(VehicleType("T系列", ""));
    logo.TypeList.push_back(VehicleType("F系列", ""));
    logo.TypeList.push_back(VehicleType("D-MAX", ""));
    logo.TypeList.push_back(VehicleType("mu-X牧游侠", ""));
    logo.TypeList.push_back(VehicleType("瑞迈", ""));
    logo.TypeList.push_back(VehicleType("铃拓", ""));
    logo.TypeList.push_back(VehicleType("", "MU-X"));
    logo_list.push_back(logo);

    logo.name_CHS = "夏利", logo.name_ENG = "xiali";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "雪佛兰", logo.name_ENG = "Chevrolet";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("沃兰多", ""));
    logo.TypeList.push_back(VehicleType("科沃兹", ""));
    logo.TypeList.push_back(VehicleType("探界者", ""));
    logo.TypeList.push_back(VehicleType("迈锐宝XL", ""));
    logo.TypeList.push_back(VehicleType("迈锐宝", ""));
    logo.TypeList.push_back(VehicleType("科鲁兹", ""));
    logo.TypeList.push_back(VehicleType("赛欧3", ""));
    logo.TypeList.push_back(VehicleType("创酷", ""));
    logo.TypeList.push_back(VehicleType("科帕奇", ""));
    logo.TypeList.push_back(VehicleType("乐风RV", ""));
    logo.TypeList.push_back(VehicleType("乐风", ""));
    logo.TypeList.push_back(VehicleType("赛欧", ""));
    logo.TypeList.push_back(VehicleType("景程", ""));
    logo.TypeList.push_back(VehicleType("乐骋", ""));
    logo.TypeList.push_back(VehicleType("爱唯欧", ""));
    logo.TypeList.push_back(VehicleType("科鲁泽", ""));
    logo.TypeList.push_back(VehicleType("科迈罗", ""));
    logo.TypeList.push_back(VehicleType("探际者", ""));
    logo.TypeList.push_back(VehicleType("索罗德", ""));
    logo.TypeList.push_back(VehicleType("库罗德", ""));
    logo.TypeList.push_back(VehicleType("开拓者", ""));
    logo.TypeList.push_back(VehicleType("沃蓝达", ""));
    logo.TypeList.push_back(VehicleType("科帕奇", ""));
    logo.TypeList.push_back(VehicleType("斯帕可", ""));
    logo.TypeList.push_back(VehicleType("", "EXPRESS"));
    logo.TypeList.push_back(VehicleType("科尔维特", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "雪铁龙", logo.name_ENG = "Citroen";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("天逸 C5 AIRCROSS", ""));
    logo.TypeList.push_back(VehicleType("云逸 C4 AIRCROSS", ""));
    logo.TypeList.push_back(VehicleType("爱丽舍", ""));
    logo.TypeList.push_back(VehicleType("C4世嘉", ""));
    logo.TypeList.push_back(VehicleType("", "C5"));
    logo.TypeList.push_back(VehicleType("", "C6"));
    logo.TypeList.push_back(VehicleType("", "C3-XR"));
    logo.TypeList.push_back(VehicleType("", "C4L"));
    logo.TypeList.push_back(VehicleType("世嘉", ""));
    logo.TypeList.push_back(VehicleType("凯旋", ""));
    logo.TypeList.push_back(VehicleType("富康", ""));
    logo.TypeList.push_back(VehicleType("", "C2"));
    logo.TypeList.push_back(VehicleType("萨拉-毕加索", ""));
    logo.TypeList.push_back(VehicleType("赛纳", ""));
    logo.TypeList.push_back(VehicleType("", "C4 PICASSO"));
    logo.TypeList.push_back(VehicleType("", "C4"));
    logo.TypeList.push_back(VehicleType("", "C6"));
    logo.TypeList.push_back(VehicleType("", "C5"));
    logo.TypeList.push_back(VehicleType("", "C4 AIRCROSS"));
    logo_list.push_back(logo);

    logo.name_CHS = "扬子", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("猎豹CT5", ""));
    logo.TypeList.push_back(VehicleType("猎豹飞扬", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "一汽", logo.name_ENG = "FAW";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("森雅R9", ""));
    logo.TypeList.push_back(VehicleType("森雅R7", ""));
    logo.TypeList.push_back(VehicleType("佳宝V52", ""));
    logo.TypeList.push_back(VehicleType("佳宝V80", ""));
    logo.TypeList.push_back(VehicleType("解放T80", ""));
    logo.TypeList.push_back(VehicleType("", "V75"));
    logo.TypeList.push_back(VehicleType("", "V77"));
    logo.TypeList.push_back(VehicleType("佳宝T51", ""));
    logo.TypeList.push_back(VehicleType("佳宝T57", ""));
    logo.TypeList.push_back(VehicleType("佳宝T50", ""));
    logo.TypeList.push_back(VehicleType("佳宝V55", ""));
    logo.TypeList.push_back(VehicleType("解放T90", ""));
    logo.TypeList.push_back(VehicleType("森雅M80", ""));
    logo.TypeList.push_back(VehicleType("森雅S80", ""));
    logo.TypeList.push_back(VehicleType("佳宝V70", ""));
    logo.TypeList.push_back(VehicleType("佳宝V70 Ⅱ", ""));
    logo.TypeList.push_back(VehicleType("奥星", ""));
    logo.TypeList.push_back(VehicleType("红旗", ""));
    logo.TypeList.push_back(VehicleType("威志", ""));
    logo.TypeList.push_back(VehicleType("夏利", ""));
    logo.TypeList.push_back(VehicleType("威乐", ""));

    logo_list.push_back(logo);
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("森雅R9", ""));
    logo.TypeList.push_back(VehicleType("森雅R7", ""));
    logo.TypeList.push_back(VehicleType("佳宝V52", ""));
    logo.TypeList.push_back(VehicleType("佳宝V80", ""));
    logo.TypeList.push_back(VehicleType("解放T80", ""));
    logo.TypeList.push_back(VehicleType("", "V75"));
    logo.TypeList.push_back(VehicleType("", "V77"));
    logo.TypeList.push_back(VehicleType("佳宝T51", ""));
    logo.TypeList.push_back(VehicleType("佳宝T57", ""));
    logo.TypeList.push_back(VehicleType("佳宝T50", ""));
    logo.TypeList.push_back(VehicleType("佳宝V55", ""));
    logo.TypeList.push_back(VehicleType("解放T90", ""));
    logo.TypeList.push_back(VehicleType("森雅M80", ""));
    logo.TypeList.push_back(VehicleType("森雅S80", ""));
    logo.TypeList.push_back(VehicleType("佳宝V70", ""));
    logo.TypeList.push_back(VehicleType("佳宝V70 Ⅱ", ""));
    logo.TypeList.push_back(VehicleType("奥星", ""));
    logo.TypeList.push_back(VehicleType("红旗", ""));
    logo.TypeList.push_back(VehicleType("威志", ""));
    logo.TypeList.push_back(VehicleType("夏利", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "依维柯", logo.name_ENG = "IVECO";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("得意", ""));
    logo.TypeList.push_back(VehicleType("Daily欧胜", ""));
    logo.TypeList.push_back(VehicleType("", "Power Daily"));
    logo.TypeList.push_back(VehicleType("", "Ouba"));
    logo.TypeList.push_back(VehicleType("", "Venice"));
    logo.TypeList.push_back(VehicleType("康果", ""));
    logo.TypeList.push_back(VehicleType("都灵", ""));
    logo.TypeList.push_back(VehicleType("欧霸", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "英菲尼迪", logo.name_ENG = "Infiniti";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "QX50"));
    logo.TypeList.push_back(VehicleType("", "Q50L"));
    logo.TypeList.push_back(VehicleType("", "ESQ"));
    logo.TypeList.push_back(VehicleType("", "QX30"));
    logo.TypeList.push_back(VehicleType("", "QX60"));
    logo.TypeList.push_back(VehicleType("", "QX70"));
    logo.TypeList.push_back(VehicleType("", "QX80"));
    logo.TypeList.push_back(VehicleType("", "Q50"));
    logo.TypeList.push_back(VehicleType("", "Q60"));
    logo.TypeList.push_back(VehicleType("", "Q70L"));
    logo.TypeList.push_back(VehicleType("", "Q30"));
    logo.TypeList.push_back(VehicleType("", "EX"));
    logo.TypeList.push_back(VehicleType("", "FX"));
    logo.TypeList.push_back(VehicleType("", "G"));
    logo.TypeList.push_back(VehicleType("", "JX"));
    logo.TypeList.push_back(VehicleType("", "M"));
    logo.TypeList.push_back(VehicleType("", "QX"));
    logo_list.push_back(logo);

    logo.name_CHS = "永源飞碟", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "UFO"));
    logo.TypeList.push_back(VehicleType("", "UFO-A380"));
    logo_list.push_back(logo);

    logo.name_CHS = "驭胜", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "S330"));
    logo.TypeList.push_back(VehicleType("", "S350"));
    logo.TypeList.push_back(VehicleType("", "江铃"));
    logo_list.push_back(logo);

    logo.name_CHS = "中华", logo.name_ENG = "zhonghua";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "V7"));
    logo.TypeList.push_back(VehicleType("", "V6"));
    logo.TypeList.push_back(VehicleType("", "V3"));
    logo.TypeList.push_back(VehicleType("", "H3"));
    logo.TypeList.push_back(VehicleType("", "V5"));
    logo.TypeList.push_back(VehicleType("", "H530"));
    logo.TypeList.push_back(VehicleType("骏捷FRV", ""));
    logo.TypeList.push_back(VehicleType("中华", ""));
    logo.TypeList.push_back(VehicleType("骏捷", ""));
    logo.TypeList.push_back(VehicleType("", "H330"));
    logo.TypeList.push_back(VehicleType("", "H230"));
    logo.TypeList.push_back(VehicleType("酷宝", ""));
    logo.TypeList.push_back(VehicleType("", "H220"));
    logo.TypeList.push_back(VehicleType("骏捷FSV", ""));
    logo.TypeList.push_back(VehicleType("尊驰", ""));
    logo.TypeList.push_back(VehicleType("骏捷Cross", ""));
    logo.TypeList.push_back(VehicleType("", "H320"));
    logo.TypeList.push_back(VehicleType("中华豚", ""));
    logo.TypeList.push_back(VehicleType("", "H230EV"));
    logo_list.push_back(logo);

    logo.name_CHS = "中顺", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("世纪", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "中兴", logo.name_ENG = "ZXAUTO";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("大领主", ""));
    logo.TypeList.push_back(VehicleType("小老虎", ""));
    logo.TypeList.push_back(VehicleType("威虎", ""));
    logo.TypeList.push_back(VehicleType("旗舰", ""));
    logo.TypeList.push_back(VehicleType("无限", ""));
    logo.TypeList.push_back(VehicleType("田野皮卡", ""));
    logo.TypeList.push_back(VehicleType("中兴老虎", ""));
    logo.TypeList.push_back(VehicleType("福星皮卡", ""));
    logo.TypeList.push_back(VehicleType("长铃皮卡", ""));
    logo.TypeList.push_back(VehicleType("威虎G3", ""));
    logo.TypeList.push_back(VehicleType("福星SUV", ""));
    logo.TypeList.push_back(VehicleType("田野SUV", ""));
    logo.TypeList.push_back(VehicleType("驰野", ""));
    logo.TypeList.push_back(VehicleType("金狮", ""));
    logo.TypeList.push_back(VehicleType("海豹", ""));
    logo.TypeList.push_back(VehicleType("万禧龙", ""));
    logo.TypeList.push_back(VehicleType("", "C3"));
    logo.TypeList.push_back(VehicleType("", "GX3"));
    logo_list.push_back(logo);

    logo.name_CHS = "众泰", logo.name_ENG = "ZOTYE";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "SR7"));
    logo.TypeList.push_back(VehicleType("", "SR9"));
    logo.TypeList.push_back(VehicleType("", "T300"));
    logo.TypeList.push_back(VehicleType("", "T500"));
    logo.TypeList.push_back(VehicleType("", "T600"));
    logo.TypeList.push_back(VehicleType("", "T600 Coupe"));
    logo.TypeList.push_back(VehicleType("", "T700"));
    logo.TypeList.push_back(VehicleType("", "T800"));
    logo.TypeList.push_back(VehicleType("大迈X5", ""));
    logo.TypeList.push_back(VehicleType("大迈X7", ""));
    logo.TypeList.push_back(VehicleType("", "Z360"));
    logo.TypeList.push_back(VehicleType("", "Z560"));
    logo.TypeList.push_back(VehicleType("", "Z700"));
    logo.TypeList.push_back(VehicleType("", "Z300"));
    logo.TypeList.push_back(VehicleType("", "Z500"));
    logo.TypeList.push_back(VehicleType("", "V10"));
    logo.TypeList.push_back(VehicleType("", "2008"));
    logo.TypeList.push_back(VehicleType("", "5008"));
    logo.TypeList.push_back(VehicleType("", "T200"));
    logo.TypeList.push_back(VehicleType("江南TT", "Z560"));
    logo.TypeList.push_back(VehicleType("", "Z100"));
    logo.TypeList.push_back(VehicleType("", "Z200HB"));
    logo.TypeList.push_back(VehicleType("", "Z200"));
    logo.TypeList.push_back(VehicleType("", "M300"));
    logo.TypeList.push_back(VehicleType("斯威", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "众泰2", logo.name_ENG = "ZOTYE";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "SR7"));
    logo.TypeList.push_back(VehicleType("", "SR9"));
    logo.TypeList.push_back(VehicleType("", "T300"));
    logo.TypeList.push_back(VehicleType("", "T500"));
    logo.TypeList.push_back(VehicleType("", "T600"));
    logo.TypeList.push_back(VehicleType("", "T600 Coupe"));
    logo.TypeList.push_back(VehicleType("", "T700"));
    logo.TypeList.push_back(VehicleType("", "T800"));
    logo.TypeList.push_back(VehicleType("大迈X5", ""));
    logo.TypeList.push_back(VehicleType("大迈X7", ""));
    logo.TypeList.push_back(VehicleType("", "Z360"));
    logo.TypeList.push_back(VehicleType("", "Z560"));
    logo.TypeList.push_back(VehicleType("", "Z700"));
    logo.TypeList.push_back(VehicleType("", "Z300"));
    logo.TypeList.push_back(VehicleType("", "Z500"));
    logo.TypeList.push_back(VehicleType("", "V10"));
    logo.TypeList.push_back(VehicleType("", "2008"));
    logo.TypeList.push_back(VehicleType("", "5008"));
    logo.TypeList.push_back(VehicleType("", "T200"));
    logo.TypeList.push_back(VehicleType("江南TT", "Z560"));
    logo.TypeList.push_back(VehicleType("", "Z100"));
    logo.TypeList.push_back(VehicleType("", "Z200HB"));
    logo.TypeList.push_back(VehicleType("", "Z200"));
    logo.TypeList.push_back(VehicleType("", "M300"));
    logo_list.push_back(logo);

    logo.name_CHS = "众泰3", logo.name_ENG = "ZOTYE";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "SR7"));
    logo.TypeList.push_back(VehicleType("", "SR9"));
    logo.TypeList.push_back(VehicleType("", "T300"));
    logo.TypeList.push_back(VehicleType("", "T500"));
    logo.TypeList.push_back(VehicleType("", "T600"));
    logo.TypeList.push_back(VehicleType("", "T600 Coupe"));
    logo.TypeList.push_back(VehicleType("", "T700"));
    logo.TypeList.push_back(VehicleType("", "T800"));
    logo.TypeList.push_back(VehicleType("大迈X5", ""));
    logo.TypeList.push_back(VehicleType("大迈X7", ""));
    logo.TypeList.push_back(VehicleType("", "Z360"));
    logo.TypeList.push_back(VehicleType("", "Z560"));
    logo.TypeList.push_back(VehicleType("", "Z700"));
    logo.TypeList.push_back(VehicleType("", "Z300"));
    logo.TypeList.push_back(VehicleType("", "Z500"));
    logo.TypeList.push_back(VehicleType("", "V10"));
    logo.TypeList.push_back(VehicleType("", "2008"));
    logo.TypeList.push_back(VehicleType("", "5008"));
    logo.TypeList.push_back(VehicleType("", "T200"));
    logo.TypeList.push_back(VehicleType("江南TT", "Z560"));
    logo.TypeList.push_back(VehicleType("", "Z100"));
    logo.TypeList.push_back(VehicleType("", "Z200HB"));
    logo.TypeList.push_back(VehicleType("", "Z200"));
    logo.TypeList.push_back(VehicleType("", "M300"));
    logo_list.push_back(logo);

    logo.name_CHS = "众泰4", logo.name_ENG = "ZOTYE";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "SR7"));
    logo.TypeList.push_back(VehicleType("", "SR9"));
    logo.TypeList.push_back(VehicleType("", "T300"));
    logo.TypeList.push_back(VehicleType("", "T500"));
    logo.TypeList.push_back(VehicleType("", "T600"));
    logo.TypeList.push_back(VehicleType("", "T600 Coupe"));
    logo.TypeList.push_back(VehicleType("", "T700"));
    logo.TypeList.push_back(VehicleType("", "T800"));
    logo.TypeList.push_back(VehicleType("大迈X5", ""));
    logo.TypeList.push_back(VehicleType("大迈X7", ""));
    logo.TypeList.push_back(VehicleType("", "Z360"));
    logo.TypeList.push_back(VehicleType("", "Z560"));
    logo.TypeList.push_back(VehicleType("", "Z700"));
    logo.TypeList.push_back(VehicleType("", "Z300"));
    logo.TypeList.push_back(VehicleType("", "Z500"));
    logo.TypeList.push_back(VehicleType("", "V10"));
    logo.TypeList.push_back(VehicleType("", "2008"));
    logo.TypeList.push_back(VehicleType("", "5008"));
    logo.TypeList.push_back(VehicleType("", "T200"));
    logo.TypeList.push_back(VehicleType("江南TT", "Z560"));
    logo.TypeList.push_back(VehicleType("", "Z100"));
    logo.TypeList.push_back(VehicleType("", "Z200HB"));
    logo.TypeList.push_back(VehicleType("", "Z200"));
    logo.TypeList.push_back(VehicleType("", "M300"));
    logo_list.push_back(logo);

    logo.name_CHS ="吉利全球鹰", logo.name_ENG = "GLEAGLE";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("吉利全球鹰EX3", ""));
    logo.TypeList.push_back(VehicleType("吉利全球鹰K27", ""));
    logo.TypeList.push_back(VehicleType("缤越", ""));
    logo.TypeList.push_back(VehicleType("缤瑞", ""));
    logo.TypeList.push_back(VehicleType("博越", ""));
    logo.TypeList.push_back(VehicleType("帝豪GS", ""));
    logo.TypeList.push_back(VehicleType("远景X3", ""));
    logo.TypeList.push_back(VehicleType("帝豪GL", ""));
    logo.TypeList.push_back(VehicleType("帝豪", ""));
    logo.TypeList.push_back(VehicleType("博瑞GE", ""));
    logo.TypeList.push_back(VehicleType("远景", ""));
    logo.TypeList.push_back(VehicleType("远景SUV", ""));
    logo.TypeList.push_back(VehicleType("远景S1", ""));
    logo.TypeList.push_back(VehicleType("博瑞", ""));
    logo.TypeList.push_back(VehicleType("远景X1", ""));
    logo.TypeList.push_back(VehicleType("金刚", ""));
    logo.TypeList.push_back(VehicleType("熊猫", ""));
    logo.TypeList.push_back(VehicleType("", "GX7"));
    logo.TypeList.push_back(VehicleType("自由舰", ""));
    logo.TypeList.push_back(VehicleType("", "EC8"));
    logo.TypeList.push_back(VehicleType("", "TX4"));
    logo.TypeList.push_back(VehicleType("中国龙", ""));
    logo.TypeList.push_back(VehicleType("美人豹", ""));
    logo.TypeList.push_back(VehicleType("", "GC7"));
    logo.TypeList.push_back(VehicleType("海景", ""));
    logo.TypeList.push_back(VehicleType("美日", ""));
    logo.TypeList.push_back(VehicleType("豪情SUV", ""));
    logo.TypeList.push_back(VehicleType("", "GX2"));
    logo.TypeList.push_back(VehicleType("", "SX7"));
    logo.TypeList.push_back(VehicleType("英伦C5", ""));
    logo.TypeList.push_back(VehicleType("", "SC3"));
    logo.TypeList.push_back(VehicleType("美日之星", ""));
    logo.TypeList.push_back(VehicleType("豪情", ""));
    logo.TypeList.push_back(VehicleType("优利欧", ""));
    logo.TypeList.push_back(VehicleType("嘉际", ""));
    logo.TypeList.push_back(VehicleType("博瑞GE PHEV", ""));
    logo.TypeList.push_back(VehicleType("帝豪GSe", ""));
    logo.TypeList.push_back(VehicleType("帝豪EV", ""));
    logo.TypeList.push_back(VehicleType("帝豪PHEV", ""));
    logo.TypeList.push_back(VehicleType("嘉际PHEV", ""));
    logo.TypeList.push_back(VehicleType("吉利GE11", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "吉利英伦", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("吉利", ""));
    logo.TypeList.push_back(VehicleType("英伦", ""));
    logo.TypeList.push_back(VehicleType("缤越", ""));
    logo.TypeList.push_back(VehicleType("缤瑞", ""));
    logo.TypeList.push_back(VehicleType("博越", ""));
    logo.TypeList.push_back(VehicleType("帝豪GS", ""));
    logo.TypeList.push_back(VehicleType("远景X3", ""));
    logo.TypeList.push_back(VehicleType("帝豪GL", ""));
    logo.TypeList.push_back(VehicleType("帝豪", ""));
    logo.TypeList.push_back(VehicleType("博瑞GE", ""));
    logo.TypeList.push_back(VehicleType("远景", ""));
    logo.TypeList.push_back(VehicleType("远景SUV", ""));
    logo.TypeList.push_back(VehicleType("远景S1", ""));
    logo.TypeList.push_back(VehicleType("博瑞", ""));
    logo.TypeList.push_back(VehicleType("远景X1", ""));
    logo.TypeList.push_back(VehicleType("金刚", ""));
    logo.TypeList.push_back(VehicleType("熊猫", ""));
    logo.TypeList.push_back(VehicleType("", "GX7"));
    logo.TypeList.push_back(VehicleType("自由舰", ""));
    logo.TypeList.push_back(VehicleType("", "EC8"));
    logo.TypeList.push_back(VehicleType("", "TX4"));
    logo.TypeList.push_back(VehicleType("中国龙", ""));
    logo.TypeList.push_back(VehicleType("美人豹", ""));
    logo.TypeList.push_back(VehicleType("", "GC7"));
    logo.TypeList.push_back(VehicleType("海景", ""));
    logo.TypeList.push_back(VehicleType("美日", ""));
    logo.TypeList.push_back(VehicleType("豪情SUV", ""));
    logo.TypeList.push_back(VehicleType("", "GX2"));
    logo.TypeList.push_back(VehicleType("", "SX7"));
    logo.TypeList.push_back(VehicleType("英伦C5", ""));
    logo.TypeList.push_back(VehicleType("", "SC3"));
    logo.TypeList.push_back(VehicleType("美日之星", ""));
    logo.TypeList.push_back(VehicleType("豪情", ""));
    logo.TypeList.push_back(VehicleType("优利欧", ""));
    logo.TypeList.push_back(VehicleType("嘉际", ""));
    logo.TypeList.push_back(VehicleType("博瑞GE PHEV", ""));
    logo.TypeList.push_back(VehicleType("帝豪GSe", ""));
    logo.TypeList.push_back(VehicleType("帝豪EV", ""));
    logo.TypeList.push_back(VehicleType("帝豪PHEV", ""));
    logo.TypeList.push_back(VehicleType("嘉际PHEV", ""));
    logo.TypeList.push_back(VehicleType("吉利GE11", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "跃进", logo.name_ENG = "Yuejin";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("财神", ""));
    logo.TypeList.push_back(VehicleType("帅虎", ""));
    logo.TypeList.push_back(VehicleType("欧卡", ""));
    logo.TypeList.push_back(VehicleType("凌野", ""));
    logo.TypeList.push_back(VehicleType("开拓者", ""));
    logo.TypeList.push_back(VehicleType("跃进底盘", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "宇通", logo.name_ENG = "YUTONG";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "一汽凌河", logo.name_ENG = "";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "野马", logo.name_ENG = "YEMA";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("野马T70", ""));
    logo.TypeList.push_back(VehicleType("野马T80", ""));
    logo.TypeList.push_back(VehicleType("博骏", ""));
    logo.TypeList.push_back(VehicleType("野马EC30", ""));
    logo.TypeList.push_back(VehicleType("斯派卡", ""));
    logo.TypeList.push_back(VehicleType("小哥2号", ""));
    logo.TypeList.push_back(VehicleType("野马EC60", ""));
    logo.TypeList.push_back(VehicleType("野马EC70", ""));
    logo.TypeList.push_back(VehicleType("小哥1号", ""));
    logo.TypeList.push_back(VehicleType("野马M302", ""));
    logo.TypeList.push_back(VehicleType("野马C60", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "亚星", logo.name_ENG = "";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "亚星", logo.name_ENG = "";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "徐工", logo.name_ENG = "Xugong";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("汉风", ""));
    logo.TypeList.push_back(VehicleType("瑞龙", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "星马", logo.name_ENG = "";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "陕汽", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("德龙", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "", logo.name_ENG = "DS";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "Deesse"));
    logo.TypeList.push_back(VehicleType("", "DS 7"));
    logo.TypeList.push_back(VehicleType("", "DS 4S"));
    logo.TypeList.push_back(VehicleType("", "DS 5"));
    logo.TypeList.push_back(VehicleType("", "DS 5LS"));
    logo.TypeList.push_back(VehicleType("", "DS 6"));
    logo.TypeList.push_back(VehicleType("", "DS 3 Crossback E-Tense"));
    logo.TypeList.push_back(VehicleType("", "DS 9"));
    logo.TypeList.push_back(VehicleType("", "DS 7 Crossback E-Tense"));
    logo_list.push_back(logo);

    logo.name_CHS = "", logo.name_ENG = "GMC";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("", "SAVANA"));
    logo.TypeList.push_back(VehicleType("", "SIERRA"));
    logo.TypeList.push_back(VehicleType("", "YUKON"));
    logo_list.push_back(logo);

    logo.name_CHS = "别克荣御", logo.name_ENG = "Buick Royal";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "北奔", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("北奔NG80", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "北京汽车", logo.name_ENG = "BAIC";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "比速", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("比速T3", ""));
    logo.TypeList.push_back(VehicleType("比速T5", ""));
    logo.TypeList.push_back(VehicleType("比速M3", ""));
    logo.TypeList.push_back(VehicleType("比速T7", ""));
    logo_list.push_back(logo);



    logo.name_CHS = "乘龙", logo.name_ENG = "";
    logo.TypeList.clear();
    logo_list.push_back(logo);


    logo.name_CHS = "福仕达", logo.name_ENG = "Fostar";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("腾达", ""));
    logo.TypeList.push_back(VehicleType("海马", ""));
    logo_list.push_back(logo);


    logo.name_CHS = "广汽传祺", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("传祺GS4", ""));
    logo.TypeList.push_back(VehicleType("传祺GM8", ""));
    logo.TypeList.push_back(VehicleType("传祺GM6", ""));
    logo.TypeList.push_back(VehicleType("传祺GS8", ""));
    logo.TypeList.push_back(VehicleType("传祺GS5", ""));
    logo.TypeList.push_back(VehicleType("传祺GA6", ""));
    logo.TypeList.push_back(VehicleType("传祺GS3", ""));
    logo.TypeList.push_back(VehicleType("传祺GA4", ""));
    logo.TypeList.push_back(VehicleType("传祺GS7", ""));
    logo.TypeList.push_back(VehicleType("传祺GA8", ""));
    logo.TypeList.push_back(VehicleType("传祺GA6 PHEV", ""));
    logo.TypeList.push_back(VehicleType("", "E Concept"));
    logo_list.push_back(logo);

    logo.name_CHS = "广汽吉奥", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("传祺GS4", ""));
    logo.TypeList.push_back(VehicleType("传祺GM8", ""));
    logo.TypeList.push_back(VehicleType("传祺GM6", ""));
    logo.TypeList.push_back(VehicleType("传祺GS8", ""));
    logo.TypeList.push_back(VehicleType("传祺GS5", ""));
    logo.TypeList.push_back(VehicleType("传祺GA6", ""));
    logo.TypeList.push_back(VehicleType("传祺GS3", ""));
    logo.TypeList.push_back(VehicleType("传祺GA4", ""));
    logo.TypeList.push_back(VehicleType("传祺GS7", ""));
    logo.TypeList.push_back(VehicleType("传祺GA8", ""));
    logo.TypeList.push_back(VehicleType("传祺GA6 PHEV", ""));
    logo.TypeList.push_back(VehicleType("", "E Concept"));
    logo_list.push_back(logo);

    logo.name_CHS = "豪曼", logo.name_ENG = "Hammer";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "红岩", logo.name_ENG = "Hongyan";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "凯马", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("凯捷", ""));
    logo.TypeList.push_back(VehicleType("金运卡", ""));
    logo.TypeList.push_back(VehicleType("骏腾", ""));
    logo.TypeList.push_back(VehicleType("福运来", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "马自达", logo.name_ENG = "Mazda";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("马自达CX-5", ""));
    logo.TypeList.push_back(VehicleType("马自达CX-8", ""));
    logo.TypeList.push_back(VehicleType("马自达3 昂克赛拉", ""));
    logo.TypeList.push_back(VehicleType("马自达CX-4", ""));
    logo.TypeList.push_back(VehicleType("阿特兹", ""));
    logo.TypeList.push_back(VehicleType("马自达CX-3", ""));
    logo.TypeList.push_back(VehicleType("马自达MX-5", ""));
    logo.TypeList.push_back(VehicleType("马自达CX-30", ""));
    logo.TypeList.push_back(VehicleType("马自达MX-30", ""));
    logo.TypeList.push_back(VehicleType("马自达3", ""));
    logo.TypeList.push_back(VehicleType("星骋", ""));
    logo.TypeList.push_back(VehicleType("马自达2", ""));
    logo.TypeList.push_back(VehicleType("马自达6", ""));
    logo.TypeList.push_back(VehicleType("马自达CX-7", ""));
    logo.TypeList.push_back(VehicleType("马自达8", ""));
    logo.TypeList.push_back(VehicleType("睿翼", ""));
    logo.TypeList.push_back(VehicleType("马自达5", ""));
    logo.TypeList.push_back(VehicleType("马自达CX-5", ""));
    logo.TypeList.push_back(VehicleType("马自达CX-7", ""));
    logo.TypeList.push_back(VehicleType("马自达CX-9", ""));
    logo.TypeList.push_back(VehicleType("马自达RX-8", ""));
    logo.TypeList.push_back(VehicleType("红旗", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "三一", logo.name_ENG = "hqc";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "川汽野马", logo.name_ENG = "hqc";
    logo.TypeList.clear();
    logo_list.push_back(logo);

    logo.name_CHS = "海马王子", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("奥路卡", ""));
    logo_list.push_back(logo);

    logo.name_CHS = "华泰", logo.name_ENG = "";
    logo.TypeList.clear();
    logo.TypeList.push_back(VehicleType("圣达菲经典", ""));
    logo.TypeList.push_back(VehicleType("宝利格", ""));
    logo.TypeList.push_back(VehicleType("特拉卡", ""));
    logo.TypeList.push_back(VehicleType("华泰B11", ""));
    logo.TypeList.push_back(VehicleType("路盛E70", ""));
    logo.TypeList.push_back(VehicleType("圣达菲5", ""));
    logo.TypeList.push_back(VehicleType("华泰iEV230", ""));
    logo.TypeList.push_back(VehicleType("路盛S1 iEV360", ""));
    logo.TypeList.push_back(VehicleType("圣达菲5 XEV260", ""));
    logo.TypeList.push_back(VehicleType("圣达菲00", ""));
    logo.TypeList.push_back(VehicleType("路盛E80", ""));
    logo.TypeList.push_back(VehicleType("路盛S1 EV160R", ""));
    logo_list.push_back(logo);
}





//判断连个飞空字符产 是否相互包含
#define IS_STRING_CONTIAN(_t_str1, _t_str2) (  ((_t_str1).size() > 0  && (_t_str2).size() > 0 ) &&   \
 ( (_t_str1).find(_t_str2)!=std::string::npos   || (_t_str2).find(_t_str1)!=std::string::npos )  )

bool isSubCheckPass(std::string srcClpp, VehicleLogo* logo)
{
    if ( IS_STRING_CONTIAN(srcClpp ,logo->name_ENG ) ) return true ;
    if ( IS_STRING_CONTIAN(srcClpp ,logo->name_CHS ) ) return true ;
    for (unsigned int j = 0; j < logo->TypeList.size(); ++j)
    {
        VehicleType* ptype=&logo->TypeList[j] ;
      //  printf("=={%s ,%s},\n",ptype->name_ENG.c_str(), ptype->name_CHS.c_str());
        if ( IS_STRING_CONTIAN(srcClpp ,ptype->name_CHS ) ) return true ;
        if ( IS_STRING_CONTIAN(srcClpp ,ptype->name_ENG ) ) return true ;
    }
    return  false ;
}

bool  checkIsPass(std::string srcClpp, std::string outputname)
{
    if( (outputname.size() == 0)  || ( srcClpp.size() == 0 )   )
        return false ;

    if(srcClpp.find("牌")!=std::string::npos)
    {
        srcClpp = srcClpp.substr(0,srcClpp.size()-strlen("牌"));
    }
    if ( IS_STRING_CONTIAN(srcClpp ,outputname ) ) return true ;
   // std::cout<< srcClpp << "--" << outputname<< std::endl ;
    unsigned int  i = 0 ;
    VehicleLogo* logo = NULL ;
    for (   ; i < logo_list.size(); i++ )
    {
        logo= &logo_list[i] ;
        //printf("{\"%s\",\"%s\"},\n", logo->name_ENG.c_str(),logo->name_CHS.c_str() );
        if (logo->name_ENG == outputname || logo->name_CHS == outputname )
        {
            break;
        }
        logo = NULL ;
    }

    if( logo == NULL){
        //直接比对没找到 进行模糊比对
        for (   i = 0 ; i < logo_list.size(); i++ )
        {
            logo= &logo_list[i] ;
            //if (logo->name_ENG == outputname || logo->name_CHS == outputname )
            if(IS_STRING_CONTIAN(logo->name_CHS, outputname) )
            {
               //************** printf("logo->name_ENG:%s ,outputname:%s \n",logo->name_CHS.c_str() ,outputname.c_str() );
                if( isSubCheckPass( srcClpp,   logo) ){
                    return true ;
                }
            }
        }
    }else{
        //直接比对 进行子项查找
        return isSubCheckPass( srcClpp,   logo);
    }
    return false ;
}




///////////////////////////////以下用于桩测试 请勿删除/////////////////////////////////////////

#if 0
void test_print();
bool test_case() ;

int main ()
{
    initLogoList();
    test_case();
}

bool test_case()
{
    typedef struct {
        string  srcname;
        string  dstname;
    }LogoName;

    {
        printf("test------------true------------\n");
        LogoName  strlog[]={
            {"长安牌","铃木"},
            {"桑塔纳牌","大众"},
            {"福克斯牌","福特"},
            {"依维柯牌","依维柯"},
            {"奇瑞牌","奇瑞"},
            {"金杯牌","金杯"},
            {"大众汽车牌","大众"},
        };
        for (int i = 0 ; i < sizeof(strlog)/sizeof(LogoName) ; i++ )
        {
            std::cout<<  strlog[i].dstname <<":"<<checkIsPass(  strlog[i].srcname,   strlog[i].dstname)  <<std::endl;
        }
    }

    {
        printf("test------------false----------------\n");
        LogoName  strlog[]={
            {"长安牌","大众"},
            {"桑塔纳牌","斯柯达"},
            {"福克斯牌","金杯"},
            {"长城牌","斯柯达"},
            {"依维柯牌","斯柯达"},
            {"奇瑞牌","金杯"},
            {"金杯牌","大众"},
            {"大众汽车牌","长安"},
        };
        for (int i = 0 ; i < sizeof(strlog)/sizeof(LogoName) ; i++ )
        {
            std::cout<<  strlog[i].dstname << ":"<< checkIsPass(  strlog[i].srcname,   strlog[i].dstname)  <<std::endl;
        }
    }
}

void test_print()
{
    initLogoList();
    printf("======================%d\n",logo_list.size() );
    int num = 0 ;
    for (int i =0 ; i < logo_list.size(); i++ )
    {
        VehicleLogo* logo= &logo_list[i] ;
      //  printf("+++{%s ,%s}++++\n", logo->name_CHS.c_str() , logo->name_ENG.c_str());
      //  printf("-----------------------------------\n");
        printf("\n");
        if(logo->name_ENG.size() > 0)
        {
            printf("{\"%s\",\"%s\"},\n", logo->name_ENG.c_str(),logo->name_CHS.c_str() );
       //     mchebiao[logo->name_ENG] = logo->name_CHS ;
        }
        num +=logo->TypeList.size()+1;
        for (int j = 0; j < logo->TypeList.size(); ++j)
        {
            VehicleType* ptype=&logo->TypeList[j] ;
           // printf("{%s ,%s},\n",ptype->name_ENG.c_str(), ptype->name_CHS.c_str());

            if((ptype->name_ENG).size() > 0)
            {
               // mchebiao[ptype->name_ENG] = logo->name_CHS ;
                printf("{\"%s\",\"%s\"},\n",ptype->name_ENG.c_str(),logo->name_CHS.c_str());
            }
            if(ptype->name_CHS.size() > 0)
            {
               // mchebiao[ptype->name_CHS] = logo->name_CHS ;
                printf("{\"%s\",\"%s\"},\n",ptype->name_CHS.c_str(), logo->name_CHS.c_str());
            }
        }
    }
}
#endif
