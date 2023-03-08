#include "Thread.h"

using namespace NDIReceiver;

Thread::Thread():
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
    auto lock = std::unique_lock{mutex};

    messages .push(std::move(func));
    condition.notify_one();
}

void Thread::threadFunc()
{
    while(!stopped.load())
    {
        auto lock = std::unique_lock<std::mutex>{mutex};
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
    stopped  .store(true);
    condition.notify_one();
    worker   .join();
}
