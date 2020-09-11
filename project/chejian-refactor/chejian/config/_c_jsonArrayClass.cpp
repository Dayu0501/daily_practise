#include "_c_jsonArrayClass.h"
#include "base/baseTool.h"

Json::Value _c_jsonSetArray::convertToJson()
{
    Json::Value root;
    for (auto iter = _arrayList.begin(); iter != _arrayList.end(); iter++)
    {
        Json::Value subRoot;
        _c_jsonArrayBaseSet *pArray = (*iter);
        std::vector<_c_jsonArrayBaseItem *> *pItems = pArray->getSetPtr();
        for (unsigned int j = 0; j < pItems->size(); j++)
        {
            subRoot[(*pItems)[j]->_name] = (*pItems)[j]->_value;
        }

        root.append(subRoot);
    }
    return root;
}

void _c_jsonSetArray::analyseJsonToArray(Json::Value &root)
{
    for (unsigned int i = 0; i < root.size(); i++)
    {
        Json::Value subRoot = root[i];
//        printf("JsonArray %s\n", subRoot.toStyledString().c_str());
        _c_jsonArrayBaseSet *pSet = new _c_jsonArrayBaseSet;
        for (unsigned int j = 0; j < _memberNameVectror.size(); j++)
        {
//            printf("memberName %s\n", _memberNameVectror[j].c_str());
            if (!subRoot[_memberNameVectror[j]].empty())
            {
                std::string value = subRoot[_memberNameVectror[j]].asString();
                _c_jsonArrayBaseItem *pItem = new _c_jsonArrayBaseItem(_memberNameVectror[j], value);
                pSet->addBaseItem(pItem);
            }
        }
        addSetItem(pSet);
    }
}

void _c_jsonSetArray::addSetItem(_c_jsonArrayBaseSet *pSet)
{
    _arrayList.push_back(pSet);
}

void _c_jsonSetArray::jsonArrayRelease()
{
    for (auto iter = _arrayList.begin(); iter != _arrayList.end();)
    {
        _c_jsonArrayBaseSet *pSet = (*iter);
        _arrayList.erase(iter++);
        delete pSet;
    }
    _arrayList.clear();
}

void _c_jsonSetArray::initMemberNameVectror(std::vector<std::string> &vector)
{
    _memberNameVectror.assign(vector.begin(), vector.end());
}

void _c_jsonSetArray::printfForEach()
{
    for (auto iter = _arrayList.begin(); iter != _arrayList.end(); iter++)
    {
        _c_jsonArrayBaseSet *pArray = (*iter);
        std::vector<_c_jsonArrayBaseItem *> *pItems = pArray->getSetPtr();
        for (unsigned int j = 0; j < pItems->size(); j++)
        {
            printf("%s:[%s]\n", (*pItems)[j]->_name.c_str(), (*pItems)[j]->_value.c_str());
        }
    }
}

void _c_jsonSetArray::deleteSetItemByBaseItem(_c_jsonArrayBaseItem *pItem)
{
    bool isFound = false;
    for (auto iter = _arrayList.begin(); iter != _arrayList.end(); iter++)
    {
        _c_jsonArrayBaseSet *pSet = (*iter);
        for (unsigned int i = 0; i < pSet->_arrayItem.size(); i++)
        {
            _c_jsonArrayBaseItem *tmp = pSet->_arrayItem[i];
            if (tmp->_name == pItem->_name)
            {
                if (tmp->_value == pItem->_value)
                {
                    isFound = true;
                    break;
                }
            }
        }

        if (isFound)
        {
            _arrayList.erase(iter);
            delete pSet;
            break;
        }
    }
}
