#ifndef _C_ALGBASECLASS_H
#define _C_ALGBASECLASS_H
#include "base/_c_object.h"
#include "base/baseInc.h"
#include "../algTaskBase.h"

class _c_algTask;

#define  GetPhotoAttrValue(_attr_name)  ((_attr_name) == "无数据" ? "None":_attr_name)
#define  GetPhotoAttrValueDateFormting(_attr_name)  ((_attr_name) == "无数据" ? "None":baseTool::formatingDate(_attr_name) )
#define  GetPhotoAttrValueFileNameFormating(_attr_name)  ((_attr_name) == "无数据" ? "None":baseTool::formatFileName(_attr_name) )
#define  GetPhotoAttrValueFileNameLunTaiFormating(_attr_name)  ((_attr_name) == "无数据" ? "None":baseTool::formatFileNameLunTai(_attr_name))

class _c_algBaseClass{
public:
    PicType mainPhotoType;
    PicType subPhotoType;
    std::vector<memberItem> *pInMemberList;     //参数成员列表指针 如果不是派生类该指针为NULL
    std::vector<memberItem> *pResultMemberList; //输出成员列表指针 如果不是派生类该指针为NULL
    std::vector<resultMemberList> inListVector; //的输入参数列表集合，因为分为摩托，大车，小车，所以这是包含了大车，小车，摩托的
    std::vector<resultMemberList> resultListVector; //存放返回结果的list

    std::vector<objectMember *> *pAllParamVector;
    std::vector<algItem> *pAllAlgItemVector;
    std::vector<_c_algTask *> *pAlgTaskVector;
    std::vector<_c_object *> *pWangLuoJieKouReturnVector;

    bool isVideo = false;

    virtual ~_c_algBaseClass(){}
    void setBaseParam(CityType cityType,PicType type, std::string algName); //填充参数
    void resetBaseParam(PicType type); //重置参数
    void setAlgType(AlgType type); //重置算法id

    //初始化图片默认名称
    void createPhotoNameByType(std::string algcode);
	//获取入参值
    std::string getObjectItemValueByName(const char *attrName);
    std::string getObjectItemValueFormatByName(const char *attrName);
	//获取输出对象属性结构值
    memberItem* getOutputMemberItem(const char *attrName);
    //关闭其他输出项, 只打印本条错误信息
    bool checkMemberItemAndSetAllUnOutput(const char *attrName,bool isMust =false, std::vector<memberItem>* pResult = NULL);

    void initAlgClass();
    virtual bool seekMemberListPointer(){return true;}
    virtual bool subClassLoadNewResultMember(){return true;}
    virtual void loadAlgClassConfig();
    virtual void setResultConfig(Json::Value root);
    Json::Value getResultMemberListJson();
    void setResultMember(std:: string memberName, memberItem *pResultMember);
    void saveResultConfig();
    virtual Json::Value getInParamJson(std::string keyCode,unsigned int timeOut, bool isVideo, std::string reponseChan);
    void setAllParam(std::vector<objectMember *> *pVector);
    virtual bool InParamEdit(){return true;}
    virtual bool beforLoadResult(){return true;}
    virtual bool LoadResult(std::string redisRet, std::vector<objectMember> *pVector);
    virtual bool beforeResultEdit();
    virtual bool ResultEdit(){return true;}
    virtual bool afterResultEdit(){return true;}
    virtual bool loadExtAlgClass(std::vector<_c_algTask *> *pVector){UNUSED(pVector);return true;}
    virtual void setPhoto(std::string mainPhoto, std::string mainPath, std::string subPhoto, std::string subPath);
    virtual E_JG getResult(std::string *pReason);
    virtual _c_algTask *loadExtAlgTask(){return NULL;}
    virtual std::string getPhotoName(std::string algcode);
    virtual std::string getPhotoBaseName(std::string algcode);
	virtual void setAlgIds();
	bool setInParamEdit();

protected:
	std::vector<AlgType> algIDs;

    CityType _cityType;                          //城市类型
    PicType _type;                               //图片处理类型
    AlgType _algType;                               //算法处理类型
    std::string _algName;                        //算法名称或者说明(暂时无用，后续准备当作输出前缀使用)
    std::string _configRoot = "/opt/vehicle/program/CheJianConfig";
    std::string _mainPhoto = "TDB";
    std::string _subPhoto = "TDB";

    std::string _mainPath = "TDB";
    std::string _subPath = "TDB";
};

#endif // _C_ALGBASECLASS_H
