#ifndef _C_DEVICE_H
#define _C_DEVICE_H
#include <condition_variable>
#include "baseInc.h"
#include <assert.h>
#include "base/json/json.h"


#define UNUSED(x) (void)x

#pragma once

class _c_device{
public:
    std::string deviceMac = "NULL";
    Json::Value root;
    _c_device(std::string redisStr)
    {
        Json::Reader reader;
        if (reader.parse(redisStr, root, false))
        {
            if(!root.isObject())
            {
                printf("算法回复json有误\n");
                return;
            }
            deviceMac = root["deviceMac"].asString();
            return;
        }
    }
};


class NoBlockDeviceVector
{
public:
    NoBlockDeviceVector() : _mutex(), _vector()
    {

    }

    void Put(_c_device *device)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        for (unsigned int i = 0; i < _vector.size(); i++) {
             if(_vector[i]->deviceMac == device->deviceMac)
             {
                _vector[i]->root = device->root;
                delete device;
                return;
             }
        }
        _vector.push_back(device);
    }

    size_t Size() const
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _vector.size();
    }

    Json::Value getDeviceStateJson()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        getDeviceState();
        return _deviceVectorRoot;
    }

private:
    mutable std::mutex _mutex;
    std::vector<_c_device *> _vector;
    Json::Value _deviceVectorRoot;

    void getDeviceState()
    {
        _deviceVectorRoot.clear();
        for (unsigned int i = 0; i < _vector.size(); i++)
        {
            _deviceVectorRoot.append(_vector[i]->root);
        }
    }

};

#endif // _C_DEVICE_H
