#include "Thread.h"
#include <mutex>

using namespace NDIReceiver;

Thread::Thread() :
stopped     (false),
worker      ([this] { threadFunc(); })
{
}

Thread::~Thread()
{
    stopped = true;
}

void Thread::executeAsync(std::function<void()> func)
{
    std::unique_lock<std::mutex> lock(mutex);
    messages.push(std::move(func));
    condition.notify_one();
}

void Thread::threadFunc()
{
    
    while(!stopped.load())
    {
        std::unique_lock<std::mutex> lock(mutex);
        if (messages.empty())
        {
            condition.wait(lock);

            if (stopped) return;
        }

        auto message = std::move(messages.front());
        messages.pop();
        lock.unlock();

        if (message) message();
    }
}

void Thread::stop()
{
    stopped.store(true);
    condition.notify_one();
    worker.join();
}
