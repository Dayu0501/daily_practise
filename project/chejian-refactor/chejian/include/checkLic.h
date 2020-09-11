
#ifndef _CHECKLIC_


/*检测显卡
//输入conf_name:lic文件路径名称
//返回值：	0：lic文件uuid比对成功
			1:显卡驱动等出错或未安装显卡
			2：查询显卡数量失败
			3：没有找到显卡设备
			4：获取到显卡uuid失败
			5：未找到lic文件
			6：lic文件读取失败
			7：lic文件开始年份过期
			8：lic文件开始月份过期
			9：lic文件开始日过期
			10：lic文件结束年份过期
			11：lic文件结束月份过期
			12：lic文件结束日过期
			13：lic文件uuid比对失败
*/
int check_licence(std::string conf_name,std::string& startDate,std::string& endDate);

#endif


