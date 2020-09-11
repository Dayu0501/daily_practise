#include "_c_algTaskResponse.h"
#include "base/baseTool.h"

std::string _c_algTask_Reponse::getAlgResultByCodeName(std::string codeName)
{
    for (unsigned int i = 0; i < memberVector.size(); i++) {
        if(memberVector[i].codeName == codeName)
        {
            return *memberVector[i].value;
        }
    }
    return " ";
}

void _c_algTask_Reponse::reponseInit()
{
    loadUuid();
    tableName = "reponse_err_info";
    memberVector.push_back({"UUID", "UUID", &uuid, "uuid", DBOPTION_DEFAULT});
    memberVector.push_back({"algTaskKeyCode", "algTaskKeyCode", &algTaskKeyCode, "算法任务guid", DBOPTION_DEFAULT});
    memberVector.push_back({"algReturn", "algReturn", &algReturn, "算法逻辑判定结果", DBOPTION_DEFAULT});
}

_c_algTask_Reponse::_c_algTask_Reponse(std::string redisStr) {
	reponseInit();
	Json::Value root;
	Json::Reader reader;
	if (reader.parse(redisStr, root, false)) {
		if (!root.isObject()) {
			printf("算法回复json有误\n");

			return;
		}

		algTaskKeyCode = root["algTaskKeyCode"].asString();
		Json::Value algReturnObj = root["algReturn"];   //此处应该加上该字段有无的处理，不然容易导致程序crash
		if (!algReturnObj.isObject()) {
			printf("算法回复json有误, algReturn 是非obj类型\n");

			return;
		}
		algReturn = algReturnObj["status"].asString();  //算法逻辑判定结果
		//LOG(ALG,INFO,"redis response json[%s]:[%s]\n",algTaskKeyCode.c_str(),redisStr.c_str());

		Json::Value subRoot = root["returnResultMemberList"];
		if (!subRoot.empty()) {
			int index{0};
			std::string desKey = handleSpecilAlgIdS(subRoot);
			if (!desKey.empty())
				printf("TTTTTTTTTT desKey is %s \n", desKey.c_str());

			for (auto const &item : subRoot) {
				if (item.isObject() && !item.empty()) {
					Json::Value::Members members = item.getMemberNames(); //获得所有key值
					for (const auto &strKey : members) {
						if (strKey != desKey && !desKey.empty()) continue;

						Json::Value resArray = item[strKey];
						if (!resArray.isArray()) {
							printf("算法回复json有误, id %s 不是array!\n", strKey.c_str());

							return;
						}

						for (const auto &subItem : resArray) {
							std::string name = subItem["name"].asString();
							std::string value = subItem["value"].asString();

							if (!findItem(name))
								setMember(index++, name, name, value);
						}
					}
				}
			}
		}

		Json::Value subOther = root["other"];
		if (!subOther.empty()) {
			algRunTime = std::to_string(subOther["AlgObjTime"].asDouble());
			algProcTime = std::to_string(subOther["AlgProcTime"].asDouble());
			photoDownTime = std::to_string(subOther["AlgPicParseTime"].asDouble());
			processIp = subOther["AlgIp"].asString();
		}
		return;
	} else {
		algReturn = "-1";
		printf("算法回复解析有误\n");

		return;
	}
}

std::string _c_algTask_Reponse::handleSpecilAlgIdS(Json::Value obj) {
	for (auto const &item : obj) {
		if (item.isObject() && !item.empty()) {
			Json::Value::Members members = item.getMemberNames();
			for (const auto &strKey : members) {
				if (strKey == TABLENAMEAPI) {
					Json::Value resArray = item[strKey];
					if (!resArray.isArray()) {
						printf("算法回复json有误, id %s 不是array!\n", strKey.c_str());

						return "";
					}

					for (const auto &subItem : resArray) {
						std::string name = subItem["name"].asString();
						std::string value = subItem["value"].asString();

						//printf("%s name is %s\n", __PRETTY_FUNCTION__, name.c_str());
						//printf("%s value is %s\n", __PRETTY_FUNCTION__, value.c_str());
						if (name == TABLENAME && !value.empty())
							return _tableNameAndAlgIdMap[value];
						else if (name == TABLENAME && value.empty())
							return JIAOQIANGXIAOAPI;
					}
				}
			}
		}
	}

	return "";
}

bool _c_algTask_Reponse::setMember(unsigned int index, std::string soapName, std::string codeName, std::string value)
{
    //判断序号是否超出最大值
    if(index < MAX_REPONSE_MEMBER)
    {
        //将内容放到index对应坑位
        __Reponse[index] = value;
        //创建object实体
        objectMember obj = {soapName,codeName, &__Reponse[index]," ",DBOPTION_NODB};
        //插入memlist中
        memberVector.push_back(obj);
        return true;
    }
    return false;
}

bool _c_algTask_Reponse::findItem(const std::string & soapName) {
	for (const auto & item : memberVector) {
		if (item.soapName == soapName) return true;
	}

	return false;
}

std::vector<objectMember> *_c_algTask_Reponse::getResultList()
{
    return &memberVector;
}

void _c_algTask_Reponse::beforDbWork()
{
    memberVector.clear();
    reponseInit();
}


