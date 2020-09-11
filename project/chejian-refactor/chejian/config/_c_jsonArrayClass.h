#ifndef _C_JSONARRAYCLASS_H
#define _C_JSONARRAYCLASS_H
#include <vector>
#include <list>
#include "base/json/json.h"
#include "base/_c_object.h"

//表示JSON集合中的一个单项
class _c_jsonArrayBaseItem
{
public:
    _c_jsonArrayBaseItem(std::string name, std::string value)
    {
        _name = name;
        _value = value;
    }

    std::string _name;
    std::string _value;
};

//表示JSON集合
class _c_jsonArrayBaseSet
{
public:
    ~_c_jsonArrayBaseSet()
    {
        if (_isNeedFree)
        {
            for (unsigned int i = 0; i < _arrayItem.size(); i++) {
                _c_jsonArrayBaseItem *p = _arrayItem[i];
                delete p;
            }
            _arrayItem.clear();
        }
    }

    std::vector<_c_jsonArrayBaseItem *> *getSetPtr()
    {
        return &_arrayItem;
    }

    void addBaseItem(_c_jsonArrayBaseItem *pItem)
    {
        _arrayItem.push_back(pItem);
    }

public:
    bool _isNeedFree = true;//如果不是动态分配的,则不需要释放,最好统一动态分配
    std::vector<_c_jsonArrayBaseItem *> _arrayItem;
};

//表示JSON集合组成的数组(非纯数组) 只支持字符串类型
class _c_jsonSetArray {
public:
    Json::Value convertToJson();
    void addSetItem(_c_jsonArrayBaseSet *pSet);
    void deleteSetItemByBaseItem(_c_jsonArrayBaseItem *pItem);
    void analyseJsonToArray(Json::Value &jsonNode);
    void initNodeName(std::string name) {_jsonNodeName = name;}
    void initMemberNameVectror(std::vector<std::string> &vector);
    void jsonArrayRelease();
    void printfForEach();

public:
    std::list<_c_jsonArrayBaseSet *> _arrayList;
    std::vector<std::string> _memberNameVectror;

    std::string _jsonNodeName;
};

#endif// _C_JSONARRAYCLASS_H
