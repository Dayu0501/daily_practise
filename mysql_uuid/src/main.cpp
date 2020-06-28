#include "_c_dbTask_sqlOper.h"
#include "baseTool.h"
#include <iostream>
#include <unistd.h>

#include "DB_tools.h"

using namespace std;

int main(int argc, char *argv[]) {

    DB_PARAM dbParam;
    dbParam.strDbName = "db_test";
    dbParam.strHost = "192.168.20.71";
    dbParam.port = 3306;
    dbParam.strUserName = "root";
    dbParam.strPassword = "em-data-9527";

    DB_tools dbToolsIns;

    dbToolsIns.DB_conn(dbParam, true);

    _c_dbTaskSqlOper operIns = _c_dbTaskSqlOper::getInstance();

    operIns.executeCreatDb(DB_MYSQL, &dbParam);

    std::string strCreateTab = "CREATE TABLE `vehicle_info` (\
   `UUID` varchar(32) DEFAULT NULL COMMENT 'UUID',\
   `liuShuiHao` varchar(32) DEFAULT NULL COMMENT '流水号',\
   `jianYanJiGouBianHao` varchar(32) DEFAULT NULL COMMENT '检验机构编号',\
   `jianYanLeiBie` varchar(32) DEFAULT NULL COMMENT '检验类别',\
   `haoPaiZhongLei` varchar(32) DEFAULT NULL COMMENT '号牌种类',\
   `chePaiHao` varchar(32) DEFAULT NULL COMMENT '号牌号码',\
   `cheJiaHao` varchar(32) DEFAULT NULL COMMENT '车辆识别代号',\
   `shiYongRen` varchar(32) DEFAULT NULL COMMENT '使用人',\
   `shouJiHaoMa` varchar(32) DEFAULT NULL COMMENT '手机号码',\
   `shengXiaoRiQi` varchar(32) DEFAULT NULL COMMENT '保险生效日期',\
   `zhongZhiRiQi` varchar(32) DEFAULT NULL COMMENT '保险终止日期',\
   `cheLiangLeiXing` varchar(32) DEFAULT NULL COMMENT '车辆类型',\
   `shiYongXingZhi` varchar(32) DEFAULT NULL COMMENT '使用性质',\
   `zhengBeiZhiLiang` varchar(32) DEFAULT NULL COMMENT '整备质量',\
   `jianYanKaiShiShiJian` varchar(32) DEFAULT NULL COMMENT '检验开始时间',\
   `jianYanJieShuShiJian` varchar(32) DEFAULT NULL COMMENT '检验结束时间',\
   `faDongJiHao` varchar(32) DEFAULT NULL COMMENT '发动机/电动机号码',\
   `cheLiangPinPai` varchar(32) DEFAULT NULL COMMENT '车辆品牌',\
   `cheLiangXingHao` varchar(32) DEFAULT NULL COMMENT '车辆型号',\
   `chuCiDengJiRiQi` varchar(32) DEFAULT NULL COMMENT '初次登记日期',\
   `zhiZaoRiQi` varchar(32) DEFAULT NULL COMMENT '出厂日期',\
   `cheLiangWaiGuanJianYanYuan` varchar(32) DEFAULT NULL COMMENT '车辆外观检验员',\
   `xingShiZhengXinBianHao` varchar(32) DEFAULT NULL COMMENT '行驶证编号',\
   `faZhengRiQi` varchar(32) DEFAULT NULL COMMENT '行驶证发证日期',\
   `ranLiangZhongLei` varchar(32) DEFAULT NULL COMMENT '燃料种类',\
   `xuYaoDuiBiZhaoPianZongShu` varchar(32) DEFAULT NULL COMMENT '需要对比照片总数',\
   `xuYaoDuiBiShiPinZongShu` varchar(32) DEFAULT NULL COMMENT '需要对比视频总数',\
   `duiBiBuHeGeShu` varchar(32) DEFAULT NULL COMMENT '对比不合格数',\
   `cheLiangYanSe` varchar(32) DEFAULT NULL COMMENT '车辆颜色',\
   `paiLiang` varchar(32) DEFAULT NULL COMMENT '排量',\
   `gongLv` varchar(32) DEFAULT NULL COMMENT '功率',\
   `zhuanXiangXingShi` varchar(32) DEFAULT NULL COMMENT '转向形式',\
   `cheWaiKuoChang` varchar(32) DEFAULT NULL COMMENT '车外廓长',\
   `cheWaiKuoKuan` varchar(32) DEFAULT NULL COMMENT '车外廓宽',\
   `cheWaiKuoGao` varchar(32) DEFAULT NULL COMMENT '车外廓高',\
   `huoXiangNeiBuChangDu` varchar(32) DEFAULT NULL COMMENT '货箱内部长度',\
   `huoXiangNeiBuKuanDu` varchar(32) DEFAULT NULL COMMENT '货箱内部宽度',\
   `huoXiangNeiBuGaoDu` varchar(32) DEFAULT NULL COMMENT '货箱内部高度',\
   `gangBanTanPianShu` varchar(32) DEFAULT NULL COMMENT '钢板弹簧片数'\
   ) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

    operIns.executeSql(DB_MYSQL, &dbParam, strCreateTab, false);

    dbToolsIns.DB_execSql("START TRANSACTION");

    cout << "please input insert num : ";
    int i;
    cin >> i;
    while (--i) {
        string strInsert = "INSERT INTO vehicle_info VALUES (\"";
        strInsert += baseTool::newGuid();
        strInsert += "\", \"";
        strInsert += baseTool::newGuid();
        strInsert += "\", \"ABCDE\", \"A\", 'BB', '888888', '666666', 'laowang', "
                     "'1388888888', '" + baseTool::getCurTime() + "', '2010-03-19', ";
        strInsert += "'YY', 'BBB', '1630', '2010-03-15', '2010-03-18', '9999999', "
                     "'mashaladi', '8888', '2010-03-18', '2010-03-18', ";
        strInsert +=
                "'laochang', '9999999', '2010-03-15', 'A', '8', '8', '9', 'A', "
                "'33', '180', 'aaa', 'bbb', 'ccc', 'ddd', ";
        strInsert += "'150', '180', '190', '33');";

        dbToolsIns.DB_execSql(strInsert);
    }

    dbToolsIns.DB_execSql("COMMIT");

    cout << "exe end !" << endl;

    // string strSql = "DROP PROCEDURE IF EXISTS pro_AddColumn; CREATE PROCEDURE testDb() BEGIN SELECT 'HELLO WORLD !'";
    // strSql += "END; CALL testDb;";

    // dbToolsIns.returnExecSql(strSql);

    // cout << "ok or no ok !" << endl;

    // sleep(11);

    // dbToolsIns.getResult();

    string createTabSql =
            string("create table if not exists hwg_data_20151110 (") + "id int primary key auto_increment," +
            "dev_type smallint unsigned not null, dev_id	 smallint unsigned not null, data_time datetime not null, data_time_ms smallint unsigned, \
	data_time_us smallint unsigned, yc_ac_ia smallint unsigned,	yc_ac_ic smallint unsigned,	yc_ac_in smallint unsigned, \
	yx1 smallint unsigned, yx2 smallint unsigned, freq smallint unsigned,	tmp1 smallint unsigned, tmp2 smallint unsigned, tmp3 smallint unsigned \
    );";

    dbToolsIns.DB_execSql(createTabSql);
    cout << "1111" << endl;

    string str2 = "drop procedure if exists proc_get_newest_yc; delimiter //";
    str2 += "create procedure proc_get_newest_yc(OUT myval float) begin \
	declare mydate varchar(8); \
	declare date_str varchar(17); \ 
    declare sqlstr varchar(128); \
	select date_format(current_date(), '%Y%m%d') into mydate; \
	select concat('hwg_data_',mydate) into date_str; \
    set @sqlstr = concat('', 'select yc_ac_ia from '); \
	set @sqlstr = concat(@sqlstr,date_str); \
    set @sqlstr = concat(@sqlstr,''); \
    select @sqlstr into sqlstr; \
    prepare sqlstr from @sqlstr; \
    execute sqlstr; \
    end;";

    dbToolsIns.DB_execSql(str2);
    cout << "2222" << endl;

    dbToolsIns.data_dispatcher_init();

    return 0;
}