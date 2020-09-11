#ifndef ThreadPool_H
#define ThreadPool_H

#include <functional>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>
#include <memory>
#include <chrono>
using namespace std::chrono;

class Task
{
public:
    enum InvokeStatus
    {
        INVOKE_WAIT=1,
        INVOKE_BEGIN,
        INVOKE_END
    };
    Task() : runTime_(0.0),createTick_(system_clock::now()),beginRunTick_(system_clock::now()),status_(INVOKE_WAIT){ }
    virtual ~Task(){ }
    void Invoke()
    {
        beginRunTick_=system_clock::now();
        status_=INVOKE_BEGIN;
        system_clock::time_point start=system_clock::now();
        Run();
        runTime_=duration<double, std::milli>(system_clock::now() - start).count();
        status_=INVOKE_END;
    }
    double GetRunTime()
    {
        return runTime_;
    }
    double GetWaitTime()
    {
        if(status_ == INVOKE_WAIT || status_ == INVOKE_BEGIN)
            return duration<double, std::milli>(system_clock::now() - createTick_).count();
        return duration<double, std::milli>(beginRunTick_-createTick_).count();
    }
    InvokeStatus GetStatus()
    {
        return status_;
    }
    virtual void StopRun()=0;
protected:
    virtual void Run()=0;
private:
    double runTime_;
    system_clock::time_point createTick_;
    system_clock::time_point beginRunTick_;
    InvokeStatus status_;
};

class ThreadPool
{
private:
    int threadNum_;
    std::mutex mutex_;
    std::condition_variable notEmpty_;
    std::condition_variable notFull_;
    std::vector<std::thread> threads_;
    std::deque<std::shared_ptr<Task>> queue_;
    unsigned int maxTaskSize_;
    bool running_;
public:
    ThreadPool() = delete;
    ThreadPool(const ThreadPool&) = delete;
    void operator=(const ThreadPool&) = delete;
    ThreadPool(int threadNum,int maxTaskSize): threadNum_(threadNum),maxTaskSize_(maxTaskSize),running_(false)
    { }

    ~ThreadPool()
    {
        if (running_) {
            Stop();
        }
    }

    void SetMaxTaskSize(int maxSize)
    {
        maxTaskSize_ = maxSize;
    }

    void Start()
    {
        running_ = true;
        threads_.reserve(threadNum_);
        for (int i = 0; i<threadNum_; i++) {
            threads_.push_back(std::thread(std::bind(&ThreadPool::ThreadFunc, this)));
        }
    }

    void Stop()
    {
        if (running_)
        {
            {
                std::unique_lock<std::mutex> ul(mutex_);
                running_ = false;
                notEmpty_.notify_all();
                notFull_.notify_all();
            }
            for (auto &iter : threads_) {
                iter.join();
            }
        }
    }

    bool RunTask(std::shared_ptr<Task> t)
    {
        if (threads_.empty()) {
            return false;
        }
        else {
            std::unique_lock<std::mutex> ul(mutex_);
            while (IsFull() && running_) {
                notFull_.wait(ul);
            }
            if(!running_){
                return false;
            }
            queue_.push_back(t);
            notEmpty_.notify_one();
        }
        return true;
    }

private:
    bool IsFull() const
    {
        return maxTaskSize_ > 0 && queue_.size() >= maxTaskSize_;
    }

    std::shared_ptr<Task> Take()
    {
        std::unique_lock<std::mutex> ul(mutex_);
        while (queue_.empty() && running_) {
            notEmpty_.wait(ul);
        }
        if (!queue_.empty()) {
            std::shared_ptr<Task> task = queue_.front();
            queue_.pop_front();
            notFull_.notify_one();
            return task;
        }
        return nullptr;
    }

    void ThreadFunc()
    {
        while (running_)
        {
            std::shared_ptr<Task> task=Take();
            if (task)
                task->Invoke();
        }
    }


};

#endif
