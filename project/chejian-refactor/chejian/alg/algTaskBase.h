#ifndef _ALGTASKEBASE_H
#define _ALGTASKEBASE_H
#include "base/baseInc.h"

enum E_JG {
    PASS = 1,               /* 通过 */
    UNABLE_IDENTIFY = 4,    /* 无法比对,需人工 */
    NOT_PASS = 5,           /* 不通过 */
};

enum E_ZZJG {

    SOFT_NOTPROCESS = -1,       //-1：软件没有审核。使用性质，车辆类型等不在软件处理范围内。照片没有经过算法处理。
    SOFT_NOTPASS = 0,           //0：软件审核不通过。照片数量不全，或者任何一个照片判定为不通过。
    SOFT_PASS = 1,              //1：软件审核通过。所有照片都经过算法处理，并且都通过。
    MAN_PASS = 2,               //2：人工审核通过
    MAN_NOTPASS = 3,            //3：人工审核不通过
    SOFT_ERR = 4,               //4：软件审核未知。所有照片都经过算法处理，出现了判定为未知的照片，并且没有出现判定为不通过的照片。
};

enum PicType//
{
    e0111 = 1,    //车辆左前方斜视45度照片 0111
    e0112 = 2,    //车辆右后方斜视45度照片 0112
    e0113 = 3,        //车辆识别照片（车架号） 0113
    e0167 = 4,            //车辆正前方牌照片 0176
    e0168 = 5,
    e0175 = 6,
    e0201 = 7,
    e0202 = 8,
    e0203 = 9,
    e0204 = 10,
    e0288 = 11,
    e0209 = 12,
    e0297 = 13,
    e0321 = 14,
    e0352 = 15,
    e0322 = 16,
    e0348 = 17,
    e0344 = 18,
    e0342 = 19,
    e0351 = 20,
    e0323 = 21,
    e0287 = 22,
    e0292 = 23,
    e0136 = 24,
    e0156 = 25,
    e0157 = 26,
    e0206 = 27,
    e0205 = 28,
    e0119 = 29,
    e0166 = 30,
    e0115 = 31,
//    e0114 = 32,
    e0208 = 33,
    e0186 = 37,
    e0216 = 38,
    e0218 = 39,
    e0219 = 40,
    e0158 = 41,
    e0144 = 42,
	e0159 = 43,
//    e0353 = 43,
    e0211 = 44,
    e0212 = 45,
    e0213 = 46,
    e0214 = 47,
    e0215 = 48,
    e0217 = 49,
    e0220 = 50,
    e0221 = 51,
    e0222 = 52,
    e0223 = 53,
    e0120 = 54,
    e0121 = 55,
    e0122 = 56,
    e0224 = 57,
    e0123 = 58,
    e0225 = 59,
    e0354 = 60,
    e0226 = 61,
    e0227 = 62,
    e0228 = 63,     //送检人身份证 正面
    e0296 = 64,     //罚单
    e0260 = 65,     //送检人身份证 背面
    e0286 = 66,     //仪器设备检验表
    e0341 = 67,     //路试制动开始
    e0343 = 68,     //路试制动结束
    e0135 = 69,     //轮胎花纹对比 (前轮)
    e0151 = 70,     //轮胎花纹对比 (后轮)
    e0114 = 71,     //驾驶员可视区玻璃照片(算法没有支持)
    e0360 = 72,      //外廓尺寸自动测量前面
    e0361 = 73,      //外廓尺寸自动测量侧面
    e0362 = 74,      //尾箱改装
    e0324 = 75,      //底盘间隙测量
    e0199 = 76,      //身份证 首页<link>
    e0200 = 77,      //身份证 背面<link>
	e0555 = 80,		 //后续编号从80 开始累加
    e0155 = 81,      //左后轮胎规格型号-照片
    e0160 = 82,      //右后轮胎规格型号-照片
    e0177 = 83,      //核定载客数-照片   算法接口已废除
    e0234 = 84,      //定期检验告知书-照片
    e0140 = 85,      //副制动踏板(教练车)
    e0235 = 86,     //机动车制动检测曲线报告

    eCLZQFXS45DZP_A = 100,        //车辆左前方斜视45度照片档案照片
    eCLSBDHZP_TYM,                //拓印膜照片
    eCLSBDHZP_JLBZM,              //记录表字模照片
    eWQDZP2,                      //尾气单第二张照片
    eNULL,

    eH0111 = 1000,
    eH0112 = 1001,
    eH0113 = 1002,
    eH0002 = 1003,
    eH0003 = 1004,
    eH0004 = 1005,
    eH0005 = 1006,
    eH0006 = 1007,
    eH0007 = 1008,
    eH0008 = 1009,
    eH0009 = 1010,
    eH0001 = 1011,
    eH3020 = 2000,  //左右尾灯照片类型
    e0110 = 2001,
    e0325 = 2002,
    eH0199 = 2003,
    e0213_1 = 2102,  //气瓶使用证1
    e0258 = 2103,    //气瓶使用证2
    eH0186 = 2104,
    evideo = 10000,
};

enum AlgType//algID
{
    alg0111 = 1,    //车辆左前方斜视45度照片 0111
    alg0112 = 2,    //车辆右后方斜视45度照片 0112
    alg0113 = 3,        //车辆识别照片（车架号） 0113
    alg0167 = 4,            //车辆正前方牌照片 0176
    alg0168 = 5,
    alg0175 = 6,
    alg0201 = 7,
    alg0202 = 8,
    alg0203 = 9,
    alg0204 = 10,
    alg0288 = 11,
    alg0209 = 12,
    //alg0297 = 13,
    alg0321 = 14,
    alg0352 = 15,
    alg0322 = 16,
    alg0348 = 17,
    alg0344 = 18,
    alg0342 = 19,
    alg0351 = 20,
    alg0323 = 21,
    alg0287 = 22,
    alg0292 = 23,
    alg0136 = 24,
    alg0156 = 25,
    alg0157 = 26,
    alg0206 = 27,
    alg0297 = 28,
    alg0119 = 29,
    alg0166 = 30,
    alg0115 = 31,
//  alg0114 = 32,
    alg0208 = 33,

    alg0111_dache = 34,
    alg0112_dache = 35,
    alg0115_dache = 36,

    alg0186 = 37,
    alg0216 = 38,
    alg0218 = 39,
    alg0219 = 40,
    alg0158 = 41,
    alg0144 = 42,
	alg0159 = 43,
//    alg0353 = 43,
    alg0211 = 44,
    alg0212 = 45,
    alg0213 = 46,
    alg0214 = 47,
    alg0215 = 48,
    alg0217 = 49,
    alg0220 = 50,
    alg0221 = 51,
    alg0222 = 52,
    alg0223 = 53,
    alg0120 = 54,
    alg0121 = 55,
    alg0122 = 56,
    alg0224 = 57,
    alg0123 = 58,
    alg0225 = 59,
    alg0354 = 60,
    alg0226 = 61,
    alg0227 = 62,   //已废除
    alg0228 = 63,   //送检人身份证
    alg0296 = 64,   //罚单
    alg0260 = 65,   //送检人身份证
    alg0286 = 66,   //仪器设备检验表
    alg0135 = 69,     //轮胎花纹对比 (前轮)
    alg0151 = 70,     //轮胎花纹对比 (后轮)
    alg0114 = 71,     //驾驶员可视区玻璃照片
    alg0362 = 72,     //苏州：尾箱改装
    alg0324 = 73,     //底盘间隙测量
    alg0325 = 74,
	alg0258 = 75,  //气瓶使用证1和气瓶使用证2
	alg0555 = 80,	  //后续编号从80 开始累加

    algCLZQFXS45DZP_A = 100,        //车辆左前方斜视45度照片档案照片
    algCLSBDHZP_TYM,                //拓印膜照片
    algCLSBDHZP_JLBZM,              //记录表字模照片
    algWQDZP2,                      //尾气单第二张照片
    algNULL,
	algShuiYinRiQi = 998,           //水印日期接口
    algTypeIdentify = 999,          //类型识别接口
	alg0177 = 20004,
};

enum VideoProcessState {
    videoProcessUnInit = 0,         //默认不是视频的处理状态
    videoProcessSendToRedis = 1,
    videoProcessRecvFromRedis = 2,
};

class algItem {
public:
    std::string code;           //处理类型识别code
    bool isOpen;                //接口是否启用(参数配置)
    std::string name;           //处理算法名称
    PicType type;               //处理类型唯一ID，不可重复
    bool needCheck;             //是否需要检测
    bool isTenYears;            //十年车检测项开关
    bool subAlgClass;           //使用派生类私有参数类
    bool isMust;                //是否是必须检测项
    std::string link;           //关联项
    std::vector<std::string> examplePics;    //示例照片
};

typedef struct _ALG_PARM_MEMBER
{
    std::string inData;     //输入数据
    std::string OutData;    //输出数据
    bool result;            //返回结果
}ALG_PARM_MEMBER, *PALG_PARM_MEMBER;

typedef struct _ALG_PARAM_LINK
{
    int linkType;           // -1_无, 0_&&, 1_||
    std::string linkName;   //关联数据名称
}ALG_PARAM_LINK,*PALG_PARAM_LINK;

//std::vector<ALG_PARAM_LINK> linkVector = {};
typedef struct _ALG_PARM_CONFIG
{
    bool isOpen;                            //是否使用该字段
    bool descOpen;                          //是否使用参数文件中的desc
    std::vector<ALG_PARAM_LINK> linkVector; //关联器
    E_JG errLevel;                          //错误严重等级等级

}ALG_PARM_CONFIG, *PALG_PARM_CONFIG;

#define CONFIG_DEFAULT {true, true, {}, NOT_PASS}
#define CONFIG_DEFAULT_UNABLE {true, true, {}, UNABLE_IDENTIFY}
#define CONFIG_NOCHECK {false, true, {}, NOT_PASS}
#define CONFIG_NOCHECK_UNABLE {false, true, {}, UNABLE_IDENTIFY}
#define ALG_PARAM_DEFAULT {"", "", false}

class memberItem {
public:
    std::string name;           //对应字段名称
    std::string desc;           //描述
    PALG_PARM_MEMBER value;     //值地址
    bool output;                //是否输出
    ALG_PARM_CONFIG config;     //参数配置
};

class resultMemberList {
public:
    std::string name;
    std::vector<memberItem> *pVector;
};

#endif // _ALGTASKEBASE_H



