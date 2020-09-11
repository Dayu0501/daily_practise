#ifndef BLOCKVECTOR_H
#define BLOCKVECTOR_H
#include <condition_variable>
#include <assert.h>
#include "_c_session.h"

#define UNUSED(x) (void)x

#pragma once
class NoBlockSessionVector
{
public:
    NoBlockSessionVector() : _mutex(), _vector()
    {

    }

    void Put(_c_session *task)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _vector.push_back(task);
    }

    size_t Size() const
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _vector.size();
    }

    Json::Value getWorkSessionStateJson()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _sessionVectorRoot;
    }

    _c_session *getWorkEndSession()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        getWorkSessionState();
        auto pSession = _vector.begin() ;
        while (pSession != _vector.end())
        {
            if ((*pSession)->isEndWork()) //判断所有的task都结束了，如果所有的task结束，就认为session结束了把session返回
            {
                _c_session *pReturn = (*pSession);
                _vector.erase(pSession);
                return pReturn;
            }
            else
            {
                pSession++;
            }
        }
        return NULL;
    }

private:
    mutable std::mutex _mutex;
    std::vector<_c_session *> _vector;
    Json::Value _sessionVectorRoot;

    void getWorkSessionState()
    {
        _sessionVectorRoot.clear();
        for (unsigned int i = 0; i < _vector.size(); i++)
        {
            _sessionVectorRoot.append(_vector[i]->getSessionJson());
        }
    }

};


#endif // BLOCKVECTOR_H
