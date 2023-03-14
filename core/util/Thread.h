#pragma once

#include <thread>
#include <functional>
#include <condition_variable>
#include <queue>
#include <atomic>

namespace NDIReceiver
{

class Thread
{
public:
            Thread          ();
    virtual ~Thread         ();

    void    executeAsync    (std::function<void()> func);
    void    stop            ();


private:
    void    threadFunc();

    std::thread                             worker;
    std::condition_variable                 condition;
    std::mutex                              mutex;
    std::atomic<bool>                       stopped;

    std::queue<std::function<void()>>       messages;
};

}
