#pragma once

#include "Thread.h"
#include "frame.h"

#include "NdiConnection.h"

namespace NDIReceiver 
{

class ReceiverAsync 
{
public:
    ReceiverAsync(Thread& threadMain, NdiConnection& ndiConnection);
    virtual ~ReceiverAsync() = default;

    void recvAsync();
    void stop();

    std::function<void(std::shared_ptr<NdiFrame>)> eventImage;

private:
    NdiConnection&  connection;
    Thread&         threadMain;
    Thread          threadBackground;
};

} // namespace